/* 223_topo.c —— 拓扑排序（AOV 网）与关键路径概念（AOE 网）
 *
 * 拓扑排序要解决的问题：
 *   一堆任务有先后依赖（比如「先修 A 才能修 B」），
 *   求一个合法的执行顺序。
 *
 * AOV 网：Activity On Vertex，顶点表示活动，边表示优先关系。
 * 拓扑排序算法（Kahn 算法）：
 *   ① 找所有入度为 0 的顶点，入队
 *   ② 出队一个，输出，把它的所有后继入度减 1
 *   ③ 减完变成 0 的入队
 *   ④ 重复直到队列空
 *
 * 如果输出顶点数 < 总顶点数 → 图中有环，无法拓扑排序。
 *
 * AOE 网：Activity On Edge，边表示活动（带时间），用于求关键路径。
 */

#include <stdio.h>

#define MAXV 8

/* 邻接矩阵存有向图 */
typedef struct {
    int matrix[MAXV][MAXV];
    int n;
} DiGraph;

static void dgInit(DiGraph *G, int n)
{
    G->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G->matrix[i][j] = 0;
}

static void dgAddEdge(DiGraph *G, int u, int v)
{
    G->matrix[u][v] = 1;                /* 有向：只置一个方向 */
}

/* 求所有顶点的入度 */
static void calcIndegree(DiGraph *G, int indeg[])
{
    for (int i = 0; i < G->n; i++) indeg[i] = 0;
    for (int u = 0; u < G->n; u++)
        for (int v = 0; v < G->n; v++)
            if (G->matrix[u][v]) indeg[v]++;
}

/* 拓扑排序：返回 1 成功，0 表示有环 */
int topoSort(DiGraph *G, int order[])
{
    int indeg[MAXV];
    int q[MAXV];
    int front = 0, rear = 0;
    int cnt = 0;

    calcIndegree(G, indeg);

    printf("  初始入度：");
    for (int i = 0; i < G->n; i++) printf("%d:%d  ", i, indeg[i]);
    printf("\n");

    /* ① 入度为 0 的全部入队 */
    for (int i = 0; i < G->n; i++) {
        if (indeg[i] == 0) q[rear++] = i;
    }

    printf("  入度为 0 的顶点入队：");
    for (int i = front; i < rear; i++) printf("%d ", q[i]);
    printf("\n");

    /* ② 反复出队、减入度 */
    while (front < rear) {
        int u = q[front++];
        order[cnt++] = u;
        printf("    输出 %d", u);

        int changed = 0;
        for (int v = 0; v < G->n; v++) {
            if (G->matrix[u][v]) {
                indeg[v]--;
                if (indeg[v] == 0) {
                    q[rear++] = v;
                    if (!changed) printf("  →  入度归零入队：");
                    printf("%d ", v);
                    changed = 1;
                }
            }
        }
        printf("\n");
    }

    return (cnt == G->n) ? 1 : 0;
}

int main(void)
{
    /* 课程依赖（AOV 网）
     *   0 → 1 → 3
     *   ↓   ↓   ↓
     *   2 → 4 → 5
     *
     * 含义：学了 0 才能学 1、2；学了 1、2 才能学 4；等等
     */
    DiGraph G;
    dgInit(&G, 6);
    dgAddEdge(&G, 0, 1);
    dgAddEdge(&G, 0, 2);
    dgAddEdge(&G, 1, 3);
    dgAddEdge(&G, 1, 4);
    dgAddEdge(&G, 2, 4);
    dgAddEdge(&G, 3, 5);
    dgAddEdge(&G, 4, 5);

    printf("=== AOV 网（课程依赖）===\n");
    printf("  边：0→1 0→2 1→3 1→4 2→4 3→5 4→5\n");
    printf("  含义：「先学 u 才能学 v」\n");

    printf("\n=== ① 拓扑排序 ===\n");
    int order[MAXV];
    int ok = topoSort(&G, order);

    printf("\n  拓扑序列：");
    for (int i = 0; i < G.n && i < 8; i++) {
        if (i >= 0 && order[i] >= 0) {
            printf("%d", order[i]);
            if (i != G.n - 1) printf(" → ");
        }
    }
    printf("\n  %s\n", ok ? "排序成功（无环）" : "排序失败（有环）");

    printf("\n  ⭐ 拓扑序列可能不唯一：\n");
    printf("     入度为 0 的点谁先谁后都可以，所以有多种合法顺序。\n");
    printf("     软考常问「下列哪个不是合法拓扑序列」。\n");

    /* ---------- 有环的情况 ---------- */
    printf("\n=== ② 有环的图：拓扑排序失败 ===\n");
    DiGraph G2;
    dgInit(&G2, 4);
    dgAddEdge(&G2, 0, 1);
    dgAddEdge(&G2, 1, 2);
    dgAddEdge(&G2, 2, 3);
    dgAddEdge(&G2, 3, 1);               /* 1→2→3→1 形成环 */

    printf("  边：0→1 1→2 2→3 3→1（1-2-3 成环）\n");
    int order2[MAXV];
    int ok2 = topoSort(&G2, order2);
    printf("\n  结果：%s\n", ok2 ? "成功" : "失败 —— 输出顶点数 < 总顶点数，说明有环");

    printf("\n  ⭐ 拓扑排序的第二个用途：判断有向图有没有环。\n");
    printf("     输出顶点数 == n → 无环；< n → 有环。\n");

    /* ---------- AOV vs AOE ---------- */
    printf("\n=== ③ AOV 网 vs AOE 网 ===\n");
    printf("  %-14s %-22s %s\n", "对比", "AOV 网", "AOE 网");
    printf("  ------------------------------------------------------------------\n");
    printf("  %-14s %-22s %s\n", "顶点表示", "活动（任务）", "事件（状态）");
    printf("  %-14s %-22s %s\n", "边表示", "优先关系", "活动（带持续时间）");
    printf("  %-14s %-22s %s\n", "用于", "拓扑排序", "关键路径");
    printf("  %-14s %-22s %s\n", "有无权值", "无权", "边有权（时间）");

    printf("\n=== ④ 关键路径（AOE 网）===\n");
    printf("  关键路径 = 从源点到汇点的【最长】路径。\n");
    printf("  它决定整个工程的最短完成时间 —— 因为最长的活干完了才能收工。\n");
    printf("\n  四个术语（软考必考）：\n");
    printf("    ve(i)：事件 i 的最早发生时间   ← 从前往后推，取 max\n");
    printf("    vl(i)：事件 i 的最晚发生时间   ← 从后往前推，取 min\n");
    printf("    e(a)：活动 a 的最早开始时间 = 起点的 ve\n");
    printf("    l(a)：活动 a 的最晚开始时间 = 终点的 vl - 活动时长\n");
    printf("\n  ⭐ 关键活动 = e(a) == l(a) 的活动（没有时间余量）。\n");
    printf("     关键路径上的活动全是关键活动。\n");
    printf("  📌 缩短工期 → 只能缩短关键活动，缩短非关键活动没用。\n");

    printf("\n=== ⑤ 软考怎么考 ===\n");
    printf("  1. 给 AOV 网，写出一个合法拓扑序列\n");
    printf("  2. 给几个序列，判断哪个不是合法拓扑序列\n");
    printf("  3. 给 AOE 网，求关键路径 / 最短工期\n");
    printf("  4. 问「缩短哪个活动能缩短工期」→ 关键活动\n");
    printf("  📌 拓扑排序是应用题常客，关键路径通常只在选择题出现。\n");

    return 0;
}
