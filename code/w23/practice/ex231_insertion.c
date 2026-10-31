/* ex231_insertion.c —— 直接插入排序
 *
 * 要求：
 *   1. insertionSort(a, n)：升序，返回比较次数
 *   2. 每趟结束后打印数组，观察「前 i+1 个元素局部有序」
 *
 * 测试：[49 38 65 97 76 13 27 49]
 * 期望过程（前几个）：
 *   第 1 趟后：38 49 65 97 76 13 27 49
 *   第 2 趟后：38 49 65 97 76 13 27 49（65 不用动）
 *
 * 提示：
 *   key = a[i]，从 i-1 往前找位置，比 key 大的都后移
 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;

/* TODO 1：插入排序（每趟打印） */
void insertionSort(int a[], int n)
{
    (void)a; (void)n;
}

int main(void)
{
    int a[N] = {49, 38, 65, 97, 76, 13, 27, 49};

    /* TODO 2：调用排序，输出过程和比较次数 */

    printf("\n=== 关键点 ===\n");
    printf("  1. 数据已有序时只比较 n-1 次 → O(n)\n");
    printf("  2. 稳定：只和相邻元素比较，相等时不交换\n");
    printf("  3. 空间 O(1)\n");

    return 0;
}
