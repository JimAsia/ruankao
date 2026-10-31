/* ex166_seqlist_uniq.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 30

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

static void build(SqList *L, const int a[], int n)
{
    for (int i = 0; i < n; i++) L->data[i] = a[i];
    L->length = n;
}

void show(const char *label, const SqList *L)
{
    printf("  %-10s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]  (length=%d)\n", L->length);
}

/* 有序表去重：O(n) */
int dedupSorted(SqList *L)
{
    if (L->length <= 1) return 0;

    int k = 1, removed = 0;         /* 第一个元素一定保留 */
    for (int i = 1; i < L->length; i++) {
        if (L->data[i] != L->data[k - 1]) {     /* 和「已保留的最后一个」比 */
            L->data[k++] = L->data[i];
        } else {
            removed++;
        }
    }
    L->length = k;
    return removed;
}

/* 无序表去重：O(n^2)，保留首次出现 */
int dedupUnsorted(SqList *L)
{
    if (L->length <= 1) return 0;

    int k = 1, removed = 0;         /* 第一个元素保留 */

    for (int i = 1; i < L->length; i++) {
        int dup = 0;
        /* 在「已保留」的部分里找有没有相同的 */
        for (int t = 0; t < k; t++) {
            if (L->data[t] == L->data[i]) { dup = 1; break; }
        }
        if (!dup) {
            L->data[k++] = L->data[i];
        } else {
            removed++;
        }
    }
    L->length = k;
    return removed;
}

int main(void)
{
    /* ---------- 有序去重 ---------- */
    printf("=== 有序表去重 ===\n");
    int a[] = {1, 1, 2, 2, 2, 3, 5, 5, 8};
    SqList L1; build(&L1, a, 9);
    show("原表", &L1);
    int r = dedupSorted(&L1);
    show("去重后", &L1);
    printf("  删掉 %d 个\n", r);

    printf("\n  ⭐ 比较对象是 data[k-1]（已保留的最后一个），不是 data[i-1]。\n");
    printf("     因为被删元素的位置会被后面的覆盖，data[i-1] 可能是被丢弃的值。\n");

    /* ---------- 无序去重 ---------- */
    printf("\n=== 无序表去重 ===\n");
    int b[] = {5, 3, 5, 1, 3, 5, 8, 1};
    SqList L2; build(&L2, b, 8);
    show("原表", &L2);
    r = dedupUnsorted(&L2);
    show("去重后", &L2);
    printf("  删掉 %d 个（保留首次出现的 5、3、1、8）\n", r);

    printf("\n  ⭐ 无序去重必须「和前面所有已保留的元素比」，不能只比前一个。\n");
    printf("     本例 5 3 5 1 3 5 8 1：\n");
    printf("       第 3 个 5 与前面的 5 重复 → 丢\n");
    printf("       第 5 个 3 与前面的 3 重复 → 丢\n");

    /* ---------- 复杂度对比 ---------- */
    printf("\n=== 复杂度对比 ===\n");
    printf("  %-16s %-14s %-10s %s\n", "方法", "时间", "空间", "前提");
    printf("  ------------------------------------------------------------\n");
    printf("  %-16s %-14s %-10s %s\n", "有序去重", "O(n)", "O(1)", "表必须有序");
    printf("  %-16s %-14s %-10s %s\n", "无序去重", "O(n^2)", "O(1)", "无");
    printf("  %-16s %-14s %-10s %s\n", "先排序再去重", "O(n log n)", "O(1)", "无");

    printf("\n  ⭐ 结论：无序表去重的最优解不是「直接双重循环」，\n");
    printf("     而是「先排序 O(n log n)，再用 O(n) 的有序去重」。\n");
    printf("     总复杂度 O(n log n)，比 O(n^2) 好一个量级。\n");

    printf("\n=== 软考怎么考 ===\n");
    printf("  1. 给有序表去重的代码，挖空填 data[k-1] 或 k++\n");
    printf("  2. 问「无序表去重至少需要多少时间」→ 答 O(n log n)（基于比较）\n");
    printf("  3. 问「去重后长度怎么变」→ 用 k 而不是每次 length--\n");
    printf("  📌 用 k 记录写入位置是原地删除/去重的通用套路，\n");
    printf("     和 162 的覆盖法、164 的分割是同一个思想。\n");

    return 0;
}
