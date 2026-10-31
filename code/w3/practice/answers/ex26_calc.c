/* ex26 参考答案 —— 简易计算器 */
#include <stdio.h>

int main(void)
{
    double a = 0.0, b = 0.0, result = 0.0;
    char op = 0;

    printf("请输入算式(例如 3 + 4): ");
    /* %c 前面的空格很重要：跳过数字后面残留的空白，否则 op 会读到空格 */
    if (scanf("%lf %c %lf", &a, &op, &b) != 3) {
        printf("输入格式不对\n");
        return 1;
    }

    switch (op) {
        case '+':
            result = a + b;
            printf("%.2f + %.2f = %.2f\n", a, b, result);
            break;

        case '-':
            result = a - b;
            printf("%.2f - %.2f = %.2f\n", a, b, result);
            break;

        case '*':
            result = a * b;
            printf("%.2f * %.2f = %.2f\n", a, b, result);
            break;

        case '/':
            /* 除法必须单独判 0，否则运行时直接崩（浮点除零会得到 inf，整数除零是崩溃） */
            if (b == 0.0) {
                printf("除数不能为 0\n");
            } else {
                result = a / b;
                printf("%.2f / %.2f = %.2f\n", a, b, result);
            }
            break;

        default:
            printf("无效运算符：%c\n", op);
            break;
    }

    return 0;
}
