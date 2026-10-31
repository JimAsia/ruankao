/* ex226_summary.c —— 参考答案 */

#include <stdio.h>

int main(void)
{
    printf("=== 图的综合小测 ===\n\n");

    /* 题 1、2 */
    int n = 8;
    printf("题 1：无向完全图 %d 个顶点的边数\n", n);
    printf("      n(n-1)/2 = %d×%d/2 = %d ✓\n\n", n, n - 1, n * (n - 1) / 2);

    printf("题 2：有向完全图 %d 个顶点的边数\n", n);
    printf("      n(n-1) = %d×%d = %d ✓\n\n", n, n - 1, n * (n - 1));

    /* 题 3 */
    int v = 10;
    printf("题 3：%d 个顶点的连通图，生成树边数\n", v);
    printf("      n-1 = %d ✓\n\n", v - 1);

    /* 题 4 */
    int n2 = 20, e2 = 30;
    printf("题 4：n=%d, e=%d 的空间占用\n", n2, e2);
    printf("      邻接矩阵：n^2 = %d 个 int = %d 字节\n",
           n2 * n2, (int)(n2 * n2 * sizeof(int)));
    printf("      邻接表  ：%d 个头指针 + 2e = %d 个边节点\n",
           n2, 2 * e2);
    printf("      ⭐ 边节点每个含 1 个 int + 1 个指针 = %d 字节\n",
           (int)(sizeof(int) + sizeof(void *)));
    printf("         总共约 %d + %d×%d = %d 字节（不算头指针）\n",
           0, 2 * e2, (int)(sizeof(int) + sizeof(void *)),
           2 * e2 * (int)(sizeof(int) + sizeof(void *)));
    printf("      ⭐ 稀疏图用邻接表省很多空间。\n\n");

    /* 题 5 */
    int n3 = 10, c = 3;
    printf("题 5：%d 个顶点 %d 个连通分量，生成森林边数\n", n3, c);
    printf("      n - c = %d - %d = %d ✓\n", n3, c, n3 - c);
    printf("      推导：每个分量 k 个点有 k-1 条边，\n");
    printf("            总和 = (k1-1)+(k2-1)+... = n - 分量数\n\n");

    /* 题 6 */
    printf("题 6：DFS 和 BFS 用什么结构？\n");
    printf("      DFS → 栈（或递归）\n");
    printf("      BFS → 队列\n");
    printf("      ⭐ 记法：DFS 一条路走到底（像栈的「后进先出」），\n");
    printf("         BFS 一层层扩散（像队列的「先进先出」）。\n");

    printf("\n=== 六条必背结论 ===\n");
    printf("  1. 无向完全图边数 = n(n-1)/2\n");
    printf("  2. 有向完全图边数 = n(n-1)\n");
    printf("  3. 生成树边数 = n-1\n");
    printf("  4. 无向图度之和 = 2e；有向图入度和 = 出度和 = e\n");
    printf("  5. 生成森林边数 = n - 连通分量数\n");
    printf("  6. DFS 用栈，BFS 用队列\n");

    printf("\n=== 图算法总览 ===\n");
    printf("  %-22s %-14s %s\n", "问题", "算法", "复杂度");
    printf("  ------------------------------------------------------\n");
    printf("  %-22s %-14s %s\n", "遍历", "DFS / BFS", "O(n^2) 或 O(n+e)");
    printf("  %-22s %-14s %s\n", "最小生成树", "Prim", "O(n^2) 稠密图");
    printf("  %-22s %-14s %s\n", "最小生成树", "Kruskal", "O(e log e) 稀疏图");
    printf("  %-22s %-14s %s\n", "单源最短路径", "Dijkstra", "O(n^2)");
    printf("  %-22s %-14s %s\n", "所有点对最短路径", "Floyd", "O(n^3)");
    printf("  %-22s %-14s %s\n", "拓扑排序", "Kahn", "O(n+e)");
    printf("  %-22s %-14s %s\n", "判环（有向）", "DFS 三色/拓扑", "O(n+e)");
    printf("  %-22s %-14s %s\n", "判环（无向）", "并查集", "O(e α(n))");

    return 0;
}
