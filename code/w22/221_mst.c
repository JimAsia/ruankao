/* 221_mst.c —— 最小生成树：Prim 与 Kruskal
 *
 * 生成树：连通图的「极小连通子图」—— 包含全部 n 个顶点，只有 n-1 条边，无环。
 * 最小生成树（MST）：所有生成树中边权之和最小的那棵。
 *
 * 两个算法，两种思路：
 *   Prim  （加点法）：从一个点开始，每次选「离当前树最近的」点加进来 —— 像滚雪球
 *   Kruskal（加边法）：把所有边按权值排序，从小到大选，只要不成环就要 —— 像拼图
 *
 * 选择依据（软考常考）：
 *   Prim    O(n^2)，适合【稠密图】（边多）
 *   Kruskal O(e log e)，适合【稀疏图】（边少）
 *
 * 重要性质：MST 的边权之和唯一，但形态可能不唯一（等权边可换）。
 */

#include <stdio.h>

#define MAXV 8
#define INF  99999

/* ==================== Prim（加点法）==================== */
/* 从顶点 0 出发，每次选「离已选集合最近」的顶点 */
int prim(int cost[MAXV][MAXV], int n)
{
    int lowcost[MAXV];              /* lowcost[i] = i 到已选集合的最小边权 */
    int visited[MAXV];
    int total = 0;

    /* 初始化：把 0 加进集合 */
    for (int i = 0; i < n; i++) {
        lowcost[i] = cost[0][i];
        visited[i] = 0;
    }
    visited[0] = 1;

    printf("  从顶点 0 开始\n");

    for (int round = 1; round < n; round++) {
        /* ① 找 lowcost 最小的未访问顶点 */
        int minIdx = -1, minVal = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && lowcost[i] < minVal) {
                minVal = lowcost[i];
                minIdx = i;
            }
        }
        if (minIdx == -1) {
            printf("  图不连通，无法生成树\n");
            return -1;
        }

        /* ② 把该顶点加进集合 */
        printf("    第 %d 步：加入顶点 %d，边权 %d\n", round, minIdx, minVal);
        visited[minIdx] = 1;
        total += minVal;

        /* ③ 用新顶点更新 lowcost */
        for (int i = 0; i < n; i++) {
            if (!visited[i] && cost[minIdx][i] < lowcost[i]) {
                lowcost[i] = cost[minIdx][i];
            }
        }
    }
    return total;
}

/* ==================== Kruskal（加边法）==================== */
/* 把所有边排序，从小到大选，用并查集判环 */
typedef struct {
    int u, v, w;
} Edge;

/* 并查集：判断两个点是否已在同一棵树上 */
static int parent[MAXV];

static int ufFind(int x)
{
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];      /* 路径压缩 */
        x = parent[x];
    }
    return x;
}

static int ufUnion(int a, int b)
{
    int ra = ufFind(a), rb = ufFind(b);
    if (ra == rb) return 0;                 /* 已连通，加这条边会成环 */
    parent[ra] = rb;
    return 1;
}

/* 冒泡排序边（按权值升序） */
static void sortEdges(Edge edges[], int m)
{
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (edges[j].w > edges[j + 1].w) {
                Edge t = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = t;
            }
        }
    }
}

int kruskal(Edge edges[], int m, int n)
{
    for (int i = 0; i < n; i++) parent[i] = i;   /* 初始化并查集 */

    sortEdges(edges, m);

    printf("  边按权值排序：");
    for (int i = 0; i < m; i++) printf("%d-%d(%d) ", edges[i].u, edges[i].v, edges[i].w);
    printf("\n");

    int total = 0, picked = 0;
    for (int i = 0; i < m && picked < n - 1; i++) {
        if (ufUnion(edges[i].u, edges[i].v)) {
            printf("    选边 %d-%d，权 %d\n", edges[i].u, edges[i].v, edges[i].w);
            total += edges[i].w;
            picked++;
        } else {
            printf("    跳过 %d-%d（会成环）\n", edges[i].u, edges[i].v);
        }
    }

    if (picked < n - 1) {
        printf("  只选出 %d 条边（需要 %d 条），图不连通\n", picked, n - 1);
        return -1;
    }
    return total;
}

int main(void)
{
    /* 经典教材例子（6 个顶点）
     *      A ---6--- B ---5--- C
     *      |  \      |      /
     *      1   5     3    6
     *      |     \   |  /
     *      D ---5--- E ---2--- F
     *                |
     *                4
     *                |
     *               （实际用下面的边集）
     */
    int cost[MAXV][MAXV];
    int n = 6;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    /* 边集：u, v, w */
    int raw[][3] = {
        {0, 1, 6}, {0, 2, 1}, {0, 3, 5},
        {1, 2, 5}, {1, 4, 3},
        {2, 3, 5}, {2, 4, 6}, {2, 5, 4},
        {3, 5, 2},
        {4, 5, 6}
    };
    int m = 10;

    for (int i = 0; i < m; i++) {
        int u = raw[i][0], v = raw[i][1], w = raw[i][2];
        cost[u][v] = w;
        cost[v][u] = w;
    }

    printf("=== 图（6 顶点 10 条边，无向带权）===\n");
    printf("  边：");
    for (int i = 0; i < m; i++)
        printf("%d-%d(%d) ", raw[i][0], raw[i][1], raw[i][2]);
    printf("\n");

    /* ---------- Prim ---------- */
    printf("\n=== ① Prim（加点法）===\n");
    int w1 = prim(cost, n);
    printf("  最小生成树总权值 = %d\n", w1);

    /* ---------- Kruskal ---------- */
    printf("\n=== ② Kruskal（加边法）===\n");
    Edge edges[16];
    for (int i = 0; i < m; i++) {
        edges[i].u = raw[i][0];
        edges[i].v = raw[i][1];
        edges[i].w = raw[i][2];
    }
    int w2 = kruskal(edges, m, n);
    printf("  最小生成树总权值 = %d\n", w2);

    printf("\n  ⭐ 两个算法结果相同（%d）—— MST 的权值之和唯一。\n", w1);

    /* ---------- 对比 ---------- */
    printf("\n=== ③ Prim vs Kruskal ===\n");
    printf("  %-16s %-22s %s\n", "对比项", "Prim", "Kruskal");
    printf("  ------------------------------------------------------------------\n");
    printf("  %-16s %-22s %s\n", "思路", "加点（滚雪球）", "加边（拼图）");
    printf("  %-16s %-22s %s\n", "复杂度", "O(n^2)", "O(e log e)");
    printf("  %-16s %-22s %s\n", "适合", "稠密图", "稀疏图");
    printf("  %-16s %-22s %s\n", "需要什么", "邻接矩阵 + lowcost 数组", "边集 + 并查集");
    printf("  %-16s %-22s %s\n", "判环方式", "天然不会成环", "并查集");

    printf("\n  ⭐ 软考常问「哪个适合稀疏图」→ Kruskal。\n");
    printf("     因为 O(e log e) 里 e 小就快，而 Prim 的 O(n^2) 与边数无关。\n");

    /* ---------- 生成树的性质 ---------- */
    printf("\n=== ④ 生成树的性质（必背）===\n");
    printf("  n 个顶点的生成树，一定恰好有 n-1 条边。\n");
    printf("  本例 n=6，所以 MST 有 5 条边。\n");
    printf("\n  ⭐ 判断「是不是生成树」的三个条件：\n");
    printf("     1. 包含全部 n 个顶点\n");
    printf("     2. 恰好 n-1 条边\n");
    printf("     3. 连通（n-1 条边 + 连通 ⟹ 无环）\n");
    printf("\n  📌 少一条边 → 不连通；多一条边 → 必有环。\n");

    return 0;
}
