/* ex236_basic_compare.c —— 三种基本排序的全面对比
 *
 * 要求：在 n=1000 的随机数据上跑三种排序，统计：
 *   1. 比较次数
 *   2. 耗时（毫秒，用 clock()）
 *   3. 验证结果都正确（升序且和参考答案一致）
 *
 * 期望（大致量级）：
 *   插入：约 25 万次比较
 *   冒泡：约 50 万次比较
 *   选择：约 50 万次比较（恒为 n(n-1)/2）
 *   耗时都在几十毫秒内
 *
 * 提示：
 *   clock() 精度 1ms，n=1000 可能量不出来，可以放大到 n=5000
 *   用 volatile 或把结果打印出来，防止编译器优化掉
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 5000

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

int main(void)
{
    int n = 1000;
    int *src = (int *)malloc(sizeof(int) * (size_t)n);
    int *work = (int *)malloc(sizeof(int) * (size_t)n);

    srand(123);
    for (int i = 0; i < n; i++) src[i] = rand() % 100000;

    printf("=== n = %d 随机数据 ===\n\n", n);
    printf("  %-10s %-16s %-14s %s\n", "排序", "比较次数", "耗时(ms)", "结果正确");
    printf("  ------------------------------------------------------------\n");

    /* TODO 1：三种排序各跑一次，输出比较次数、耗时、是否正确 */

    printf("\n=== 结论 ===\n");
    printf("  三者时间复杂度都是 O(n^2)，差别在常数和适用场景：\n");
    printf("    - 插入：数据基本有序时最快（可退化成 O(n)）\n");
    printf("    - 冒泡：交换次数多，实际最慢\n");
    printf("    - 选择：比较次数固定，但交换次数最少\n");
    printf("\n  ⭐ n=1000 时差不多，n=10000 时差别就很明显了。\n");

    free(src);
    free(work);
    return 0;
}
