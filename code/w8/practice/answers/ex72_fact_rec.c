/* ex72 参考答案 —— 递归求阶乘 */
#include <stdio.h>

long long fact(int n)
{
    if (n <= 1) return 1;               /* 出口：0! 和 1! 都是 1 */
    return (long long)n * fact(n - 1);  /* 递推 */
}

int main(void)
{
    printf("fact(10) = %lld\n", fact(10));
    printf("fact(20) = %lld\n", fact(20));
    return 0;
}

/* ⚠️ 两个要点：
 *   ① 返回类型必须是 long long。20! = 2432902008176640000，
 *     远超 int 的 21 亿上限。
 *   ② 出口写 n <= 1 而不是 n == 1，这样 fact(0) 也能正确返回 1
 *     （数学上 0! = 1，是组合数计算的基础）。
 *
 * 如果出口只写 n == 1，那 fact(0) 会一直递归到 n = -1, -2...
 * 直到栈溢出 —— 这是「出口没覆盖边界」的典型后果。 */
