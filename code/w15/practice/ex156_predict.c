/* ex156_predict.c —— 综合：用复杂度预测运行时间
 *
 * 这是复杂度最实用的用途：**在写代码之前就知道会不会超时**。
 *
 * 要求：
 *   1. 实现 opsOf(complexity, n)：根据复杂度类型算出大致操作次数
 *        'a' = O(n)          → n
 *        'b' = O(n log n)    → n * log2(n)
 *        'c' = O(n^2)        → n * n
 *        'd' = O(2^n)        → 2^n（n > 60 时直接返回 -1 表示「天文数字」）
 *   2. 实现 secondsOf(ops)：假设每秒 1 亿次操作，换算成秒
 *   3. 对 n = 1000 / 10000 / 100000 / 1000000 输出四种复杂度的预计耗时
 *
 * 预期（n = 1000000 那一行）：
 *   O(n)        约 0.01 秒
 *   O(n log n)  约 0.2 秒
 *   O(n^2)      约 2.8 小时
 *   O(2^n)      天文数字
 *
 * 提示：
 *   log2 用循环算：int lg = 0; while ((1 << lg) < n) lg++;
 *   或者用 math.h 的 log2(n)（编译要加 -lm）
 *   2^n 要用 long long 并防止溢出
 */

#include <stdio.h>
#include <math.h>

/* TODO 1：算出操作次数 */
static long long opsOf(char complexity, int n)
{
    (void)complexity; (void)n;
    return 0;
}

/* TODO 2：换算成秒（每秒 1 亿次操作） */
static double secondsOf(long long ops)
{
    (void)ops;
    return 0.0;
}

/* TODO 3：把秒数格式化成人能读的形式（秒/分钟/小时/天） */
static void printTime(double sec)
{
    if (sec < 0)            { printf("%-14s", "算不完"); return; }
    if (sec < 1.0)          { printf("%-14.4f秒", sec); return; }
    if (sec < 60.0)         { printf("%-14.2f秒", sec); return; }
    if (sec < 3600.0)       { printf("%-14.1f分钟", sec / 60.0); return; }
    if (sec < 86400.0)      { printf("%-14.1f小时", sec / 3600.0); return; }
    printf("%-14.1f天", sec / 86400.0);
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

    printf("\n=== 结论：机考 1 秒能做什么 ===\n");
    printf("  常见评测机每秒约 1 亿次基本操作（保守按 1e8 算）。\n");
    printf("  n = 10^6 时，只有 O(n) 和 O(n log n) 能过；\n");
    printf("  n = 10^6 用 O(n^2) 要几个小时 —— 这就是「超时」。\n");
    printf("\n  ⭐ 做题时的经验值：\n");
    printf("     n ≤ 10    → 可以 O(n!) 或 O(2^n)\n");
    printf("     n ≤ 1000  → 可以 O(n^2)\n");
    printf("     n ≤ 10^5  → 需要 O(n log n)\n");
    printf("     n ≤ 10^7  → 只能 O(n)\n");

    return 0;
}
