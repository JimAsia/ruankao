/* ============================================================================
 * ex261_fastpow.c  —— 参考答案
 *
 * 【解题要点】
 *   递归：先算 a^(n/2)，再平方 —— 关键只递归一次
 *   迭代：把 n 写成二进制，n 的每一位对应一个 base = a^(2^k)
 *
 * 【迭代版推导】
 *   a^13 = a^(1101₂) = a^8 · a^4 · a^1
 *   循环里 base 依次是 a^1, a^2, a^4, a^8，
 *   遇到 n 的当前位是 1 就把它乘进 result。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex261.exe ex261_fastpow.c
 * ==========================================================================*/

#include <stdio.h>

static long long g_mul = 0;

/* ---------- 1. 递归版 ---------- */
long long powRec(long long a, long long n, long long m)
{
    if (n == 0) return 1 % m;
    long long half = powRec(a, n / 2, m);       /* 只递归一次！ */
    long long r = half * half % m;
    g_mul++;
    if (n & 1) { r = r * a % m; g_mul++; }
    return r;
}

/* ---------- 2. 迭代版（二进制拆分）---------- */
long long powIter(long long a, long long n, long long m)
{
    long long r = 1 % m;
    long long base = a % m;
    while (n > 0) {
        if (n & 1) { r = r * base % m; g_mul++; }
        n >>= 1;
        if (n) { base = base * base % m; g_mul++; }
    }
    return r;
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

    printf("\n=== ④ 为什么递归版是 1.5·log2(n) 次乘法 ===\n");
    printf("  n=1024 时：递归深度 10 层，每层 1 次平方 + 偶/奇各半的额外一次乘。\n");
    printf("  实测 n=1000 是 16 次；n=10^7 是 32 次。\n");
    printf("  都不超过 2·log2(n)，而朴素是 n 次 —— 差距随 n 指数级拉大。\n");
    return 0;
}
