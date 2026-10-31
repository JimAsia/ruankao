/* ex234_shell.c —— 希尔排序
 *
 * 要求：
 *   1. shellSort(a, n)：用 gap = n/2, n/4, ..., 1
 *   2. 每趟打印数组，观察「越来越大致的顺序」
 *   3. 和直接插入排序对比比较次数
 *
 * 测试：[49 38 65 97 76 13 27 49 55 4]
 * 期望：
 *   gap=5 后：13 27 49 55 4 49 38 65 97 76
 *   gap=2 后：4 27 13 49 38 55 49 65 97 76
 *   gap=1 后：4 13 27 38 49 49 55 65 76 97（完全有序）
 *
 * 提示：
 *   和插入排序一样，只是步长从 1 变成 gap
 */

#include <stdio.h>

#define N 10

static long long g_cmp = 0;

/* TODO 1：希尔排序 */
void shellSort(int a[], int n)
{
    (void)a; (void)n;
}

/* 直接插入（对照，已给出） */
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

int main(void)
{
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};

    /* TODO 2：希尔排序，输出过程和比较次数 */

    /* TODO 3：直接插入对照，比较次数 */

    printf("\n=== 结论 ===\n");
    printf("  1. 复杂度约 O(n^1.3)，不是 O(n log n)\n");
    printf("  2. 空间 O(1)\n");
    printf("  3. 不稳定\n");
    printf("  ⚠️ 增量最后必须是 1，否则不保证有序\n");

    return 0;
}
