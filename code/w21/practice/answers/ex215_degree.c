/* ex215_degree.c —— 参考答案 */

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

void gAddArc(Graph *G, int u, int v)
{
    G->matrix[u][v] = 1;                /* 只置一个方向 = 有向 */
    G->e++;
}

int outDegree(const Graph *G, int v)
{
    int d = 0;
    for (int j = 0; j < G->n; j++) if (G->matrix[v][j]) d++;
    return d;
}

int inDegree(const Graph *G, int v)
{
    int d = 0;
    for (int i = 0; i < G->n; i++) if (G->matrix[i][v]) d++;
    return d;
}

int main(void)
{
    Graph G;
    gInit(&G, 5);
    gAddArc(&G, 0, 1);
    gAddArc(&G, 0, 2);
    gAddArc(&G, 1, 3);
    gAddArc(&G, 2, 3);
    gAddArc(&G, 3, 4);
    gAddArc(&G, 4, 0);

    printf("=== 有向图：0→1 0→2 1→3 2→3 3→4 4→0 ===\n");
    printf("  边数 = %d\n\n", G.e);

    printf("  %-8s %-10s %s\n", "顶点", "入度", "出度");
    printf("  --------------------------\n");
    int sumIn = 0, sumOut = 0;
    for (int v = 0; v < G.n; v++) {
        int in = inDegree(&G, v);
        int out = outDegree(&G, v);
        sumIn += in;
        sumOut += out;
        printf("  %-8d %-10d %d\n", v, in, out);
    }

    printf("\n  入度之和 = %d，出度之和 = %d，边数 = %d\n",
           sumIn, sumOut, G.e);
    printf("  验证：%s\n",
           (sumIn == G.e && sumOut == G.e) ? "两者都等于边数 ✓" : "不等 ✗");

    printf("\n=== 必背的两个结论 ===\n");
    printf("  无向图：所有顶点的【度】之和 = 2 × 边数\n");
    printf("         因为每条边被两个端点各数一次。\n");
    printf("  有向图：【入度】之和 = 【出度】之和 = 边数\n");
    printf("         每条边贡献 1 个出度 + 1 个入度。\n");
    printf("  📌 软考选择题常考这两个等式。\n");

    printf("\n=== 入度的用处 ===\n");
    printf("  拓扑排序就是反复找「入度为 0」的顶点。\n");
    printf("  入度为 0 = 没有前置任务 = 可以开始做。\n");

    return 0;
}
