/* ============================================================================
 * 264_dp_knapsack.c  —— 两个必考动规：0-1 背包、最长公共子序列
 *
 * 动规题的四步（照着填就不会卡）：
 *   ① 定义状态：dp[i][j] 到底表示什么？—— 一句话说不清就是没定义好
 *   ② 写转移方程：dp[i][j] 从哪来？
 *   ③ 定边界：i=0 或 j=0 时是多少？
 *   ④ 定方向：填表顺序（决定能不能压成一维）
 *
 * 本文件：
 *   ① 0-1 背包：二维表 → 一维滚动数组，并演示「为什么必须逆序」
 *   ② LCS：填表 + 回溯出具体子序列
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 264.exe 264_dp_knapsack.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

#define MAXN 32
#define MAXC 64

/* ==========================================================================
 * 一、0-1 背包
 *
 *   状态：dp[i][j] = 只考虑前 i 件物品、容量为 j 时能装的最大价值
 *   转移：dp[i][j] = max( dp[i-1][j],                       // 不装第 i 件
 *                         dp[i-1][j-w[i]] + v[i] )          // 装第 i 件
 *   边界：dp[0][j] = 0
 * ========================================================================*/

/* 二维版：能看清「每一行只依赖上一行」 */
int knapsack2D(const int *w, const int *v, int n, int cap, int dp[MAXN][MAXC])
{
    for (int j = 0; j <= cap; j++) dp[0][j] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= cap; j++) {
            dp[i][j] = dp[i - 1][j];                        /* 不装 */
            if (j >= w[i - 1]) {
                int take = dp[i - 1][j - w[i - 1]] + v[i - 1];
                if (take > dp[i][j]) dp[i][j] = take;       /* 装 */
            }
        }
    }
    return dp[n][cap];
}

/* 一维版：dp[j] 就是二维的 dp[i-1][j]，原地更新 */
int knapsack1D(const int *w, const int *v, int n, int cap, int *out)
{
    for (int j = 0; j <= cap; j++) out[j] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = cap; j >= w[i]; j--) {                 /* 逆序！ */
            int take = out[j - w[i]] + v[i];
            if (take > out[j]) out[j] = take;
        }
    }
    return out[cap];
}

/* 故意写错：正序更新，等价于「物品可以重复拿」= 完全背包 */
int knapsackForward(const int *w, const int *v, int n, int cap, int *out)
{
    for (int j = 0; j <= cap; j++) out[j] = 0;
    for (int i = 0; i < n; i++)
        for (int j = w[i]; j <= cap; j++)                   /* 正序 → 会重复用同一件 */
            if (out[j - w[i]] + v[i] > out[j]) out[j] = out[j - w[i]] + v[i];
    return out[cap];
}

/* ==========================================================================
 * 二、最长公共子序列（LCS）
 *
 *   状态：dp[i][j] = X 的前 i 个字符 与 Y 的前 j 个字符 的 LCS 长度
 *   转移：X[i-1] == Y[j-1] → dp[i][j] = dp[i-1][j-1] + 1
 *         否则             → dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   边界：dp[0][*] = dp[*][0] = 0
 * ========================================================================*/

int lcs(const char *x, const char *y, int dp[MAXN][MAXC])
{
    int m = (int)strlen(x), n = (int)strlen(y);
    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1]
                           ? dp[i - 1][j] : dp[i][j - 1];
        }
    }
    return dp[m][n];
}

/* 回溯：从右下角往左上走，相等就记下字符 */
void lcsTrace(const char *x, const char *y, int dp[MAXN][MAXC], char *out)
{
    int i = (int)strlen(x), j = (int)strlen(y), k = 0;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) { out[k++] = x[i - 1]; i--; j--; }
        else if (dp[i - 1][j] >= dp[i][j - 1]) i--;
        else j--;
    }
    out[k] = '\0';
    /* 反转 */
    for (int a = 0, b = k - 1; a < b; a++, b--) {
        char t = out[a]; out[a] = out[b]; out[b] = t;
    }
}

int main(void)
{
    /* ---------------- ① 0-1 背包 ---------------- */
    printf("=== ① 0-1 背包 ===\n");
    int w[] = {2, 3, 4, 5};
    int v[] = {3, 4, 5, 6};
    int n = 4, cap = 8;

    printf("  容量 %d，物品（重量, 价值）：", cap);
    for (int i = 0; i < n; i++) printf("(%d,%d) ", w[i], v[i]);
    printf("\n\n");

    static int dp[MAXN][MAXC];
    int best = knapsack2D(w, v, n, cap, dp);
    printf("  二维 dp 表（行 = 前 i 件，列 = 容量 j）：\n");
    printf("      j:");
    for (int j = 0; j <= cap; j++) printf("%4d", j);
    printf("\n");
    for (int i = 0; i <= n; i++) {
        printf("  i=%-3d", i);
        for (int j = 0; j <= cap; j++) printf("%4d", dp[i][j]);
        printf("\n");
    }
    printf("  dp[%d][%d] = %d\n", n, cap, best);

    static int one[MAXC];
    printf("\n  一维滚动数组：dp[j] 从右往左更新\n");
    for (int i = 0; i < n; i++) {
        printf("    放物品 %d (w=%d,v=%d) 后：", i + 1, w[i], v[i]);
        knapsack1D(w, v, i + 1, cap, one);
        for (int j = 0; j <= cap; j++) printf("%d ", one[j]);
        printf("\n");
    }
    int best1 = knapsack1D(w, v, n, cap, one);
    printf("  一维结果 = %d，二维结果 = %d  %s\n", best1, best,
           best1 == best ? "一致 ✓" : "不一致 ✗");

    printf("\n=== ② 为什么必须逆序 ===\n");
    static int fwd[MAXC];
    int bad = knapsackForward(w, v, n, cap, fwd);
    printf("  逆序（正确，0-1 背包）：%d\n", best1);
    printf("  正序（错误，变成完全背包）：%d\n", bad);
    printf("  正序时 dp 表：[");
    for (int j = 0; j <= cap; j++) printf("%d%s", fwd[j], j == cap ? "" : " ");
    printf("]\n");
    printf("\n  ⭐ 原因：正序时 dp[j-w[i]] 已经被本轮的物品 i 更新过，\n");
    printf("     相当于「物品 i 可以再拿一次」→ 变成了完全背包。\n");
    printf("     逆序时 dp[j-w[i]] 还是上一轮的旧值，保证每件只用一次。\n");

    /* ---------------- ③ LCS ---------------- */
    printf("\n=== ③ 最长公共子序列 ===\n");
    const char *x = "ABCBDAB";
    const char *y = "BDCABA";
    int m = (int)strlen(x), ny = (int)strlen(y);

    static int ld[MAXN][MAXC];
    int len = lcs(x, y, ld);

    printf("  X = %s（长 %d）\n", x, m);
    printf("  Y = %s（长 %d）\n\n", y, ny);
    printf("  dp 表（行 = X 的前 i 个，列 = Y 的前 j 个）：\n");
    printf("        ");
    for (int j = 0; j <= ny; j++) printf("%3c", j == 0 ? ' ' : y[j - 1]);
    printf("\n");
    for (int i = 0; i <= m; i++) {
        printf("   %3c", i == 0 ? ' ' : x[i - 1]);
        for (int j = 0; j <= ny; j++) printf("%3d", ld[i][j]);
        printf("\n");
    }
    printf("  LCS 长度 = %d\n", len);

    char seq[MAXN];
    lcsTrace(x, y, ld, seq);
    printf("  LCS = %s\n", seq);

    printf("\n  ⭐ 注意 dp[m][n] 只是【长度】，想要具体子序列必须回溯。\n");
    printf("     回溯规则：字符相等就往左上走并记录；否则往 dp 值大的方向走。\n");

    /* ---------------- ④ 两个问题的对照 ---------------- */
    printf("\n=== ④ 背包与 LCS 的对照 ===\n");
    printf("  %-14s %-34s %s\n", "问题", "状态定义", "转移来源");
    printf("  %-14s %-34s %s\n", "0-1 背包", "dp[i][j] 前 i 件、容量 j 的最大价值", "上 / 左上");
    printf("  %-14s %-34s %s\n", "LCS", "dp[i][j] 两个前缀的 LCS 长度", "上 / 左 / 左上");
    printf("  ⭐ 共同点：都是二维表、都只依赖「上一行」和「本行左边」。\n");
    printf("     这就是它们都能用一维滚动数组优化的原因。\n");
    return 0;
}
