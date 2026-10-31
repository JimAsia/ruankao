/* ex121_mask.c —— 位掩码三个操作
 *
 * 要求：实现三个函数，对整数 x 的第 n 位（n 从 0 起）操作
 *   1. setBit(x, n)    → 把第 n 位置 1
 *   2. clearBit(x, n)  → 把第 n 位清 0
 *   3. testBit(x, n)   → 返回第 n 位的值（0 或 1）
 *
 * 然后对 x = 10（二进制 1010）依次测试：
 *   置位 bit0 → 11
 *   清位 bit3 → 3
 *   测试 bit1 → 1
 *
 * 输出示例：
 *   x = 10
 *   置位 bit0 后 = 11
 *   清位 bit3 后 = 3
 *   测试 bit1 = 1
 *   测试 bit2 = 0
 *
 * 要点：
 *   置位 x | (1u << n)
 *   清位 x & ~(1u << n)
 *   测试 (x >> n) & 1u
 */

#include <stdio.h>

/* TODO 1：写 setBit */
/* TODO 2：写 clearBit */
/* TODO 3：写 testBit */

int main(void)
{
    unsigned int x = 10;

    /* TODO 4：依次调用并输出 */

    return 0;
}
