/* ex212_list.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

#define MAXV 8

typedef struct EdgeNode {
    int             adjvex;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    EdgeNode *head[MAXV];
    int       n;
    int       e;
} ListGraph;

void lgInit(ListGraph *G, int n)
{
    G->n = n;
    G->e = 0;
    for (int i = 0; i < n; i++) G->head[i] = NULL;
}

static void addArc(ListGraph *G, int u, int v)
{
    EdgeNode *node = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (!node) return;
    node->adjvex = v;
    node->next = G->head[u];            /* 头插 */
    G->head[u] = node;
}

void lgAddEdge(ListGraph *G, int u, int v)
{
    addArc(G, u, v);
    addArc(G, v, u);                    /* 无向图双向 */
    G->e++;
}

int lgDegree(const ListGraph *G, int v)
{
    int d = 0;
    for (EdgeNode *p = G->head[v]; p; p = p->next) d++;
    return d;
}

void lgDestroy(ListGraph *G)
{
    for (int i = 0; i < G->n; i++) {
        EdgeNode *p = G->head[i];
        while (p) { EdgeNode *nx = p->next; free(p); p = nx; }
        G->head[i] = NULL;
    }
}

void lgPrint(const ListGraph *G)
{
    for (int i = 0; i < G->n; i++) {
        printf("  %d → ", i);
        for (EdgeNode *p = G->head[i]; p; p = p->next) {
            printf("%d", p->adjvex);
            if (p->next) printf(" → ");
        }
        printf("\n");
    }
}

int main(void)
{
    ListGraph G;
    lgInit(&G, 5);
    lgAddEdge(&G, 0, 1);
    lgAddEdge(&G, 0, 2);
    lgAddEdge(&G, 1, 3);
    lgAddEdge(&G, 2, 3);
    lgAddEdge(&G, 3, 4);

    printf("=== 邻接表（边 %d 条）===\n", G.e);
    lgPrint(&G);

    int nodes = 0;
    for (int i = 0; i < G.n; i++) nodes += lgDegree(&G, i);
    printf("\n  边节点 %d 个 = 2e = %d ✓\n", nodes, 2 * G.e);

    printf("\n=== 各顶点的度 ===\n  ");
    for (int v = 0; v < G.n; v++) printf("%d:%d  ", v, lgDegree(&G, v));
    printf("\n");

    printf("\n=== 注意：顺序是倒的 ===\n");
    printf("  0 的邻居打印成 2 → 1，因为用头插法。\n");
    printf("  如果想让顺序和输入一致，改成尾插（要维护尾指针）。\n");
    printf("  ⭐ 遍历时顺序不影响正确性，软考不纠结这点。\n");

    printf("\n=== 邻接表的特点 ===\n");
    printf("  1. 空间 O(n+e)，稀疏图省空间\n");
    printf("  2. 找「i 的所有邻居」很快，O(度)\n");
    printf("  3. 判断 i、j 是否相邻要遍历链表，O(度)\n");
    printf("  4. 无向图边节点数 = 2e（每条边存两次）\n");

    printf("\n=== 内存管理 ===\n");
    printf("  ⚠️ 每个边节点都是 malloc 的，销毁时必须全部 free。\n");
    printf("     否则 n 个顶点 e 条边就泄漏 2e 个节点。\n");

    lgDestroy(&G);
    printf("  已释放。\n");

    return 0;
}
