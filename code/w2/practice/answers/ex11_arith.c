/* ex11 参考答案 —— 五种运算 + 真实商 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    printf("请输入两个整数(空格分隔): ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("输入格式不对\n");
        return 1;
    }

    printf("和 = %d，差 = %d，积 = %d\n", a + b, a - b, a * b);
    printf("整数商 = %d，余数 = %d\n", a / b, a % b);

    /* 关键：转换必须在除法之前 */
    printf("真实商 = %.3f\n", (double)a / b);

    return 0;
}
