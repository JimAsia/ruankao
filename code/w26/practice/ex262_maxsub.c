/* ============================================================================
 * ex262_maxsub.c  —— 练习 2：最大子段和（要返回起止下标）
 *
 * 【题目】
 *   数组 a 可能含负数，求连续子段的最大和，**并输出起止下标**。
 *   1. 动规版 maxSubDP：O(n)，返回最大和，起止下标通过指针回传
 *   2. 分治版 maxSubDC：O(n log n)，同样返回起止下标
 *   3. 用同一组数据验证两版结果完全一致
 *   4. 测试用例要包含：全负数、只有一个正数、答案跨中点
 *
 * 【预期】
 *   {-2, 11, -4, 13, -5, -2} → 和 20，区间 [1, 3]（11 - 4 + 13）
 *   {-5, -2, -8}            → 和 -2，区间 [1, 1]（全负数时取最大单元素）
 *   {5, -100, 5, 5}         → 和 10，区间 [2, 3]
 *
 * 【提示】
 *   动规：cur 表示「以 i 结尾的最大子段和」。
 *         若 cur > 0 就接上，否则从 i 重新开始 —— 重新开始时左端点要更新。
 *   分治：左半、右半、跨中点三者取最大。跨中点要同时记录左边界和右边界。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex262.exe ex262_maxsub.c
 * ==========================================================================*/

#include <stdio.h>

/* ---------- 1. 动规版 ---------- */
long long maxSubDP(const int *a, int n, int *lo, int *hi)
{
    /* TODO: 返回最大和，*lo / *hi 写起止下标 */
    (void)a; (void)n; (void)lo; (void)hi;
    return 0;
}

/* ---------- 2. 分治版 ---------- */
long long maxSubDC(const int *a, int n, int *lo, int *hi)
{
    /* TODO: 可以再写一个带边界的递归函数 */
    (void)a; (void)n; (void)lo; (void)hi;
    return 0;
}

/* ---------- 3. 暴力版（只用来对答案，不要求优化）---------- */
long long maxSubBrute(const int *a, int n, int *lo, int *hi)
{
    long long best = a[0];
    *lo = *hi = 0;
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = i; j < n; j++) {
            s += a[j];
            if (s > best) { best = s; *lo = i; *hi = j; }
        }
    }
    return best;
}

static void runCase(const char *name, const int *a, int n)
{
    int l1, h1, l2, h2, l3, h3;
    long long v1 = maxSubDP(a, n, &l1, &h1);
    long long v2 = maxSubDC(a, n, &l2, &h2);
    long long v3 = maxSubBrute(a, n, &l3, &h3);

    printf("  %-22s 动规 %lld [%d,%d]  分治 %lld [%d,%d]  暴力 %lld [%d,%d]  %s\n",
           name, v1, l1, h1, v2, l2, h2, v3, l3, h3,
           (v1 == v3 && v2 == v3) ? "✓" : "✗");
}

int main(void)
{
    int a1[] = {-2, 11, -4, 13, -5, -2};
    int a2[] = {-5, -2, -8};
    int a3[] = {5, -100, 5, 5};
    int a4[] = {1, 2, 3, 4, 5};
    int a5[] = {-1, 2, -1, 3, -10, 4};

    printf("=== ① 五组数据，三版对照 ===\n");
    runCase("{-2,11,-4,13,-5,-2}", a1, 6);
    runCase("{-5,-2,-8}", a2, 3);
    runCase("{5,-100,5,5}", a3, 4);
    runCase("{1,2,3,4,5}", a4, 5);
    runCase("{-1,2,-1,3,-10,4}", a5, 6);

    printf("\n=== ② 分治的跨中点分支 ===\n");
    printf("  以 {-2,11,-4,13,-5,-2} 为例：mid=2，左半最大 11、右半最大 13，\n");
    printf("  但答案 20 来自跨中点（11 + (-4) + 13）。\n");
    printf("  ⭐ 所以分治的合并必须算三种情况的最大值，漏掉跨中点就错。\n");

    printf("\n=== ③ 复杂度对照 ===\n");
    printf("  %-12s %-10s %-10s %s\n", "方法", "时间", "空间", "说明");
    printf("  %-12s %-10s %-10s %s\n", "暴力", "O(n^2)", "O(1)", "最好写");
    printf("  %-12s %-10s %-10s %s\n", "分治", "O(n log n)", "O(log n)", "递归栈");
    printf("  %-12s %-10s %-10s %s\n", "动规", "O(n)", "O(1)", "最优");
    return 0;
}
