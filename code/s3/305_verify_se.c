/* ============================================================================
 * 305_verify_se.c  —— S3-05 软件工程：两个真正会算的题
 *
 * 软件工程大部分是背概念，但有两类必须动笔算：
 *   ① McCabe 环形复杂度 V(G) = E − N + 2 = 判定节点数 + 1
 *   ② 关键路径：最早/最晚开始时间、总浮动时间、关键活动
 *
 * 这两个都能用程序验证，本文件把它们算一遍。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 305.exe 305_verify_se.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

/* ==========================================================================
 * 一、McCabe 环形复杂度
 * ========================================================================*/

typedef struct {
    const char *name;
    int n;                          /* 节点数 */
    int edges[32][2];               /* 边表 */
    int ne;
} FlowGraph;

static void mccabe(const FlowGraph *g)
{
    /* 节点的出度，用来数判定节点（出度 ≥ 2） */
    int outdeg[16] = {0};
    for (int i = 0; i < g->ne; i++) outdeg[g->edges[i][0]]++;

    int decisions = 0;
    printf("  %s\n", g->name);
    printf("    节点数 N = %d，边数 E = %d\n", g->n, g->ne);
    printf("    各节点出度：");
    for (int i = 1; i <= g->n; i++) printf("%d:%d ", i, outdeg[i]);
    printf("\n    判定节点（出度≥2）：");
    for (int i = 1; i <= g->n; i++)
        if (outdeg[i] >= 2) { printf("%d ", i); decisions++; }
    if (decisions == 0) printf("无");

    int v1 = g->ne - g->n + 2;
    printf("\n\n    公式一：V(G) = E − N + 2 = %d − %d + 2 = %d\n", g->ne, g->n, v1);
    printf("    公式二：V(G) = 判定节点数 + 1 = %d + 1 = %d\n", decisions, decisions + 1);
    printf("    %s\n\n", (v1 == decisions + 1) ? "两式一致 ✓" : "两式不一致 ✗");
}

/* ==========================================================================
 * 二、关键路径
 * ========================================================================*/

typedef struct {
    char id;
    int dur;
    int pre[4];         /* 前置活动下标，-1 表示无 */
    int npre;
} Act;

/* 活动必须按拓扑序给出（前面的活动不依赖后面的） */
static void criticalPath(Act *a, int n)
{
    int ES[16], EF[16], LS[16], LF[16], TF[16];

    /* 正推：ES = max(前驱 EF)，EF = ES + 工期 */
    for (int i = 0; i < n; i++) {
        int es = 0;
        for (int k = 0; k < a[i].npre; k++) {
            int p = a[i].pre[k];
            if (EF[p] > es) es = EF[p];
        }
        ES[i] = es;
        EF[i] = es + a[i].dur;
    }

    /* 总工期 = 所有 EF 的最大值 */
    int total = 0;
    for (int i = 0; i < n; i++) if (EF[i] > total) total = EF[i];

    /* 逆推：LF = min(后继的 LS)，没有后继则为总工期；LS = LF − 工期 */
    for (int i = 0; i < n; i++) LF[i] = total;      /* 先全部置为总工期 */
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++)
            for (int k = 0; k < a[j].npre; k++)
                if (a[j].pre[k] == i && LS[j] < LF[i]) LF[i] = LS[j];
        LS[i] = LF[i] - a[i].dur;
        TF[i] = LS[i] - ES[i];                      /* 总浮动时间 */
    }

    printf("  %-4s %-4s %-4s %-4s %-4s %-4s %s\n",
           "活动", "工期", "ES", "EF", "LS", "LF", "总浮动");
    for (int i = 0; i < n; i++)
        printf("  %-4c %-4d %-4d %-4d %-4d %-4d %d%s\n",
               a[i].id, a[i].dur, ES[i], EF[i], LS[i], LF[i], TF[i],
               TF[i] == 0 ? "  ← 关键活动" : "");

    printf("\n  总工期 = %d\n", total);
    printf("  关键路径 = ");
    for (int i = 0; i < n; i++)
        if (TF[i] == 0) printf("%c → ", a[i].id);
    printf("结束\n");
}

int main(void)
{
    printf("################ 一、McCabe 环形复杂度 ################\n\n");

    /* 一个带 while + if 的函数，控制流图：
     *   1(init) → 2(while判定)
     *   2 --true--> 3(if判定)
     *   2 --false-> 5(exit)
     *   3 --true--> 4(r+=a)
     *   3 --false-> 6(a--)
     *   4 → 6
     *   6 → 2
     */
    FlowGraph g1 = {
        "函数 f（一个 while + 一个 if）",
        6,
        {{1,2},{2,3},{2,5},{3,4},{3,6},{4,6},{6,2}},
        7
    };
    mccabe(&g1);

    /* 顺序结构：无判定 */
    FlowGraph g2 = {
        "顺序结构（无判定）",
        3,
        {{1,2},{2,3}},
        2
    };
    mccabe(&g2);

    /* 两个并列 if */
    FlowGraph g3 = {
        "if-else 结构（一个判定）",
        5,
        {{1,2},{1,3},{2,4},{3,4},{4,5}},
        5
    };
    mccabe(&g3);

    printf("  ⭐ 结论：V(G) 就是「独立路径条数」，也就是至少要设计多少个测试用例\n");
    printf("     才能覆盖所有分支。V(G) ≤ 10 一般认为模块可测性良好。\n");

    /* ---------------- 关键路径 ---------------- */
    printf("\n################ 二、关键路径 ################\n\n");

    /* A(2) B(3) 无前置；C(4) 依赖A；D(2) 依赖A；E(5) 依赖B；
     * F(3) 依赖C、D；G(2) 依赖E、F；H(4) 依赖G */
    Act a[] = {
        {'A', 2, {-1}, 0},
        {'B', 3, {-1}, 0},
        {'C', 4, {0}, 1},
        {'D', 2, {0}, 1},
        {'E', 5, {1}, 1},
        {'F', 3, {2, 3}, 2},
        {'G', 2, {4, 5}, 2},
        {'H', 4, {6}, 1}
    };
    printf("  活动表：\n");
    printf("    A(2)  B(3)  C(4)←A  D(2)←A  E(5)←B  F(3)←C,D  G(2)←E,F  H(4)←G\n\n");
    criticalPath(a, 8);

    printf("\n  ⭐ 验证：A→C→F→G→H = 2+4+3+2+4 = 15\n");
    printf("     B→E→G→H = 3+5+2+4 = 14，比关键路径短 1，所以 B 有 1 天浮动。\n");

    printf("\n  三个结论：\n");
    printf("    ① 关键路径是【最长】的那条路，长度 = 总工期\n");
    printf("    ② 关键活动的总浮动时间 = 0\n");
    printf("    ③ 缩短总工期只能压缩关键活动；压缩非关键活动没用\n");
    return 0;
}
