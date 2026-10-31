/* ex71 —— 递归求和
 * 要求：写递归函数 int sumTo(int n)，返回 1+2+...+n。
 *
 * 测试：sumTo(10) = 55
 *
 * 提示：出口 n == 1 返回 1；递推 n + sumTo(n-1)
 */
#include <stdio.h>

int sumTo(int n)
{
    /* TODO */
    return 0;
}

int main(void)
{
    printf("sumTo(10) = %d\n", sumTo(10));
    printf("sumTo(100) = %d\n", sumTo(100));
    return 0;
}
