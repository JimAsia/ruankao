/* ============================================================================
 * ex266_lcs.c  —— 练习 6：最长公共子序列（长度 + 具体序列）
 *
 * 【题目】
 *   给定两个字符串 X、Y，求最长公共子序列（不要求连续）。
 *   1. 实现 lcsLen(x, y, dp)：填表并返回长度
 *   2. 实现 lcsTrace(x, y, dp, out)：回溯出具体的一个 LCS
 *   3. 测试三组数据：
 *        "ABCBDAB" / "BDCABA"     → 长度 4
 *        "ABCDEF"  / "ACE"        → 长度 3
 *        "ABC"     / "DEF"        → 长度 0
 *   4. 打印第一组的完整 dp 表
 *
 * 【注意】
 *   LCS 不要求连续，所以 "ABCBDAB" 和 "BDCABA" 的答案是 BCBA（或 BDAB），
 *   长度都是 4。**多个答案都算对**，回溯方向不同会得到不同的序列。
 *
 *   如果题目要求「最长公共【子串】」（必须连续），那 DP 定义要改：
 *   dp[i][j] = 以 X[i-1]、Y[j-1] 结尾的最长公共子串长度，不等时置 0。
 *
 * 【提示】
 *   转移：
 *     相等：dp[i][j] = dp[i-1][j-1] + 1
 *     不等：dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   回溯：从 (m,n) 开始，相等就记录并往左上走，否则往 dp 值大的方向走。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex266.exe ex266_lcs.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

#define MAXN 64

/* ---------- 1. 填表 ---------- */
int lcsLen(const char *x, const char *y, int dp[MAXN][MAXN])
{
    /* TODO */
    (void)x; (void)y; (void)dp;
    return 0;
}

/* ---------- 2. 回溯 ---------- */
void lcsTrace(const char *x, const char *y, int dp[MAXN][MAXN], char *out)
{
    /* TODO: 从右下角回溯，记得最后要把结果反转 */
    (void)x; (void)y; (void)dp; (void)out;
}

/* ---------- 3. 最长公共子串（对照用，已给出）---------- */
int lcsubstr(const char *x, const char *y)
{
    int dp[MAXN][MAXN];
    int m = (int)strlen(x), n = (int)strlen(y), best = 0;
    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > best) best = dp[i][j];
            } else {
                dp[i][j] = 0;               /* 不连续就断掉 */
            }
        }
    }
    return best;
}

static void showTable(const char *x, const char *y, int dp[MAXN][MAXN])
{
    int m = (int)strlen(x), n = (int)strlen(y);
    printf("        ");
    for (int j = 0; j <= n; j++) printf("%3c", j == 0 ? ' ' : y[j - 1]);
    printf("\n");
    for (int i = 0; i <= m; i++) {
        printf("   %3c", i == 0 ? ' ' : x[i - 1]);
        for (int j = 0; j <= n; j++) printf("%3d", dp[i][j]);
        printf("\n");
    }
}

int main(void)
{
    const char *cases[3][2] = {
        {"ABCBDAB", "BDCABA"},
        {"ABCDEF",  "ACE"},
        {"ABC",     "DEF"}
    };

    printf("=== ① 三组数据 ===\n");
    for (int t = 0; t < 3; t++) {
        static int dp[MAXN][MAXN];
        const char *x = cases[t][0], *y = cases[t][1];
        int len = lcsLen(x, y, dp);
        char out[MAXN];
        lcsTrace(x, y, dp, out);
        printf("  X=%-10s Y=%-10s → LCS 长度 %d，序列 \"%s\"（子串长度 %d）\n",
               x, y, len, out, lcsubstr(x, y));
    }

    printf("\n=== ② 第一组的 dp 表 ===\n");
    {
        static int dp[MAXN][MAXN];
        lcsLen(cases[0][0], cases[0][1], dp);
        showTable(cases[0][0], cases[0][1], dp);
    }

    printf("\n=== ③ 子序列 vs 子串 ===\n");
    printf("  \"ABCBDAB\" 与 \"BDCABA\"：\n");
    printf("    最长公共【子序列】长度 4（BCBA，可以不连续）\n");
    printf("    最长公共【子串】长度 2（如 \"AB\"，必须连续）\n");
    printf("  ⭐ 题目说「子序列」和「子串」是两个完全不同的问题，别混。\n");

    printf("\n=== ④ 复杂度 ===\n");
    printf("  时间 O(m×n)，空间 O(m×n)；只求长度时可压成两行 O(n)。\n");
    printf("  想要具体序列就必须保留整张表（或者用额外的方向数组）来回溯。\n");
    return 0;
}
