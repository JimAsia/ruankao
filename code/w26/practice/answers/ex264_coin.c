/* ============================================================================
 * ex264_coin.c  —— 参考答案
 *
 * 【贪心】
 *   从大面额开始，能减就减。O(面额数)。
 *
 * 【动规】
 *   dp[0] = 0
 *   dp[y] = min{ dp[y-c] + 1 }  对每个 c <= y
 *   from[y] 记录 y 是用哪枚硬币凑出来的，用于回溯方案。
 *
 * 【本题的看点】
 *   1/5/11 这组币值下，贪心在多个金额上失效（15 是最小的一个）。
 *   失效原因：11 拿走以后，余数 4 只能用 4 个 1 —— 但最优是 5+5+5。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex264.exe ex264_coin.c
 * ==========================================================================*/

#include <stdio.h>

#define MAXA 128

static const int coins[] = {1, 5, 11};
static const int CN = 3;

/* ---------- 1. 贪心 ---------- */
int greedyCoin(int x, int *used, int *cnt)
{
    int k = 0, rest = x;
    for (int i = CN - 1; i >= 0; i--) {
        while (rest >= coins[i]) {
            rest -= coins[i];
            used[k++] = coins[i];
        }
    }
    *cnt = k;
    return k;
}

/* ---------- 2. 动规 ---------- */
int dpCoin(int x, int *used, int *cnt)
{
    int dp[MAXA], from[MAXA];
    for (int i = 0; i <= x; i++) { dp[i] = 1 << 28; from[i] = -1; }
    dp[0] = 0;
    for (int y = 1; y <= x; y++) {
        for (int i = 0; i < CN; i++) {
            if (coins[i] <= y && dp[y - coins[i]] + 1 < dp[y]) {
                dp[y] = dp[y - coins[i]] + 1;
                from[y] = coins[i];
            }
        }
    }
    int k = 0, y = x;
    while (y > 0 && from[y] > 0) { used[k++] = from[y]; y -= from[y]; }
    *cnt = k;
    return dp[x];
}

int main(void)
{
    printf("=== ① 1..50 逐个对比 ===\n");
    printf("  %-6s %-10s %-10s %s\n", "金额", "贪心枚数", "最优枚数", "贪心是否失效");

    int failCnt = 0, firstFail = -1, worstGap = 0, worstAt = -1;
    for (int x = 1; x <= 50; x++) {
        int u1[64], u2[64], c1, c2;
        int g = greedyCoin(x, u1, &c1);
        int d = dpCoin(x, u2, &c2);
        int bad = (g != d);
        if (bad) {
            failCnt++;
            if (firstFail < 0) firstFail = x;
            if (g - d > worstGap) { worstGap = g - d; worstAt = x; }
        }
        if (bad || x <= 12 || x % 10 == 0)
            printf("  %-6d %-10d %-10d %s\n", x, g, d, bad ? "★ 失效" : "");
    }
    printf("\n  1..50 中贪心失效的金额共 %d 个，最小的是 %d\n", failCnt, firstFail);
    printf("  差距最大的是 %d 元：贪心多用了 %d 枚\n\n", worstAt, worstGap);

    printf("=== ② 典型金额的方案对比 ===\n");
    int tests[] = {15, 16, 22, 27, 33};
    for (int i = 0; i < 5; i++) {
        int x = tests[i];
        int u1[64], u2[64], c1, c2;
        int g = greedyCoin(x, u1, &c1);
        int d = dpCoin(x, u2, &c2);
        printf("  %2d 元：\n", x);
        printf("    贪心 %d 枚 → ", g);
        for (int k = 0; k < g; k++) printf("%d ", u1[k]);
        printf("\n    最优 %d 枚 → ", d);
        for (int k = 0; k < d; k++) printf("%d ", u2[k]);
        printf("\n");
    }

    printf("\n=== ③ 结论 ===\n");
    printf("  贪心失效的根源：拿了 11 之后，剩下的余数用 5 和 1 凑不干净。\n");
    printf("  动规不会犯这个错，因为它比较了「用每枚硬币」的所有分支。\n");
    printf("  复杂度：贪心 O(面额数)，动规 O(金额 × 面额数) —— 贪心快但不保证最优。\n");

    printf("\n=== ④ 人民币为什么可以用贪心 ===\n");
    printf("  人民币面额 1/2/5/10/20/50/100，相邻面额满足「后一个是前一个的 2 倍及以上」，\n");
    printf("  这种叫【规范币值系统】，贪心保证最优。\n");
    printf("  1/5/11 不满足（5 到 11 不到 2 倍），所以会出现 11+1+1+1+1 这种坏选择。\n");
    printf("  ⭐ 软考选择题常问「找零钱能否用贪心」，答案取决于币值是否规范。\n");
    return 0;
}
