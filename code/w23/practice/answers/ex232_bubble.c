/* ex232_bubble.c —— 参考答案 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            g_cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                swapped = 1;
            }
        }
        printf("  第 %d 趟后：", i + 1);
        for (int k = 0; k < n; k++) printf("%d ", a[k]);
        printf("%s\n", swapped ? "" : "（本趟无交换，提前结束）");
        if (!swapped) break;
    }
}

void bubbleSortNaive(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            g_cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

int main(void)
{
    int sorted[N] = {13, 27, 38, 49, 49, 65, 76, 97};
    int work[N];

    printf("=== 已有序数据上对比 ===\n");
    printf("  数据：");
    for (int i = 0; i < N; i++) printf("%d ", sorted[i]);
    printf("\n\n");

    /* 有优化 */
    for (int i = 0; i < N; i++) work[i] = sorted[i];
    g_cmp = 0;
    printf("【带提前退出】\n");
    bubbleSort(work, N);
    long long c1 = g_cmp;

    /* 无优化 */
    for (int i = 0; i < N; i++) work[i] = sorted[i];
    g_cmp = 0;
    bubbleSortNaive(work, N);
    long long c2 = g_cmp;

    printf("\n  %-18s %s\n", "写法", "比较次数");
    printf("  ------------------------------\n");
    printf("  %-18s %lld\n", "带提前退出", c1);
    printf("  %-18s %lld\n", "不带优化", c2);
    printf("\n  ⭐ 差 %lld 倍：%lld vs %lld\n", c2 / c1, c1, c2);

    printf("\n=== 为什么差这么多 ===\n");
    printf("  无优化版本不管数据怎样都跑满 n-1 趟，共 n(n-1)/2 = 28 次比较。\n");
    printf("  有优化版本发现第 1 趟没交换，立刻知道已有序 → 只比较 7 次。\n");

    printf("\n=== 结论 ===\n");
    printf("  冒泡加提前退出后，最好情况 O(n)。\n");
    printf("  ⚠️ 但每趟仍要扫一遍，所以「几乎有序」时反而不如插入排序\n");
    printf("     —— 插入排序一趟就能把元素放到位，冒泡要一趟趟浮。\n");
    printf("  ⭐ 冒泡的实用价值主要是教学，实际很少用。\n");

    return 0;
}
