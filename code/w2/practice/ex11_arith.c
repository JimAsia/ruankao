/* ex11 —— 两个整数的五种运算 + 真实商
 * 要求：读入两个整数 a、b（假设 b 不为 0），输出：
 *   a + b、a - b、a * b 的值
 *   a / b 的整数商
 *   a % b 的余数
 *   a / b 的真实商（保留 3 位小数）
 *
 * 测试数据：输入 17 5
 *   期望输出：
 *     和 = 22，差 = 12，积 = 85
 *     整数商 = 3，余数 = 2
 *     真实商 = 3.400
 *
 * 注意最后一行：必须让操作数变成浮点，别写成 (double)(a / b)
 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    /* TODO: 读入 a 和 b */
	scanf("%d%d", &a, &b);
	
    /* TODO: 输出六项结果 */
	printf("和 = %d，差 = %d，积 = %d，\n整数商 = %d，余数 = %d，\n真实商 = %.3f\n", a+b, a-b, a*b, a/b, a%b, (double)a/b);
    return 0;
}
