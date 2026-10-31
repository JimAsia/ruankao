/* ex74 —— 递归求最大公约数
 * 要求：写递归函数 int gcd(int a, int b)，用辗转相除法。
 *
 * 测试：gcd(12, 18) = 6
 *       gcd(100, 75) = 25
 *       gcd(17, 5) = 1
 *
 * 提示：出口 b == 0 返回 a；递推 gcd(b, a % b)
 *       三行代码就能写完，这是递归最优雅的例子。
 */
#include <stdio.h>

int gcd(int a, int b)
{
    /* TODO */
    return 0;
}

int main(void)
{
    printf("gcd(12, 18) = %d\n", gcd(12, 18));
    printf("gcd(100, 75) = %d\n", gcd(100, 75));
    printf("gcd(17, 5) = %d\n", gcd(17, 5));
    return 0;
}
