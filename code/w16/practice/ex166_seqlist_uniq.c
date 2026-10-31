/* ex166_seqlist_uniq.c —— 两种去重：有序表 vs 无序表
 *
 * 要求：
 *   1. dedupSorted(L)：对【有序】表去重，O(n) 时间 O(1) 空间
 *   2. dedupUnsorted(L)：对【无序】表去重，允许 O(n^2) 时间，O(1) 空间
 *   3. 分别输出去重前后的内容和删掉的个数
 *
 * 测试数据：
 *   有序：  1 1 2 2 2 3 5 5 8  →  1 2 3 5 8，删掉 4 个
 *   无序：  5 3 5 1 3 5 8 1    →  5 3 1 8，删掉 4 个（保留首次出现）
 *
 * 提示：
 *   有序去重：k 记录写入位置，和 data[k-1] 比较
 *   无序去重：对每个 data[i]，检查它前面是否出现过；
 *             用 k 记录已保留的个数，data[i] 和 data[0..k-1] 逐个比
 */

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
    printf("]\n");
}

/* TODO 1：有序表去重，返回删除个数 */
int dedupSorted(SqList *L)
{
    (void)L;
    return 0;
}

/* TODO 2：无序表去重，返回删除个数 */
int dedupUnsorted(SqList *L)
{
    (void)L;
    return 0;
}

int main(void)
{
    /* TODO 3：测试有序去重 */

    /* TODO 4：测试无序去重 */

    printf("\n=== 复杂度对比 ===\n");
    printf("  %-14s %-12s %-12s %s\n", "方法", "时间", "空间", "前提");
    printf("  ----------------------------------------------------------\n");
    printf("  %-14s %-12s %-12s %s\n", "有序去重", "O(n)", "O(1)", "表必须有序");
    printf("  %-14s %-12s %-12s %s\n", "无序去重", "O(n^2)", "O(1)", "无");
    printf("  %-14s %-12s %-12s %s\n", "先排序再去重", "O(n log n)", "O(1)", "无");
    printf("\n  ⭐ 所以「无序表去重」的最佳方案是：先排序，再用有序去重。\n");
    printf("     O(n log n) 比 O(n^2) 好一个量级。\n");

    return 0;
}
