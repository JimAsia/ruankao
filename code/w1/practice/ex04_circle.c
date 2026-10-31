/* ex04 —— 圆的周长和面积
 * 要求：读入半径 r（小数），输出周长和面积，各保留 3 位小数。
 *   周长 = 2 × π × r
 *   面积 = π × r × r
 * 圆周率用 3.1415926，或者用 <math.h> 里的 M_PI（需 #define _USE_MATH_DEFINES）
 *
 * 测试：输入 2     输出 周长 = 12.566，面积 = 12.566
 */
#include <stdio.h>

int main(void)
{
    double r = 0.0;

    /* TODO */
	scanf("%lf", &r);
	double pi = 3.1415926;
	printf("周长=%.3f，面积=%.3f\n", pi * 2 * r, pi * r * r);
    return 0;
}
