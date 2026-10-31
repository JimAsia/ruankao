/* ex154_sort_compare.c —— 三种排序的比较次数与交换次数实测
 *
 * 要求：
 *   1. 实现冒泡、选择、插入三种排序，各自统计「比较次数」和「交换（移动）次数」
 *   2. 在同一组数据上运行，对比谁比较多、谁交换多
 *   3. 用两种数据测试：随机乱序 和 已排好序
 *
 * 预期规律：
 *   冒泡：比较次数固定 n(n-1)/2；已排序时若加优化则只跑 1 趟
 *   选择：比较次数固定 n(n-1)/2；交换次数最少（最多 n-1 次）
 *   插入：有序数据时几乎不交换，退化为 O(n)；乱序时比较次数与逆序对相关
 *
 * 提示：
 *   三个函数都要接收 g_cmp / g_swap 两个全局计数器（直接 ++ 即可）
 *   交换用临时变量，每交换一次 g_swap++
 *   插入排序里是「移动」不是「交换」，也用 g_swap 计数
 */

#include <stdio.h>
#include <stdlib.h>

#define N 8

static long long g_cmp  = 0;
static long long g_swap = 0;

/* TODO 1：冒泡排序（带提前退出），统计比较与交换 */
static void bubbleSort(int a[], int n)
{
    (void)a; (void)n;
}

/* TODO 2：选择排序，统计比较与交换 */
static void selectionSort(int a[], int n)
{
    (void)a; (void)n;
}

/* TODO 3：插入排序，统计比较与移动 */
static void insertionSort(int a[], int n)
{
    (void)a; (void)n;
}

/* 打印数组 */
static void show(const char *label, const int a[], int n)
{
    printf("  %-10s", label);
    for (int i = 0; i < n; i++) printf("%3d", a[i]);
    printf("\n");
}

int main(void)
{
    int base[N] = {64, 25, 12, 22, 11, 90, 45, 33};

    printf("=== 原始数据 ===\n");
    show("乱序", base, N);

    /* TODO 4：分别复制一份，各跑一种排序，输出比较/交换次数和排序结果 */

    /* TODO 5：用已排序数据 {11,12,22,25,33,45,64,90} 再跑一遍，对比 */

    printf("\n=== 软考常问的结论 ===\n");
    printf("  冒泡：比较次数固定 n(n-1)/2 = %d 次（n=8）\n", N * (N - 1) / 2);
    printf("        交换次数 = 逆序对个数\n");
    printf("  选择：比较次数固定 n(n-1)/2，交换次数最多 n-1 次（最少）\n");
    printf("  插入：对近乎有序的数据最快，最好情况 O(n)\n");
    printf("\n  三者平均都是 O(n^2)，但常数和适用场景不同。\n");

    return 0;
}
