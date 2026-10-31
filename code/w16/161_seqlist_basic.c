/* 161_seqlist_basic.c —— 顺序表：用数组实现线性表
 *
 * 线性表是最基础的数据结构：一串「一个接一个」的元素。
 * 两种实现方式：
 *   顺序表（数组）—— 逻辑相邻 = 物理相邻，本文件
 *   链表（指针）—— 逻辑相邻 ≠ 物理相邻，W17 讲
 *
 * 顺序表的核心三件事：插入、删除、查找。
 * 插入删除都要「挪元素」，这是它最大的代价。
 */

#include <stdio.h>

#define MAXSIZE 20

/* ---------- 顺序表的结构 ---------- */
typedef struct {
    int data[MAXSIZE];      /* 存数据的数组 */
    int length;             /* 当前实际元素个数（不是容量！） */
} SqList;

/* 全局计数器：统计元素移动次数 */
static long long g_moves = 0;

/* ---------- 初始化 ---------- */
void initList(SqList *L)
{
    L->length = 0;
}

/* ---------- 遍历 ---------- */
void showList(const SqList *L)
{
    printf("  [");
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]  length=%d\n", L->length);
}

/* ---------- 按位置插入：在第 pos 个位置（0 起）插入 value ---------- */
/* 返回 1 成功，0 失败 */
int insertAt(SqList *L, int pos, int value)
{
    /* ① 位置合法性：可以插在 0..length（末尾也算合法） */
    if (pos < 0 || pos > L->length) {
        printf("  插入失败：pos=%d 越界（合法范围 0..%d）\n", pos, L->length);
        return 0;
    }
    /* ② 空间是否已满 */
    if (L->length >= MAXSIZE) {
        printf("  插入失败：表已满\n");
        return 0;
    }

    /* ③ 从最后一个元素开始，把 pos 及之后的元素整体后移一格
     *    ⚠️ 必须【从后往前】移，否则会覆盖还没搬的数据 */
    for (int i = L->length; i > pos; i--) {
        L->data[i] = L->data[i - 1];
        g_moves++;
    }

    L->data[pos] = value;
    L->length++;
    return 1;
}

/* ---------- 按位置删除：删除第 pos 个元素（0 起）---------- */
int deleteAt(SqList *L, int pos, int *out)
{
    if (pos < 0 || pos >= L->length) {
        printf("  删除失败：pos=%d 越界（合法范围 0..%d）\n", pos, L->length - 1);
        return 0;
    }

    if (out != NULL) *out = L->data[pos];

    /* 从 pos+1 开始，把后面的元素整体前移一格
     * 这里【从前往后】移是对的，因为目标位置已经腾空了 */
    for (int i = pos; i < L->length - 1; i++) {
        L->data[i] = L->data[i + 1];
        g_moves++;
    }

    L->length--;
    return 1;
}

/* ---------- 按值查找：返回下标，找不到返回 -1 ---------- */
int findByValue(const SqList *L, int value)
{
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == value) return i;
    }
    return -1;
}

/* ---------- 按位置取值 ---------- */
int getAt(const SqList *L, int pos, int *out)
{
    if (pos < 0 || pos >= L->length) return 0;
    *out = L->data[pos];
    return 1;
}

int main(void)
{
    SqList L;
    initList(&L);

    /* ---------- ① 建表 ---------- */
    printf("=== ① 初始化并插入 5 个元素 ===\n");
    g_moves = 0;
    for (int i = 0; i < 5; i++) {
        insertAt(&L, L.length, (i + 1) * 10);   /* 每次插在末尾 */
    }
    showList(&L);
    printf("  插在末尾共移动 %lld 次（末尾插入不用挪元素）\n", g_moves);

    /* ---------- ② 表头插入 ---------- */
    printf("\n=== ② 在表头插入 5 ===\n");
    g_moves = 0;
    insertAt(&L, 0, 5);
    showList(&L);
    printf("  移动了 %lld 次 = 原来的 5 个元素全部后移\n", g_moves);

    printf("\n  ⭐ 这就是顺序表的代价：\n");
    printf("     插表头要挪 n 次，插表尾挪 0 次。\n");
    printf("     平均挪 n/2 次 → 时间复杂度 O(n)。\n");

    /* ---------- ③ 中间插入 ---------- */
    printf("\n=== ③ 在下标 3 插入 77 ===\n");
    g_moves = 0;
    insertAt(&L, 3, 77);
    showList(&L);
    printf("  移动了 %lld 次\n", g_moves);

    /* ---------- ④ 删除 ---------- */
    printf("\n=== ④ 删除下标 3 的元素 ===\n");
    int out = 0;
    g_moves = 0;
    if (deleteAt(&L, 3, &out)) {
        printf("  被删除的是 %d\n", out);
        showList(&L);
        printf("  移动了 %lld 次 = 后面 3 个元素全部前移\n", g_moves);
    }

    printf("\n=== ⑤ 删除表头 vs 表尾 ===\n");
    g_moves = 0;
    deleteAt(&L, 0, &out);
    printf("  删表头：移动 %lld 次（后面全部前移）\n", g_moves);
    g_moves = 0;
    deleteAt(&L, L.length - 1, &out);
    printf("  删表尾：移动 %lld 次（没有元素需要前移）\n", g_moves);
    showList(&L);

    /* ---------- ⑥ 查找：两种方式，复杂度不同 ---------- */
    printf("\n=== ⑥ 两种查找，复杂度完全不同 ===\n");
    int v;
    if (getAt(&L, 2, &v)) {
        printf("  按位置取值 L[2] = %d   → O(1) 随机访问\n", v);
    }
    int idx = findByValue(&L, 40);
    printf("  按值查找 40 → 下标 %d   → O(n) 要逐个比\n", idx);
    idx = findByValue(&L, 999);
    printf("  按值查找 999 → %d（找不到）\n", idx);

    printf("\n  ⭐ 为什么按位置取值是 O(1)？\n");
    printf("     因为数组元素的地址可以直接算出来：\n");
    printf("     地址 = 首地址 + 下标 × sizeof(int)\n");
    printf("     所以 L.data[500] 和 L.data[0] 一样快。\n");
    printf("     这叫「随机访问」，链表做不到（W17 会讲原因）。\n");

    /* ---------- ⑦ 完整操作一览 ---------- */
    printf("\n=== ⑦ 顺序表操作复杂度总表 ===\n");
    printf("  %-22s %-12s %s\n", "操作", "复杂度", "原因");
    printf("  ----------------------------------------------------------\n");
    printf("  %-22s %-12s %s\n", "按位置取值 L[i]", "O(1)", "地址可算，随机访问");
    printf("  %-22s %-12s %s\n", "按值查找", "O(n)", "要逐个比较");
    printf("  %-22s %-12s %s\n", "表尾插入", "O(1)", "不用挪元素");
    printf("  %-22s %-12s %s\n", "表头/中间插入", "O(n)", "平均挪 n/2 个");
    printf("  %-22s %-12s %s\n", "表尾删除", "O(1)", "不用挪元素");
    printf("  %-22s %-12s %s\n", "表头/中间删除", "O(n)", "平均挪 (n-1)/2 个");

    return 0;
}
