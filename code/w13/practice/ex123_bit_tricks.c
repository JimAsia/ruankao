/* ex123_bit_tricks.c —— 三个位运算小技巧
 *
 * 要求：
 *   1. isOdd(x)：不用 % 判断奇偶（只能在二进制上看最低位）
 *   2. swapXor(a, b)：用异或交换两个数（不用临时变量）
 *   3. absBit(x)：用位运算求 int 的绝对值（不用 if、不用 abs）
 *
 * 提示：
 *   奇偶：(x & 1) != 0 就是奇数
 *   交换：a^=b; b^=a; a^=b;
 *   绝对值：int mask = x >> 31;  (x + mask) ^ mask
 *           负数右移 31 位得 -1（全 1），正数得 0
 *
 * 输出示例：
 *   7 是奇数
 *   -4 是偶数
 *   交换前 a=5 b=9 → 交换后 a=9 b=5
 *   |7| = 7    |-7| = 7
 */

#include <stdio.h>

/* TODO 1：isOdd */

/* TODO 2：swapXor（用指针，因为要改外面的变量） */

/* TODO 3：absBit */

int main(void)
{
    /* TODO 4：测试三个函数 */
    /* 注意：负数取余 -7 % 2 == -1，所以不能用 % 判奇偶 */

    return 0;
}
