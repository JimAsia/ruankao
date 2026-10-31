/* ex04 参考答案 —— 圆的周长和面积 */
#include <stdio.h>

#define PI 3.1415926

int main(void)
{
    double r = 0.0;

    printf("请输入半径: ");
    if (scanf("%lf", &r) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    printf("周长 = %.3f，面积 = %.3f\n", 2 * PI * r, PI * r * r);
    return 0;
}
