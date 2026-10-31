/* 71_recursion_basic.c —— 递归的三要素
 *
 * 递归 = 函数调用自己。
 * 三要素：出口、递推关系、规模缩小。
 */

#include <stdio.h>

/* ---------- ① 最简单的递归：倒计数 ---------- */
void countdown(int n)
{
    if (n == 0) {                       /* 出口 */
        printf("发射！\n");
        return;
    }
    printf("%d ", n);
    countdown(n - 1);                   /* 递推 + 规模缩小 */
}

/* ---------- ② 追踪调用栈：进栈和出栈的顺序 ---------- */
void trace(int n)
{
    printf("  [进栈] n = %d\n", n);

    if (n == 0) {
        printf("  [出口] n = 0，开始返回\n");
        return;
    }

    trace(n - 1);                       /* 递归调用 */

    printf("  [出栈] n = %d\n", n);     /* 这一句在递归返回之后才执行 */
}

/* ---------- ③ 递归求和：1 + 2 + ... + n ---------- */
int sumTo(int n)
{
    if (n == 1) return 1;               /* 出口 */
    return n + sumTo(n - 1);            /* 递推 */
}

/* ---------- ④ 递归求幂：x^n ---------- */
long long power(int x, int n)
{
    if (n == 0) return 1;               /* 出口：x^0 = 1 */
    return x * power(x, n - 1);
}

/* ---------- ⑤ 打印数字的每一位（正序） ---------- */
void printDigits(int n)
{
    if (n < 10) {                       /* 出口：只剩一位 */
        printf("%d ", n);
        return;
    }
    printDigits(n / 10);                /* 先递归处理高位 */
    printf("%d ", n % 10);              /* 再输出这一位 */
}

int main(void)
{
    printf("=== ① 倒计数 ===\n");
    countdown(5);

    printf("\n=== ② 调用栈的进与出 ===\n");
    trace(3);
    printf("  注意顺序：先进后出，像栈一样\n");

    printf("\n=== ③ 递归求和 ===\n");
    printf("  sumTo(10) = %d\n", sumTo(10));
    printf("  递推过程：sumTo(10) = 10 + sumTo(9) = 10 + 9 + sumTo(8) = ...\n");

    printf("\n=== ④ 递归求幂 ===\n");
    printf("  power(2, 10) = %lld\n", power(2, 10));
    printf("  power(3, 5)  = %lld\n", power(3, 5));

    printf("\n=== ⑤ 正序打印各位数字 ===\n");
    printf("  3725 → ");
    printDigits(3725);
    printf("\n");
    printf("  关键：先递归再输出，顺序就是正的\n");
    printf("  如果先输出再递归，会变成倒序（5257 那样）\n");

    printf("\n=== 三要素检查 ===\n");
    printf("  函数         出口              递推关系\n");
    printf("  countdown    n == 0            countdown(n-1)\n");
    printf("  sumTo        n == 1            n + sumTo(n-1)\n");
    printf("  power        n == 0            x * power(x, n-1)\n");
    printf("  printDigits  n < 10            printDigits(n/10)\n");
    printf("  每个都必须满足：每次调用都让 n 更靠近出口\n");

    return 0;
}
