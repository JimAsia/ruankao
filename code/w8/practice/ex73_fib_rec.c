/* ex73 —— 递归求斐波那契
 * 要求：写递归函数 long long fib(int n)，返回第 n 项（前两项都是 1）。
 *
 * 测试：fib(30) = 832040
 *
 * 提示：出口 n <= 2 返回 1；递推 fib(n-1) + fib(n-2)
 *
 * ⚠️ 这题只要求你写出递归版。它其实很慢（fib(30) 要调用 166 万次），
 *    这正是书上说的「朴素递归的问题」，S2 会讲怎么优化。
 */
#include <stdio.h>

long long fib(int n)
{
    /* TODO */
    return 1;
}

int main(void)
{
    printf("fib(10) = %lld\n", fib(10));
    printf("fib(20) = %lld\n", fib(20));
    printf("fib(30) = %lld\n", fib(30));
    return 0;
}
