/* ex216_components.c —— 求连通分量个数
 *
 * 要求：
 *   1. countComponents(G)：返回连通分量个数
 *   2. 同时输出每个分量包含哪些顶点
 *   3. 用 DFS 实现
 *
 * 测试图（7 个点）：
 *   0-1, 1-2   （分量 1）
 *   3-4        （分量 2）
 *   5          （分量 3，孤立点）
 *   6          （分量 4，孤立点）
 *
 * 期望：4 个连通分量
 *   {0 1 2} {3 4} {5} {6}
 *
 * 提示：
 *   循环所有顶点，每遇到一个未访问的就：
 *     分量数 +1，从这个点开始 DFS（把整个分量标记掉）
 *
 * ⭐ 这是「非连通图遍历」的标准写法，软考常考。
 */

#include <stdio.h>

#define MAXV 10

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

static int visited[MAXV];

void gInit(Graph *G, int n)
{
    G->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) G->matrix[i][j] = 0;
}

void gAddEdge(Graph *G, int u, int v)
{
    G->matrix[u][v] = 1;
    G->matrix[v][u] = 1;
}

/* TODO 1：DFS（把 v 所在的分量全部标记） */
static void dfs(Graph *G, int v)
{
    (void)G; (void)v;
}

/* TODO 2：求连通分量数，并输出每个分量 */
int countComponents(Graph *G)
{
    (void)G;
    return 0;
}

int main(void)
{
    Graph G;
    gInit(&G, 7);
    gAddEdge(&G, 0, 1);
    gAddEdge(&G, 1, 2);
    gAddEdge(&G, 3, 4);

    for (int i = 0; i < G.n; i++) visited[i] = 0;

    /* TODO 3：调用并输出结果、验证 */

    printf("\n=== 关键点 ===\n");
    printf("  连通分量数 = 启动 DFS 的次数\n");
    printf("  ⭐ 判断图是否连通：分量数 == 1 则连通\n");
    printf("  📌 生成树的意义：每个分量各有一棵生成树，\n");
    printf("     整个图的「生成森林」有 (n - 分量数) 条边。\n");

    return 0;
}
