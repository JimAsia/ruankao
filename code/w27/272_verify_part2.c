/* ============================================================================
 * 272_verify_part2.c  —— W27 大题专项（二）答案验证
 *
 *   题 4：哈希表填表 + ASL（成功 / 失败）
 *   题 5：图 —— Dijkstra 最短路 + Prim 最小生成树
 *   题 6：0-1 背包的 dp 表与最优方案
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 272.exe 272_verify_part2.c
 * ==========================================================================*/

#include <stdio.h>

/* ==========================================================================
 * 题 4：哈希表
 *   关键字 19 14 23 1 68 20 84 27 55 11 10
 *   H(k) = k % 13，表长 16，线性探测
 * ========================================================================*/

#define HM 16
#define HP 13
#define EMPTY (-1)

static int htab[HM];

static int hInsert(int key, int *probes)
{
    int h = key % HP;
    for (int i = 0; i < HM; i++) {
        int pos = (h + i) % HM;
        (*probes)++;
        if (htab[pos] == EMPTY) { htab[pos] = key; return pos; }
        if (htab[pos] == key) return -2;
    }
    return -1;
}

/* ==========================================================================
 * 题 5：图
 *
 *      4        1
 *   0 ----- 1 ----- 2
 *   |       |      /|
 *  2|      5|    8/ |10
 *   |       |    /  |
 *   3?  —— 用邻接矩阵，见 initGraph
 * ========================================================================*/

#define INF 1000000
#define V 6

static int cost[V][V];

static void initGraph(void)
{
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) cost[i][j] = (i == j) ? 0 : INF;

    /* 边：0-1(4) 0-2(2) 1-2(1) 1-3(5) 2-3(8) 2-4(10) 3-4(2) 3-5(6) 4-5(3) */
    int e[][3] = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5}, {2, 3, 8},
        {2, 4, 10}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}
    };
    for (int i = 0; i < 9; i++) {
        int u = e[i][0], v = e[i][1], w = e[i][2];
        cost[u][v] = cost[v][u] = w;         /* 无向图 */
    }
}

static void dijkstra(int src)
{
    int dist[V], done[V], path[V];
    for (int i = 0; i < V; i++) { dist[i] = INF; done[i] = 0; path[i] = -1; }
    dist[src] = 0;

    for (int it = 0; it < V; it++) {
        /* 选当前 dist 最小的未确定点 */
        int u = -1, best = INF;
        for (int i = 0; i < V; i++)
            if (!done[i] && dist[i] < best) { best = dist[i]; u = i; }
        if (u < 0) break;
        done[u] = 1;

        printf("    确定 %d（dist=%d），松弛：", u, dist[u]);
        int any = 0;
        for (int v = 0; v < V; v++) {
            if (done[v] || cost[u][v] >= INF) continue;
            if (dist[u] + cost[u][v] < dist[v]) {
                printf("%d:%d→%d ", v, dist[v], dist[u] + cost[u][v]);
                dist[v] = dist[u] + cost[u][v];
                path[v] = u;
                any = 1;
            }
        }
        if (!any) printf("无");
        printf("\n");
    }

    printf("  最终：");
    for (int i = 0; i < V; i++) printf("%d:%d  ", i, dist[i]);
    printf("\n");

    /* 打印 0→5 的路径 */
    int stack[V], top = 0, x = 5;
    while (x != -1) { stack[top++] = x; x = path[x]; }
    printf("  0 → 5 的路径：");
    for (int i = top - 1; i >= 0; i--) printf("%d%s", stack[i], i ? " → " : "");
    printf("（长度 %d）\n", dist[5]);
}

static void prim(void)
{
    int lowcost[V], parent[V], chosen[V];
    for (int i = 0; i < V; i++) { lowcost[i] = cost[0][i]; parent[i] = 0; chosen[i] = 0; }
    chosen[0] = 1;

    int total = 0;
    printf("  从顶点 0 出发：\n");
    for (int k = 1; k < V; k++) {
        int u = -1, best = INF;
        for (int i = 1; i < V; i++)
            if (!chosen[i] && lowcost[i] < best) { best = lowcost[i]; u = i; }
        if (u < 0) break;
        chosen[u] = 1;
        total += best;
        printf("    选边 %d-%d（权 %d），累计 %d\n", parent[u], u, best, total);
        for (int v = 1; v < V; v++)
            if (!chosen[v] && cost[u][v] < lowcost[v]) {
                lowcost[v] = cost[u][v];
                parent[v] = u;
            }
    }
    printf("  MST 总权值 = %d\n", total);
}

/* ==========================================================================
 * 题 6：0-1 背包
 *   物品 (2,3) (3,5) (4,6) (5,7)，容量 9
 * ========================================================================*/

#define N6 4
#define C6 9

int main(void)
{
    /* ---------------- 题 4 ---------------- */
    printf("=== 题 4：哈希表（H(k)=k%%13，表长 16，线性探测）===\n");
    int keys[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10};
    int n = 11;
    for (int i = 0; i < HM; i++) htab[i] = EMPTY;

    int totalProbe = 0;
    printf("  %-6s %-8s %-8s %s\n", "key", "H(key)", "落位", "探测");
    for (int i = 0; i < n; i++) {
        int p = 0;
        int pos = hInsert(keys[i], &p);
        totalProbe += p;
        printf("  %-6d %-8d %-8d %d\n", keys[i], keys[i] % HP, pos, p);
    }

    printf("\n  表：");
    for (int i = 0; i < HM; i++) printf("%4d", i);
    printf("\n      ");
    for (int i = 0; i < HM; i++) {
        if (htab[i] == EMPTY) printf("%4s", "-");
        else                  printf("%4d", htab[i]);
    }
    printf("\n  ASL(成功) = %d/%d = %.4f\n", totalProbe, n, (double)totalProbe / n);

    int totalFail = 0;
    printf("  各地址失败查找比较次数：\n    ");
    for (int a = 0; a < HM; a++) {
        int cnt = 0;
        for (int i = 0; i < HM; i++) {
            cnt++;
            if (htab[(a + i) % HM] == EMPTY) break;
        }
        totalFail += cnt;
        printf("%d:%d ", a, cnt);
    }
    printf("\n  ASL(失败) = %d/%d = %.4f\n", totalFail, HM, (double)totalFail / HM);

    /* ---------------- 题 5 ---------------- */
    printf("\n=== 题 5：图 ===\n");
    initGraph();
    printf("  (a) Dijkstra，源点 0：\n");
    dijkstra(0);
    printf("\n  (b) Prim 最小生成树：\n");
    prim();

    /* ---------------- 题 6 ---------------- */
    printf("\n=== 题 6：0-1 背包（容量 9）===\n");
    int w[N6 + 1] = {0, 2, 3, 4, 5};
    int v[N6 + 1] = {0, 3, 4, 5, 9};
    int dp[N6 + 1][C6 + 1];

    for (int j = 0; j <= C6; j++) dp[0][j] = 0;
    for (int i = 1; i <= N6; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= C6; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i]) {
                int t = dp[i - 1][j - w[i]] + v[i];
                if (t > dp[i][j]) dp[i][j] = t;
            }
        }
    }

    printf("      j:");
    for (int j = 0; j <= C6; j++) printf("%4d", j);
    printf("\n");
    for (int i = 0; i <= N6; i++) {
        printf("  i=%-3d", i);
        for (int j = 0; j <= C6; j++) printf("%4d", dp[i][j]);
        printf("\n");
    }
    printf("  最优值 = %d\n", dp[N6][C6]);

    int j = C6;
    printf("  选中物品：");
    int tw = 0, tv = 0;
    for (int i = N6; i >= 1; i--) {
        if (j >= w[i] && dp[i][j] == dp[i - 1][j - w[i]] + v[i]) {
            printf("%d(w=%d,v=%d) ", i, w[i], v[i]);
            tw += w[i]; tv += v[i];
            j -= w[i];
        }
    }
    printf("→ 重 %d，值 %d\n", tw, tv);

    printf("\n  对照：若按单位价值贪心\n");
    printf("    物品1 3/2=1.50  物品2 4/3=1.33  物品3 5/4=1.25  物品4 9/5=1.80\n");
    printf("    贪心先拿物品4（单位价值最高，重5），再拿物品1（重2）→ 重 7，值 9+3 = 12\n");
    printf("    剩余 2 装不下物品2(3) 和物品3(4)，贪心止步于 12。\n");
    printf("    动规最优 = %d（选物品3+4，重 9）—— 贪心少 %d。\n",
           dp[N6][C6], dp[N6][C6] - 12);
    return 0;
}
