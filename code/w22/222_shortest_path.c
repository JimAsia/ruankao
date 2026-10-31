/* 222_shortest_path.c —— 最短路径：Dijkstra（单源最短路径）
 *
 * 问题：从一个源点到其他所有点的最短距离。
 *
 * Dijkstra 的思路（贪心）：
 *   维护一个 dist[] 数组，dist[i] = 从源点到 i 的当前最短距离
 *   每轮：在未确定的点中选 dist 最小的，把它「确定」下来，
 *        然后用它去「松弛」邻居（如果绕道更近就更新）
 *
 * 关键限制：不能有【负权边】（否则贪心失效）。
 * 有负权要用 Bellman-Ford / SPFA。
 *
 * 复杂度：O(n^2)（邻接矩阵 + 线性找最小），软考按这个回答。
 *         用优先队列（堆）可优化到 O((n+e) log n)。
 */

#include <stdio.h>

#define MAXV 8
#define INF  99999

/* 返回 dist[] 数组，path[i] 记录 i 的前驱（用于回溯路径） */
void dijkstra(int cost[MAXV][MAXV], int n, int src, int dist[], int path[])
{
    int visited[MAXV];

    /* 初始化 */
    for (int i = 0; i < n; i++) {
        dist[i] = cost[src][i];
        visited[i] = 0;
        path[i] = (cost[src][i] < INF && i != src) ? src : -1;
    }
    dist[src] = 0;
    visited[src] = 1;

    printf("  初始化 dist：");
    for (int i = 0; i < n; i++) {
        if (dist[i] >= INF) printf("INF ");
        else printf("%d ", dist[i]);
    }
    printf("（源点 %d 已确定）\n", src);

    /* 主循环：还要确定 n-1 个点 */
    for (int round = 1; round < n; round++) {
        /* ① 在未确定的点里找 dist 最小的 */
        int u = -1, minVal = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minVal) {
                minVal = dist[i];
                u = i;
            }
        }
        if (u == -1) break;                 /* 剩下的都不可达 */
        visited[u] = 1;

        printf("    第 %d 步：确定顶点 %d（dist=%d）\n", round, u, minVal);

        /* ② 用 u 松弛它的邻居 */
        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] < INF) {
                if (dist[u] + cost[u][v] < dist[v]) {
                    int old = dist[v];
                    dist[v] = dist[u] + cost[u][v];
                    path[v] = u;
                    if (old >= INF) {
                        printf("        松弛 %d：INF → %d（经 %d）\n",
                               v, dist[v], u);
                    } else {
                        printf("        松弛 %d：%d → %d（经 %d）\n",
                               v, old, dist[v], u);
                    }
                }
            }
        }
    }
}

/* 回溯路径：从 src 到 dst */
void printPath(const int path[], int src, int dst)
{
    if (dst == src) { printf("%d", src); return; }

    int stack[MAXV], top = -1;
    int cur = dst;
    while (cur != -1) {
        stack[++top] = cur;
        if (cur == src) break;
        cur = path[cur];
    }
    if (cur != src) { printf("不可达"); return; }

    while (top >= 0) {
        printf("%d", stack[top--]);
        if (top >= 0) printf(" → ");
    }
}

int main(void)
{
    /* 教材经典例子（6 个顶点，有向带权）
     *      0 --10--> 2 --1--> ...
     *      0 --4---> 1 --1--> 2 ...
     */
    int n = 6;
    int cost[MAXV][MAXV];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    /* 有向边 u → v，权 w */
    int raw[][3] = {
        {0, 2, 10}, {0, 4, 30}, {0, 5, 100},
        {1, 2, 5},
        {2, 3, 50},
        {3, 5, 10},
        {4, 3, 20}, {4, 5, 60}
    };
    int m = 8;

    for (int i = 0; i < m; i++) {
        cost[raw[i][0]][raw[i][1]] = raw[i][2];
    }

    printf("=== 有向图（6 顶点 8 条边）===\n");
    printf("  边：");
    for (int i = 0; i < m; i++)
        printf("%d→%d(%d) ", raw[i][0], raw[i][1], raw[i][2]);
    printf("\n  ⚠️ 顶点 1 没有入边，从 0 无法到达 1\n");

    printf("\n=== ① Dijkstra：求 0 到各点的最短距离 ===\n");
    int dist[MAXV], path[MAXV];
    dijkstra(cost, n, 0, dist, path);

    printf("\n=== ② 结果 ===\n");
    printf("  %-8s %-12s %s\n", "目标", "最短距离", "路径");
    printf("  ------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("  %-8d ", i);
        if (dist[i] >= INF) printf("%-12s 不可达\n", "INF");
        else {
            printf("%-12d ", dist[i]);
            printPath(path, 0, i);
            printf("\n");
        }
    }

    printf("\n  ⭐ 验证最短路 0→3：\n");
    printf("     直接走 0→3 没有边\n");
    printf("     0→2→3 = 10+50 = 60\n");
    printf("     0→4→3 = 30+20 = 50  ← 更短\n");
    printf("     程序结果 dist[3] = %d ✓\n", dist[3]);

    printf("\n=== ③ Dijkstra 的三个要点 ===\n");

    printf("  ① 贪心策略：每轮确定「当前最近」的点，之后不再改\n");
    printf("     ⭐ 这是它能工作的前提 —— 因为边权非负，\n");
    printf("        「绕远路」不可能比「直达」更近，所以最近的确定后不会变。\n");

    printf("\n  ② 松弛（relax）操作\n");
    printf("     if (dist[u] + cost[u][v] < dist[v]) dist[v] = dist[u] + cost[u][v];\n");
    printf("     ⭐ 这是所有最短路径算法的核心，只有这一行。\n");

    printf("\n  ③ 不能有负权边\n");
    printf("     负权会让「绕远路反而更近」，贪心失效。\n");
    printf("     有负权要用 Bellman-Ford（O(ne)）或 SPFA。\n");

    printf("\n=== ④ 复杂度 ===\n");
    printf("  %-26s %-16s %s\n", "实现方式", "复杂度", "适用");
    printf("  ------------------------------------------------------\n");
    printf("  %-26s %-16s %s\n", "邻接矩阵 + 线性找最小", "O(n^2)", "稠密图");
    printf("  %-26s %-16s %s\n", "邻接表 + 优先队列（堆）", "O((n+e)log n)", "稀疏图");
    printf("\n  ⭐ 软考按 O(n^2) 回答即可。\n");

    printf("\n=== ⑤ 一个常见误区 ===\n");
    printf("  Dijkstra 求的是「单源」最短路径（一个源点到所有点）。\n");
    printf("  求「所有点对」之间的最短路径，要对每个点跑一次 Dijkstra，\n");
    printf("  或者用 Floyd 算法 O(n^3)。\n");
    printf("  📌 软考选择题会区分：单源 → Dijkstra，全对 → Floyd。\n");

    return 0;
}
