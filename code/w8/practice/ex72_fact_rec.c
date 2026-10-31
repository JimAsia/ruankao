/* ex72 —— 递归求阶乘
 * 要求：写递归函数 long long fact(int n)，返回 n!。
 *
 * 测试：fact(10) = 3628800
 *       fact(20) = 2432902008176640000
 *
 * 提示：出口 n <= 1 返回 1；递推 n * fact(n-1)
 *       返回类型必须是 long long。
 */
#include <stdio.h>

long long fact(int n)
{
    /* TODO */
    return 1;
}

int main(void)
{
    printf("fact(10) = %lld\n", fact(10));
    printf("fact(20) = %lld\n", fact(20));
    return 0;
}
