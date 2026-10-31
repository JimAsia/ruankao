/* ex242_quick.c —— 参考答案 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;

static int partition(int a[], int lo, int hi)
{
    int pivot = a[lo];
    int i = lo, j = hi;
    while (i < j) {
        while (i < j && (g_cmp++, a[j] >= pivot)) j--;
        if (i < j) a[i] = a[j];
        while (i < j && (g_cmp++, a[i] <= pivot)) i++;
        if (i < j) a[j] = a[i];
    }
    a[i] = pivot;
    return i;
}

void quickSort(int a[], int lo, int hi)
{
    if (lo >= hi) return;
    int p = partition(a, lo, hi);
    quickSort(a, lo, p - 1);
    quickSort(a, p + 1, hi);
}

int kthSmallest(int a[], int n, int k)
{
    int lo = 0, hi = n - 1;
    int target = k - 1;                 /* k 从 1 开始，下标从 0 开始 */

    while (lo <= hi) {
        int p = partition(a, lo, hi);
        if (p == target)      return a[p];
        else if (p > target)  hi = p - 1;   /* 在左半找 */
        else                  lo = p + 1;   /* 在右半找 */
    }
    return -1;
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
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49};
    int work[N];

    /* ---------- 完整快排 ---------- */
    printf("=== ① 完整快排 ===\n");
    for (int i = 0; i < N; i++) work[i] = src[i];
    printArr("原始", work, N);

    g_cmp = 0;
    quickSort(work, 0, N - 1);
    printArr("排序后", work, N);
    printf("  比较 %lld 次\n", g_cmp);

    /* ---------- 第 k 小 ---------- */
    printf("\n=== ② 第 k 小 ===\n");
    int pos[][2] = {{3, 0}, {5, 0}};        /* {k, 占位} */
    for (int t = 0; t < 2; t++) {
        int k = pos[t][0];
        for (int i = 0; i < N; i++) work[i] = src[i];
        g_cmp = 0;
        int v = kthSmallest(work, N, k);
        printf("  第 %d 小 = %d（比较 %lld 次）\n", k, v, g_cmp);
    }

    printf("\n  验证：排序后是 13 27 38 49 49 65 76 97\n");
    printf("        第 3 小 = 38，第 5 小 = 49 ✓\n");

    /* ---------- 随机 vs 已有序 ---------- */
    printf("\n=== ③ 随机 vs 已有序的比较次数 ===\n");
    int sorted[N] = {13, 27, 38, 49, 49, 65, 76, 97};

    for (int i = 0; i < N; i++) work[i] = src[i];
    g_cmp = 0; quickSort(work, 0, N - 1);
    long long c1 = g_cmp;

    for (int i = 0; i < N; i++) work[i] = sorted[i];
    g_cmp = 0; quickSort(work, 0, N - 1);
    long long c2 = g_cmp;

    printf("  %-12s %s\n", "数据", "比较次数");
    printf("  ------------------------\n");
    printf("  %-12s %lld\n", "随机", c1);
    printf("  %-12s %lld\n", "已有序", c2);
    printf("  ⭐ 已有序时 %lld = n(n-1)/2 = %d → 退化成 O(n^2)！\n",
           c2, N * (N - 1) / 2);

    printf("\n=== 为什么第 k 小是 O(n) ===\n");
    printf("  完整快排：递归两边，每层总共扫 n → O(n log n)\n");
    printf("  第 k 小  ：只递归一边，工作量 n + n/2 + n/4 + ... = 2n → O(n)\n");
    printf("  ⭐ 这个技巧叫「快速选择」（quickselect）。\n");
    printf("  📌 前提是每次分区大致平分；最坏也是 O(n^2)。\n");

    return 0;
}
