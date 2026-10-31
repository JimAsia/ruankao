/* ex221_prim.c —— Prim 算法求最小生成树
 *
 * 要求：
 *   1. 用邻接矩阵存图
 *   2. prim(cost, n)：从顶点 0 出发，输出选中的边和总权值
 *
 * 测试图（5 个顶点）：
 *   0-1(2)  0-3(6)  1-2(3)  1-3(8)  1-4(5)  2-4(7)  3-4(9)
 *   期望总权值 = 2+3+5+6 = 16
 *   选中的边：0-1(2) 1-2(3) 1-4(5) 0-3(6)
 *
 * 提示：
 *   lowcost[i] = i 到已选集合的最小边权
 *   每轮找 lowcost 最小的未访问点 → 加入 → 更新 lowcost
 *   ⚠️ 初始化时 lowcost[i] = cost[0][i]（从 0 出发）
 */

#include <stdio.h>

#define MAXV 8
#define INF  99999

/* TODO 1：Prim，返回总权值 */
int prim(int cost[MAXV][MAXV], int n)
{
    (void)cost; (void)n;
    return 0;
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

    printf("=== 图：5 顶点 7 边 ===\n");
    for (int i = 0; i < 7; i++)
        printf("  %d-%d(%d)\n", raw[i][0], raw[i][1], raw[i][2]);

    /* TODO 2：调用 prim 并输出结果，验证是 16 */

    printf("\n=== 生成树性质 ===\n");
    printf("  n 个顶点的生成树有 n-1 条边，本例 %d 条。\n", n - 1);

    return 0;
}
