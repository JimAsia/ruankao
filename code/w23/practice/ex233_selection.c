/* ex233_selection.c —— 选择排序
 *
 * 要求：
 *   1. selectionSort(a, n)：升序，统计比较次数和交换次数
 *   2. 每趟打印，观察「最小的元素逐步到最前」
 *   3. 用三种数据验证：比较次数恒定，交换次数不同
 *
 * 测试：
 *   乱序：[49 38 65 97 76 13 27 49]
 *   已有序：[13 27 38 49 49 65 76 97]
 *   完全逆序：[97 76 65 49 49 38 27 13]
 *
 * 期望：
 *   三者比较次数都是 28（= n(n-1)/2）
 *   交换次数：乱序若干次、已有序 0 次、逆序若干次
 *
 * 提示：
 *   每轮记录最小值的下标，最后只交换一次（不是每次比较都交换）
 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;
static long long g_swap = 0;

/* TODO 1：选择排序 */
void selectionSort(int a[], int n)
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
    int random[]   = {49, 38, 65, 97, 76, 13, 27, 49};
    int sorted[]   = {13, 27, 38, 49, 49, 65, 76, 97};
    int reversed[] = {97, 76, 65, 49, 49, 38, 27, 13};

    /* TODO 2：三种数据各跑一次，输出比较/交换次数 */

    printf("\n=== 结论 ===\n");
    printf("  1. 比较次数恒为 n(n-1)/2，与数据无关\n");
    printf("  2. 交换次数最多 n-1 次 —— 是所有排序里最少的\n");
    printf("     ⭐ 所以「交换（写）代价高」时选选择排序\n");
    printf("  3. 不稳定（远距离交换会跨越相等元素）\n");

    return 0;
}
