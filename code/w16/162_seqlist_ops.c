/* 162_seqlist_ops.c —— 顺序表的四个典型操作
 *
 * ① 逆置：首尾交换，O(n)
 * ② 删除所有指定值：覆盖法，O(n)，不能边删边挪
 * ③ 归并两个有序表：双指针，O(n+m)
 * ④ 有序表去重：相邻比较，O(n)
 *
 * 这四个是软考「线性表」大题的原型。
 */

#include <stdio.h>

#define MAXSIZE 30

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

static void show(const char *label, const SqList *L)
{
    printf("  %-14s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]\n");
}

/* ---------- ① 逆置：首尾交换 ---------- */
void reverseList(SqList *L)
{
    /* i 从前往后，j 从后往前，i < j 时交换
     * ⚠️ 写成 i < L->length 的话每个元素会被换两次，等于没换 */
    int i = 0, j = L->length - 1;
    while (i < j) {
        int t = L->data[i];
        L->data[i] = L->data[j];
        L->data[j] = t;
        i++;
        j--;
    }
}

/* ---------- ② 删除所有值为 value 的元素 ---------- */
/* 覆盖法：用 k 记录「下一个该写入的位置」，扫一遍就完成
 * 复杂度 O(n)，比「找到一个就整体前移」（O(n^2)）好得多 */
int removeAll(SqList *L, int value)
{
    int k = 0;                      /* k 是新的写入位置 */
    int removed = 0;

    for (int i = 0; i < L->length; i++) {
        if (L->data[i] != value) {
            L->data[k] = L->data[i];    /* 保留：写到 k 位置 */
            k++;
        } else {
            removed++;
        }
    }
    L->length = k;
    return removed;
}

/* ---------- ③ 归并两个有序表（升序）---------- */
/* 前提：A、B 都已升序。结果放进 C，仍升序 */
void mergeSorted(const SqList *A, const SqList *B, SqList *C)
{
    int i = 0, j = 0, k = 0;

    /* 两个都没走完时，取较小的那个 */
    while (i < A->length && j < B->length) {
        if (A->data[i] <= B->data[j]) {
            C->data[k++] = A->data[i++];
        } else {
            C->data[k++] = B->data[j++];
        }
    }
    /* 剩下谁就全搬过来 */
    while (i < A->length) C->data[k++] = A->data[i++];
    while (j < B->length) C->data[k++] = B->data[j++];

    C->length = k;
}

/* ---------- ④ 有序表去重（保留一个）---------- */
int dedupSorted(SqList *L)
{
    if (L->length <= 1) return 0;

    int k = 1;                      /* 第一个元素一定保留 */
    int removed = 0;

    for (int i = 1; i < L->length; i++) {
        if (L->data[i] != L->data[k - 1]) {     /* 和「已保留的最后一个」比 */
            L->data[k] = L->data[i];
            k++;
        } else {
            removed++;
        }
    }
    L->length = k;
    return removed;
}

/* 辅助：从数组建表 */
static void build(SqList *L, const int a[], int n)
{
    for (int i = 0; i < n; i++) L->data[i] = a[i];
    L->length = n;
}

int main(void)
{
    /* ---------- ① 逆置 ---------- */
    printf("=== ① 逆置 ===\n");
    int a1[] = {1, 2, 3, 4, 5, 6, 7};
    SqList L1;
    build(&L1, a1, 7);
    show("原表", &L1);
    reverseList(&L1);
    show("逆置后", &L1);
    printf("  时间 O(n)：每个元素最多被访问一次\n");

    printf("\n  ⚠️ 循环条件必须是 i < j，不能是 i < length\n");
    printf("     写 i < length 时：i=0 换 6、i=1 换 5 ... i=6 又换回 0，\n");
    printf("     每个元素被交换两次，结果和原来一样。\n");

    /* ---------- ② 删除所有指定值 ---------- */
    printf("\n=== ② 删除所有 3 ===\n");
    int a2[] = {3, 5, 3, 7, 3, 9, 1, 3};
    SqList L2;
    build(&L2, a2, 8);
    show("原表", &L2);
    int r = removeAll(&L2, 3);
    show("删除后", &L2);
    printf("  删掉了 %d 个\n", r);

    printf("\n  ⭐ 两种写法的复杂度差一个量级：\n");
    printf("     ❌ 边扫边挪：找到一个就整体前移，共有 m 个就挪 m 次 n，O(n^2)\n");
    printf("     ✅ 覆盖法  ：k 记录写入位置，一趟扫完，O(n)\n");
    printf("     关键：k 永远 <= i，所以 data[k] = data[i] 不会覆盖还没读的数据。\n");

    /* ---------- ③ 归并两个有序表 ---------- */
    printf("\n=== ③ 归并两个升序表 ===\n");
    int a3[] = {1, 4, 7, 10};
    int a4[] = {2, 3, 8, 11, 15};
    SqList A, B, C;
    build(&A, a3, 4);
    build(&B, a4, 5);
    show("表 A", &A);
    show("表 B", &B);
    mergeSorted(&A, &B, &C);
    show("归并结果", &C);

    printf("\n  ⭐ 双指针归并，时间 O(n+m)，空间 O(n+m)\n");
    printf("     这是归并排序（S2 后面讲）的核心步骤。\n");
    printf("     ⚠️ 前提是两个表必须**已经有序**，否则结果不对。\n");

    /* ---------- ④ 有序表去重 ---------- */
    printf("\n=== ④ 有序表去重 ===\n");
    int a5[] = {1, 1, 2, 2, 2, 3, 5, 5, 8};
    SqList L3;
    build(&L3, a5, 9);
    show("原表", &L3);
    int rd = dedupSorted(&L3);
    show("去重后", &L3);
    printf("  删掉了 %d 个重复元素\n", rd);

    printf("\n  ⭐ 比较的对象是 data[k-1]（已保留的最后一个），不是 data[i-1]。\n");
    printf("     因为删除后下标会变，data[i-1] 可能是已经被丢弃的元素。\n");
    printf("  ⚠️ 这个方法只对**有序表**有效。无序表去重要用双重循环 O(n^2)，\n");
    printf("     或者先排序再这招 O(n log n)。\n");

    /* ---------- ⑤ 复杂度小结 ---------- */
    printf("\n=== ⑤ 四个操作的复杂度 ===\n");
    printf("  %-18s %-10s %s\n", "操作", "时间", "空间");
    printf("  ------------------------------------------\n");
    printf("  %-18s %-10s %s\n", "逆置", "O(n)", "O(1) 原地交换");
    printf("  %-18s %-10s %s\n", "删除所有指定值", "O(n)", "O(1) 覆盖法");
    printf("  %-18s %-10s %s\n", "归并两个有序表", "O(n+m)", "O(n+m) 需要新表");
    printf("  %-18s %-10s %s\n", "有序表去重", "O(n)", "O(1) 原地");

    return 0;
}
