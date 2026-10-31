/* ex213_dfs.c —— 参考答案 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

static int visited[MAXV];
static int count_ = 0;

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

void resetVisited(int n)
{
    for (int i = 0; i < n; i++) visited[i] = 0;
    count_ = 0;
}

void dfs(Graph *G, int v)
{
    visited[v] = 1;
    count_++;
    printf("%d ", v);

    for (int w = 0; w < G->n; w++) {
        if (G->matrix[v][w] && !visited[w]) {
            dfs(G, w);
        }
    }
}

int main(void)
{
    /* ---------- 测试图 1：连通 ---------- */
    printf("=== 测试 1：连通图 0-1 0-2 1-3 2-4 3-4 ===\n");
    Graph G1;
    gInit(&G1, 5);
    gAddEdge(&G1, 0, 1);
    gAddEdge(&G1, 0, 2);
    gAddEdge(&G1, 1, 3);
    gAddEdge(&G1, 2, 4);
    gAddEdge(&G1, 3, 4);

    resetVisited(G1.n);
    printf("  从 0 出发：");
    dfs(&G1, 0);
    printf("\n  访问了 %d 个点（共 5 个）→ %s\n",
           count_, count_ == G1.n ? "全部连通 ✓" : "未访问完");

    /* ---------- 测试图 2：不连通 ---------- */
    printf("\n=== 测试 2：不连通图 0-1 2-3 4(孤立) ===\n");
    Graph G2;
    gInit(&G2, 5);
    gAddEdge(&G2, 0, 1);
    gAddEdge(&G2, 2, 3);

    resetVisited(G2.n);
    printf("  从 0 出发：");
    dfs(&G2, 0);
    printf("\n  访问了 %d 个点（共 5 个）→ 只走了一个分量\n", count_);

    printf("  从 2 出发：");
    resetVisited(G2.n);
    dfs(&G2, 2);
    printf("\n  访问了 %d 个点\n", count_);

    printf("\n  ⭐ 从单个点出发只能访问「一个连通分量」。\n");
    printf("     遍历整张图必须循环所有顶点。\n");

    printf("\n=== DFS 的特点 ===\n");
    printf("  1. 一条路走到底，走不通再回退（回溯）\n");
    printf("  2. 用递归或显式栈实现\n");
    printf("  3. 复杂度：矩阵 O(n^2)，邻接表 O(n+e)\n");
    printf("  4. 用途：判连通、找连通分量、拓扑排序、判环\n");

    return 0;
}
