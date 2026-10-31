/* ex122_count_bits.c —— 参考答案 */

#include <stdio.h>

/* 统计 1 的个数：每次消掉最低位的 1 */
int countOnes(unsigned int x)
{
    int cnt = 0;
    while (x) {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

/* 判断 2 的幂 */
int isPowerOfTwo(unsigned int x)
{
    return x != 0 && (x & (x - 1)) == 0;
}

int main(void)
{
    unsigned int tests[] = {0, 1, 2, 3, 7, 8, 16, 100, 255, 1024};
    int n = (int)(sizeof(tests) / sizeof(tests[0]));

    printf("%-8s %-12s %s\n", "数值", "1 的个数", "是否 2 的幂");
    for (int i = 0; i < n; i++) {
        printf("%-8u %-12d %s\n",
               tests[i],
               countOnes(tests[i]),
               isPowerOfTwo(tests[i]) ? "是" : "不是");
    }

    printf("\n⭐ x &= x - 1 为什么能消掉最低位的 1：\n");
    printf("   例 x = 12 = 1100\n");
    printf("      x - 1   = 1011   （最低位的 1 变 0，右边全变 1）\n");
    printf("      x & x-1 = 1000   ← 最低位的那个 1 没了\n");
    printf("   循环次数正好等于 1 的个数，比固定循环 32 次更快。\n");

    printf("\n⚠️ isPowerOfTwo 里的 x != 0 不能省：\n");
    printf("   0 & (0-1) = 0 & 0xFFFFFFFF = 0，不加判断会把 0 判成 2 的幂。\n");

    return 0;
}
