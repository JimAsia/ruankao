/* ex121_mask.c —— 参考答案 */

#include <stdio.h>

/* 置位：把第 n 位置 1 */
unsigned int setBit(unsigned int x, int n)
{
    return x | (1u << n);
}

/* 清位：把第 n 位清 0 */
unsigned int clearBit(unsigned int x, int n)
{
    return x & ~(1u << n);
}

/* 测试：返回第 n 位的值（0 或 1） */
int testBit(unsigned int x, int n)
{
    return (int)((x >> n) & 1u);
}

/* 辅助：打印 8 位二进制 */
void show(const char *label, unsigned int x)
{
    printf("  %-14s = ", label);
    for (int i = 7; i >= 0; i--) printf("%u", (x >> i) & 1u);
    printf("  (%u)\n", x);
}

int main(void)
{
    unsigned int x = 10;
    show("x", x);

    unsigned int y = setBit(x, 0);
    printf("置位 bit0 后 = %u\n", y);
    show("  二进制", y);

    unsigned int z = clearBit(y, 3);
    printf("清位 bit3 后 = %u\n", z);
    show("  二进制", z);

    printf("测试 bit1 = %d\n", testBit(x, 1));
    printf("测试 bit2 = %d\n", testBit(x, 2));

    printf("\n⭐ 三个公式必须背下来：\n");
    printf("   置位 x | (1u << n)\n");
    printf("   清位 x & ~(1u << n)\n");
    printf("   测试 (x >> n) & 1u\n");
    printf("\n⚠️ 用 1u 而不是 1：1 是 int，左移 31 位会溢出成负数，\n");
    printf("   1u 是无符号，左移 31 位得到 0x80000000，正确。\n");

    return 0;
}
