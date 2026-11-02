/* ex32 —— 阶乘表
 * 要求：输出 1! 到 10! 的值，每行一个，格式：
 *   1! = 1
 *   2! = 2
 *   3! = 6
 *   ...
 *   10! = 3628800
 *
 * 关键：用【累乘】范式，而不是每轮从头乘一遍。
 *       fac 是 long long 类型。
 */
#include <stdio.h>

int main(void)
{
    /* TODO */
	long long fac = 1;
	for (int i = 1; i <= 10; ++i) {
		fac *= i;
		printf("%d! = %lld\n", i, fac);
	}
	
    return 0;
}
