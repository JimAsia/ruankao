/* ex225_cycle.c —— 判断图有没有环
 *
 * 要求：
 *   1. hasCycleDirected(G)：判断【有向图】有没有环
 *      方法：DFS + 三色标记（白色未访问 / 灰色在栈上 / 黑色已完成）
 *      遇到灰色节点 = 有回边 = 有环
 *   2. hasCycleUndirected(G)：判断【无向图】有没有环
 *      方法：并查集，加边时如果两端已连通，说明会成环
 *
 * 测试：
 *   有向图 0→1 1→2 2→0  → 有环
 *   有向图 0→1 1→2 2→3  → 无环
 *   无向图 0-1 1-2 2-0  → 有环
 *   无向图 0-1 1-2      → 无环
 *
 * 提示：
 *   有向图判环不能用「访问过就说明有环」，
 *   因为 0→1、0→2、1→2 里 2 被访问两次但没环。
 *   必须区分「正在访问（灰色）」和「已访问完（黑色）」。
 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

/* 0=白（未访问）1=灰（在递归栈上）2=黑（已完成） */
static int color[MAXV];

void gInit(Graph *G, int n)
{
    G->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) G->matrix[i][j] = 0;
}

void gAddArc(Graph *G, int u, int v) { G->matrix[u][v] = 1; }
void gAddEdge(Graph *G, int u, int v)
{
    G->matrix[u][v] = 1;
    G->matrix[v][u] = 1;
}

/* TODO 1：有向图判环（三色标记） */
static int dfsCycle(Graph *G, int v)
{
    (void)G; (void)v;
    return 0;
}

int hasCycleDirected(Graph *G)
{
    for (int i = 0; i < G->n; i++) color[i] = 0;
    for (int v = 0; v < G->n; v++) {
        if (color[v] == 0 && dfsCycle(G, v)) return 1;
    }
    return 0;
}

/* TODO 2：无向图判环（并查集） */
static int parent[MAXV];

static int ufFind(int x)
{
    while (parent[x] != x) x = parent[x];
    return x;
}

int hasCycleUndirected(Graph *G)
{
    for (int i = 0; i < G->n; i++) parent[i] = i;

    for (int u = 0; u < G->n; u++) {
        for (int v = u + 1; v < G->n; v++) {
            if (!G->matrix[u][v]) continue;
            int ru = ufFind(u), rv = ufFind(v);
            if (ru == rv) return 1;         /* 已连通，这条边成环 */
            parent[ru] = rv;
        }
    }
    return 0;
}

int main(void)
{
    /* TODO 3：测四个用例，验证结果 */

    printf("\n=== 两种判环方法的区别 ===\n");
    printf("  有向图：DFS 三色标记（灰色回边 = 环）\n");
    printf("          也可以用拓扑排序：输出数 < n 即有环\n");
    printf("  无向图：并查集（加边时两端已连通 = 环）\n");
    printf("  ⭐ 无向图也能用 DFS：遇到「已访问且不是父亲」的点就是环。\n");

    return 0;
}
