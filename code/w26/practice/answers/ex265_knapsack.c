/* ============================================================================
 * ex265_knapsack.c  —— 参考答案
 *
 * 【二维 dp】
 *   dp[i][j] = 前 i 件物品、容量 j 的最大价值
 *   转移：不装 dp[i-1][j]，装 dp[i-1][j-w]+v，取大
 *
 * 【回溯】
 *   从 dp[n][cap] 开始。若 dp[i][j] == dp[i-1][j-w[i-1]] + v[i-1]，
 *   说明第 i 件被装进去了 —— 注意必须先判 j >= w[i-1]，
 *   否则 dp[i-1][负数] 会越界（或读到无意义的值）。
 *
 * 【一维滚动】
 *   逆序更新，保证 dp[j-w] 是「上一轮」的旧值，每件物品只用一次。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex265.exe ex265_knapsack.c
 * ==========================================================================*/

#include <stdio.h>

#define MAXN 16
#define MAXC 64

/* ---------- 1. 二维 dp ---------- */
int knapsack(int *w, int *v, int n, int cap, int dp[MAXN][MAXC])
{
    for (int j = 0; j <= cap; j++) dp[0][j] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= cap; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1]) {
                int take = dp[i - 1][j - w[i - 1]] + v[i - 1];
                if (take > dp[i][j]) dp[i][j] = take;
            }
        }
    }
    return dp[n][cap];
}

/* ---------- 2. 一维滚动 ---------- */
int knapsack1D(int *w, int *v, int n, int cap, int *out)
{
    for (int j = 0; j <= cap; j++) out[j] = 0;
    for (int i = 0; i < n; i++)
        for (int j = cap; j >= w[i]; j--) {         /* 逆序 */
            int take = out[j - w[i]] + v[i];
            if (take > out[j]) out[j] = take;
        }
    return out[cap];
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
    int j = cap, tw = 0, tv = 0, picked[8] = {0};
    printf("  从 dp[%d][%d] 往左上走：\n", n, cap);
    for (int i = n; i >= 1; i--) {
        if (j >= w[i - 1] && dp[i][j] == dp[i - 1][j - w[i - 1]] + v[i - 1]) {
            printf("    物品 %d (w=%d,v=%d) 选中，容量 %d → %d\n",
                   i, w[i - 1], v[i - 1], j, j - w[i - 1]);
            tw += w[i - 1]; tv += v[i - 1];
            picked[i] = 1;
            j -= w[i - 1];
        } else {
            printf("    物品 %d (w=%d,v=%d) 未选\n", i, w[i - 1], v[i - 1]);
        }
    }
    printf("  合计：重量 %d，价值 %d  %s\n", tw, tv,
           (tw <= cap && tv == best) ? "✓" : "✗");
    printf("  选中集合：");
    for (int i = 1; i <= n; i++) if (picked[i]) printf("%d ", i);
    printf("\n");

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
    printf("  贪心会先选物品 1、2（重 5，价值 7），余 3 装不下物品 3 和 4 → 只得到 7。\n");
    printf("  ⭐ 最优 10 需要选物品 2、4（重 8，价值 10），贪心拿不到。\n");

    printf("\n=== ⑤ 一维数组为什么必须逆序 ===\n");
    printf("  正序时 dp[j-w] 已经被本轮更新过，相当于同一件物品拿了两次，\n");
    printf("  那算的是【完全背包】，不是 0-1 背包。\n");
    printf("  逆序时 dp[j-w] 还是上一行的值，保证每件只用一次。\n");
    return 0;
}
