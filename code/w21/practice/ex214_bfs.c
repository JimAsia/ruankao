/* ex214_bfs.c —— BFS 广度优先遍历 + 求最短跳数
 *
 * 要求：
 *   1. bfs(G, start)：用队列实现，输出访问顺序和每个点的层数
 *   2. 层数就是「从起点到该点的最少边数」
 *
 * 测试图（5 个点）：
 *   0-1, 0-2, 1-3, 2-3, 3-4
 *   从 0 出发：
 *     第 0 层：0
 *     第 1 层：1 2
 *     第 2 层：3
 *     第 3 层：4
 *
 * 提示：
 *   起点入队并标记
 *   循环：出队 → 访问 → 所有未访问邻居「标记 + 记层数 + 入队」
 *   ⚠️ 标记必须在入队时做，不是出队时
 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

static int visited[MAXV];
static int dist[MAXV];

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

/* TODO 1：BFS */
void bfs(Graph *G, int start)
{
    (void)G; (void)start;
}

int main(void)
{
    Graph G;
    gInit(&G, 5);
    gAddEdge(&G, 0, 1);
    gAddEdge(&G, 0, 2);
    gAddEdge(&G, 1, 3);
    gAddEdge(&G, 2, 3);
    gAddEdge(&G, 3, 4);

    for (int i = 0; i < G.n; i++) { visited[i] = 0; dist[i] = -1; }

    /* TODO 2：BFS 遍历，输出每点层数 */

    /* TODO 3：输出「0 到 4 的最短跳数」 */

    printf("\n=== BFS 的用途 ===\n");
    printf("  1. 无权图的最短路径（最少边数）\n");
    printf("  2. 按层处理（如二叉树层序、社交网络几度好友）\n");
    printf("  ⭐ 有权的图求最短路径不能用 BFS，要用 Dijkstra。\n");

    return 0;
}
