/* ex211_matrix.c —— 邻接矩阵的基本操作
 *
 * 要求：
 *   1. 建图（无向、无权）：0-1, 0-2, 1-3, 2-3, 3-4
 *   2. 输出邻接矩阵
 *   3. 求每个顶点的度
 *   4. 判断两点是否相邻
 *
 * 期望：
 *   顶点 5 个，边 5 条
 *   各点度数：0:2  1:2  2:2  3:3  4:1
 *   度之和 = 10 = 2×5 ✓
 *   0 和 1 相邻？是    0 和 4 相邻？否
 *
 * 提示：
 *   无向图 matrix[u][v] = matrix[v][u] = 1
 *   度 = 那一行有几个 1
 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
    int e;
} Graph;

void gInit(Graph *G, int n)
{
    (void)G; (void)n;
}

/* TODO 1：加边 */
void gAddEdge(Graph *G, int u, int v)
{
    (void)G; (void)u; (void)v;
}

/* TODO 2：求度 */
int gDegree(const Graph *G, int v)
{
    (void)G; (void)v;
    return 0;
}

/* TODO 3：判断相邻 */
int gAdjacent(const Graph *G, int u, int v)
{
    (void)G; (void)u; (void)v;
    return 0;
}

/* 打印矩阵（已给出） */
void gPrint(const Graph *G)
{
    printf("   ");
    for (int j = 0; j < G->n; j++) printf("%2d", j);
    printf("\n");
    for (int i = 0; i < G->n; i++) {
        printf("%2d ", i);
        for (int j = 0; j < G->n; j++) printf("%2d", G->matrix[i][j]);
        printf("\n");
    }
}

int main(void)
{
    /* TODO 4：建图并输出 */

    /* TODO 5：输出各点度数和度之和，验证 = 2e */

    /* TODO 6：判断 0-1 和 0-4 是否相邻 */

    return 0;
}
