/* ex15 参考答案 —— 位运算实战 */
#include <stdio.h>

int main(void)
{
    unsigned int a = 0, b = 0;

    printf("请输入两个非负整数(空格分隔): ");
    if (scanf("%u %u", &a, &b) != 2) {
        printf("输入格式不对\n");
        return 1;
    }

    printf("a = %u, b = %u\n", a, b);
    printf("a & b = %u\n", a & b);
    printf("a | b = %u\n", a | b);
    printf("a ^ b = %u\n", a ^ b);

    /* 最低位是 0 → 偶数，是 1 → 奇数 */
    printf("a 的最低位 = %u   （0 表示偶数，1 表示奇数）\n", a & 1);

    printf("a << 1 = %u\n", a << 1);
    printf("a >> 1 = %u\n", a >> 1);

    return 0;
}
