/* ex241_partition.c —— 快速排序的分区（partition）
 *
 * 要求：
 *   1. partition(a, lo, hi)：以 a[lo] 为基准，把 <= 基准的放左边、>= 的放右边
 *   2. 返回基准的最终位置
 *   3. 每次赋值都打印，观察「挖坑填数」的过程
 *
 * 测试：[49 38 65 97 76 13 27 49]，lo=0, hi=7
 * 期望：基准 49 最终落到下标 3
 *   分区后：[27 38 13 49 76 97 65 49]
 *
 * 提示（挖坑法）：
 *   pivot = a[lo]（a[lo] 成了「坑」）
 *   j 从右往左找 < pivot 的，填到左边的坑，j 变成新坑
 *   i 从左往右找 > pivot 的，填到右边的坑，i 变成新坑
 *   最后 a[i] = pivot
 */

#include <stdio.h>

#define N 8

/* TODO 1：分区，返回基准最终位置 */
int partition(int a[], int lo, int hi)
{
    (void)a; (void)lo; (void)hi;
    return lo;
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

    /* TODO 2：调用 partition，输出结果和基准位置 */

    /* TODO 3：验证分区正确性（左边都 <= 基准，右边都 >= 基准） */

    printf("\n=== 分区是快排的核心 ===\n");
    printf("  一趟分区后：基准到了【最终位置】，左边都比它小、右边都比它大。\n");
    printf("  然后对左右两半递归，就完成了整个排序。\n");

    return 0;
}
