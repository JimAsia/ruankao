/* ex222_kruskal.c —— 参考答案 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int u, v, w;
} Edge;

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
    if (ra == rb) return 0;                 /* 已连通 → 会成环 */
    parent[ra] = rb;
    return 1;
}

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
    for (int i = 0; i < n; i++) parent[i] = i;

    sortEdges(edges, m);

    printf("  排序后：");
    for (int i = 0; i < m; i++)
        printf("%d-%d(%d) ", edges[i].u, edges[i].v, edges[i].w);
    printf("\n\n");

    int total = 0, picked = 0;
    for (int i = 0; i < m && picked < n - 1; i++) {
        if (ufUnion(edges[i].u, edges[i].v)) {
            printf("    选 %d-%d(%d)\n", edges[i].u, edges[i].v, edges[i].w);
            total += edges[i].w;
            picked++;
        } else {
            printf("    跳过 %d-%d(%d) —— 会成环\n",
                   edges[i].u, edges[i].v, edges[i].w);
        }
    }
    return (picked == n - 1) ? total : -1;
}

int main(void)
{
    int n = 5;
    Edge edges[] = {
        {0,1,2},{0,3,6},{1,2,3},{1,3,8},{1,4,5},{2,4,7},{3,4,9}
    };
    int m = 7;

    printf("=== Kruskal ===\n");
    int total = kruskal(edges, m, n);
    printf("\n  总权值 = %d（期望 16）%s\n", total, total == 16 ? "✓" : "✗");

    printf("\n=== 关键：并查集判环 ===\n");
    printf("  为什么选到 2-4(7) 要跳过？\n");
    printf("    前面已选 0-1、1-2、1-4，此时 2 和 4 已经连通，\n");
    printf("    再加 2-4 就形成一个环 1-2-4-1。\n");
    printf("  并查集 find(2) == find(4) → 说明已连通 → 跳过。\n");

    printf("\n=== Kruskal 的三步 ===\n");
    printf("  1. 所有边按权值升序排序        O(e log e)\n");
    printf("  2. 依次取边，用并查集判环      O(e α(n)) ≈ O(e)\n");
    printf("  3. 选够 n-1 条就停\n");
    printf("  ⭐ 总复杂度 O(e log e)，瓶颈在排序。\n");

    printf("\n=== 为什么适合稀疏图 ===\n");
    printf("  O(e log e) 里 e 越小越快。\n");
    printf("  稀疏图 e ≈ n，复杂度约 O(n log n)，比 Prim 的 O(n^2) 好。\n");

    printf("\n=== Prim 和 Kruskal 都能求 MST ===\n");
    printf("  两者结果权值一定相同（MST 权值和唯一），\n");
    printf("  但选出的边集可能不同（等权边可互换）。\n");

    return 0;
}
