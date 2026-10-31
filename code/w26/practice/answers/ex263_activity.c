/* ============================================================================
 * ex263_activity.c  —— 参考答案
 *
 * 【解题要点】
 *   贪心：按结束时间升序，依次选 start >= lastEnd
 *   暴力：枚举 2^n 个子集，两两检查是否重叠，取最大
 *
 * 【为什么「结束时间最早」是对的】
 *   设最优解的第一个活动是 A，贪心选的是结束最早的 B。
 *   因为 B.end <= A.end，把 A 换成 B 后剩下的空间只会更多，
 *   所以一定还存在一个同样大的最优解包含 B —— 这就是「交换论证」。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex263.exe ex263_activity.c
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

typedef struct { int start, end; } Act;

static int cmpEnd(const void *x, const void *y)
{
    const Act *a = x, *b = y;
    return a->end - b->end;
}

static int cmpStart(const void *x, const void *y)
{
    const Act *a = x, *b = y;
    return a->start - b->start;
}

/* 对照实验：按开始时间最早的贪心（错误的策略） */
static int maxByStart(Act *acts, int n)
{
    qsort(acts, n, sizeof(Act), cmpStart);
    int cnt = 0, lastEnd = -1;
    for (int i = 0; i < n; i++) {
        if (acts[i].start >= lastEnd) { cnt++; lastEnd = acts[i].end; }
    }
    return cnt;
}

/* ---------- 1. 贪心 ---------- */
int maxActivities(Act *acts, int n)
{
    qsort(acts, n, sizeof(Act), cmpEnd);
    int cnt = 0, lastEnd = -1;
    for (int i = 0; i < n; i++) {
        if (acts[i].start >= lastEnd) {
            cnt++;
            lastEnd = acts[i].end;
        }
    }
    return cnt;
}

/* ---------- 2. 暴力枚举子集 ---------- */
int maxActivitiesBrute(const Act *acts, int n)
{
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int idx[16], k = 0, ok = 1;
        for (int i = 0; i < n; i++) if (mask & (1 << i)) idx[k++] = i;

        /* 两两检查：任意两个活动不能重叠 */
        for (int i = 0; i < k && ok; i++)
            for (int j = i + 1; j < k && ok; j++) {
                const Act *p = &acts[idx[i]], *q = &acts[idx[j]];
                if (!(p->end <= q->start || q->end <= p->start)) ok = 0;
            }
        if (ok && k > best) best = k;
    }
    return best;
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
        int n = 3 + (int)(t % 10);
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
    printf("  反例：\n");
    Act bad[] = {{0, 10}, {1, 2}, {2, 3}, {3, 4}};
    int bn = 4;
    printf("    活动：[0,10) [1,2) [2,3) [3,4)\n");
    printf("    最优是 3 个（后三个），但按开始时间会先选 [0,10)，只能得 1 个。\n");

    Act copy1[4], copy2[4];
    for (int i = 0; i < bn; i++) { copy1[i] = bad[i]; copy2[i] = bad[i]; }
    printf("    按【开始时间】贪心 = %d 个\n", maxByStart(copy1, bn));
    printf("    按【结束时间】贪心 = %d 个\n", maxActivities(copy2, bn));
    printf("    ⭐ 同一个问题，选错排序标准就从 3 掉到 1。\n");

    printf("\n=== ④ 贪心正确性的「交换论证」 ===\n");
    printf("  设最优解首选 A，贪心选 B（B 的结束时间最早）。\n");
    printf("  因 B.end <= A.end，把 A 换成 B 后，剩余可安排的时间只会更多，\n");
    printf("  所以仍存在同样大的最优解包含 B。逐步替换，贪心解 = 最优解。\n");
    printf("  ⭐ 这段话是软考简答题的标准答案，记住「交换论证」四个字。\n");
    return 0;
}
