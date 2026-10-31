/* 72_factorial_fib.c —— 阶乘与斐波那契：递归 vs 迭代
 *
 * 这两个是递归的入门题，但斐波那契的递归版本有严重的性能问题 ——
 * 本文件用「调用次数统计」把它量化出来。
 */

#include <stdio.h>

/* 统计递归调用次数的全局计数器 */
long long callCount = 0;

/* ---------- ① 阶乘：递归版 ---------- */
long long factRec(int n)
{
    callCount++;
    if (n <= 1) return 1;               /* 出口 */
    return n * factRec(n - 1);
}

/* ---------- ② 阶乘：迭代版 ---------- */
long long factIter(int n)
{
    long long f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

/* ---------- ③ 斐波那契：朴素递归（有大问题） ---------- */
long long fibRec(int n)
{
    callCount++;
    if (n <= 2) return 1;               /* 出口 */
    return fibRec(n - 1) + fibRec(n - 2);
}

/* ---------- ④ 斐波那契：迭代版 ---------- */
long long fibIter(int n)
{
    if (n <= 2) return 1;
    long long a = 1, b = 1, c = 0;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(void)
{
    /* ---------- ① 阶乘 ---------- */
    printf("=== ① 阶乘：递归 vs 迭代 ===\n");
    for (int i = 5; i <= 10; i += 5) {
        callCount = 0;
        long long r1 = factRec(i);
        long long c1 = callCount;

        long long r2 = factIter(i);

        printf("  %2d! 递归 = %-12lld（调用 %lld 次）  迭代 = %-12lld  一致？%s\n",
               i, r1, c1, r2, (r1 == r2) ? "是" : "否");
    }
    printf("  阶乘的递归：n=10 只调用 10 次，和迭代差不多\n");
    printf("  因为每次只调用自己一次，是一条链，不是树\n");

    /* ---------- ② 斐波那契：递归的灾难 ---------- */
    printf("\n=== ② 斐波那契：递归 vs 迭代 ===\n");
    printf("  %-4s %-12s %-14s %-12s %s\n", "n", "递归结果", "递归调用次数", "迭代结果", "一致");

    int testN[] = {10, 20, 25, 30};
    for (int k = 0; k < 4; k++) {
        int n = testN[k];

        callCount = 0;
        long long r1 = fibRec(n);
        long long c1 = callCount;

        long long r2 = fibIter(n);

        printf("  %-4d %-12lld %-14lld %-12lld %s\n",
               n, r1, c1, r2, (r1 == r2) ? "是" : "否");
    }

    printf("\n  ⚠️ 看调用次数：n=30 时递归调用了上百万次！\n");
    printf("  原因：fibRec(n-1) 和 fibRec(n-2) 会重复计算大量相同的值\n");
    printf("     比如算 fib(30) 时，fib(25) 会被算很多遍\n");
    printf("  复杂度：递归版 O(2ⁿ)，迭代版 O(n) —— 天壤之别\n");

    printf("\n=== ③ 这个例子的意义 ===\n");
    printf("  递归不是「更高级」的写法，它是一种权衡：\n");
    printf("    优点是贴合数学定义，代码短\n");
    printf("    缺点是可能有大量重复计算、栈空间开销\n");
    printf("  能看出「这题递归会不会爆」，是 S2 学算法时的关键能力\n");

    return 0;
}
