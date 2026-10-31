/* ex36 参考答案 —— 最大公约数与最小公倍数 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    printf("请输入两个正整数(空格分隔): ");
    if (scanf("%d %d", &a, &b) != 2 || a <= 0 || b <= 0) {
        printf("输入格式不对\n");
        return 1;
    }

    /* ⚠️ 先存一份原始值：辗转相除会把 a、b 改掉，
     * 后面算最小公倍数时还需要用原值。 */
    int origA = a, origB = b;

    /* 辗转相除法：反复用余数替换，直到除数为 0 */
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    /* 循环结束时 a 就是最大公约数（gcd） */
    int gcd = a;

    /* 最小公倍数 = 两数之积 / 最大公约数
     * 先除后乘能减小溢出的可能：origA / gcd * origB */
    int lcm = origA / gcd * origB;

    printf("最大公约数 = %d\n", gcd);
    printf("最小公倍数 = %d\n", lcm);

    /* 验算 12 和 18：
     *   gcd(12,18) → 12%18=12, 18%12=6, 12%6=0 → gcd=6
     *   lcm = 12/6*18 = 2*18 = 36
     */

    return 0;
}
