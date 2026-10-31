/* ============================================================================
 * ex266_lcs.c  —— 参考答案
 *
 * 【填表】
 *   dp[i][j] = X 前 i 个字符 与 Y 前 j 个字符 的 LCS 长度
 *   相等 → 左上 + 1；不等 → 上、左取大
 *
 * 【回溯】
 *   从 (m,n) 出发：
 *     字符相等 → 记录，i-- j--（走左上）
 *     不等     → 往 dp 值大的方向走（上或左）
 *   得到的序列是【逆序】的，最后要反转。
 *
 * 【多个答案】
 *   "ABCBDAB" 与 "BDCABA" 的 LCS 有 BCBA 和 BDAB 两个，
 *   长度都是 4。回溯规则不同（相等时先走哪边）会得到不同序列，都算对。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex266.exe ex266_lcs.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

#define MAXN 64

/* ---------- 1. 填表 ---------- */
int lcsLen(const char *x, const char *y, int dp[MAXN][MAXN])
{
    int m = (int)strlen(x), n = (int)strlen(y);
    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])
                           ? dp[i - 1][j] : dp[i][j - 1];
        }
    }
    return dp[m][n];
}

/* ---------- 2. 回溯 ---------- */
void lcsTrace(const char *x, const char *y, int dp[MAXN][MAXN], char *out)
{
    int i = (int)strlen(x), j = (int)strlen(y), k = 0;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            out[k++] = x[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    out[k] = '\0';
    for (int a = 0, b = k - 1; a < b; a++, b--) {
        char t = out[a]; out[a] = out[b]; out[b] = t;
    }
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
                dp[i][j] = 0;
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

    printf("\n=== ⑤ 回溯方向的两种写法，答案不同但都对 ===\n");
    printf("  dp[i-1][j] >= dp[i][j-1] 时走上 → 得到一种 LCS\n");
    printf("  反之走左 → 可能得到另一种 LCS（长度相同）\n");
    printf("  软考大题一般只要求长度；要求写序列时，任意一个合法答案都给分。\n");
    return 0;
}
