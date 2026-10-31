/* ============================================================================
 * ex265_knapsack.c  —— 练习 5：0-1 背包 + 输出选了哪些物品
 *
 * 【题目】
 *   物品（重量, 价值）：(2,3) (3,4) (4,5) (5,6)，背包容量 8。
 *   1. 用二维 dp 求最大价值
 *   2. 回溯输出选中的物品编号
 *   3. 再用一维滚动数组求一次，验证两个版本价值相同
 *   4. 额外要求：输出 dp 表，并解释「为什么第 4 件物品放不进去」
 *
 * 【预期】
 *   最大价值 10，选中物品 2 和 4（3 + 5 = 8 重，4 + 6 = 10 价值）
 *
 * 【提示】
 *   回溯规则（从 dp[n][cap] 开始）：
 *     if (dp[i][j] != dp[i-1][j]) → 第 i 件被选中，j -= w[i-1]，i--
 *     else                        → 第 i 件没选，i--
 *   注意 dp[i][j] != dp[i-1][j] 这个判断，只有在「装与不装价值不同」时成立；
 *   严谨写法是判断 j >= w[i-1] && dp[i][j] == dp[i-1][j-w[i-1]] + v[i-1]。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex265.exe ex265_knapsack.c
 * ==========================================================================*/

#include <stdio.h>

#define MAXN 16
#define MAXC 64

/* ---------- 1. 二维 dp ---------- */
int knapsack(int *w, int *v, int n, int cap, int dp[MAXN][MAXC])
{
    /* TODO */
    (void)w; (void)v; (void)n; (void)cap; (void)dp;
    return 0;
}

/* ---------- 2. 一维滚动 ---------- */
int knapsack1D(int *w, int *v, int n, int cap, int *out)
{
    /* TODO: 逆序更新 */
    (void)w; (void)v; (void)n; (void)cap; (void)out;
    return 0;
}

int main(void)
{
    int w[] = {2, 3, 4, 5};
    int v[] = {3, 4, 5, 6};
    int n = 4, cap = 8;

    static int dp[MAXN][MAXC];
    int best = knapsack(w, v, n, cap, dp);

    printf("=== ① dp 表 ===\n");
    printf("      j:");
    for (int j = 0; j <= cap; j++) printf("%4d", j);
    printf("\n");
    for (int i = 0; i <= n; i++) {
        printf("  i=%-3d", i);
        for (int j = 0; j <= cap; j++) printf("%4d", dp[i][j]);
        printf("\n");
    }
    printf("  最大价值 = %d\n", best);

    printf("\n=== ② 回溯选中物品 ===\n");
    int j = cap, tw = 0, tv = 0;
    printf("  从 dp[%d][%d] 往左上走：\n", n, cap);
    for (int i = n; i >= 1; i--) {
        if (j >= w[i - 1] && dp[i][j] == dp[i - 1][j - w[i - 1]] + v[i - 1]) {
            printf("    物品 %d (w=%d,v=%d) 选中，容量 %d → %d\n",
                   i, w[i - 1], v[i - 1], j, j - w[i - 1]);
            tw += w[i - 1]; tv += v[i - 1];
            j -= w[i - 1];
        } else {
            printf("    物品 %d (w=%d,v=%d) 未选\n", i, w[i - 1], v[i - 1]);
        }
    }
    printf("  合计：重量 %d，价值 %d  %s\n", tw, tv,
           (tw <= cap && tv == best) ? "✓" : "✗");

    printf("\n=== ③ 一维滚动数组 ===\n");
    static int one[MAXC];
    int best1 = knapsack1D(w, v, n, cap, one);
    printf("  dp 数组：");
    for (int k = 0; k <= cap; k++) printf("%d ", one[k]);
    printf("\n  一维结果 = %d，二维结果 = %d  %s\n", best1, best,
           best1 == best ? "一致 ✓" : "不一致 ✗");

    printf("\n=== ④ 为什么不是全部装下 ===\n");
    printf("  四件全装要 %d 重，容量只有 %d。\n", 2 + 3 + 4 + 5, cap);
    printf("  贪心按单位价值：(2,3)=1.50 (3,4)=1.33 (4,5)=1.25 (5,6)=1.20\n");
    printf("  贪心会选 1、2 两件（重 5，价值 7），剩 3 装不下第 3 件 → 得到 7。\n");
    printf("  ⭐ 最优 10 需要选 2、4 两件，贪心拿不到 —— 这就是 0-1 背包不能用贪心的原因。\n");
    return 0;
}
