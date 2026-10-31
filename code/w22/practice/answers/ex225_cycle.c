/* ex225_cycle.c —— 参考答案 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

static int color[MAXV];             /* 0=白 1=灰 2=黑 */

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

/* 有向图判环：DFS 三色 */
static int dfsCycle(Graph *G, int v)
{
    color[v] = 1;                       /* 标记为灰：正在递归栈上 */

    for (int w = 0; w < G->n; w++) {
        if (!G->matrix[v][w]) continue;

        if (color[w] == 1) return 1;    /* 遇到灰色 = 回边 = 有环 */
        if (color[w] == 0 && dfsCycle(G, w)) return 1;
    }

    color[v] = 2;                       /* 标记为黑：完成 */
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

/* 无向图判环：并查集 */
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
            if (ru == rv) return 1;     /* 已连通，这条边成环 */
            parent[ru] = rv;
        }
    }
    return 0;
}

int main(void)
{
    /* 用例 1：有向图有环 */
    Graph G1;
    gInit(&G1, 3);
    gAddArc(&G1, 0, 1); gAddArc(&G1, 1, 2); gAddArc(&G1, 2, 0);
    printf("有向图 0→1→2→0：%s\n", hasCycleDirected(&G1) ? "有环 ✓" : "无环");

    /* 用例 2：有向图无环 */
    Graph G2;
    gInit(&G2, 4);
    gAddArc(&G2, 0, 1); gAddArc(&G2, 1, 2); gAddArc(&G2, 2, 3);
    printf("有向图 0→1→2→3：%s\n", hasCycleDirected(&G2) ? "有环" : "无环 ✓");

    /* 用例 3：无向图有环 */
    Graph G3;
    gInit(&G3, 3);
    gAddEdge(&G3, 0, 1); gAddEdge(&G3, 1, 2); gAddEdge(&G3, 2, 0);
    printf("无向图 0-1-2-0：%s\n", hasCycleUndirected(&G3) ? "有环 ✓" : "无环");

    /* 用例 4：无向图无环（一棵树） */
    Graph G4;
    gInit(&G4, 3);
    gAddEdge(&G4, 0, 1); gAddEdge(&G4, 1, 2);
    printf("无向图 0-1-2（树）：%s\n", hasCycleUndirected(&G4) ? "有环" : "无环 ✓");

    printf("\n=== 为什么有向图不能用「访问过就说明有环」===\n");
    printf("  图：0→1、0→2、1→2\n");
    printf("  2 被访问了两次（从 1 和从 0），但没有环！\n");
    printf("  ⭐ 必须区分「正在访问（灰色）」和「已访问完（黑色）」。\n");
    printf("     只有遇到【灰色】节点，才说明走回了当前路径上，才有环。\n");

    printf("\n=== 有向图判环的两种方法 ===\n");
    printf("  1. DFS 三色标记 —— 遇到灰色即有环\n");
    printf("  2. 拓扑排序 —— 输出顶点数 < n 即有环\n");

    printf("\n=== 无向图判环的两种方法 ===\n");
    printf("  1. 并查集 —— 加边时两端已连通即有环\n");
    printf("  2. DFS —— 遇到「已访问且不是父亲」的点即有环\n");

    return 0;
}
