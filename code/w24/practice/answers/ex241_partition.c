/* ex241_partition.c —— 参考答案 */

#include <stdio.h>

#define N 8

int partition(int a[], int lo, int hi)
{
    int pivot = a[lo];              /* a[lo] 成为第一个「坑」 */
    int i = lo, j = hi;

    printf("  基准 = %d\n", pivot);

    while (i < j) {
        /* j 从右往左找比基准小的 */
        while (i < j && a[j] >= pivot) j--;
        if (i < j) {
            printf("    a[%d]=%d 填到 i=%d（左边）\n", j, a[j], i);
            a[i] = a[j];            /* 填左边的坑，j 变成新坑 */
        }

        /* i 从左往右找比基准大的 */
        while (i < j && a[i] <= pivot) i++;
        if (i < j) {
            printf("    a[%d]=%d 填到 j=%d（右边）\n", i, a[i], j);
            a[j] = a[i];            /* 填右边的坑，i 变成新坑 */
        }
    }

    a[i] = pivot;                   /* 基准填进最后的坑 */
    printf("  基准 %d 归位到下标 %d\n", pivot, i);
    return i;
}

static void printArr(const char *label, const int a[], int n)
{
    printf("  %-14s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    int a[N] = {49, 38, 65, 97, 76, 13, 27, 49};

    printf("=== 分区 ===\n");
    printArr("原始", a, N);
    printf("\n");

    int p = partition(a, 0, N - 1);

    printf("\n");
    printArr("分区后", a, N);

    printf("\n=== 验证分区正确性 ===\n");
    int ok = 1;
    for (int i = 0; i < p; i++) if (a[i] > a[p]) ok = 0;
    for (int i = p + 1; i < N; i++) if (a[i] < a[p]) ok = 0;

    printf("  基准在下标 %d，值 %d\n", p, a[p]);
    printf("  左边都 <= 基准？%s\n", ok ? "是 ✓" : "否 ✗");
    printf("  右边都 >= 基准？%s\n", ok ? "是 ✓" : "否 ✗");

    printf("\n=== 挖坑法的三步 ===\n");
    printf("  ① pivot = a[lo]，a[lo] 变成「坑」\n");
    printf("  ② j 从右往左找 < pivot 的，填到左边的坑；\n");
    printf("     i 从左往右找 > pivot 的，填到右边的坑\n");
    printf("  ③ i、j 相遇时，把 pivot 填进去\n");
    printf("  ⭐ 全程只有「赋值」，没有「交换」，比交换法效率高一点。\n");

    printf("\n=== 为什么分区是快排的核心 ===\n");
    printf("  一趟分区后：基准到了【最终位置】，左边都比它小、右边都比它大。\n");
    printf("  ⭐ 这个「最终位置」的含义很重要：\n");
    printf("     后续递归不会再动它，所以快排每趟至少确定一个元素。\n");
    printf("  📌 软考问「快排一趟后能确定几个元素」→ 至少 1 个（基准）。\n");

    printf("\n=== 分区不唯一 ===\n");
    printf("  基准选法不同（首/尾/中间/随机/三数取中），分区结果不同。\n");
    printf("  但只要满足「左小右大」，都是合法的分区。\n");
    printf("  ⚠️ 所以软考给「一趟后的结果」，可能有多个正确答案，\n");
    printf("     要看题目指定的基准选法。\n");

    return 0;
}
