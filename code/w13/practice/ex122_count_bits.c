/* ex122_count_bits.c —— 位运算经典两题
 *
 * 要求：
 *   1. countOnes(x)：统计 x 的二进制中有几个 1（用 x &= x-1 的技巧）
 *   2. isPowerOfTwo(x)：判断 x 是不是 2 的幂（用 x & (x-1)）
 *
 * 测试数据：0 1 2 3 7 8 16 100 255 1024
 * 输出示例：
 *   0      1 的个数 0   不是 2 的幂
 *   1      1 的个数 1   是 2 的幂
 *   ...
 *
 * 要点：
 *   countOnes 的循环次数等于 1 的个数，不是固定 32 次
 *   isPowerOfTwo 要单独排除 0
 */

#include <stdio.h>

/* TODO 1：countOnes */

/* TODO 2：isPowerOfTwo */

int main(void)
{
    unsigned int tests[] = {0, 1, 2, 3, 7, 8, 16, 100, 255, 1024};

    /* TODO 3：遍历数组，对每个数输出 1 的个数 和 是否 2 的幂 */

    return 0;
}
