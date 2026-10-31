/* ex214_bfs.c —— 参考答案 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

static int visited[MAXV];
static int dist[MAXV];

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

void bfs(Graph *G, int start)
{
    int q[MAXV];
    int front = 0, rear = 0;

    visited[start] = 1;
    dist[start] = 0;                    /* 起点层数 0 */
    q[rear++] = start;

    while (front < rear) {
        int v = q[front++];             /* 出队 */
        printf("%d(第%d层) ", v, dist[v]);

        for (int w = 0; w < G->n; w++) {
            if (G->matrix[v][w] && !visited[w]) {
                visited[w] = 1;         /* ⚠️ 入队时就标记 */
                dist[w] = dist[v] + 1;  /* 层数 = 上一层 + 1 */
                q[rear++] = w;
            }
        }
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

    for (int i = 0; i < G.n; i++) { visited[i] = 0; dist[i] = -1; }

    printf("=== 图：0-1 0-2 1-3 2-3 3-4 ===\n");
    printf("  从 0 出发 BFS：");
    bfs(&G, 0);
    printf("\n");

    printf("\n=== 层数 = 最短跳数 ===\n");
    for (int i = 0; i < G.n; i++) {
        printf("  0 → %d 最少 %d 条边\n", i, dist[i]);
    }

    printf("\n  ⭐ 验证 0→4：0-1-3-4 或 0-2-3-4，都是 3 条边。\n");
    printf("     程序算出 dist[4] = %d ✓\n", dist[4]);

    printf("\n=== 为什么 BFS 能求最短跳数 ===\n");
    printf("  BFS 按层扩展：先访问所有距离 1 的，再距离 2 的……\n");
    printf("  所以第一次访问到某个点时，走的边数一定最少。\n");
    printf("  ⭐ 前提是【无权图】（或每边权相等）。\n");
    printf("     有权图求最短路径要用 Dijkstra。\n");

    printf("\n=== 标记时机为什么关键 ===\n");
    printf("  ✅ 入队时标记：每个点只入队一次\n");
    printf("  ❌ 出队时标记：同一点可能被多个邻居重复入队，\n");
    printf("     队列膨胀，层数也可能被后入队的覆盖成更大的值。\n");

    return 0;
}
