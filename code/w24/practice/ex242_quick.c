/* ex242_quick.c —— 完整快排 + 求第 k 小
 *
 * 要求：
 *   1. quickSort(a, lo, hi)：完整快排
 *   2. kthSmallest(a, n, k)：求第 k 小的元素（k 从 1 开始）
 *      ⭐ 用快排的分区思想，不用完全排序，平均 O(n)
 *   3. 统计快排在「随机 / 已有序」两种数据上的比较次数
 *
 * 测试：
 *   [49 38 65 97 76 13 27 49] 排序后 → 13 27 38 49 49 65 76 97
 *   第 3 小 = 38，第 5 小 = 49
 *
 * 提示：
 *   第 k 小：分区后看基准位置 p
 *     p == k-1 → 就是它
 *     p > k-1  → 在左半找
 *     p < k-1  → 在右半找
 *   每次只递归一边 → 平均 O(n)（不是 O(n log n)）
 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;

/* TODO 1：分区 */
static int partition(int a[], int lo, int hi)
{
    (void)a; (void)lo; (void)hi;
    return lo;
}

/* TODO 2：完整快排 */
void quickSort(int a[], int lo, int hi)
{
    (void)a; (void)lo; (void)hi;
}

/* TODO 3：第 k 小 */
int kthSmallest(int a[], int n, int k)
{
    (void)a; (void)n; (void)k;
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

    /* TODO 4：完整快排，输出结果 */

    /* TODO 5：求第 3 小和第 5 小 */

    /* TODO 6：随机 vs 已有序的比较次数对比 */

    printf("\n=== 为什么第 k 小是 O(n) ===\n");
    printf("  完整快排要递归两边，每层总共 n 次 → O(n log n)\n");
    printf("  第 k 小只递归一边，工作量 n + n/2 + n/4 + ... = 2n → O(n)\n");
    printf("  ⭐ 这个技巧叫「快速选择」（quickselect）。\n");

    return 0;
}
