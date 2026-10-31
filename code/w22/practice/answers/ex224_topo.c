/* ex224_topo.c —— 参考答案 */

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

void gAddArc(Graph *G, int u, int v) { G->matrix[u][v] = 1; }

int topoSort(Graph *G, int order[])
{
    int indeg[MAXV];
    int q[MAXV];
    int front = 0, rear = 0;
    int cnt = 0;

    /* ① 算入度 */
    for (int i = 0; i < G->n; i++) indeg[i] = 0;
    for (int u = 0; u < G->n; u++)
        for (int v = 0; v < G->n; v++)
            if (G->matrix[u][v]) indeg[v]++;

    printf("  初始入度：");
    for (int i = 0; i < G->n; i++) printf("%d:%d ", i, indeg[i]);
    printf("\n");

    /* ② 入度为 0 的入队 */
    for (int i = 0; i < G->n; i++)
        if (indeg[i] == 0) q[rear++] = i;

    /* ③ 反复出队、减入度 */
    while (front < rear) {
        int u = q[front++];
        order[cnt++] = u;

        for (int v = 0; v < G->n; v++) {
            if (G->matrix[u][v]) {
                indeg[v]--;
                if (indeg[v] == 0) q[rear++] = v;
            }
        }
    }

    return (cnt == G->n) ? 1 : 0;       /* 输出数 == n → 无环 */
}

int main(void)
{
    /* ---------- 无环 ---------- */
    printf("=== 图 1：0→1 0→2 1→3 1→4 2→4 3→5 4→5 ===\n");
    Graph G1;
    gInit(&G1, 6);
    gAddArc(&G1, 0, 1); gAddArc(&G1, 0, 2);
    gAddArc(&G1, 1, 3); gAddArc(&G1, 1, 4);
    gAddArc(&G1, 2, 4);
    gAddArc(&G1, 3, 5); gAddArc(&G1, 4, 5);

    int order[MAXV];
    int ok = topoSort(&G1, order);
    printf("  拓扑序列：");
    for (int i = 0; i < G1.n; i++) {
        printf("%d", order[i]);
        if (i != G1.n - 1) printf(" → ");
    }
    printf("\n  结果：%s\n", ok ? "成功（无环）✓" : "失败");

    /* ---------- 有环 ---------- */
    printf("\n=== 图 2：0→1 1→2 2→0（成环）===\n");
    Graph G2;
    gInit(&G2, 3);
    gAddArc(&G2, 0, 1);
    gAddArc(&G2, 1, 2);
    gAddArc(&G2, 2, 0);

    int order2[MAXV];
    int ok2 = topoSort(&G2, order2);
    printf("  结果：%s\n", ok2 ? "成功" : "失败 → 有环 ✓");

    printf("\n=== 拓扑排序的两个用途 ===\n");
    printf("  1. 求任务的合法执行顺序（AOV 网）\n");
    printf("  2. 判断有向图有没有环（输出数 < n 即有环）\n");

    printf("\n=== 拓扑序列不唯一 ===\n");
    printf("  图 1 的序列 0 1 2 3 4 5 和 0 2 1 4 3 5 都合法。\n");
    printf("  因为入度为 0 的点谁先谁后都行。\n");
    printf("  📌 软考常问「下列哪个不是合法拓扑序列」，\n");
    printf("     判断标准：任何一个点出现时，它的所有前驱必须已经出现过。\n");

    return 0;
}
