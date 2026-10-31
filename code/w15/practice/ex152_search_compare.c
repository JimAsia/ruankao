/* ex152_search_compare.c —— 顺序查找 vs 二分查找：比较次数实测
 *
 * 要求：
 *   1. 数组 a[i] = i * 2（n 个元素，严格升序）
 *   2. 分别实现：
 *        linearSearch：从前往后找，返回下标或 -1
 *        binarySearch：二分查找（迭代版，不要递归），返回下标或 -1
 *   3. 对「不存在的值」（走最坏情况）统计两者的比较次数
 *   4. 输出 n = 100 / 1000 / 10000 / 100000 的对比
 *
 * 预期输出（n=1000 那一行）：
 *   顺序查找：1000 次比较
 *   二分查找：18 次比较（约 2×log2(1000)，因为每轮算 2 次比较）
 *
 * 提示：
 *   全局计数变量 g_cmp，两个函数里每比较一次就 g_cmp++
 *   二分用 while (lo <= hi)，mid = lo + (hi - lo) / 2
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

static long long g_cmp = 0;

/* TODO 1：顺序查找，每次比较 a[i] == key 时 g_cmp++ */
static int linearSearch(const int a[], int n, int key)
{
    (void)a; (void)n; (void)key;
    return -1;
}

/* TODO 2：二分查找（迭代版），每次比较 a[mid] 与 key 时 g_cmp++ */
static int binarySearch(const int a[], int n, int key)
{
    (void)a; (void)n; (void)key;
    return -1;
}

int main(void)
{
    static int a[MAXN];                 /* 10 万个 int 放全局/静态，避免爆栈 */

    int sizes[] = {100, 1000, 10000, 100000};

    printf("%-10s %-16s %-16s %s\n", "n", "顺序查找", "二分查找", "快多少倍");
    printf("------------------------------------------------------\n");

    for (int k = 0; k < 4; k++) {
        int n = sizes[k];
        for (int i = 0; i < n; i++) a[i] = i * 2;

        /* TODO 3：用不存在的 key（比如 -1）测最坏情况 */

        /* TODO 4：输出两个比较次数和倍数 */
    }

    return 0;
}
