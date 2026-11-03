/* ex36 —— 最大公约数与最小公倍数
 * 要求：读入两个正整数 a、b，输出它们的最大公约数和最小公倍数。
 *
 * 测试：输入 12 18
 *   输出：最大公约数 = 6
 *         最小公倍数 = 36
 *
 * 提示（辗转相除法）：
 *   while (b != 0) {
 *       t = a % b;
 *       a = b;
 *       b = t;
 *   }
 *   循环结束时 a 就是最大公约数。
 *
 * 最小公倍数 = 原两数之积 / 最大公约数。
 * ⚠️ 注意：求 lcm 时要用【原始的 a、b】，而辗转相除会把它们改掉，
 *    所以要先存一份。
 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d%d", &a, &b);
	//
	int t = 0;
	int mul = a*b;
	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}
	int m = 0;
	m = mul / a;
	
	printf("最大公约数 = %d\n", a);
	printf("最小公倍数 = %d\n", m);
	
    return 0;
}
