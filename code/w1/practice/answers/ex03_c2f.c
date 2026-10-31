/* ex03 参考答案 —— 摄氏转华氏 */
#include <stdio.h>

int main(void)
{
    double c = 0.0, f = 0.0;

    printf("请输入摄氏温度: ");
    if (scanf("%lf", &c) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    /* 关键：写 9.0 / 5.0，不能写 9 / 5（那是整数除法，等于 1） */
    f = c * 9.0 / 5.0 + 32.0;

    printf("%.2f\n", f);
    return 0;
}
