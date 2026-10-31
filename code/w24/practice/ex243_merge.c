/* ex243_merge.c —— 归并排序 + 统计逆序对
 *
 * 要求：
 *   1. mergeSort(a, n)：归并排序
 *   2. countInversions(a, n)：用归并思想统计逆序对个数
 *      逆序对 = 前面的数大于后面的数的对数
 *
 * 测试：
 *   [49 38 65 97 76 13 27 49] 排序后 → 13 27 38 49 49 65 76 97
 *   逆序对个数需要程序算
 *
 * 提示：
 *   逆序对可以在归并时顺便统计：
 *   当归并时取右边元素（说明 a[i] > a[j]），
 *   那么左边从 i 到 mid 的所有元素都比 a[j] 大
 *   → 逆序对增加 (mid - i + 1) 个
 *
 * ⭐ 这是「归并排序的经典应用」，软考和面试都常考。
 */

#include <stdio.h>

#define N 8

static int g_tmp[N];
static long long g_inv = 0;
static long long g_cmp = 0;

/* TODO 1：归并（顺便统计逆序对） */
static void merge(int a[], int lo, int mid, int hi)
{
    (void)a; (void)lo; (void)mid; (void)hi;
}

/* TODO 2：归并排序 */
void mergeSort(int a[], int lo, int hi)
{
    (void)a; (void)lo; (void)hi;
}

/* TODO 3：统计逆序对（复用归并） */
long long countInversions(int a[], int n)
{
    (void)a; (void)n;
    return 0;
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

    /* TODO 4：归并排序 */

    /* TODO 5：统计逆序对（注意要复制一份，因为排序会破坏原数组） */

    return 0;
}
