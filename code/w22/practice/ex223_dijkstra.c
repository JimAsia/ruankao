/* ex223_dijkstra.c —— Dijkstra 求单源最短路径
 *
 * 要求：
 *   1. 用邻接矩阵存有向图
 *   2. dijkstra(cost, n, src, dist)：求 src 到各点的最短距离
 *   3. 输出距离表
 *
 * 测试图（5 个顶点，有向）：
 *   0→1(10)  0→3(30)  0→4(100)  1→2(50)  2→3(20)  2→4(10)  3→4(60)
 *
 * 期望（源点 0）：
 *   到 0 = 0
 *   到 1 = 10（直达）
 *   到 2 = 60（0→1→2）
 *   到 3 = 30（0→3）
 *   到 4 = 70（0→3→4，比 0→1→2→4=70 一样，比直达 100 短）
 *
 * 提示：
 *   初始化 dist[i] = cost[src][i]
 *   每轮找未确定里 dist 最小的 → 确定 → 松弛它的邻居
 */

#include <stdio.h>

#define MAXV 8
#define INF  99999

/* TODO 1：Dijkstra */
void dijkstra(int cost[MAXV][MAXV], int n, int src, int dist[])
{
    (void)cost; (void)n; (void)src; (void)dist;
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

    printf("=== 有向图：5 顶点 7 边 ===\n");
    for (int i = 0; i < 7; i++)
        printf("  %d→%d(%d)\n", raw[i][0], raw[i][1], raw[i][2]);

    /* TODO 2：调用 dijkstra，输出距离表，验证 10 60 30 70 */

    printf("\n=== 关键点 ===\n");
    printf("  1. 松弛：if (dist[u] + cost[u][v] < dist[v]) dist[v] = ...\n");
    printf("  2. 不能有负权边（负权会让贪心失效）\n");
    printf("  3. 复杂度 O(n^2)（邻接矩阵 + 线性找最小）\n");
    printf("  ⭐ 单源最短路径用 Dijkstra，全对最短路径用 Floyd O(n^3)。\n");

    return 0;
}
