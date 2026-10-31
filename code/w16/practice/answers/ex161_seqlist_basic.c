/* ex161_seqlist_basic.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 20

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

static long long g_moves = 0;

void initList(SqList *L)
{
    L->length = 0;
}

void show(const char *label, const SqList *L)
{
    printf("  %-12s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]  (length=%d)\n", L->length);
}

int insertAt(SqList *L, int pos, int value)
{
    if (pos < 0 || pos > L->length) {
        printf("  插入失败：pos=%d 越界\n", pos);
        return 0;
    }
    if (L->length >= MAXSIZE) {
        printf("  插入失败：表满\n");
        return 0;
    }

    /* 从后往前挪，给 pos 腾位置 */
    for (int i = L->length; i > pos; i--) {
        L->data[i] = L->data[i - 1];
        g_moves++;
    }
    L->data[pos] = value;
    L->length++;
    return 1;
}

int deleteAt(SqList *L, int pos, int *out)
{
    if (pos < 0 || pos >= L->length) {
        printf("  删除失败：pos=%d 越界\n", pos);
        return 0;
    }
    if (out) *out = L->data[pos];

    /* 从前往后挪，覆盖被删元素 */
    for (int i = pos; i < L->length - 1; i++) {
        L->data[i] = L->data[i + 1];
        g_moves++;
    }
    L->length--;
    return 1;
}

int locate(const SqList *L, int value)
{
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == value) return i;
    }
    return -1;
}

int main(void)
{
    SqList L;
    initList(&L);

    printf("=== 末尾插入 10 20 30 40 50 ===\n");
    g_moves = 0;
    for (int i = 1; i <= 5; i++) insertAt(&L, L.length, i * 10);
    show("结果", &L);
    printf("  移动 %lld 次（末尾插入不用挪）\n", g_moves);

    printf("\n=== 在下标 2 插入 99 ===\n");
    g_moves = 0;
    insertAt(&L, 2, 99);
    show("结果", &L);
    printf("  移动 %lld 次（下标 2 之后的 3 个元素后移）\n", g_moves);

    printf("\n=== 删除下标 0 ===\n");
    int out = 0;
    g_moves = 0;
    deleteAt(&L, 0, &out);
    printf("  被删的是 %d\n", out);
    show("结果", &L);
    printf("  移动 %lld 次（后面 5 个元素全部前移）\n", g_moves);

    printf("\n=== 查找 ===\n");
    printf("  找 30  → 下标 %d\n", locate(&L, 30));
    printf("  找 999 → %d（找不到）\n", locate(&L, 999));

    printf("\n=== 边界测试 ===\n");
    printf("  在下标 99 插入："); insertAt(&L, 99, 1);
    printf("  删除下标 99    ："); deleteAt(&L, 99, &out);
    printf("  在下标 0 插入（合法）："); insertAt(&L, 0, 7); printf("OK\n");
    show("结果", &L);

    printf("\n=== 关键点 ===\n");
    printf("  1. 插入的合法范围是 0..length（末尾也算）\n");
    printf("  2. 删除的合法范围是 0..length-1\n");
    printf("  3. 插入【从后往前】挪，删除【从前往后】挪\n");
    printf("     —— 方向反了会覆盖还没搬的数据\n");

    return 0;
}
