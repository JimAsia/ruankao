/* ex05 —— 交换两个变量的值
 * 这是软考应用技术里反复出现的最小模型，务必手熟。
 *
 * 第一问：读入两个整数 a、b，用第三个变量 temp 交换它们的值，然后输出。
 * 第二问（进阶）：不许用第三个变量，只靠加减法实现交换。
 *
 * 测试：输入 3 8
 *  第一问期望：交换后 a = 8, b = 3
 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    /* TODO 第一问 */
	/*
	int temp = 0;
	scanf("%d%d", &a, &b);
	temp = a;
	a = b;
	b = temp;
	printf("交换后 a = %d, b = %d", a, b);
	*/
	
	scanf("%d%d", &a, &b);
	a = a + b;
	b = a - b;
	a = a - b;
	printf("交换后 a = %d, b = %d", a, b);
    /* TODO 第二问：注释掉上面的代码，换成加减法版本 */
    /* 提示：a = a + b;  b = a - b;  a = a - b;  想一想为什么成立 */

    return 0;
}
