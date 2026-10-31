/* ex16 参考答案 —— 类型转换的四种情形 */
#include <stdio.h>

int main(void)
{
    int a = 17, b = 5;

    /* ① 先做整数除法，再把结果 3 转成 double */
    double x = a / b;
    printf("① a / b          = %.2f      ← 先除后转，小数早丢了\n", x);

    /* ② 先把 a 转成 double，再做除法 */
    double y = (double)a / b;
    printf("② (double)a / b  = %.2f      ← 先转后除，才是真商\n", y);

    /* ③ 浮点转整数：向零截断 */
    double d = -3.99;
    int n = (int)d;
    printf("③ (int)(-3.99)   = %d        ← 向零截断\n", n);

    /* ④ 无符号溢出：按 256 取模回绕 */
    unsigned char c = 200;
    c = c + 100;
    printf("④ 200 + 100      = %u        ← 无符号按 256 取模回绕\n", c);

    return 0;
}
