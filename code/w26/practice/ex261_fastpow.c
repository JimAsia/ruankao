/* ============================================================================
 * ex261_fastpow.c  —— 练习 1：快速幂的两个版本
 *
 * 【题目】
 *   实现 a^n mod m，要求 O(log n)。
 *   1. 递归版 powRec(a, n, m)：n 为偶数时 a^n = (a^(n/2))^2，
 *      奇数时再乘一个 a。注意只能递归一次！
 *   2. 迭代版 powIter(a, n, m)：把 n 看成二进制，逐位处理：
 *        result = 1, base = a
 *        while (n) {
 *            if (n & 1) result = result * base % m;
 *            base = base * base % m;
 *            n >>= 1;
 *        }
 *   3. 两个版本都要统计乘法次数（每次 % 运算算一次乘法）
 *   4. 用 n = 1000 / 100000 / 10000000 对比朴素循环、递归、迭代
 *
 * 【预期】
 *   三个版本结果必须完全一致。
 *   递归版乘法次数 ≈ 1.5·log2(n)，迭代版 = ⌊log2 n⌋ + popcount(n) − 1 左右。
 *   n = 10^7 时朴素要 1000 万次，快速幂只要 30 次上下。
 *
 * 【提示】
 *   递归版最常见的错误是写成 return powRec(a,n/2,m) * powRec(a,n/2,m)，
 *   这样每层算两次，复杂度直接回到 O(n)。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex261.exe ex261_fastpow.c
 * ==========================================================================*/

#include <stdio.h>

static long long g_mul = 0;

/* ---------- 1. 递归版 ---------- */
long long powRec(long long a, long long n, long long m)
{
    /* TODO */
    (void)a; (void)n; (void)m;
    return 0;
}

/* ---------- 2. 迭代版（二进制拆分）---------- */
long long powIter(long long a, long long n, long long m)
{
    /* TODO */
    (void)a; (void)n; (void)m;
    return 0;
}

/* ---------- 3. 朴素版（对照组）---------- */
long long powNaive(long long a, long long n, long long m)
{
    long long r = 1 % m;
    for (long long i = 0; i < n; i++) { r = r * a % m; g_mul++; }
    return r;
}

int main(void)
{
    long long m = 1000000007LL;

    printf("=== ① 三个版本结果一致性（a=3, m=1e9+7）===\n");
    printf("  %-12s %-16s %-16s %-16s %s\n", "n", "朴素", "递归", "迭代", "一致");
    long long ns[] = {10, 100, 1000};
    for (int i = 0; i < 3; i++) {
        long long n = ns[i];
        g_mul = 0; long long v1 = powNaive(3, n, m); long long c1 = g_mul;
        g_mul = 0; long long v2 = powRec(3, n, m);   long long c2 = g_mul;
        g_mul = 0; long long v3 = powIter(3, n, m);  long long c3 = g_mul;
        printf("  %-12lld %-8lld(%lld) %-8lld(%lld) %-8lld(%lld) %s\n",
               n, v1, c1, v2, c2, v3, c3,
               (v1 == v2 && v2 == v3) ? "✓" : "✗");
    }

    printf("\n=== ② 大指数下只有快速幂能跑 ===\n");
    long long big = 10000000LL;
    g_mul = 0; long long vr = powRec(3, big, m);  long long cr = g_mul;
    g_mul = 0; long long vi = powIter(3, big, m); long long ci = g_mul;
    printf("  n = %lld\n", big);
    printf("    递归：%lld 次乘法，结果 %lld\n", cr, vr);
    printf("    迭代：%lld 次乘法，结果 %lld\n", ci, vi);
    printf("    朴素：需要 %lld 次乘法 —— %.0f 倍差距\n",
           big, (double)big / ci);

    printf("\n=== ③ 结论 ===\n");
    printf("  递归与迭代的结果必须一致；迭代版没有递归栈，工程上更常用。\n");
    printf("  时间复杂度 O(log n)，因为每次 n 减半。\n");
    printf("  这就是软考「分治法降低复杂度」的典型例子。\n");
    return 0;
}
