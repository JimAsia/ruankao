/* 151_bigO.c —— 复杂度的本质：数「基本操作执行了多少次」
 *
 * 很多人以为复杂度要靠「感觉」估。其实它非常机械：
 *   把代码里最内层那句「基本操作」的执行次数数出来，取 n 趋于无穷时的量级。
 *
 * 本程序不去计时（计时受机器影响），而是直接把次数数出来 —— 这才是复杂度的定义。
 */

#include <stdio.h>

/* ==================== 各种复杂度的函数 ==================== */

/* O(1)：无论 n 多大，只做一次 */
long long opConstant(int n)
{
    (void)n;                    /* 故意不用 n */
    return 1;
}

/* O(log n)：n 每次减半，问「减到 0 要几次」 */
long long opLog(int n)
{
    long long cnt = 0;
    int x = n;
    while (x > 0) {
        x /= 2;
        cnt++;
    }
    return cnt;
}

/* O(n)：一层循环 */
long long opLinear(int n)
{
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt++;                  /* 基本操作 */
    }
    return cnt;
}

/* O(n log n)：外层 n 次，内层每次 log i 次 */
long long opNLogN(int n)
{
    long long cnt = 0;
    for (int i = 1; i <= n; i++) {
        int x = i;
        while (x > 0) {
            x /= 2;
            cnt++;
        }
    }
    return cnt;
}

/* O(n^2)：两层循环，内层跑满 n 次 */
long long opQuadratic(int n)
{
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt++;
        }
    }
    return cnt;
}

/* O(n(n+1)/2)：内层只跑 i 次 —— 还是 O(n^2)，但次数少一半 */
long long opTriangle(int n)
{
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cnt++;
        }
    }
    return cnt;
}

/* O(2^n)：朴素斐波那契递归 */
long long opExp(int n)
{
    if (n <= 1) return 1;               /* 一次比较 + 返回，算 1 次 */
    return 1 + opExp(n - 1) + opExp(n - 2);
}

int main(void)
{
    /* ---------- ① 一张表看尽复杂度 ---------- */
    printf("=== ① 各种复杂度的实际操作次数 ===\n\n");
    printf("%-10s %-12s %-10s %-14s %-10s\n",
           "n", "O(log n)", "O(n)", "O(n log n)", "O(n^2)");
    printf("----------------------------------------------------\n");

    int ns[] = {8, 16, 32, 64, 128};
    for (int k = 0; k < 5; k++) {
        int n = ns[k];
        printf("%-10d %-12lld %-10lld %-14lld %-10lld\n",
               n,
               opLog(n),
               opLinear(n),
               opNLogN(n),
               opQuadratic(n));
    }

    printf("\n⭐ 看 n 从 8 翻倍到 16 时各列怎么变：\n");
    printf("   O(log n) 只 +1      （2 的幂时）\n");
    printf("   O(n)     翻倍\n");
    printf("   O(n log n) 翻倍多一点\n");
    printf("   O(n^2)   变 4 倍\n");

    /* ---------- ② 自己算一遍翻倍倍数 ---------- */
    printf("\n=== ② 翻倍时的增长倍数（n=64 → 128）===\n");
    int n1 = 64, n2 = 128;
    printf("  O(log n)   : %lld → %lld    增 %.2f 倍\n",
           opLog(n1), opLog(n2), (double)opLog(n2) / (double)opLog(n1));
    printf("  O(n)       : %lld → %lld  增 %.2f 倍\n",
           opLinear(n1), opLinear(n2), (double)opLinear(n2) / (double)opLinear(n1));
    printf("  O(n log n) : %lld → %lld  增 %.2f 倍\n",
           opNLogN(n1), opNLogN(n2), (double)opNLogN(n2) / (double)opNLogN(n1));
    printf("  O(n^2)     : %lld → %lld  增 %.2f 倍\n",
           opQuadratic(n1), opQuadratic(n2),
           (double)opQuadratic(n2) / (double)opQuadratic(n1));

    printf("\n  ⭐ 这张表就是复杂度的定义：\n");
    printf("     n 翻倍时，操作次数涨多少倍，决定了复杂度是哪一档。\n");

    /* ---------- ③ 常数和低阶项为什么可以忽略 ---------- */
    printf("\n=== ③ 常数与低阶项的意义 ===\n");
    printf("  O(n^2)          = %lld 次\n", opQuadratic(64));
    printf("  O(n(n+1)/2)     = %lld 次\n", opTriangle(64));
    printf("  两者比值        = %.2f\n",
           (double)opQuadratic(64) / (double)opTriangle(64));

    printf("\n  三角形循环次数比满矩阵少一半，但**复杂度仍是 O(n^2)**。\n");
    printf("  因为 n 趋于无穷时，比值稳定在 2 —— 是个常数，不影响量级。\n");
    printf("  ⭐ 大 O 只关心「增长趋势」，不关心具体倍数。\n");

    printf("\n  再看：3n + 5 和 n\n");
    printf("  n = 64   : 3*64+5 = %d\n", 3 * 64 + 5);
    printf("  n = 1024 : 3*1024+5 = %d\n", 3 * 1024 + 5);
    printf("  ⭐ 系数 3 和常数 5 都不影响「线性」这个结论，所以写成 O(n)。\n");

    /* ---------- ④ 指数级：小 n 就爆 ---------- */
    printf("\n=== ④ 指数级：n 只要大一点点就完蛋 ===\n");
    printf("  %-6s %-14s %s\n", "n", "O(2^n) 次数", "对比 O(n^2)");
    for (int n = 5; n <= 30; n += 5) {
        long long e = opExp(n);
        long long q = opQuadratic(n);
        printf("  %-6d %-14lld %lld\n", n, e, q);
    }

    printf("\n  ⭐ n=30 时指数级已经是 %.0f 万次，而平方级只有 %lld 次。\n",
           (double)opExp(30) / 10000.0, opQuadratic(30));
    printf("     这就是为什么朴素递归求斐波那契「看起来能跑」，\n");
    printf("     n 到 40 就明显卡 —— 这是复杂度决定的，不是机器慢。\n");

    /* ---------- ⑤ 结论 ---------- */
    printf("\n=== ⑤ 复杂度阶的排序（从小到大）===\n");
    printf("  O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(n^3) < O(2^n) < O(n!)\n");
    printf("\n  ⭐ 判断复杂度的三步法：\n");
    printf("     1. 找到最内层的「基本操作」（赋值、比较、加法）\n");
    printf("     2. 数它被执行了多少次（写成 n 的表达式）\n");
    printf("     3. 丢掉常数系数和低阶项，只留增长最快的项\n");

    return 0;
}
