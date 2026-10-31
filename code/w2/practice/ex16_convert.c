/* ex16 —— 类型转换的四种情形
 *
 * 要求：不读输入，直接演示并输出下面四种情况，每种后面用注释写清结论：
 *   ① 整数除法 → 赋值给 double     int a = 17, b = 5; double x = a / b;
 *   ② 先转换再除法                 double y = (double)a / b;
 *   ③ 浮点转整数（截断方向）        double d = -3.99; int n = (int)d;
 *   ④ 无符号溢出                   unsigned char c = 200; c = c + 100;
 *
 * 期望输出格式（数值请自己核对）：
 *   ① a / b        = 3.00      ← 先除后转，小数早丢了
 *   ② (double)a / b = 3.40     ← 先转后除，才是真商
 *   ③ (int)(-3.99) = -3        ← 向零截断
 *   ④ 200 + 100    = 44        ← 无符号按 256 取模回绕
 */
#include <stdio.h>

int main(void)
{
    int a = 17, b = 5;

    /* ① TODO */
	double x = a / b;
	printf("a / b = %.2f\n", x);
    /* ② TODO */
	double y = (double)a / b;
	printf("%.2f\n", y);
    /* ③ TODO */
	double d = -3.99; 
	int n = (int)d;
	printf("%d\n", n);
    /* ④ TODO */
	unsigned char c = 200; 
	c = c + 100;
	printf("%d\n", c);
    return 0;
}
