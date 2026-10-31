/* ex222_kruskal.c —— Kruskal 算法求最小生成树
 *
 * 要求：
 *   1. 把边按权值排序
 *   2. 用并查集判环，从小到大选边
 *   3. 输出选中的边和总权值
 *
 * 测试图（同一张图，用于和 Prim 对照）：
 *   0-1(2)  0-3(6)  1-2(3)  1-3(8)  1-4(5)  2-4(7)  3-4(9)
 *   期望总权值 = 16（和 Prim 相同）
 *   排序后：2,3,5,6,7,8,9
 *   选边：0-1(2) 1-2(3) 1-4(5) 0-3(6)
 *   跳过：2-4(7) 会成环；1-3(8) 会成环；3-4(9) 已够 n-1 条
 *
 * 提示：
 *   并查集：parent[i] = i 初始化
 *   find(x) 找根，union(a,b) 合并（同一根说明会成环）
 *   选够 n-1 条边就停
 */

#include <stdio.h>

#define MAXV 8

typedef struct {
    int u, v, w;
} Edge;

static int parent[MAXV];

/* TODO 1：并查集 find（带路径压缩） */
static int ufFind(int x)
{
    (void)x;
    return 0;
}

/* TODO 2：并查集 union，返回 1 表示合并成功，0 表示已连通（会成环） */
static int ufUnion(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

/* TODO 3：按权值升序排序（冒泡即可） */
static void sortEdges(Edge edges[], int m)
{
    (void)edges; (void)m;
}

/* TODO 4：Kruskal，返回总权值 */
int kruskal(Edge edges[], int m, int n)
{
    (void)edges; (void)m; (void)n;
    return 0;
}

int main(void)
{
    int n = 5;
    Edge edges[] = {
        {0,1,2},{0,3,6},{1,2,3},{1,3,8},{1,4,5},{2,4,7},{3,4,9}
    };
    int m = 7;

    /* TODO 5：调用 kruskal，验证结果 16 */

    printf("\n=== Prim vs Kruskal ===\n");
    printf("  两者结果权值相同，因为 MST 的权值和唯一。\n");
    printf("  Prim 适合稠密图 O(n^2)，Kruskal 适合稀疏图 O(e log e)。\n");

    return 0;
}
