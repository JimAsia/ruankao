/* ex156_predict.c —— 参考答案 */

#include <stdio.h>
#include <math.h>

#define OPS_PER_SEC 100000000.0          /* 1 亿次/秒 */

/* 算出操作次数 */
static long long opsOf(char complexity, int n)
{
    switch (complexity) {
        case 'a':                        /* O(n) */
            return (long long)n;

        case 'b': {                      /* O(n log n) */
            int lg = 0, x = n;
            while (x > 1) { x /= 2; lg++; }
            return (long long)n * (long long)lg;
        }

        case 'c':                        /* O(n^2) */
            return (long long)n * (long long)n;

        case 'd': {                      /* O(2^n) */
            if (n > 62) return -1;       /* 用 long long 也装不下 */
            long long r = 1;
            for (int i = 0; i < n; i++) r *= 2;
            return r;
        }

        default:
            return -1;
    }
}

/* 换算成秒 */
static double secondsOf(long long ops)
{
    if (ops < 0) return -1.0;            /* 约定：负数表示「算不完」 */
    return (double)ops / OPS_PER_SEC;
}

static void printTime(double sec)
{
    char buf[32];
    if (sec < 0)            snprintf(buf, sizeof(buf), "算不完");
    else if (sec < 1.0)     snprintf(buf, sizeof(buf), "%.4f秒", sec);
    else if (sec < 60.0)    snprintf(buf, sizeof(buf), "%.2f秒", sec);
    else if (sec < 3600.0)  snprintf(buf, sizeof(buf), "%.1f分钟", sec / 60.0);
    else if (sec < 86400.0) snprintf(buf, sizeof(buf), "%.1f小时", sec / 3600.0);
    else                    snprintf(buf, sizeof(buf), "%.1f天", sec / 86400.0);
    printf("%-16s", buf);            /* 整体按宽度对齐，单位不会跑偏 */
}

int main(void)
{
    printf("%-10s %-16s %-16s %-16s %s\n",
           "n", "O(n)", "O(n log n)", "O(n^2)", "O(2^n)");
    printf("----------------------------------------------------------------------\n");

    int ns[] = {1000, 10000, 100000, 1000000};
    for (int k = 0; k < 4; k++) {
        int n = ns[k];
        printf("%-10d ", n);
        printTime(secondsOf(opsOf('a', n)));
        printTime(secondsOf(opsOf('b', n)));
        printTime(secondsOf(opsOf('c', n)));
        printTime(secondsOf(opsOf('d', n)));
        printf("\n");
    }

    printf("\n=== 具体数字（n = 10^6）===\n");
    long long a = opsOf('a', 1000000);
    long long b = opsOf('b', 1000000);
    long long c = opsOf('c', 1000000);
    printf("  O(n)       = %lld 次操作  → %.4f 秒\n", a, secondsOf(a));
    printf("  O(n log n) = %lld 次操作  → %.2f 秒\n", b, secondsOf(b));
    printf("  O(n^2)     = %lld 次操作  → %.1f 小时\n", c, secondsOf(c) / 3600.0);

    printf("\n=== 结论：机考 1 秒能做什么 ===\n");
    printf("  常见评测机每秒约 1 亿次基本操作（保守按 1e8 算）。\n");
    printf("  n = 10^6 时，只有 O(n) 和 O(n log n) 能过；\n");
    printf("  n = 10^6 用 O(n^2) 要几个小时 —— 这就是「超时」。\n");

    printf("\n  ⭐ 做题时的经验值（记住这张表）：\n");
    printf("     n ≤ 10    → 可以 O(n!) 或 O(2^n)\n");
    printf("     n ≤ 1000  → 可以 O(n^2)\n");
    printf("     n ≤ 10^5  → 需要 O(n log n)\n");
    printf("     n ≤ 10^7  → 只能 O(n)\n");

    printf("\n=== 常见误区 ===\n");
    printf("  1. 「O(n log n) 比 O(n) 只多一点」—— n=10^6 时差 20 倍，不是一点。\n");
    printf("  2. 「两个算法都 O(n)，速度一样」—— 常数可能差 100 倍。\n");
    printf("  3. 「小数据测过能跑就行」—— n=100 时 O(n^2) 只要 0.1 毫秒，\n");
    printf("     看不出问题，规模一上来就崩。\n");

    return 0;
}
