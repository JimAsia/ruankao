/* ex22 —— 三个数的最大值与最小值
 * 要求：读入三个整数 a、b、c，输出最大值和最小值。
 *      【必须用 if 判断，不许用 ?: 三元运算符】—— 这题练的是分支。
 *
 * 测试：输入 3 9 5    输出：最大值 = 9，最小值 = 3
 *
 * 提示：先假设 a 是最大，再依次和 b、c 比。
 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0, c = 0;

    /* TODO: 读入三个数 */
	scanf("%d%d%d", &a, &b, &c);
    /* TODO: 求最大值 */
	int t = 0;
	if (a > b) {t = a; a = b; b = t;}
	if (a > c) {t = a; a = c; c = t;}
	if (b > c) {t = b; b = c; c = t;}
    /* TODO: 求最小值 */
	printf("最大值 = %d, 最小值 = %d", c, a);
    return 0;
}
