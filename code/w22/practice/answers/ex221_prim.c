/* ex221_prim.c —— 参考答案 */

#include <stdio.h>

#define MAXV 8
#define INF  99999

int prim(int cost[MAXV][MAXV], int n)
{
    int lowcost[MAXV];
    int visited[MAXV];
    int total = 0;

    for (int i = 0; i < n; i++) {
        lowcost[i] = cost[0][i];        /* 从 0 出发 */
        visited[i] = 0;
    }
    visited[0] = 1;

    printf("  从顶点 0 开始\n");

    for (int round = 1; round < n; round++) {
        /* 找 lowcost 最小的未访问点 */
        int minIdx = -1, minVal = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && lowcost[i] < minVal) {
                minVal = lowcost[i];
                minIdx = i;
            }
        }
        if (minIdx == -1) { printf("  图不连通\n"); return -1; }

        printf("    第 %d 步：加入顶点 %d，边权 %d\n", round, minIdx, minVal);
        visited[minIdx] = 1;
        total += minVal;

        /* 用新点更新 lowcost */
        for (int i = 0; i < n; i++) {
            if (!visited[i] && cost[minIdx][i] < lowcost[i]) {
                lowcost[i] = cost[minIdx][i];
            }
        }
    }
    return total;
}

int main(void)
{
    int n = 5;
    int cost[MAXV][MAXV];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    int raw[][3] = {
        {0,1,2},{0,3,6},{1,2,3},{1,3,8},{1,4,5},{2,4,7},{3,4,9}
    };
    for (int i = 0; i < 7; i++) {
        int u = raw[i][0], v = raw[i][1], w = raw[i][2];
        cost[u][v] = w;
        cost[v][u] = w;
    }

    printf("=== 图：0-1(2) 0-3(6) 1-2(3) 1-3(8) 1-4(5) 2-4(7) 3-4(9) ===\n\n");
    int total = prim(cost, n);
    printf("\n  最小生成树总权值 = %d（期望 16）%s\n",
           total, total == 16 ? "✓" : "✗");

    printf("\n=== 手算验证 ===\n");
    printf("  从 0 开始，能选的最小边是 0-1(2)\n");
    printf("  加入 1 后，可选 0-3(6) 1-2(3) 1-4(5) 1-3(8) → 选 1-2(3)\n");
    printf("  加入 2 后，可选 0-3(6) 1-4(5) 2-4(7) → 选 1-4(5)\n");
    printf("  加入 4 后，可选 0-3(6) 3-4(9) → 选 0-3(6)\n");
    printf("  共 5-1 = 4 条边，总权 2+3+5+6 = 16 ✓\n");

    printf("\n=== Prim 的三个要点 ===\n");
    printf("  1. 只用「点」的角度：维护 lowcost（到已选集合的最小边权）\n");
    printf("  2. 每轮 O(n) 找最小，共 n-1 轮 → O(n^2)\n");
    printf("  3. 天然不会成环（每次只连一个新点）\n");

    printf("\n=== 为什么 Prim 适合稠密图 ===\n");
    printf("  复杂度 O(n^2) 只和顶点数有关，和边数无关。\n");
    printf("  稠密图的边数接近 n^2，用 Prim 比 O(e log e) 的 Kruskal 快。\n");

    return 0;
}
