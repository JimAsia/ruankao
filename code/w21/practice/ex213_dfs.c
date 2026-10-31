/* ex213_dfs.c —— DFS 深度优先遍历
 *
 * 要求：
 *   1. dfs(G, v)：递归实现，输出访问顺序
 *   2. 统计访问到的顶点数
 *   3. 用连通分量验证：图分两块时，从 0 出发只能访问到一块
 *
 * 测试图 1（连通）：
 *   0-1, 0-2, 1-3, 2-4, 3-4
 *   从 0 出发应该访问全部 5 个点
 *
 * 测试图 2（不连通）：
 *   0-1, 2-3, 4（孤立）
 *   从 0 出发只能访问 2 个点（0、1）
 *
 * 提示：
 *   访问 v → 标记 → 对每个未访问邻居递归
 */

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

/* TODO 1：DFS 递归 */
void dfs(Graph *G, int v)
{
    (void)G; (void)v;
}

int main(void)
{
    /* TODO 2：测试图 1（连通） */

    /* TODO 3：测试图 2（不连通），验证只能访问一部分 */

    printf("\n=== 关键点 ===\n");
    printf("  1. 必须用 visited 标记，否则有环会死循环\n");
    printf("  2. 非连通图从单点出发只能访问一个连通分量\n");
    printf("  3. 要遍历整张图，要循环所有顶点，每次对未访问的启动一次 DFS\n");

    return 0;
}
