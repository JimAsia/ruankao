/* ex215_degree.c —— 有向图的入度与出度
 *
 * 要求：
 *   1. 建有向图：0→1, 0→2, 1→3, 2→3, 3→4, 4→0
 *   2. 求每个顶点的入度和出度
 *   3. 验证：所有顶点的入度之和 = 出度之和 = 边数
 *
 * 期望：
 *   顶点  入度  出度
 *     0    1     2
 *     1    1     1
 *     2    1     1
 *     3    2     1
 *     4    1     1
 *   入度之和 = 6，出度之和 = 6，边数 = 6 ✓
 *
 * 提示：
 *   出度 = 那一行有几个 1
 *   入度 = 那一列有几个 1
 *
 * ⭐ 无向图里「度之和 = 2e」，有向图里「入度和 = 出度和 = e」。
 *    这两个结论软考都考。
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
    G->n = n;
    G->e = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) G->matrix[i][j] = 0;
}

/* TODO 1：加一条有向边 u→v（只置一个方向） */
void gAddArc(Graph *G, int u, int v)
{
    (void)G; (void)u; (void)v;
}

/* TODO 2：出度 */
int outDegree(const Graph *G, int v)
{
    (void)G; (void)v;
    return 0;
}

/* TODO 3：入度 */
int inDegree(const Graph *G, int v)
{
    (void)G; (void)v;
    return 0;
}

int main(void)
{
    /* TODO 4：建图，输出入度出度表，验证和 = 边数 */

    return 0;
}
