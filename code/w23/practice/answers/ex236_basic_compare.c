/* ex236_basic_compare.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long long g_cmp = 0;

static void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            g_cmp++;
            if (a[j] > key) { a[j + 1] = a[j]; j--; }
            else break;
        }
        a[j + 1] = key;
    }
}

static void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int sw = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            g_cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; sw = 1;
            }
        }
        if (!sw) break;
    }
}

static void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int mi = i;
        for (int j = i + 1; j < n; j++) {
            g_cmp++;
            if (a[j] < a[mi]) mi = j;
        }
        if (mi != i) { int t = a[i]; a[i] = a[mi]; a[mi] = t; }
    }
}

static int isSorted(const int a[], int n)
{
    for (int i = 1; i < n; i++) if (a[i - 1] > a[i]) return 0;
    return 1;
}

static void runOne(const char *name, void (*fn)(int[], int),
                   const int src[], int n)
{
    int *work = (int *)malloc(sizeof(int) * (size_t)n);
    for (int i = 0; i < n; i++) work[i] = src[i];

    g_cmp = 0;
    clock_t t0 = clock();
    fn(work, n);
    clock_t t1 = clock();

    double ms = (double)(t1 - t0) * 1000.0 / (double)CLOCKS_PER_SEC;
    printf("  %-10s %-16lld %-14.3f %s\n",
           name, g_cmp, ms, isSorted(work, n) ? "是 ✓" : "否 ✗");

    free(work);
}

int main(void)
{
    int n = 2000;                   /* 放大到 2000，让耗时能量出来 */
    int *src = (int *)malloc(sizeof(int) * (size_t)n);

    srand(123);
    for (int i = 0; i < n; i++) src[i] = rand() % 100000;

    printf("=== n = %d 随机数据 ===\n\n", n);
    printf("  %-10s %-16s %-14s %s\n", "排序", "比较次数", "耗时(ms)", "结果正确");
    printf("  ------------------------------------------------------------\n");

    runOne("插入", insertionSort, src, n);
    runOne("冒泡", bubbleSort, src, n);
    runOne("选择", selectionSort, src, n);

    printf("\n  ⭐ n(n-1)/2 = %d（选择排序恒为此值）\n", n * (n - 1) / 2);
    printf("     插入排序通常只有一半左右 —— 因为很多元素找到位置就停了。\n");

    printf("\n=== 结论 ===\n");
    printf("  三者时间复杂度都是 O(n^2)，差别在常数和适用场景：\n");
    printf("    - 插入：数据基本有序时最快（可退化成 O(n)）\n");
    printf("    - 冒泡：交换次数多，实际最慢\n");
    printf("    - 选择：比较次数固定，但交换次数最少\n");

    printf("\n=== 为什么 n 小时看不出差别 ===\n");
    printf("  n=100 时三者都只要几微秒，clock() 精度 1ms 量不出来。\n");
    printf("  n=10000 时：插入约 2500 万次比较，冒泡/选择约 5000 万次，\n");
    printf("  差距会拉到几倍。\n");
    printf("  📌 这就是复杂度的意义：它预测「规模变大时谁更吃亏」。\n");

    free(src);
    return 0;
}
