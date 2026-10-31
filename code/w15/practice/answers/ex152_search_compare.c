/* ex152_search_compare.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

static long long g_cmp = 0;

/* 顺序查找 */
static int linearSearch(const int a[], int n, int key)
{
    for (int i = 0; i < n; i++) {
        g_cmp++;
        if (a[i] == key) return i;
    }
    return -1;
}

/* 二分查找（迭代版） */
static int binarySearch(const int a[], int n, int key)
{
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;       /* 防溢出写法 */
        g_cmp++;
        if (a[mid] == key) return mid;
        g_cmp++;
        if (a[mid] < key) lo = mid + 1;
        else              hi = mid - 1;
    }
    return -1;
}

int main(void)
{
    static int a[MAXN];

    int sizes[] = {100, 1000, 10000, 100000};

    printf("%-10s %-16s %-16s %s\n", "n", "顺序查找", "二分查找", "快多少倍");
    printf("------------------------------------------------------\n");

    for (int k = 0; k < 4; k++) {
        int n = sizes[k];
        for (int i = 0; i < n; i++) a[i] = i * 2;

        long long lc, bc;

        g_cmp = 0;
        (void)linearSearch(a, n, -1);       /* -1 不存在 → 最坏情况 */
        lc = g_cmp;

        g_cmp = 0;
        (void)binarySearch(a, n, -1);
        bc = g_cmp;

        printf("%-10d %-16lld %-16lld %.0f 倍\n",
               n, lc, bc, (double)lc / (double)bc);
    }

    printf("\n=== 结论 ===\n");
    printf("  顺序查找：比较 n 次 → O(n)\n");
    printf("  二分查找：比较约 log2(n) 次（这里每次循环算 2 次比较，所以是 2*log2 n）→ O(log n)\n");

    printf("\n⭐ 增长倍数的对照：\n");
    printf("  n 从 100 → 100000（涨 1000 倍）\n");
    printf("  顺序查找：比较次数也涨 1000 倍\n");
    printf("  二分查找：只从约 7 次涨到约 17 次\n");
    printf("  ⭐ 这就是 O(n) 和 O(log n) 的真实差距。\n");

    printf("\n=== 二分查找的前提（必考）===\n");
    printf("  1. 数据必须**有序**\n");
    printf("  2. 必须能**随机访问**（数组可以，链表不行）\n");
    printf("  ⚠️ 无序数组想用二分，得先排序 —— 那是 O(n log n)，\n");
    printf("     只查一次反而比顺序查找（O(n)）慢。\n");
    printf("     二分的价值在「查很多次」：排一次序，以后每次都是 O(log n)。\n");

    printf("\n=== mid 为什么写 lo + (hi - lo) / 2 ===\n");
    printf("  (lo + hi) / 2 在 lo、hi 都接近 INT_MAX 时会溢出成负数；\n");
    printf("  lo + (hi - lo) / 2 先做减法，不会溢出。\n");
    printf("  软考不考这个细节，但工程代码都这么写。\n");

    return 0;
}
