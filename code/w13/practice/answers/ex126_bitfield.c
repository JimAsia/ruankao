/* ex126_bitfield.c —— 参考答案
 *
 * ⚠️ 本文件故意有 3 处 -Woverflow 警告：
 *    c2.r = 200 → changes value from '200' to '8'
 *    c2.g = 150 → changes value from '150' to '22'
 *    c2.b = 100 → changes value from '100' to '4'
 *    这正是本题要演示的现象：5/6 位装不下 0~255 的值。
 */

#include <stdio.h>
#include <string.h>

/* 8+8+8 = 24 位，按 unsigned int 分配 → 4 字节 */
struct RGB {
    unsigned int r : 8;
    unsigned int g : 8;
    unsigned int b : 8;
};

/* RGB565：5+6+5 = 16 位，同样按 unsigned int 分配 → 4 字节 */
struct RGB16 {
    unsigned int r : 5;
    unsigned int g : 6;
    unsigned int b : 5;
};

int main(void)
{
    printf("=== struct RGB（每通道 8 位）===\n");
    struct RGB c1;
    memset(&c1, 0, sizeof(c1));
    c1.r = 200;
    c1.g = 150;
    c1.b = 100;
    printf("  sizeof = %zu 字节\n", sizeof(struct RGB));
    printf("  r=%u g=%u b=%u\n", c1.r, c1.g, c1.b);

    printf("\n=== struct RGB16（RGB565）===\n");
    struct RGB16 c2;
    memset(&c2, 0, sizeof(c2));
    c2.r = 200;
    c2.g = 150;
    c2.b = 100;
    printf("  sizeof = %zu 字节\n", sizeof(struct RGB16));
    printf("  r=%u g=%u b=%u\n", c2.r, c2.g, c2.b);

    printf("\n  ⭐ 为什么被截断：\n");
    printf("     200 的二进制 11001000，5 位只留低 5 位 01000 = 8\n");
    printf("     150 的二进制 10010110，6 位只留低 6 位 010110 = 22\n");
    printf("     100 的二进制 01100100，5 位只留低 5 位 00100 = 4\n");
    printf("\n     验算：200 & 31 = %d，150 & 63 = %d，100 & 31 = %d\n",
           200 & 31, 150 & 63, 100 & 31);

    printf("\n  ⚠️ sizeof 都是 4，不是因为位数相同，\n");
    printf("     而是因为声明类型是 unsigned int，编译器按 int 分配存储单元。\n");
    printf("     想压到 2 字节，得用 unsigned short 作位域类型试试。\n");

    /* 验证：用 unsigned short 作位域类型 */
    struct RGB16s {
        unsigned short r : 5;
        unsigned short g : 6;
        unsigned short b : 5;
    };
    printf("\n  用 unsigned short 作类型：%zu 字节\n", sizeof(struct RGB16s));
    printf("  ⭐ 16 位正好装满，这才是 RGB565 的正确写法\n");

    return 0;
}
