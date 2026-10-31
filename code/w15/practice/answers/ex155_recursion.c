/* ex155_recursion.c —— 参考答案 */

#include <stdio.h>

static long long g_calls = 0;

static int r1(int n)
{
    g_calls++;
    if (n <= 1) return 0;
    return 1 + r1(n / 2);
}

static int r2(int n)
{
    g_calls++;
    if (n <= 1) return 0;
    return 1 + r2(n / 2) + r2(n / 2);
}

static int r3(int n)
{
    g_calls++;
    if (n <= 0) return 0;
    return 1 + r3(n - 1);
}

int main(void)
{
    const char *c1 = "O(log n)";
    const char *c2 = "O(n)";
    const char *c3 = "O(n)";

    printf("%-6s %-14s %-14s %s\n", "n", "r1 调用次数", "r2 调用次数", "r3 调用次数");
    printf("------------------------------------------------------\n");

    int ns[] = {8, 16, 32, 64};
    long long prev1 = 0, prev2 = 0;
    for (int k = 0; k < 4; k++) {
        int n = ns[k];

        g_calls = 0; (void)r1(n); long long a = g_calls;
        g_calls = 0; (void)r2(n); long long b = g_calls;
        g_calls = 0; (void)r3(n); long long c = g_calls;

        printf("%-6d %-14lld %-14lld %lld\n", n, a, b, c);
        if (prev2 > 0) {
            printf("       %-14s %-14.2f\n", "（翻倍倍数）",
                   (double)b / (double)prev2);
        }
        (void)prev1;
        prev1 = a; prev2 = b;
    }

    printf("\n我的判断：\n");
    printf("  r1 = %s\n", c1);
    printf("  r2 = %s\n", c2);
    printf("  r3 = %s\n", c3);

    printf("\n=== 解析 ===\n");
    printf("r1：n 减半，只走一支 → 层数 = log2(n)，每层 1 次 → O(log n)\n");
    printf("    n=16 时 16,8,4,2,1 → 5 次（含 n=1 那次）\n");

    printf("\nr2：n 减半，但分两支 → 总节点数不是 2^n，而是 2n-1\n");
    printf("    T(n) = 2T(n/2) + 1，T(1) = 1 → T(n) = 2n - 1\n");
    printf("    n=16 时 31 次，n=32 时 63 次，n 翻倍次数也翻倍 → O(n)\n");
    printf("\n    ⭐ 为什么不是指数级？因为「分支多」和「规模减半」同时发生：\n");
    printf("       树的叶子数 = 2^(层数) = 2^(log2 n) = n，\n");
    printf("       总节点数 ≈ 2n，所以是线性。\n");
    printf("       指数级那种是「分两支但规模只减 1」，叶子数才是 2^n。\n");

    printf("\nr3：n 每次减 1，走一支 → 共 n+1 层 → O(n)\n");
    printf("    n=16 时 17 次（含 n=0 那次）\n");

    printf("\n=== 一句话口诀 ===\n");
    printf("  规模怎么变（减 1 还是减半）× 分几支 = 复杂度\n");
    printf("  减 1 + 1 支  → O(n)\n");
    printf("  减半 + 1 支  → O(log n)\n");
    printf("  减半 + 2 支  → O(n)      ← 本次的坑\n");
    printf("  减 1 + 2 支  → O(2^n)    ← 才会爆炸\n");

    return 0;
}
