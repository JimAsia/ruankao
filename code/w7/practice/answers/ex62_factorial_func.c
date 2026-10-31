/* ex62 参考答案 —— 用函数计算阶乘 */
#include <stdio.h>

long long factorial(int n)
{
    /* 累乘范式，初值必须是 1 */
    long long f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main(void)
{
    for (int i = 1; i <= 15; i++) {
        printf("%2d! = %lld\n", i, factorial(i));
    }

    /* ⚠️ 返回值类型必须是 long long：
     *   12! = 479001600        还在 int 范围内（21 亿）
     *   13! = 6227020800       已经超了
     *   15! = 1307674368000    必须 long long
     *
     * 如果函数写成 int factorial(int n)，从 13! 开始结果就是错的，
     * 而且编译器不会报错 —— 这是最危险的 bug 类型。
     *
     * 这也说明「函数签名里的类型」是契约的一部分：
     * 返回类型定错了，函数内部算得再对也没用。 */

    return 0;
}
