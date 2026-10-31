/* ex224_topo.c —— 拓扑排序 + 判环
 *
 * 要求：
 *   1. topoSort(G, order)：Kahn 算法，返回 1 成功 / 0 有环
 *   2. 输出拓扑序列
 *
 * 测试图 1（课程依赖，无环）：
 *   0→1  0→2  1→3  1→4  2→4  3→5  4→5
 *   一个合法序列：0 1 2 3 4 5
 *
 * 测试图 2（有环）：
 *   0→1  1→2  2→0
 *   应报告「有环」
 *
 * 提示：
 *   ① 算所有点入度
 *   ② 入度为 0 的入队
 *   ③ 出队输出，后继入度减 1，减到 0 就入队
 *   ④ 输出个数 < n 说明有环
 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

void gInit(Graph *G, int n)
{
    G->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) G->matrix[i][j] = 0;
}

void gAddArc(Graph *G, int u, int v)
{
    G->matrix[u][v] = 1;
}

/* TODO 1：拓扑排序 */
int topoSort(Graph *G, int order[])
{
    (void)G; (void)order;
    return 0;
}

int main(void)
{
    /* TODO 2：测试图 1，输出序列 */

    /* TODO 3：测试图 2，验证报告有环 */

    return 0;
}
