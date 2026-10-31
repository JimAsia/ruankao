/* 212_graph_traversal.c —— 图的两种遍历：DFS 与 BFS
 *
 * DFS（深度优先）：一条路走到底，走不通再回退 —— 用递归或【栈】
 * BFS（广度优先）：一层一层往外扩 —— 用【队列】
 *
 * 两者都要「标记已访问」，否则有环的图会死循环。
 *
 * 复杂度：
 *   邻接矩阵：O(n^2)   —— 每个顶点都要扫一整行
 *   邻接表  ：O(n+e)   —— 每个顶点和每条边访问常数次
 */

#include <stdio.h>

#define MAXV 8

/* 用邻接矩阵存图，简单直观 */
typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} Graph;

static int g_visited[MAXV];
static int g_order[MAXV];       /* 记录访问顺序 */
static int g_cnt = 0;
static long long g_ops = 0;     /* 统计「检查邻接关系」的次数 */

void gInit(Graph *G, int n)
{
    G->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G->matrix[i][j] = 0;
}

void gAddEdge(Graph *G, int u, int v)
{
    G->matrix[u][v] = 1;
    G->matrix[v][u] = 1;
}

static void reset(int n)
{
    for (int i = 0; i < n; i++) g_visited[i] = 0;
    g_cnt = 0;
    g_ops = 0;
}

/* ==================== ① DFS（递归）==================== */
static void dfsRec(Graph *G, int v)
{
    g_visited[v] = 1;
    g_order[g_cnt++] = v;
    printf("%d ", v);

    for (int w = 0; w < G->n; w++) {
        g_ops++;
        if (G->matrix[v][w] && !g_visited[w]) {
            dfsRec(G, w);
        }
    }
}

/* ==================== ② DFS（显式栈）==================== */
/* 和递归版等价，只是把「系统栈」换成「自己管理的栈」 */
static void dfsStack(Graph *G, int start)
{
    int stack[MAXV * MAXV];
    int top = -1;

    stack[++top] = start;

    while (top >= 0) {
        int v = stack[top--];               /* 出栈 */
        if (g_visited[v]) continue;         /* 可能重复入栈，跳过 */

        g_visited[v] = 1;
        g_order[g_cnt++] = v;
        printf("%d ", v);

        /* 逆序压栈，保证出栈时按编号从小到大访问 */
        for (int w = G->n - 1; w >= 0; w--) {
            g_ops++;
            if (G->matrix[v][w] && !g_visited[w]) {
                stack[++top] = w;
            }
        }
    }
}

/* ==================== ③ BFS（队列）==================== */
static void bfs(Graph *G, int start)
{
    int q[MAXV * MAXV];
    int front = 0, rear = 0;
    int dist[MAXV];                         /* 记录层数（最短跳数） */

    for (int i = 0; i < G->n; i++) dist[i] = -1;

    g_visited[start] = 1;
    dist[start] = 0;
    q[rear++] = start;

    while (front < rear) {
        int v = q[front++];                 /* 出队 */
        g_order[g_cnt++] = v;
        printf("%d(%d) ", v, dist[v]);

        for (int w = 0; w < G->n; w++) {
            g_ops++;
            if (G->matrix[v][w] && !g_visited[w]) {
                g_visited[w] = 1;           /* ⚠️ 入队时就标记，不是出队时 */
                dist[w] = dist[v] + 1;
                q[rear++] = w;
            }
        }
    }
}

int main(void)
{
    /* 图：
     *      0 --- 1
     *      |     |
     *      2 --- 3 --- 4 --- 5
     */
    Graph G;
    gInit(&G, 6);
    gAddEdge(&G, 0, 1);
    gAddEdge(&G, 0, 2);
    gAddEdge(&G, 1, 3);
    gAddEdge(&G, 2, 3);
    gAddEdge(&G, 3, 4);
    gAddEdge(&G, 4, 5);

    printf("=== 图的结构 ===\n");
    printf("      0 --- 1\n");
    printf("      |     |\n");
    printf("      2 --- 3 --- 4 --- 5\n");

    /* ---------- DFS 递归 ---------- */
    printf("\n=== ① DFS（递归）===\n");
    reset(G.n);
    printf("  从 0 出发：");
    dfsRec(&G, 0);
    printf("\n  检查邻接关系次数 = %lld（n^2 量级）\n", g_ops);
    printf("  ⭐ 走法：0 → 1 → 3 → 2，然后回退，3 → 4 → 5\n");

    /* ---------- DFS 栈 ---------- */
    printf("\n=== ② DFS（显式栈）===\n");
    reset(G.n);
    printf("  从 0 出发：");
    dfsStack(&G, 0);
    printf("\n  ⭐ 和递归版结果一致 —— 递归本身就是用栈实现的。\n");
    printf("     系统栈 = 你写的递归；显式栈 = 自己用一个数组模拟。\n");

    /* ---------- BFS ---------- */
    printf("\n=== ③ BFS（队列）===\n");
    reset(G.n);
    printf("  从 0 出发（括号里是层数）：");
    bfs(&G, 0);
    printf("\n  ⭐ 按层访问：第 0 层 0，第 1 层 1 2，第 2 层 3，第 3 层 4，第 4 层 5\n");
    printf("     括号里的数字就是「从 0 到该点的最短跳数」。\n");

    /* ---------- DFS vs BFS ---------- */
    printf("\n=== ④ DFS vs BFS ===\n");
    printf("  %-14s %-20s %s\n", "对比项", "DFS", "BFS");
    printf("  ------------------------------------------------------------------\n");
    printf("  %-14s %-20s %s\n", "走法", "一条路走到底", "一层一层扩");
    printf("  %-14s %-20s %s\n", "用的结构", "栈（或递归）", "队列");
    printf("  %-14s %-20s %s\n", "最短路径", "不适合", "适合（无权图）");
    printf("  %-14s %-20s %s\n", "典型用途", "判连通、拓扑排序", "最短跳数、层序");
    printf("  %-14s %-20s %s\n", "内存", "少（只看一条路）", "多（存整层）");

    printf("\n  ⭐ 记法：\n");
    printf("     DFS = 深度优先 = 用栈 = 一条道走到黑\n");
    printf("     BFS = 广度优先 = 用队列 = 涟漪式扩散\n");

    /* ---------- 两个必须注意的点 ---------- */
    printf("\n=== ⑤ 两个必须注意的点 ===\n");

    printf("  ① 必须标记已访问\n");
    printf("     图可以有环，不标记会无限循环。\n");
    printf("     树的遍历不需要标记，因为树无环、且每个节点只有一个父亲。\n");

    printf("\n  ② BFS 的标记时机：入队时标记，不是出队时\n");
    printf("     ⚠️ 如果出队时才标记，同一个点可能被多次入队，\n");
    printf("        队列膨胀、层数也可能算错。\n");
    printf("     本例：3 的邻居 1 和 2 都已标记，所以只入队一次。\n");

    /* ---------- 复杂度 ---------- */
    printf("\n=== ⑥ 复杂度 ===\n");
    printf("  %-18s %-14s %s\n", "存储方式", "复杂度", "原因");
    printf("  ----------------------------------------------------\n");
    printf("  %-18s %-14s %s\n", "邻接矩阵", "O(n^2)", "每个点扫一整行");
    printf("  %-18s %-14s %s\n", "邻接表", "O(n+e)", "只扫存在的边");
    printf("\n  ⭐ 本例（矩阵存储）检查邻接关系 36 次 = n^2 = 6^2。\n");
    printf("     稠密图两者差不多，稀疏图邻接表明显更快。\n");

    /* ---------- 连通分量 ---------- */
    printf("\n=== ⑦ 非连通图：要循环所有顶点 ===\n");
    Graph G2;
    gInit(&G2, 6);
    gAddEdge(&G2, 0, 1);
    gAddEdge(&G2, 2, 3);
    /* 4、5 是孤立点 */
    printf("  图：0-1，2-3，4，5（共 4 个连通分量）\n");
    reset(G2.n);
    int comp = 0;
    printf("  遍历：");
    for (int v = 0; v < G2.n; v++) {
        if (!g_visited[v]) {
            comp++;
            printf("[分量%d: ", comp);
            dfsRec(&G2, v);
            printf("] ");
        }
    }
    printf("\n  连通分量数 = %d\n", comp);
    printf("  ⭐ 遍历非连通图必须对每个未访问顶点再启动一次 DFS/BFS，\n");
    printf("     启动次数 = 连通分量数。软考常考这个。\n");

    return 0;
}
