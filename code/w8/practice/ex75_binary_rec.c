/* ex75 —— 递归输出二进制
 * 要求：写递归函数 void toBinary(int n)，正序输出 n 的二进制（不带前导零）。
 *
 * 测试：toBinary(10)   → 1010
 *       toBinary(255)  → 11111111
 *       toBinary(1024) → 10000000000
 *
 * 提示：出口 n == 0 直接 return（什么都不做）；
 *       先递归 toBinary(n/2)，再 printf("%d", n%2)。
 *       ⚠️ 顺序不能反 —— 先递归再输出才是正序。
 */
#include <stdio.h>

void toBinary(int n)
{
    /* TODO */
}

int main(void)
{
    printf("10   → ");
    toBinary(10);
    printf("\n");

    printf("255  → ");
    toBinary(255);
    printf("\n");

    printf("1024 → ");
    toBinary(1024);
    printf("\n");

    return 0;
}
