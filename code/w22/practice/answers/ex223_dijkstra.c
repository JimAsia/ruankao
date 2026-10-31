/* ex223_dijkstra.c —— 参考答案 */

#include <stdio.h>

#define MAXV 8
#define INF  99999

void dijkstra(int cost[MAXV][MAXV], int n, int src, int dist[])
{
    int visited[MAXV];

    for (int i = 0; i < n; i++) {
        dist[i] = cost[src][i];
        visited[i] = 0;
    }
    dist[src] = 0;
    visited[src] = 1;

    for (int round = 1; round < n; round++) {
        /* 找未确定里 dist 最小的 */
        int u = -1, minVal = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minVal) {
                minVal = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        printf("    确定 %d（dist=%d）", u, minVal);

        /* 松弛邻居 */
        int changed = 0;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] < INF) {
                if (dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    if (!changed) printf("  →  更新：");
                    printf("%d=%d ", v, dist[v]);
                    changed = 1;
                }
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int n = 5;
    int cost[MAXV][MAXV];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    int raw[][3] = {
        {0,1,10},{0,3,30},{0,4,100},{1,2,50},{2,3,20},{2,4,10},{3,4,60}
    };
    for (int i = 0; i < 7; i++) cost[raw[i][0]][raw[i][1]] = raw[i][2];

    printf("=== 有向图：0→1(10) 0→3(30) 0→4(100) 1→2(50) 2→3(20) 2→4(10) 3→4(60) ===\n\n");

    int dist[MAXV];
    dijkstra(cost, n, 0, dist);

    printf("\n=== 结果（源点 0）===\n");
    printf("  %-8s %s\n", "目标", "最短距离");
    printf("  ------------------\n");
    for (int i = 0; i < n; i++) {
        printf("  %-8d %d\n", i, dist[i]);
    }

    printf("\n=== 手算验证 ===\n");
    printf("  到 1：直达 10 ✓\n");
    printf("  到 2：0→1→2 = 10+50 = 60 ✓\n");
    printf("  到 3：0→3 直达 30 ✓\n");
    printf("  到 4：0→4 直达 100，但 0→3→4 = 30+60 = 90，0→1→2→4 = 10+50+10 = 70\n");
    printf("        最短是 70 ✓\n");

    printf("\n=== 松弛的核心一行 ===\n");
    printf("  if (dist[u] + cost[u][v] < dist[v]) dist[v] = dist[u] + cost[u][v];\n");
    printf("  ⭐ 全部最短路径算法（Dijkstra/Bellman-Ford/Floyd）都有这一句。\n");

    printf("\n=== 三种最短路径算法 ===\n");
    printf("  %-18s %-14s %-16s %s\n", "算法", "复杂度", "解决什么", "负权");
    printf("  ----------------------------------------------------------------------\n");
    printf("  %-18s %-14s %-16s %s\n", "Dijkstra", "O(n^2)", "单源最短路径", "不支持");
    printf("  %-18s %-14s %-16s %s\n", "Bellman-Ford", "O(ne)", "单源 + 判负环", "支持");
    printf("  %-18s %-14s %-16s %s\n", "Floyd", "O(n^3)", "所有点对", "支持");

    printf("\n  ⭐ 软考选择题区分：\n");
    printf("     「单源」→ Dijkstra（无权图也可用 BFS）\n");
    printf("     「所有顶点对」→ Floyd\n");

    return 0;
}
