/* ex211_matrix.c —— 参考答案 */

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

void gAddEdge(Graph *G, int u, int v)
{
    G->matrix[u][v] = 1;
    G->matrix[v][u] = 1;                /* 无向图：对称 */
    G->e++;
}

int gDegree(const Graph *G, int v)
{
    int d = 0;
    for (int j = 0; j < G->n; j++) {
        if (G->matrix[v][j]) d++;
    }
    return d;
}

int gAdjacent(const Graph *G, int u, int v)
{
    return G->matrix[u][v] != 0;
}

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
    Graph G;
    gInit(&G, 5);
    gAddEdge(&G, 0, 1);
    gAddEdge(&G, 0, 2);
    gAddEdge(&G, 1, 3);
    gAddEdge(&G, 2, 3);
    gAddEdge(&G, 3, 4);

    printf("=== 邻接矩阵（顶点 5，边 %d）===\n", G.e);
    gPrint(&G);

    printf("\n=== 各顶点的度 ===\n  ");
    int sum = 0;
    for (int v = 0; v < G.n; v++) {
        int d = gDegree(&G, v);
        sum += d;
        printf("%d:%d  ", v, d);
    }
    printf("\n  度之和 = %d = 2×边数 = %d ✓\n", sum, 2 * G.e);

    printf("\n=== 判断相邻 ===\n");
    printf("  0 和 1 相邻？%s\n", gAdjacent(&G, 0, 1) ? "是 ✓" : "否");
    printf("  0 和 4 相邻？%s\n", gAdjacent(&G, 0, 4) ? "是" : "否 ✓");

    printf("\n=== 两个必背结论 ===\n");
    printf("  无向图：所有顶点的度之和 = 2 × 边数\n");
    printf("         因为每条边被两个端点各算一次。\n");
    printf("  有向图：入度之和 = 出度之和 = 边数\n");
    printf("         每条边贡献 1 个出度、1 个入度。\n");

    printf("\n=== 邻接矩阵的特点 ===\n");
    printf("  1. 空间 O(n^2)，和边数无关 → 稀疏图很浪费\n");
    printf("  2. 判断 i、j 是否相邻 O(1) → 最快\n");
    printf("  3. 无向图的矩阵沿对角线对称\n");
    printf("  4. 第 i 行非零个数 = 顶点 i 的度\n");

    return 0;
}
