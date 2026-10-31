/* ex75 参考答案 —— 递归输出二进制 */
#include <stdio.h>

void toBinary(int n)
{
    if (n == 0) return;                 /* 出口：没有更多位了 */

    toBinary(n / 2);                    /* ① 先递归处理高位 */
    printf("%d", n % 2);                /* ② 再输出当前最低位 */
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

/* 为什么「先递归再输出」才是正序？
 *
 * 以 10 为例：
 *   toBinary(10) → 递归 toBinary(5) → 递归 toBinary(2) → 递归 toBinary(1)
 *                → 递归 toBinary(0)  【出口，直接返回】
 *
 * 返回时依次执行 printf：
 *   toBinary(1)  打印 1 % 2 = 1
 *   toBinary(2)  打印 2 % 2 = 0
 *   toBinary(5)  打印 5 % 2 = 1
 *   toBinary(10) 打印 10 % 2 = 0
 *
 * 输出顺序是 1 0 1 0 —— 正好是 10 的二进制 1010。
 *
 * 如果反过来（先 printf 再递归），输出会是 0101，倒的。
 *
 * ⭐ 这就是「递归顺序决定输出顺序」的典型例子：
 *    先递归 → 后序输出（从深处往外）
 *    先输出 → 前序输出（从外往里）
 *
 * ⚠️ 注意 n == 0 时什么都不输出。如果输入 0，调用方需要特殊处理。 */
