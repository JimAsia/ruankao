/* ex154_sort_compare.c —— 参考答案 */

#include <stdio.h>

#define N 8

static long long g_cmp  = 0;
static long long g_swap = 0;

/* 冒泡（带提前退出） */
static void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            g_cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                g_swap++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

/* 选择排序 */
static void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            g_cmp++;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int t = a[i]; a[i] = a[minIdx]; a[minIdx] = t;
            g_swap++;
        }
    }
}

/* 插入排序 */
static void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            g_cmp++;
            if (a[j] > key) { a[j + 1] = a[j]; g_swap++; j--; }
            else break;
        }
        a[j + 1] = key;
    }
}

static void show(const char *label, const int a[], int n)
{
    printf("  %-12s", label);
    for (int i = 0; i < n; i++) printf("%3d", a[i]);
    printf("\n");
}

/* 跑一种排序并打印统计 */
static void runOne(const char *name, void (*fn)(int[], int),
                   const int src[], int n)
{
    int work[N];
    for (int i = 0; i < n; i++) work[i] = src[i];

    g_cmp = 0; g_swap = 0;
    fn(work, n);

    printf("  %-10s 比较 %-4lld 交换/移动 %-4lld 结果：",
           name, g_cmp, g_swap);
    for (int i = 0; i < n; i++) printf("%3d", work[i]);
    printf("\n");
}

int main(void)
{
    int base[N] = {64, 25, 12, 22, 11, 90, 45, 33};
    int sorted[N] = {11, 12, 22, 25, 33, 45, 64, 90};

    printf("=== 乱序数据 ===\n");
    show("原始", base, N);
    runOne("冒泡", bubbleSort, base, N);
    runOne("选择", selectionSort, base, N);
    runOne("插入", insertionSort, base, N);

    printf("\n=== 已排好序的数据 ===\n");
    show("原始", sorted, N);
    runOne("冒泡", bubbleSort, sorted, N);
    runOne("选择", selectionSort, sorted, N);
    runOne("插入", insertionSort, sorted, N);

    printf("\n=== 结论（这三点软考常考）===\n");
    printf("  1. 冒泡的比较次数：乱序 25 次，有序只有 7 次（提前退出生效）\n");
    printf("     不加优化的话，永远是 n(n-1)/2 = 28 次\n");
    printf("  2. 选择的比较次数：两种数据都是 28 次 —— 与数据无关！\n");
    printf("     因为无论数据怎样，内层都要扫完才能确定最小值\n");
    printf("  3. 插入：有序数据时比较 7 次、移动 0 次 —— 退化成 O(n)\n");
    printf("     这是插入排序最大的价值：对近乎有序的数据极快\n");

    printf("\n=== 三者对比表 ===\n");
    printf("  %-10s %-14s %-14s %-10s\n", "算法", "比较次数", "交换次数", "稳定性");
    printf("  ------------------------------------------------------\n");
    printf("  %-10s %-14s %-14s %-10s\n", "冒泡", "n(n-1)/2", "逆序对个数", "稳定");
    printf("  %-10s %-14s %-14s %-10s\n", "选择", "n(n-1)/2", "≤ n-1", "不稳定");
    printf("  %-10s %-14s %-14s %-10s\n", "插入", "≤ n(n-1)/2", "逆序对个数", "稳定");

    printf("\n  ⭐ 三者时间复杂度都是 O(n^2)，差别在常数和适用场景：\n");
    printf("     数据基本有序 → 插入最快\n");
    printf("     要求交换次数最少 → 选择（最多 n-1 次）\n");
    printf("     教学演示 → 冒泡最直观\n");

    return 0;
}
