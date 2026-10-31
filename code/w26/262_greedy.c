/* ============================================================================
 * 262_greedy.c  —— 贪心法：三个经典问题，两个反例
 *
 * 贪心法的思路：每一步都选「当前看起来最好」的，选了就不回头。
 * 它不保证最优 —— 只有当问题满足【贪心选择性质】和【最优子结构】时才对。
 *
 * 本文件：
 *   ① 活动安排：按结束时间贪心 = 最优；按开始时间贪心 = 错
 *   ② 找零钱：币值 1/5/11 凑 15，贪心 5 枚，最优 3 枚 —— 反例
 *   ③ 背包：分数背包贪心 = 最优；0-1 背包贪心 = 错
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 262.exe 262_greedy.c
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

/* ==========================================================================
 * 一、活动安排问题
 *
 * n 个活动共用一个场地，每个活动有起止时间，求最多能安排几个不重叠的活动。
 * ========================================================================*/

typedef struct { int id, start, end; } Act;

/* 按结束时间升序 */
static int cmpEnd(const void *x, const void *y)
{
    const Act *a = x, *b = y;
    if (a->end != b->end) return a->end - b->end;
    return a->start - b->start;
}

/* 按开始时间升序 */
static int cmpStart(const void *x, const void *y)
{
    const Act *a = x, *b = y;
    return a->start - b->start;
}

/* 按区间长度升序 */
static int cmpDur(const void *x, const void *y)
{
    const Act *a = x, *b = y;
    return (a->end - a->start) - (b->end - b->start);
}

/* 贪心：按给定顺序扫描，能塞就塞。返回选中的个数，结果写入 chosen */
static int schedule(Act *acts, int n, int (*cmp)(const void *, const void *),
                    int *chosen)
{
    qsort(acts, n, sizeof(Act), cmp);
    int cnt = 0, lastEnd = -1;
    for (int i = 0; i < n; i++) {
        if (acts[i].start >= lastEnd) {         /* 与前一个不重叠 */
            chosen[cnt++] = acts[i].id;
            lastEnd = acts[i].end;
        }
    }
    return cnt;
}

/* ==========================================================================
 * 二、找零钱
 * ========================================================================*/

/* 贪心：每次用面额最大的 */
static int coinGreedy(const int *coins, int m, int amount, int *used)
{
    int cnt = 0;
    for (int i = m - 1; i >= 0; i--) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            used[cnt++] = coins[i];
        }
    }
    return cnt;
}

/* 动规：完全背包，dp[x] = 凑出 x 的最少硬币数 */
static int coinDP(const int *coins, int m, int amount, int *used)
{
    int dp[256], from[256];
    for (int i = 0; i <= amount; i++) { dp[i] = 1 << 28; from[i] = -1; }
    dp[0] = 0;
    for (int x = 1; x <= amount; x++) {
        for (int i = 0; i < m; i++) {
            if (coins[i] <= x && dp[x - coins[i]] + 1 < dp[x]) {
                dp[x] = dp[x - coins[i]] + 1;
                from[x] = coins[i];
            }
        }
    }
    /* 回溯出用了哪些硬币 */
    int cnt = 0, x = amount;
    while (x > 0 && from[x] > 0) { used[cnt++] = from[x]; x -= from[x]; }
    return dp[amount];
}

/* ==========================================================================
 * 三、背包问题
 * ========================================================================*/

typedef struct { const char *name; int w, v; } Item;

/* 0-1 背包：暴力枚举所有子集（物品少时才可行），用来拿「标准答案」 */
static int knapsack01Brute(const Item *it, int n, int cap, int *mask)
{
    int best = 0, bestMask = 0;
    for (int m = 0; m < (1 << n); m++) {
        int w = 0, v = 0;
        for (int i = 0; i < n; i++)
            if (m & (1 << i)) { w += it[i].w; v += it[i].v; }
        if (w <= cap && v > best) { best = v; bestMask = m; }
    }
    *mask = bestMask;
    return best;
}

int main(void)
{
    /* ---------------- ① 活动安排 ---------------- */
    printf("=== ① 活动安排（同一场地，求最多不重叠的活动）===\n");
    Act base[] = {
        {1, 1, 4},  {2, 3, 5},  {3, 0, 6},  {4, 5, 7},
        {5, 3, 9},  {6, 5, 9},  {7, 6, 10}, {8, 8, 11},
        {9, 8, 12}, {10, 2, 14}, {11, 12, 16}
    };
    int n = (int)(sizeof(base) / sizeof(base[0]));

    printf("  活动（编号:起-止）：");
    for (int i = 0; i < n; i++) printf("%d:%d-%d  ", base[i].id, base[i].start, base[i].end);
    printf("\n\n");

    int chosen[16], cnt;
    Act copy[16];

    /* 策略 A：按结束时间最早 */
    for (int i = 0; i < n; i++) copy[i] = base[i];
    cnt = schedule(copy, n, cmpEnd, chosen);
    printf("  按【结束时间最早】选：%d 个 → ", cnt);
    for (int i = 0; i < cnt; i++) printf("%d ", chosen[i]);
    printf("\n");

    /* 策略 B：按开始时间最早 */
    for (int i = 0; i < n; i++) copy[i] = base[i];
    cnt = schedule(copy, n, cmpStart, chosen);
    printf("  按【开始时间最早】选：%d 个 → ", cnt);
    for (int i = 0; i < cnt; i++) printf("%d ", chosen[i]);
    printf("\n");

    /* 策略 C：按持续时间最短 */
    for (int i = 0; i < n; i++) copy[i] = base[i];
    cnt = schedule(copy, n, cmpDur, chosen);
    printf("  按【持续时间最短】选：%d 个 → ", cnt);
    for (int i = 0; i < cnt; i++) printf("%d ", chosen[i]);
    printf("\n");

    printf("\n  ⭐ 正确答案是 4。按开始时间只有 3，是明确的错；\n");
    printf("     按持续时间这组凑巧也得到 4，但它【没有最优性保证】——换一组数据就可能少。\n");
    printf("     只有「按结束时间最早」是可证明的最优策略：结束越早，给后面留的越多。\n");

    /* ---------------- ② 找零钱 ---------------- */
    printf("\n=== ② 找零钱：贪心失效的反例 ===\n");
    int coins[] = {1, 5, 11};
    int m = 3, amount = 15;
    int used[64];

    int g = coinGreedy(coins, m, amount, used);
    printf("  币值 1 / 5 / 11，凑 %d 元\n", amount);
    printf("  贪心（先大后小）：");
    for (int i = 0; i < g; i++) printf("%d ", used[i]);
    printf(" = %d 枚\n", g);

    int d = coinDP(coins, m, amount, used);
    printf("  最优（动规）：    ");
    for (int i = 0; i < d; i++) printf("%d ", used[i]);
    printf(" = %d 枚\n", d);
    printf("\n  ⭐ 贪心拿 11 + 1+1+1+1，动规拿 5+5+5。贪心多用了 %d 枚。\n", g - d);
    printf("     原因：贪心只看「这一步最大」，没有考虑「剩下的能不能凑好」。\n");
    printf("     人民币面额（1/2/5/10/20/50/100）恰好满足贪心条件，所以生活中贪心能用。\n");

    /* ---------------- ③ 背包 ---------------- */
    printf("\n=== ③ 分数背包 vs 0-1 背包 ===\n");
    Item items[] = {
        {"A", 10, 60},
        {"B", 20, 100},
        {"C", 30, 120}
    };
    int in = 3, cap = 50;

    printf("  容量 %d，物品：\n", cap);
    for (int i = 0; i < in; i++)
        printf("    %s：重 %2d，价值 %3d，单位价值 %.2f\n",
               items[i].name, items[i].w, items[i].v, (double)items[i].v / items[i].w);

    /* 贪心：按单位价值从高到低（已经是 A/B/C 顺序） */
    int gw = 0, gv = 0;
    printf("\n  0-1 背包 贪心（按单位价值装）：");
    for (int i = 0; i < in; i++) {
        if (gw + items[i].w <= cap) {
            gw += items[i].w; gv += items[i].v;
            printf("%s ", items[i].name);
        }
    }
    printf("→ 重 %d，价值 %d（剩余 %d 装不下 C）\n", gw, gv, cap - gw);

    int mask;
    int opt = knapsack01Brute(items, in, cap, &mask);
    printf("  0-1 背包 最优：");
    for (int i = 0; i < in; i++) if (mask & (1 << i)) printf("%s ", items[i].name);
    printf("→ 价值 %d\n", opt);
    printf("  ⭐ 贪心 %d < 最优 %d，错了 %d。\n", gv, opt, opt - gv);
    printf("     原因：A 的单位价值最高，但它占满了容量，导致 B+C 装不进去。\n");

    /* 分数背包：同样按单位价值，最后一件可以切 */
    double fw = 0, fv = 0;
    printf("\n  分数背包（物品可以切开）贪心：");
    for (int i = 0; i < in && fw < cap; i++) {
        double take = (cap - fw >= items[i].w) ? items[i].w : (cap - fw);
        fw += take;
        fv += take * items[i].v / items[i].w;
        printf("%s 取 %.0f%% ", items[i].name, take / items[i].w * 100);
    }
    printf("→ 价值 %.1f\n", fv);
    printf("  ⭐ 分数背包里贪心【是对的】—— 这是贪心与 0-1 背包的分水岭。\n");

    /* ---------------- ④ 判断能不能用贪心 ---------------- */
    printf("\n=== ④ 什么时候能用贪心 ===\n");
    printf("  两个条件必须同时满足：\n");
    printf("    1. 贪心选择性质：局部最优能推出全局最优（可证明，不是「看起来对」）\n");
    printf("    2. 最优子结构：原问题的最优解包含子问题的最优解\n");
    printf("  拿不准的时候：\n");
    printf("    · 先想一个反例（本文件的 ② ③ 就是反例）\n");
    printf("    · 反例找不到，再用动规验证小规模数据\n");
    return 0;
}
