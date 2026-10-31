/* ex216_components.c —— 参考答案 */

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

static void dfs(Graph *G, int v)
{
    visited[v] = 1;
    printf("%d ", v);
    for (int w = 0; w < G->n; w++) {
        if (G->matrix[v][w] && !visited[w]) dfs(G, w);
    }
}

int countComponents(Graph *G)
{
    int comp = 0;
    for (int v = 0; v < G->n; v++) {
        if (!visited[v]) {
            comp++;
            printf("  分量 %d：{ ", comp);
            dfs(G, v);
            printf("}\n");
        }
    }
    return comp;
}

int main(void)
{
    Graph G;
    gInit(&G, 7);
    gAddEdge(&G, 0, 1);
    gAddEdge(&G, 1, 2);
    gAddEdge(&G, 3, 4);

    for (int i = 0; i < G.n; i++) visited[i] = 0;

    printf("=== 图：0-1-2，3-4，5，6 ===\n");
    int c = countComponents(&G);
    printf("\n  连通分量数 = %d（期望 4）%s\n", c, c == 4 ? "✓" : "✗");

    printf("\n=== 关键点 ===\n");
    printf("  连通分量数 = 启动 DFS 的次数\n");
    printf("  ⭐ 判断图是否连通：分量数 == 1 则连通\n");

    printf("\n=== 生成森林的边数 ===\n");
    printf("  每个连通分量各有一棵生成树（k_i 个点有 k_i-1 条边）。\n");
    printf("  总边数 = (k1-1) + (k2-1) + ... = n - 分量数\n");
    printf("  本例：7 - 4 = %d 条边 ✓（0-1,1-2,3-4 共 3 条）\n", G.n - c);

    printf("\n=== 软考怎么考 ===\n");
    printf("  1. 给图问「有几个连通分量」\n");
    printf("  2. 给 n 个顶点、c 个分量的图，问生成森林有几条边 → n-c\n");
    printf("  3. 问「从 v 出发能否访问所有点」→ 看是否连通\n");

    return 0;
}
