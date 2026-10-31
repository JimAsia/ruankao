/* ex02 参考答案 —— 两个整数的四则运算 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    printf("请输入两个整数(空格分隔): ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("输入格式不对\n");
        return 1;
    }

    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);
    printf("%d / %d = %d\n", a, b, a / b);     /* 整数除法，只要商 */
    printf("%d %% %d = %d\n", a, b, a % b);    /* %% 打出百分号本身 */

    return 0;
}
