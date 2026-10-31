/* 11_arith.c —— 算术运算符：+ - * / %
 *
 * 本文件只用到 W1 学过的变量和 printf，不涉及分支与循环。
 */
#include <stdio.h>

int main(void)
{
    int a = 17, b = 5;

    printf("a = %d, b = %d\n\n", a, b);

    /* ---------- 五种算术运算 ---------- */
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d     整数除法，只要商\n", a / b);
    printf("a %% b = %d     取余，只要余数\n", a % b);

    /* ---------- 整数除法的截断方向：向零 ---------- */
    printf("\n=== 整数除法向零截断，不是向下取整 ===\n");
    printf("  7 /  2 = %d\n",  7 /  2);
    printf(" -7 /  2 = %d\n", -7 /  2);
    printf("  7 / -2 = %d\n",  7 / -2);
    printf(" -7 / -2 = %d\n", -7 / -2);

    /* ---------- 取余的符号跟着被除数走（C99 起） ---------- */
    printf("\n=== 取余的符号跟被除数走 ===\n");
    printf("  7 %%  3 = %d\n",  7 %  3);
    printf(" -7 %%  3 = %d\n", -7 %  3);
    printf("  7 %% -3 = %d\n",  7 % -3);
    printf(" -7 %% -3 = %d\n", -7 % -3);

    /* ---------- 想要小数：必须让操作数变成浮点 ---------- */
    printf("\n=== 想要小数，先把某个操作数变成 double ===\n");
    printf("(double)a / b = %.2f\n", (double)a / b);
    printf("a / (double)b = %.2f\n", a / (double)b);
    printf("a / 5.0       = %.2f\n", a / 5.0);
    printf("直接写 a / b  = %d          ← 整数除法，小数部分直接丢掉\n", a / b);

    /* ---------- 混合类型自动提升 ---------- */
    printf("\n=== 混合运算自动提升到更大的类型 ===\n");
    printf("5 + 2.0  = %.1f\n", 5 + 2.0);
    printf("'A' + 1  = %d      字符当整数参与运算\n", 'A' + 1);

    return 0;
}
