/* ex71 参考答案 —— 递归求和 */
#include <stdio.h>

int sumTo(int n)
{
    if (n == 1) return 1;               /* 出口 */
    return n + sumTo(n - 1);            /* 递推 */
}

int main(void)
{
    printf("sumTo(10) = %d\n", sumTo(10));
    printf("sumTo(100) = %d\n", sumTo(100));
    return 0;
}

/* 递推过程：
 *   sumTo(10) = 10 + sumTo(9)
 *             = 10 + 9 + sumTo(8)
 *             = ...
 *             = 10 + 9 + ... + 2 + sumTo(1)
 *             = 10 + 9 + ... + 2 + 1
 *
 * 注意 100 层递归没问题，但如果是 100 万层就会栈溢出。
 * 这题用循环其实更好（连续空格判等）：
 *   int s = 0; for (int i = 1; i <= n; i++) s += i;
 * 递归版的价值在于练习「递推思维」，不是为了性能。 */
