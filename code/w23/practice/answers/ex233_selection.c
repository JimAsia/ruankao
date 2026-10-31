/* ex233_selection.c —— 参考答案 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;
static long long g_swap = 0;

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            g_cmp++;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int t = a[i];
            a[i] = a[minIdx];
            a[minIdx] = t;
            g_swap++;
        }
    }
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

static void runOne(const char *name, const int src[], int n)
{
    int work[N];
    for (int i = 0; i < n; i++) work[i] = src[i];

    g_cmp = g_swap = 0;
    selectionSort(work, n);

    printf("  %-10s 比较 %-4lld 交换 %-4lld 结果：", name, g_cmp, g_swap);
    for (int i = 0; i < n; i++) printf("%d ", work[i]);
    printf("\n");
}

int main(void)
{
    int random[]   = {49, 38, 65, 97, 76, 13, 27, 49};
    int sorted[]   = {13, 27, 38, 49, 49, 65, 76, 97};
    int reversed[] = {97, 76, 65, 49, 49, 38, 27, 13};

    printf("=== 选择排序：三种数据 ===\n");
    printArr("乱序", random, N);
    printArr("已有序", sorted, N);
    printArr("完全逆序", reversed, N);
    printf("\n");

    runOne("乱序", random, N);
    runOne("已有序", sorted, N);
    runOne("完全逆序", reversed, N);

    printf("\n=== 结论 ===\n");
    printf("  1. 比较次数恒为 n(n-1)/2 = %d，与数据完全无关\n", N * (N - 1) / 2);
    printf("     因为不管数据怎样，都要扫完才知道最小值在哪。\n");
    printf("  2. 交换次数最多 n-1 次 = %d —— 是所有排序里最少的\n", N - 1);
    printf("     ⭐ 所以「交换（写）代价高」时选选择排序，比如写闪存、写磁盘。\n");
    printf("  3. 不稳定（远距离交换会跨越相等元素）\n");
    printf("  4. 最好情况也是 O(n^2) —— 这是它和插入/冒泡的最大区别\n");

    printf("\n=== 软考常考的对比 ===\n");
    printf("  %-10s %-18s %-18s %s\n", "排序", "比较次数", "交换次数", "受数据影响");
    printf("  --------------------------------------------------------------------\n");
    printf("  %-10s %-18s %-18s %s\n", "插入", "最好 n-1，最坏 n(n-1)/2", "最多 n(n-1)/2", "大");
    printf("  %-10s %-18s %-18s %s\n", "冒泡", "最好 n-1，最坏 n(n-1)/2", "最多 n(n-1)/2", "大");
    printf("  %-10s %-18s %-18s %s\n", "选择", "恒为 n(n-1)/2", "最多 n-1", "无");

    return 0;
}
