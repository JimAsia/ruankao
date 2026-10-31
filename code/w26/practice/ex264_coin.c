/* ============================================================================
 * ex264_coin.c  —— 练习 4：找零钱 —— 贪心到底在哪些金额上失效
 *
 * 【题目】
 *   币值 {1, 5, 11}，凑出金额 x，求最少硬币数。
 *   1. 实现贪心 greedyCoin(x)：每次尽量用大面额
 *   2. 实现动规 dpCoin(x)：dp[x] = min(dp[x-c] + 1)
 *   3. 对 x = 1..50 全部算一遍，列出两者结果不同的金额
 *   4. 打印这些金额下贪心的具体方案（例如 15 = 11+1+1+1+1）
 *
 * 【预期】
 *   15 元：贪心 5 枚（11+1+1+1+1），最优 3 枚（5+5+5）
 *   1..50 里有多个金额贪心会多给硬币。
 *
 * 【思考】
 *   人民币面额 1/2/5/10/20/50/100 为什么不失效？
 *   因为每个面额都 ≥ 前一个的 2 倍（"规范币值"），贪心保证最优。
 *   1/5/11 不满足这个性质，所以会失效。
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
    /* TODO: 从大到小枚举面额，能减就减，记录每枚硬币到 used[]
     * 返回硬币数，*cnt 也写硬币数（方便调用方） */
    (void)x; (void)used; (void)cnt;
    return 0;
}

/* ---------- 2. 动规 ---------- */
int dpCoin(int x, int *used, int *cnt)
{
    /* TODO: dp[0]=0；dp[y] = min(dp[y-c]+1)
     * 用 from[y] 记录「y 是用了哪枚硬币凑出来的」，最后回溯出方案 */
    (void)x; (void)used; (void)cnt;
    return 0;
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
    return 0;
}
