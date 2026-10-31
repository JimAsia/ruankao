/* ex212_list.c —— 邻接表的基本操作
 *
 * 要求：
 *   1. 用邻接表建图：0-1, 0-2, 1-3, 2-3, 3-4
 *   2. 输出邻接表
 *   3. 求某个顶点的度
 *   4. 销毁释放内存
 *
 * 期望（头插法，顺序是倒的）：
 *   0 → 2 → 1
 *   1 → 3 → 0
 *   2 → 3 → 0
 *   3 → 4 → 2 → 1
 *   4 → 3
 *   边节点 10 个 = 2e
 *
 * 提示：
 *   每个顶点挂一个链表，头插法加节点
 *   无向图要加两条弧（u→v 和 v→u）
 */

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
    (void)G; (void)n;
}

/* TODO 1：加一条弧（u → v） */
static void addArc(ListGraph *G, int u, int v)
{
    (void)G; (void)u; (void)v;
}

/* TODO 2：无向图加边（两个方向） */
void lgAddEdge(ListGraph *G, int u, int v)
{
    (void)G; (void)u; (void)v;
}

/* TODO 3：求度（链表长度） */
int lgDegree(const ListGraph *G, int v)
{
    (void)G; (void)v;
    return 0;
}

/* TODO 4：销毁 */
void lgDestroy(ListGraph *G)
{
    (void)G;
}

/* 打印（已给出） */
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
    /* TODO 5：建图、输出、求度、销毁 */

    return 0;
}
