/* ============================================================================
 * ex263_activity.c  —— 练习 3：活动安排（贪心的正确性验证）
 *
 * 【题目】
 *   n 个活动共用一个场地，每个活动有起止时间 [s, e)，求最多能安排几个。
 *   1. 实现贪心：按【结束时间】升序排序，依次选不冲突的
 *   2. 实现暴力：枚举所有子集，找出最多能同时安排几个（n ≤ 12 时可行）
 *   3. 随机生成 1000 组数据，比较贪心结果与暴力结果
 *   4. 统计：贪心在所有随机数据上都等于最优吗？
 *
 * 【预期】
 *   1000 组随机数据，贪心与最优全部相等（0 组不等）。
 *   这正是「贪心选择性质」的实证 —— 但注意：验证不能代替证明。
 *
 * 【提示】
 *   qsort 的比较函数：
 *     int cmp(const void *x, const void *y) {
 *         const Act *a = x, *b = y;
 *         return a->end - b->end;
 *     }
 *   选完一个活动后，记录它的结束时间 lastEnd；
 *   下一个活动要满足 start >= lastEnd。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex263.exe ex263_activity.c
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int start, end; } Act;

/* ---------- 1. 贪心 ---------- */
int maxActivities(Act *acts, int n)
{
    /* TODO: 按结束时间排序，然后贪心扫描 */
    (void)acts; (void)n;
    return 0;
}

/* ---------- 2. 暴力：枚举子集 ---------- */
int maxActivitiesBrute(const Act *acts, int n)
{
    /* TODO: 对每个子集判断是否两两不重叠，取最大的个数
     * 判断不重叠：把子集里的活动按开始时间排序，检查前一个的 end <= 后一个的 start */
    (void)acts; (void)n;
    return 0;
}

int main(void)
{
    Act demo[] = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9},
        {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}
    };
    int dn = (int)(sizeof(demo) / sizeof(demo[0]));

    printf("=== ① 经典例子 ===\n");
    printf("  活动：");
    for (int i = 0; i < dn; i++) printf("[%d,%d) ", demo[i].start, demo[i].end);
    printf("\n  贪心 = %d，暴力 = %d\n", maxActivities(demo, dn),
           maxActivitiesBrute(demo, dn));

    printf("\n=== ② 1000 组随机数据验证 ===\n");
    unsigned seed = 2024;
    int mismatch = 0;
    for (int t = 0; t < 1000; t++) {
        Act arr[12];
        int n = 3 + (int)(t % 10);              /* 3..12 个活动 */
        for (int i = 0; i < n; i++) {
            seed = seed * 1103515245u + 12345u;
            int s = (int)((seed >> 16) % 20);
            seed = seed * 1103515245u + 12345u;
            int len = 1 + (int)((seed >> 16) % 5);
            arr[i].start = s;
            arr[i].end = s + len;
        }
        Act copy[12];
        for (int i = 0; i < n; i++) copy[i] = arr[i];

        int g = maxActivities(copy, n);
        int b = maxActivitiesBrute(arr, n);
        if (g != b) {
            mismatch++;
            if (mismatch <= 3) {
                printf("  ✗ 第 %d 组：贪心 %d，最优 %d　活动：", t, g, b);
                for (int i = 0; i < n; i++) printf("[%d,%d) ", arr[i].start, arr[i].end);
                printf("\n");
            }
        }
    }
    printf("  不一致组数：%d / 1000\n", mismatch);
    if (mismatch == 0)
        printf("  ⭐ 1000 组全部相等 —— 贪心「按结束时间最早」在这类问题上是正确的。\n");

    printf("\n=== ③ 为什么是「结束时间」而不是「开始时间」 ===\n");
    printf("  反例（按开始时间会选错）：\n");
    Act bad[] = {{0, 10}, {1, 2}, {2, 3}, {3, 4}};
    int bn = 4;
    printf("    活动：[0,10) [1,2) [2,3) [3,4)\n");
    printf("    最优是 3 个（后三个），但按开始时间会先选 [0,10)，只能得 1 个。\n");
    printf("    本题的贪心结果 = %d（正确答案 3）\n", maxActivities(bad, bn));
    return 0;
}
