/* 211_graph_store.c —— 图的两种存储结构：邻接矩阵 vs 邻接表
 *
 * 图 G = (V, E)：V 是顶点集，E 是边集。比树更一般（可以有环、有多个前驱）。
 *
 * 两种存储：
 *   邻接矩阵：二维数组，matrix[i][j] = 1 表示 i、j 相邻
 *   邻接表：每个顶点挂一条链表，存它的所有邻接点
 *
 * 两者的取舍是软考必考：
 *   矩阵：空间 O(n^2)，判断「i 和 j 是否相邻」O(1)
 *   表  ：空间 O(n+e)，找「i 的所有邻居」快，判断相邻要遍历
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXV 8

/* ==================== ① 邻接矩阵 ==================== */
typedef struct {
    int matrix[MAXV][MAXV];
    int n;                          /* 顶点数 */
    int e;                          /* 边数 */
} MatrixGraph;

void mgInit(MatrixGraph *G, int n)
{
    G->n = n;
    G->e = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G->matrix[i][j] = 0;
}

/* 无向图加边：对称位置都要置 1 */
void mgAddEdge(MatrixGraph *G, int u, int v, int w)
{
    G->matrix[u][v] = w;
    G->matrix[v][u] = w;            /* 有向图就删掉这一行 */
    G->e++;
}

void mgPrint(const MatrixGraph *G)
{
    printf("  邻接矩阵：\n     ");
    for (int j = 0; j < G->n; j++) printf(" %d", j);
    printf("\n");
    for (int i = 0; i < G->n; i++) {
        printf("   %d ", i);
        for (int j = 0; j < G->n; j++) printf(" %d", G->matrix[i][j] ? 1 : 0);
        printf("\n");
    }
    printf("  顶点 %d 个，边 %d 条，占用 %d 个 int（%d 字节）\n",
           G->n, G->e, G->n * G->n, (int)(G->n * G->n * sizeof(int)));
}

/* 求某个顶点的度（无向图：那一行有几个 1） */
int mgDegree(const MatrixGraph *G, int v)
{
    int deg = 0;
    for (int j = 0; j < G->n; j++) {
        if (G->matrix[v][j]) deg++;
    }
    return deg;
}

/* ==================== ② 邻接表 ==================== */
typedef struct EdgeNode {
    int             adjvex;         /* 邻接点编号 */
    int             weight;         /* 权值 */
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    EdgeNode *head[MAXV];           /* 每个顶点的链表头 */
    int       n;
    int       e;
} ListGraph;

void lgInit(ListGraph *G, int n)
{
    G->n = n;
    G->e = 0;
    for (int i = 0; i < n; i++) G->head[i] = NULL;
}

/* 头插法加一条边 */
static void addArc(ListGraph *G, int u, int v, int w)
{
    EdgeNode *node = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (!node) return;
    node->adjvex = v;
    node->weight = w;
    node->next = G->head[u];
    G->head[u] = node;
}

void lgAddEdge(ListGraph *G, int u, int v, int w)
{
    addArc(G, u, v, w);
    addArc(G, v, u, w);             /* 无向图：双向都加 */
    G->e++;
}

void lgPrint(const ListGraph *G)
{
    printf("  邻接表：\n");
    for (int i = 0; i < G->n; i++) {
        printf("   %d → ", i);
        for (EdgeNode *p = G->head[i]; p; p = p->next) {
            printf("%d", p->adjvex);
            if (p->next) printf(" → ");
        }
        printf("\n");
    }
    int nodes = 0;
    for (int i = 0; i < G->n; i++) {
        for (EdgeNode *p = G->head[i]; p; p = p->next) nodes++;
    }
    printf("  顶点 %d 个，边 %d 条，边节点 %d 个（无向图 = 2e）\n",
           G->n, G->e, nodes);
}

void lgDestroy(ListGraph *G)
{
    for (int i = 0; i < G->n; i++) {
        EdgeNode *p = G->head[i];
        while (p) { EdgeNode *nx = p->next; free(p); p = nx; }
        G->head[i] = NULL;
    }
}

int main(void)
{
    /* 图的结构：
     *      0 --- 1
     *      |     |
     *      2 --- 3 --- 4 --- 5
     */
    int edges[][2] = {{0,1},{0,2},{1,3},{2,3},{3,4},{4,5}};
    int ne = 6;
    int n = 6;

    printf("=== 图的结构 ===\n");
    printf("      0 --- 1\n");
    printf("      |     |\n");
    printf("      2 --- 3 --- 4 --- 5\n");
    printf("  顶点 6 个，边 6 条\n");

    /* ---------- 邻接矩阵 ---------- */
    printf("\n=== ① 邻接矩阵 ===\n");
    MatrixGraph MG;
    mgInit(&MG, n);
    for (int i = 0; i < ne; i++) mgAddEdge(&MG, edges[i][0], edges[i][1], 1);
    mgPrint(&MG);

    printf("\n  各顶点的度：");
    int sumDeg = 0;
    for (int v = 0; v < n; v++) {
        int d = mgDegree(&MG, v);
        sumDeg += d;
        printf("%d:%d  ", v, d);
    }
    printf("\n  ⭐ 所有顶点的度之和 = %d = 2×边数 = %d ✓\n", sumDeg, 2 * ne);

    /* ---------- 邻接表 ---------- */
    printf("\n=== ② 邻接表 ===\n");
    ListGraph LG;
    lgInit(&LG, n);
    for (int i = 0; i < ne; i++) lgAddEdge(&LG, edges[i][0], edges[i][1], 1);
    lgPrint(&LG);

    printf("\n  ⭐ 注意邻接表的顺序是【倒的】（头插法），\n");
    printf("     所以 0 的邻居打印成 2 → 1，而不是 1 → 2。\n");
    printf("     这没关系，遍历时顺序不影响正确性。\n");

    /* ---------- 两种存储对比 ---------- */
    printf("\n=== ③ 两种存储对比 ===\n");
    printf("  %-16s %-18s %s\n", "对比项", "邻接矩阵", "邻接表");
    printf("  --------------------------------------------------------------------\n");
    printf("  %-16s %-18s %s\n", "空间", "O(n^2)", "O(n+e)");
    printf("  %-16s %-18s %s\n", "判断 i,j 相邻", "O(1)", "O(度)");
    printf("  %-16s %-18s %s\n", "找 i 的所有邻居", "O(n)", "O(度)");
    printf("  %-16s %-18s %s\n", "适合", "稠密图", "稀疏图");
    printf("  %-16s %-18s %s\n", "实现难度", "简单", "要指针");
    printf("\n  ⭐ 稠密图（边多）用矩阵，稀疏图（边少）用表。\n");
    printf("     本例 n=6, e=6：矩阵 36 个格子，表只要 12 个边节点。\n");

    /* ---------- 完全图 ---------- */
    printf("\n=== ④ 完全图的边数（必背）===\n");
    printf("  %-12s %-20s %s\n", "顶点数 n", "无向完全图", "有向完全图");
    printf("  --------------------------------------------------\n");
    for (int k = 3; k <= 6; k++) {
        printf("  %-12d n(n-1)/2 = %-8d n(n-1) = %d\n",
               k, k * (k - 1) / 2, k * (k - 1));
    }
    printf("\n  ⭐ 无向完全图：每对顶点之间一条边 → n(n-1)/2\n");
    printf("     有向完全图：每对顶点两条边（双向）→ n(n-1)\n");
    printf("     📌 这两个公式软考几乎每年都考。\n");

    lgDestroy(&LG);
    return 0;
}
