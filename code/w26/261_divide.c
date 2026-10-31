/* ============================================================================
 * 261_divide.c  —— 分治法：从「暴力」到「分而治之」
 *
 * 分治三步（背下来，所有分治题都是这个骨架）：
 *   ① 分解：把问题拆成规模更小的同类子问题
 *   ② 解决：递归求解子问题（小到能直接算就停下）
 *   ③ 合并：把子问题的解拼成原问题的解
 *
 * 本文件用两个经典问题演示：
 *   ① 快速幂：O(n) → O(log n)，乘法次数从 10 亿降到 30
 *   ② 最大子段和：暴力 O(n^3) → 分治 O(n log n) → 动规 O(n)
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 261.exe 261_divide.c
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ==========================================================================
 * 一、快速幂
 *
 *   朴素：a^n = a*a*a*...*a         n 次乘法
 *   快速：a^n = (a^(n/2))^2        每次规模减半，log n 层
 *           n 为奇数时再乘一个 a
 *
 *   注意 n 为偶数时只需算一次 a^(n/2)，然后平方 —— 不能写两次递归调用，
 *   否则又退化成 O(n)。
 * ========================================================================*/

static long long g_mul = 0;             /* 乘法计数 */

long long powNaive(long long a, long long n, long long mod)
{
    long long r = 1 % mod;
    for (long long i = 0; i < n; i++) {
        r = r * a % mod;
        g_mul++;
    }
    return r;
}

long long powFast(long long a, long long n, long long mod)
{
    if (n == 0) return 1 % mod;
    long long half = powFast(a, n / 2, mod);    /* 只递归一次！ */
    g_mul++;                                     /* half * half */
    long long r = half * half % mod;
    if (n % 2) { g_mul++; r = r * a % mod; }
    return r;
}

/* ==========================================================================
 * 二、最大子段和：给一个可能含负数的数组，求和最大的连续子段
 *
 *   例：{-2, 11, -4, 13, -5, -2} → 11-4+13 = 20
 * ========================================================================*/

/* ---------- 暴力 O(n^3) ---------- */
long long maxSubBrute3(const int *a, int n, long long *ops)
{
    long long best = a[0];
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            long long s = 0;
            for (int k = i; k <= j; k++) { s += a[k]; (*ops)++; }
            if (s > best) best = s;
        }
    }
    return best;
}

/* ---------- 暴力优化 O(n^2)：边扩展边累加 ---------- */
long long maxSubBrute2(const int *a, int n, long long *ops)
{
    long long best = a[0];
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = i; j < n; j++) {
            s += a[j]; (*ops)++;
            if (s > best) best = s;
        }
    }
    return best;
}

/* ---------- 分治 O(n log n) ---------- */
/* 跨越中点的最大子段：从中点往左扫一遍 + 往右扫一遍 */
static long long maxCrossing(const int *a, int lo, int mid, int hi, long long *ops)
{
    long long leftSum = 0, leftBest = a[mid];
    for (int i = mid; i >= lo; i--) {
        leftSum += a[i]; (*ops)++;
        if (leftSum > leftBest) leftBest = leftSum;
    }
    long long rightSum = 0, rightBest = a[mid + 1];
    for (int i = mid + 1; i <= hi; i++) {
        rightSum += a[i]; (*ops)++;
        if (rightSum > rightBest) rightBest = rightSum;
    }
    return leftBest + rightBest;
}

static long long maxSubDivide(const int *a, int lo, int hi, long long *ops)
{
    if (lo == hi) return a[lo];                 /* ① 规模足够小，直接解 */

    int mid = lo + (hi - lo) / 2;
    long long l = maxSubDivide(a, lo, mid, ops);        /* ② 递归左半 */
    long long r = maxSubDivide(a, mid + 1, hi, ops);    /* ② 递归右半 */
    long long c = maxCrossing(a, lo, mid, hi, ops);     /* ③ 合并：跨中点 */

    long long best = l > r ? l : r;
    return best > c ? best : c;
}

/* ---------- 动规 O(n)：Kadane ---------- */
long long maxSubKadane(const int *a, int n, long long *ops)
{
    long long cur = a[0], best = a[0];
    for (int i = 1; i < n; i++) {
        (*ops)++;
        /* 以 a[i] 结尾的最大子段和：要么接上前面，要么自己重新开始 */
        cur = (cur > 0) ? cur + a[i] : a[i];
        if (cur > best) best = cur;
    }
    return best;
}

int main(void)
{
    /* ---------------- ① 快速幂 ---------------- */
    printf("=== ① 快速幂：乘法次数对比（mod = 1e9+7）===\n");
    printf("  %-12s %-16s %-16s %s\n", "指数 n", "朴素 O(n)", "快速 O(log n)", "快多少倍");
    long long ns[] = {1000, 100000, 10000000};
    for (int i = 0; i < 3; i++) {
        long long n = ns[i];
        g_mul = 0;
        long long r1 = powNaive(3, n, 1000000007LL);
        long long m1 = g_mul;
        g_mul = 0;
        long long r2 = powFast(3, n, 1000000007LL);
        long long m2 = g_mul;
        printf("  %-12lld %-16lld %-16lld %.0f 倍  %s\n",
               n, m1, m2, (double)m1 / m2, r1 == r2 ? "结果一致 ✓" : "结果不一致 ✗");
    }

    g_mul = 0;
    long long big = powFast(3, 1000000000LL, 1000000007LL);
    printf("  n = 10 亿（朴素要跑 10 亿次，这里只用了 %lld 次乘法）\n", g_mul);
    printf("  3^1000000000 mod 1e9+7 = %lld\n", big);

    /* ---------------- ② 最大子段和 ---------------- */
    printf("\n=== ② 最大子段和：四种解法 ----------\n");
    int small[] = {-2, 11, -4, 13, -5, -2};
    int sn = (int)(sizeof(small) / sizeof(small[0]));
    printf("  数组：-2 11 -4 13 -5 -2\n");
    long long dummy;
    printf("  暴力 O(n^3) = %lld，暴力 O(n^2) = %lld，分治 = ",
           maxSubBrute3(small, sn, &dummy),
           maxSubBrute2(small, sn, &dummy));
    printf("%lld，动规 = %lld\n",
           maxSubDivide(small, 0, sn - 1, &dummy),
           maxSubKadane(small, sn, &dummy));
    printf("  ⭐ 答案都是 20 = 11 + (-4) + 13\n");

    printf("\n=== ③ 规模翻倍时，加法次数怎么涨 ===\n");
    printf("  %-6s %-14s %-14s %-14s %-14s\n", "n", "O(n^3)", "O(n^2)", "分治", "动规");
    int sizes[] = {50, 100, 200, 400};
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        int *arr = malloc(sizeof(int) * n);
        unsigned seed = 7;
        for (int k = 0; k < n; k++) {
            seed = seed * 1103515245u + 12345u;
            arr[k] = (int)(seed >> 16) % 201 - 100;     /* -100..100 */
        }
        long long o1 = 0, o2 = 0, o3 = 0, o4 = 0;
        maxSubBrute3(arr, n, &o1);
        maxSubBrute2(arr, n, &o2);
        maxSubDivide(arr, 0, n - 1, &o3);
        maxSubKadane(arr, n, &o4);
        printf("  %-6d %-14lld %-14lld %-14lld %-14lld\n", n, o1, o2, o3, o4);
        free(arr);
    }
    printf("  ⭐ n 从 50 到 400（8 倍）：\n");
    printf("     O(n^3) 涨约 486 倍（n^3），O(n^2) 涨约 63 倍，分治涨约 12 倍（n log n），动规涨约 8 倍（n）。\n");

    /* ---------------- ④ 分治为什么必须处理「跨中点」 ---------------- */
    printf("\n=== ④ 分治的关键：跨中点的那一段 ===\n");
    int cross[] = {-2, 11, -4, 13, -5, -2};
    int cn = 6, cmod = (0 + cn - 1) / 2;        /* mid = 2 */
    long long d = 0;
    long long lBest = maxSubDivide(cross, 0, cmod, &d);
    long long rBest = maxSubDivide(cross, cmod + 1, cn - 1, &d);
    long long cBest = maxCrossing(cross, 0, cmod, cn - 1, &d);
    long long whole = maxSubDivide(cross, 0, cn - 1, &d);

    printf("  数组：-2 11 -4  |  13 -5 -2      （mid=2，从 -4 后切开）\n");
    printf("  左半 {-2,11,-4} 最大 = %lld\n", lBest);
    printf("  右半 {13,-5,-2} 最大 = %lld\n", rBest);
    printf("  跨中点（必须含 a[2] 和 a[3]）= %lld\n", cBest);
    printf("  整体最大 = %lld\n", whole);
    printf("  ⭐ 答案 20 来自【跨中点】这一项，而不是左右最大值（11 和 13）。\n");
    printf("     所以分治的「合并」不能简单取 max，必须单独算跨中点的情况。\n");
    printf("     跨中点怎么算：从中点往左扫一遍求最大后缀，往右扫一遍求最大前缀，两者相加。\n");
    printf("     这一步是 O(n)，所以整个分治是 O(n log n) 而不是 O(n)。\n");
    return 0;
}
