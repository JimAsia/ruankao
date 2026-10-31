/* ============================================================================
 * 263_dp_basic.c  —— 动态规划入门：先看「重复子问题」有多贵
 *
 * 动规的适用条件（和分治的区别就在第一条）：
 *   ① 最优子结构：大问题的最优解由小问题的最优解拼成
 *   ② 重叠子问题：递归时会反复算同一个子问题  ← 分治没有这个特征
 *
 * 动规 = 递归 + 把子问题的答案存起来（记忆化），或者换成一维/二维表递推。
 *
 * 本文件：
 *   ① 斐波那契：朴素递归 269 万次调用 → 记忆化 59 次 → 递推 29 次
 *   ② 爬楼梯：本质是斐波那契，但要先想清楚「状态」是什么
 *   ③ 数字三角形：递归 / 记忆化 / 自底向上递推，同一个答案三种代价
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 263.exe 263_dp_basic.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

/* ==========================================================================
 * 一、斐波那契
 * ========================================================================*/

static long long g_calls = 0;

/* 朴素递归：指数级，因为 fib(n-1) 和 fib(n-2) 会重复算同一批子问题 */
long long fibNaive(int n)
{
    g_calls++;
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

/* 记忆化：算过就存下来，下次直接取 */
static long long memo[128];
long long fibMemo(int n)
{
    g_calls++;
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];          /* 命中缓存，不再递归 */
    memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
    return memo[n];
}

/* 递推（自底向上）：只保留前两项，空间 O(1) */
long long fibIter(int n, long long *ops)
{
    if (n <= 1) return n;
    long long a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; i++) {
        c = a + b; a = b; b = c;
        (*ops)++;
    }
    return b;
}

/* ==========================================================================
 * 二、爬楼梯：n 阶台阶，每次 1 或 2 阶，有多少种走法
 *
 *   状态定义：f[i] = 走到第 i 阶的方案数
 *   转移方程：f[i] = f[i-1] + f[i-2]
 *   边界：f[0] = 1（站着不动算一种），f[1] = 1
 * ========================================================================*/

long long climbStairs(int n)
{
    if (n <= 1) return 1;
    long long a = 1, b = 1, c = 1;
    for (int i = 2; i <= n; i++) { c = a + b; a = b; b = c; }
    return b;
}

/* ==========================================================================
 * 三、数字三角形：从顶端走到底部，每次只能往左下或右下，求路径最大和
 *
 *   状态定义：dp[i][j] = 从 (i,j) 走到底部的最大和
 *   转移方程：dp[i][j] = a[i][j] + max(dp[i+1][j], dp[i+1][j+1])
 *   边界：最后一行 dp[n-1][j] = a[n-1][j]
 *
 *   注意「状态定义的方向」：定义成「从 (i,j) 出发往下走」才能自底向上递推。
 *   如果定义成「从顶部走到 (i,j)」，递推方向就得从上往下，边界也不同。
 * ========================================================================*/

#define TN 5
static int tri[TN][TN] = {
    {7, 0, 0, 0, 0},
    {3, 8, 0, 0, 0},
    {8, 1, 0, 0, 0},
    {2, 7, 4, 4, 0},
    {4, 5, 2, 6, 5}
};

static long long g_triCalls = 0;

/* 朴素递归：每个节点被反复访问，指数级 */
int triNaive(int i, int j)
{
    g_triCalls++;
    if (i == TN - 1) return tri[i][j];
    int l = triNaive(i + 1, j);
    int r = triNaive(i + 1, j + 1);
    return tri[i][j] + (l > r ? l : r);
}

/* 记忆化 */
static int triMemo[TN][TN];
int triMemoi(int i, int j)
{
    g_triCalls++;
    if (i == TN - 1) return tri[i][j];
    if (triMemo[i][j] != -1) return triMemo[i][j];
    int l = triMemoi(i + 1, j);
    int r = triMemoi(i + 1, j + 1);
    triMemo[i][j] = tri[i][j] + (l > r ? l : r);
    return triMemo[i][j];
}

/* ---------- 通用版：用来测试不同行数（真递归，不是公式估算）---------- */
static int gN;
static int gtri[20][20];
static int gtriMemo[20][20];

static int gTriNaive(int i, int j)
{
    g_triCalls++;
    if (i == gN - 1) return gtri[i][j];
    int l = gTriNaive(i + 1, j);
    int r = gTriNaive(i + 1, j + 1);
    return gtri[i][j] + (l > r ? l : r);
}

static int gTriMemoi(int i, int j)
{
    g_triCalls++;
    if (i == gN - 1) return gtri[i][j];
    if (gtriMemo[i][j] != -1) return gtriMemo[i][j];
    int l = gTriMemoi(i + 1, j);
    int r = gTriMemoi(i + 1, j + 1);
    gtriMemo[i][j] = gtri[i][j] + (l > r ? l : r);
    return gtriMemo[i][j];
}

int main(void)
{
    /* ---------------- ① 斐波那契 ---------------- */
    printf("=== ① 斐波那契：三种写法的代价 ===\n");
    printf("  %-6s %-16s %-16s %-12s %s\n", "n", "朴素递归调用", "记忆化调用", "递推加法", "结果");

    int ns[] = {10, 20, 30};
    long long naiveCalls[3] = {0}, memoCalls[3] = {0};
    for (int k = 0; k < 3; k++) {
        int n = ns[k];
        g_calls = 0;
        long long v1 = fibNaive(n);
        naiveCalls[k] = g_calls;

        memset(memo, -1, sizeof(memo));
        g_calls = 0;
        long long v2 = fibMemo(n);
        memoCalls[k] = g_calls;

        long long ops = 0;
        long long v3 = fibIter(n, &ops);

        printf("  %-6d %-16lld %-16lld %-12lld %lld\n", n, naiveCalls[k], memoCalls[k], ops, v1);
        if (v1 != v2 || v2 != v3) printf("  ⚠️ 三种写法结果不一致！\n");
    }
    printf("\n  ⭐ n 从 20 涨到 30（只 +10），朴素递归调用次数从 %lld 涨到 %lld，约 %.0f 倍；\n",
           naiveCalls[1], naiveCalls[2], (double)naiveCalls[2] / naiveCalls[1]);
    printf("     记忆化只从 %lld 涨到 %lld（+10 次），递推只 +10 次加法。\n",
           memoCalls[1], memoCalls[2]);
    printf("     这就是「消除重复计算」的威力。fib(30) = %lld\n", fibIter(30, &(long long){0}));

    /* 补充说明：为什么恰好是这个数 */
    printf("\n  朴素递归的调用次数 = 2·fib(n+1) − 1（每个子问题被反复展开）。\n");
    printf("  fib(31) = 1346269，所以 2×1346269 − 1 = 2692537。\n");

    /* ---------------- ② 爬楼梯 ---------------- */
    printf("\n=== ② 爬楼梯 ===\n");
    printf("  %-8s %-10s %s\n", "台阶数", "走法", "说明");
    for (int n = 1; n <= 10; n++) {
        printf("  %-8d %-10lld %s\n", n, climbStairs(n),
               (n <= 3) ? "可以直接数出来" : "");
    }
    printf("  ⭐ f(10) = 89。它和斐波那契只差一个下标：f(n) = fib(n+1)。\n");
    printf("     动规的关键不是背公式，是【定义状态】：f[i] = 走到第 i 阶的方案数。\n");

    /* ---------------- ③ 数字三角形 ---------------- */
    printf("\n=== ③ 数字三角形 ===\n");
    printf("  三角形：\n");
    for (int i = 0; i < TN; i++) {
        printf("   ");
        for (int j = 0; j <= i; j++) printf("%3d", tri[i][j]);
        printf("\n");
    }

    g_triCalls = 0;
    int best = triNaive(0, 0);
    long long naiveTriCalls = g_triCalls;
    printf("\n  朴素递归：最大和 = %d，函数调用 %lld 次\n", best, naiveTriCalls);

    memset(triMemo, -1, sizeof(triMemo));
    g_triCalls = 0;
    int best2 = triMemoi(0, 0);
    printf("  记忆化：  最大和 = %d，函数调用 %lld 次\n", best2, g_triCalls);
    printf("  ⭐ 节点总共只有 %d 个，朴素递归却调用了 %lld 次 —— 重复计算的量级。\n",
           TN * (TN + 1) / 2, naiveTriCalls);

    /* 自底向上递推 */
    int dp[TN][TN];
    for (int j = 0; j < TN; j++) dp[TN - 1][j] = tri[TN - 1][j];
    for (int i = TN - 2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp[i][j] = tri[i][j] + (dp[i + 1][j] > dp[i + 1][j + 1]
                                    ? dp[i + 1][j] : dp[i + 1][j + 1]);

    printf("\n  自底向上填 dp 表（dp[i][j] = 从 (i,j) 走到底的最大和）：\n");
    for (int i = 0; i < TN; i++) {
        printf("   ");
        for (int j = 0; j <= i; j++) printf("%4d", dp[i][j]);
        printf("\n");
    }
    printf("  dp[0][0] = %d\n", dp[0][0]);

    /* 回溯路径 */
    printf("  最优路径：%d", tri[0][0]);
    int j = 0;
    for (int i = 1; i < TN; i++) {
        j = (dp[i][j] > dp[i][j + 1]) ? j : j + 1;
        printf(" → %d", tri[i][j]);
    }
    printf("  （和 = %d）\n", dp[0][0]);

    printf("\n=== ④ 行数变大后，重复计算有多可怕 ===\n");
    printf("  （用同样形状、按固定规律生成的三角形，真跑递归计数）\n");
    printf("  %-6s %-8s %-16s %-14s %s\n", "行数", "节点数", "朴素递归调用", "记忆化调用", "倍数");

    for (int n = 8; n <= 20; n += 4) {
        gN = n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++)
                gtri[i][j] = (i * 7 + j * 13) % 10;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++) gtriMemo[i][j] = -1;

        g_triCalls = 0;
        int v1 = gTriNaive(0, 0);
        long long naiveC = g_triCalls;

        g_triCalls = 0;
        int v2 = gTriMemoi(0, 0);
        long long memoC = g_triCalls;
        if (v1 != v2) printf("  ⚠️ 两种写法结果不一致：%d vs %d\n", v1, v2);

        printf("  %-6d %-8d %-16lld %-14lld %.0f 倍\n",
               n, n * (n + 1) / 2, naiveC, memoC, (double)naiveC / memoC);
    }
    printf("  ⭐ 节点数只按 n² 增长，朴素递归却按 2^n 增长 —— 这就是「重叠子问题」的代价。\n");
    printf("     动规把 2^n 压回 n²，靠的就是「每个状态只算一次」。\n");

    printf("\n=== ⑤ 三种写法的关系 ===\n");
    printf("  %-14s %-14s %-14s %s\n", "写法", "时间", "空间", "特点");
    printf("  %-14s %-14s %-14s %s\n", "朴素递归", "指数级", "O(n) 栈", "最好写，最慢");
    printf("  %-14s %-14s %-14s %s\n", "记忆化搜索", "O(状态数)", "O(状态数)", "改动最小，思路照抄递归");
    printf("  %-14s %-14s %-14s %s\n", "自底向上递推", "O(状态数)", "可压到 O(n)", "最快，但要想清方向");
    printf("  ⭐ 考试写动规，先写递归式，再决定是「加缓存」还是「改递推」。\n");
    return 0;
}
