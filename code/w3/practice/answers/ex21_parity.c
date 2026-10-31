/* ex21 参考答案 —— 判断奇偶与正负 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    printf("请输入一个整数: ");
    if (scanf("%d", &n) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    /* 奇偶：n % 2 != 0 判断奇数。
     * 注意负数：-3 % 2 得 -1，不等于 0，所以这个写法对负数也成立。
     * 也可以写 n & 1 —— 最低位是 1 就是奇数。 */
    if (n % 2 != 0)
        printf("%d 是奇数\n", n);
    else
        printf("%d 是偶数\n", n);

    /* 正负：三选一，用 if - else if - else */
    if (n > 0)
        printf("%d 是正数\n", n);
    else if (n < 0)
        printf("%d 是负数\n", n);
    else
        printf("%d 是零\n", n);

    return 0;
}
