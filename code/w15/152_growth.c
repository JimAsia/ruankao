/* 152_growth.c —— 用真实耗时验证复杂度
 *
 * 上一节数的是「操作次数」（理论），这一节量的是「花了多少时间」（实测）。
 * 两者结论一致，这才能说明复杂度是真的在描述运行时间。
 *
 * 计时用 clock()，它返回程序占用的 CPU 时钟数，除以 CLOCKS_PER_SEC 得秒数。
 * Windows 上 CLOCKS_PER_SEC = 1000，精度是毫秒。
 */

#include <stdio.h>
#include <time.h>

/* 用 volatile 防止编译器把整个循环优化掉
 * （不加的话 -O2 可能直接算出结果，循环一次都不跑，计时全为 0） */
static volatile long long g_sink = 0;

/* O(n)：单层循环 */
static long long workLinear(int n)
{
    long long s = 0;
    for (int i = 0; i < n; i++) {
        s += i;
    }
    return s;
}

/* O(n^2)：双层循环 */
static long long workQuadratic(int n)
{
    long long s = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s += (i ^ j);
        }
    }
    return s;
}

/* 计时辅助：跑一遍 fn(n)，返回毫秒 */
static double timeIt(long long (*fn)(int), int n)
{
    clock_t t0 = clock();
    g_sink = fn(n);
    clock_t t1 = clock();
    return (double)(t1 - t0) * 1000.0 / (double)CLOCKS_PER_SEC;
}

int main(void)
{
    printf("=== ① O(n)：n 翻倍，时间应该翻倍 ===\n");
    printf("  %-10s %-12s %s\n", "n", "耗时(ms)", "比上一行");
    printf("  ----------------------------------------\n");

    /* 注意：clock() 在 Windows 上精度是 1 毫秒，
       所以 n 必须足够大，否则全部量出 0.000 —— 这也是「计时法」的局限之一 */
    int linNs[] = {1 << 25, 1 << 26, 1 << 27, 1 << 28};   /* 约 3300万 ~ 2.7亿 */
    double prev = 0;
    for (int k = 0; k < 4; k++) {
        int n = linNs[k];
        /* 跑 3 次取最快，减少抖动 */
        double best = timeIt(workLinear, n);
        for (int r = 0; r < 2; r++) {
            double t = timeIt(workLinear, n);
            if (t < best) best = t;
        }
        printf("  %-10d %-12.3f ", n, best);
        if (prev > 0) printf("%.2f 倍", best / prev);
        printf("\n");
        prev = best;
    }

    printf("\n=== ② O(n^2)：n 翻倍，时间应该变 4 倍 ===\n");
    printf("  %-10s %-12s %s\n", "n", "耗时(ms)", "比上一行");
    printf("  ----------------------------------------\n");

    int quadNs[] = {4000, 8000, 16000, 32000};
    prev = 0;
    for (int k = 0; k < 4; k++) {
        int n = quadNs[k];
        double best = timeIt(workQuadratic, n);
        for (int r = 0; r < 2; r++) {
            double t = timeIt(workQuadratic, n);
            if (t < best) best = t;
        }
        printf("  %-10d %-12.3f ", n, best);
        if (prev > 0) printf("%.2f 倍", best / prev);
        printf("\n");
        prev = best;
    }

    printf("\n  ⭐ 关键观察：同样是「n 翻倍」，\n");
    printf("     O(n)   的时间涨约 2 倍\n");
    printf("     O(n^2) 的时间涨约 4 倍\n");
    printf("     这就是复杂度的实际含义 —— 它预测「规模变大时会发生什么」。\n");

    /* ---------- ③ 同一台机器，平方级在哪个 n 开始变慢 ---------- */
    printf("\n=== ③ 同样的操作次数，不同复杂度差多少 ===\n");
    printf("  假设每秒能执行 1 亿次基本操作：\n\n");
    printf("  %-12s %-16s %s\n", "复杂度", "n = 10^6 时", "说明");
    printf("  ------------------------------------------------------\n");
    printf("  %-12s %-16s %s\n", "O(log n)", "约 20 次", "瞬间");
    printf("  %-12s %-16s %s\n", "O(n)", "100 万次", "约 0.01 秒");
    printf("  %-12s %-16s %s\n", "O(n log n)", "2000 万次", "约 0.2 秒");
    printf("  %-12s %-16s %s\n", "O(n^2)", "1 万亿次", "约 2.8 小时");
    printf("  %-12s %-16s %s\n", "O(2^n)", "天文数字", "到宇宙毁灭也算不完");

    printf("\n  ⭐ 这就是为什么「把 O(n^2) 优化成 O(n log n)」价值巨大：\n");
    printf("     100 万条数据，前者要几小时，后者零点几秒。\n");

    /* ---------- ④ 为什么不能用计时判断复杂度 ---------- */
    printf("\n=== ④ 计时法的三个陷阱 ===\n");
    printf("  1. 受机器影响：同一段代码，你的电脑和服务器差 5 倍\n");
    printf("  2. 受常数影响：O(n) 但循环体很重，可能比 O(n^2) 但循环体极轻还慢\n");
    printf("  3. 小数据看不出差别：n=10 时，O(n^2) 和 O(n log n) 都不到 1 微秒\n");
    printf("\n  ⭐ 所以复杂度分析是「数次数」，不是「掐表」。\n");
    printf("     计时只能用来验证理论，不能用来得出理论。\n");

    return 0;
}
