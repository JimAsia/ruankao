/* ============================================================================
 * 302_verify_os.c  —— S3-02 操作系统：数值题验证
 *
 * 操作系统的计算题就三类，全部可以编程验证：
 *   ① 页面置换：FIFO / LRU / OPT 各缺页多少次
 *   ② Belady 异常：增加页框反而缺页更多（FIFO 特有）
 *   ③ 进程调度：FCFS / SJF / RR 的周转时间与带权周转时间
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 302.exe 302_verify_os.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

/* ==========================================================================
 * 一、页面置换
 * ========================================================================*/

/* FIFO：换出最早进来的那一页 */
static int simFIFO(const int *ref, int n, int frames, int verbose)
{
    int f[16], inTime[16], faults = 0, t = 0;
    for (int i = 0; i < frames; i++) { f[i] = -1; inTime[i] = 0; }

    for (int i = 0; i < n; i++) {
        int page = ref[i], hit = 0;
        for (int k = 0; k < frames; k++) if (f[k] == page) { hit = 1; break; }

        if (!hit) {
            faults++;
            int slot = -1;
            for (int k = 0; k < frames; k++) if (f[k] == -1) { slot = k; break; }
            if (slot < 0) {                     /* 满了，找最早进入的 */
                int oldest = INT_MAX;
                for (int k = 0; k < frames; k++)
                    if (inTime[k] < oldest) { oldest = inTime[k]; slot = k; }
            }
            f[slot] = page;
            inTime[slot] = ++t;
        }
        if (verbose) {
            printf("    %2d → ", page);
            for (int k = 0; k < frames; k++) {
                if (f[k] == -1) printf("[ ] ");
                else            printf("[%d] ", f[k]);
            }
            printf("%s\n", hit ? "命中" : "缺页");
        }
    }
    return faults;
}

/* LRU：换出最久没被访问的那一页 */
static int simLRU(const int *ref, int n, int frames, int verbose)
{
    int f[16], last[16], faults = 0, t = 0;
    for (int i = 0; i < frames; i++) { f[i] = -1; last[i] = 0; }

    for (int i = 0; i < n; i++) {
        int page = ref[i], hit = -1;
        for (int k = 0; k < frames; k++) if (f[k] == page) { hit = k; break; }

        if (hit >= 0) {
            last[hit] = ++t;
        } else {
            faults++;
            int slot = -1;
            for (int k = 0; k < frames; k++) if (f[k] == -1) { slot = k; break; }
            if (slot < 0) {
                int oldest = INT_MAX;
                for (int k = 0; k < frames; k++)
                    if (last[k] < oldest) { oldest = last[k]; slot = k; }
            }
            f[slot] = page;
            last[slot] = ++t;
        }
        if (verbose) {
            printf("    %2d → ", page);
            for (int k = 0; k < frames; k++) {
                if (f[k] == -1) printf("[ ] ");
                else            printf("[%d] ", f[k]);
            }
            printf("%s\n", hit >= 0 ? "命中" : "缺页");
        }
    }
    return faults;
}

/* OPT：换出「将来最久不会被用到」的那一页 */
static int simOPT(const int *ref, int n, int frames, int verbose)
{
    int f[16], faults = 0;
    for (int i = 0; i < frames; i++) f[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = ref[i], hit = 0;
        for (int k = 0; k < frames; k++) if (f[k] == page) { hit = 1; break; }

        if (!hit) {
            faults++;
            int slot = -1;
            for (int k = 0; k < frames; k++) if (f[k] == -1) { slot = k; break; }
            if (slot < 0) {
                int farthest = -1;
                for (int k = 0; k < frames; k++) {
                    int next = INT_MAX;
                    for (int j = i + 1; j < n; j++)
                        if (ref[j] == f[k]) { next = j; break; }
                    if (next > farthest) { farthest = next; slot = k; }
                }
            }
            f[slot] = page;
        }
        if (verbose) {
            printf("    %2d → ", page);
            for (int k = 0; k < frames; k++) {
                if (f[k] == -1) printf("[ ] ");
                else            printf("[%d] ", f[k]);
            }
            printf("%s\n", hit ? "命中" : "缺页");
        }
    }
    return faults;
}

/* ==========================================================================
 * 二、进程调度
 * ========================================================================*/

typedef struct { char name; int arrive, burst; } Proc;

static void report(const char *title, Proc *p, int n, int *finish)
{
    double sumT = 0, sumW = 0;
    printf("  %s\n", title);
    printf("    %-6s %-8s %-8s %-8s %-8s %s\n", "进程", "到达", "服务", "完成", "周转", "带权周转");
    for (int i = 0; i < n; i++) {
        int T = finish[i] - p[i].arrive;
        double W = (double)T / p[i].burst;
        sumT += T; sumW += W;
        printf("    %-6c %-8d %-8d %-8d %-8d %.2f\n",
               p[i].name, p[i].arrive, p[i].burst, finish[i], T, W);
    }
    printf("    平均周转时间 %.2f，平均带权周转时间 %.2f\n",
           sumT / n, sumW / n);
}

static void fcfs(Proc *p, int n)
{
    int finish[8], t = 0;
    /* 已按到达时间排序 */
    for (int i = 0; i < n; i++) {
        if (t < p[i].arrive) t = p[i].arrive;
        t += p[i].burst;
        finish[i] = t;
    }
    report("FCFS（先来先服务）", p, n, finish);
}

static void sjf(Proc *p, int n)
{
    int finish[8], done[8] = {0}, t = 0, left = n;
    while (left > 0) {
        int pick = -1, best = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].arrive <= t && p[i].burst < best) {
                best = p[i].burst; pick = i;
            }
        if (pick < 0) {                    /* 当前没有已到达的进程，时间推进 */
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!done[i] && p[i].arrive < next) next = p[i].arrive;
            t = next;
            continue;
        }
        t += p[pick].burst;
        finish[pick] = t;
        done[pick] = 1;
        left--;
    }
    report("SJF（短作业优先，非抢占）", p, n, finish);
}

static void rr(Proc *p, int n, int q)
{
    int remain[8], finish[8], t = 0, left = n;
    int queue[64], head = 0, tail = 0, inq[8] = {0};
    for (int i = 0; i < n; i++) remain[i] = p[i].burst;

    /* 初始：0 时刻到达的入队 */
    for (int i = 0; i < n; i++)
        if (p[i].arrive <= 0) { queue[tail++] = i; inq[i] = 1; }

    while (left > 0) {
        if (head == tail) {                 /* 队空，时间跳到下一个到达 */
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (remain[i] > 0 && p[i].arrive < next && !inq[i]) next = p[i].arrive;
            if (next == INT_MAX) break;
            t = next;
            for (int i = 0; i < n; i++)
                if (remain[i] > 0 && p[i].arrive <= t && !inq[i]) {
                    queue[tail++] = i; inq[i] = 1;
                }
            continue;
        }

        int cur = queue[head++];
        inq[cur] = 0;
        int run = (remain[cur] < q) ? remain[cur] : q;
        t += run;
        remain[cur] -= run;

        /* 新到达的先进队（简化处理，与常见教材一致）
         * 注意要排除刚出队的 cur，否则它会被重复入队 */
        for (int i = 0; i < n; i++)
            if (i != cur && remain[i] > 0 && !inq[i] && p[i].arrive <= t) {
                queue[tail++] = i; inq[i] = 1;
            }

        if (remain[cur] == 0) { finish[cur] = t; left--; }
        else { queue[tail++] = cur; inq[cur] = 1; }
    }
    report("时间片轮转 RR（q=2）", p, n, finish);
}

int main(void)
{
    /* ---------------- ① 页面置换 ---------------- */
    int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int n = 20, frames = 3;

    printf("=== ① 页面置换（引用串 20 个，3 个页框）===\n");
    printf("  引用串：");
    for (int i = 0; i < n; i++) printf("%d ", ref[i]);
    printf("\n\n  FIFO 过程：\n");
    int fifo = simFIFO(ref, n, frames, 1);
    printf("\n  LRU 过程：\n");
    int lru = simLRU(ref, n, frames, 1);
    printf("\n  OPT 过程：\n");
    int opt = simOPT(ref, n, frames, 1);

    printf("\n  %-8s %-10s %s\n", "算法", "缺页次数", "缺页率");
    printf("  %-8s %-10d %.1f%%\n", "FIFO", fifo, fifo * 100.0 / n);
    printf("  %-8s %-10d %.1f%%\n", "LRU", lru, lru * 100.0 / n);
    printf("  %-8s %-10d %.1f%%\n", "OPT", opt, opt * 100.0 / n);
    printf("  ⭐ OPT 是理论下界（无法实现），LRU 最接近，FIFO 最差。\n");

    /* ---------------- ② Belady 异常 ---------------- */
    printf("\n=== ② Belady 异常（FIFO 特有）===\n");
    int ref2[] = {1,2,3,4,1,2,5,1,2,3,4,5};
    int n2 = 12;
    printf("  引用串：");
    for (int i = 0; i < n2; i++) printf("%d ", ref2[i]);
    printf("\n  %-10s %-12s %s\n", "页框数", "FIFO 缺页", "LRU 缺页");
    for (int f = 3; f <= 4; f++)
        printf("  %-10d %-12d %d\n", f, simFIFO(ref2, n2, f, 0), simLRU(ref2, n2, f, 0));
    printf("  ⭐ 3 个页框缺页 9 次，4 个页框却缺页 10 次 —— 页框变多反而更差。\n");
    printf("     LRU 不会出现这种异常（它满足「栈式」性质）。\n");

    /* ---------------- ③ 调度 ---------------- */
    printf("\n=== ③ 进程调度 ===\n");
    Proc p1[4] = {{'A',0,8},{'B',1,4},{'C',2,9},{'D',3,5}};
    Proc p2[4], p3[4];
    memcpy(p2, p1, sizeof(p1));
    memcpy(p3, p1, sizeof(p1));

    printf("  进程：A(到达0,服务8) B(1,4) C(2,9) D(3,5)\n\n");
    fcfs(p1, 4);
    printf("\n");
    sjf(p2, 4);
    printf("\n");
    rr(p3, 4, 2);

    printf("\n  ⭐ SJF 的平均周转时间最短，但长作业可能「饿死」。\n");
    printf("     FCFS 最简单但「护航效应」明显（短作业排在长作业后面等很久）。\n");
    printf("     RR 的响应最公平，时间片大小的选择是关键。\n");
    return 0;
}
