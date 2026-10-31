/* ex232_bubble.c —— 冒泡排序（含提前退出优化）
 *
 * 要求：
 *   1. bubbleSort(a, n)：升序，带「本趟无交换就提前结束」优化
 *   2. 每趟结束后打印，观察「最大的元素逐步到末尾」
 *   3. 对比「有优化」和「无优化」在已有序数据上的比较次数
 *
 * 测试：
 *   乱序：[49 38 65 97 76 13 27 49]
 *   有序：[13 27 38 49 49 65 76 97]
 *
 * 期望：
 *   乱序时有优化 vs 无优化差别不大
 *   有序时：有优化只比较 7 次，无优化要比较 28 次
 *
 * 提示：
 *   swapped 标志：本趟没交换过说明已有序，直接 break
 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;

/* TODO 1：带提前退出的冒泡 */
void bubbleSort(int a[], int n)
{
    (void)a; (void)n;
}

/* TODO 2：不带优化的冒泡（对照） */
void bubbleSortNaive(int a[], int n)
{
    (void)a; (void)n;
}

static void printArr(const char *label, const int a[], int n)
{
    printf("  %-16s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    int sorted[N] = {13, 27, 38, 49, 49, 65, 76, 97};

    /* TODO 3：已有序数据上对比两种写法的比较次数 */

    printf("\n=== 结论 ===\n");
    printf("  冒泡加提前退出后，最好情况 O(n)。\n");
    printf("  ⚠️ 但每趟仍要扫一遍，所以「几乎有序」时反而不如插入排序。\n");
    printf("  ⭐ 冒泡的实用价值主要是教学，实际很少用。\n");

    return 0;
}
