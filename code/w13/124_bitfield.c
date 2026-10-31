/* 124_bitfield.c —— 位域：用位来定义结构体成员
 *
 * 位域是「结构体 + 位运算」的结合，用来把几个小数据压进一个字节。
 * 典型场景：协议头、硬件寄存器、状态标志。
 *
 * 语法：struct { unsigned int 成员名 : 位数; }
 *
 * ⚠️ 本文件第 ④ 节故意保留 2 处 -Woverflow 警告：
 *    r.a = 8  → warning: unsigned conversion from 'int' to 'unsigned char:3'
 *                       changes value from '8' to '0'
 *    这两行正是在演示「赋值超出位域范围」的后果，警告本身就是教学内容。
 *    其余部分零警告。
 */

#include <stdio.h>
#include <string.h>

/* ---------- ① 普通写法：3 个 int 占 12 字节 ---------- */
struct FlagsPlain {
    unsigned int isReady;       /* 实际只用 0 或 1，却占 4 字节 */
    unsigned int hasError;
    unsigned int isActive;
};

/* ---------- ② 位域写法：3 个字段压进 4 字节 ---------- */
struct FlagsBit {
    unsigned int isReady  : 1;  /* 只占 1 位，能表示 0~1 */
    unsigned int hasError : 1;
    unsigned int isActive : 1;
};

/* ---------- ③ 更实际的例子：日期压缩 ---------- */
/* 年 12 位（0~4095）、月 4 位（0~15）、日 5 位（0~31）共 21 位 */
struct PackedDate {
    unsigned int year  : 12;
    unsigned int month : 4;
    unsigned int day   : 5;
};

/* ---------- ④ 位域的取值范围 ---------- */
struct Range {
    unsigned int a : 3;         /* 3 位无符号：0 ~ 7 */
    signed   int b : 3;         /* 3 位有符号：-4 ~ 3 */
};

int main(void)
{
    /* ---------- ① 体积对比 ---------- */
    printf("=== ① 体积对比 ===\n");
    printf("  struct FlagsPlain 占 %zu 字节（3 个 unsigned int）\n",
           sizeof(struct FlagsPlain));
    printf("  struct FlagsBit   占 %zu 字节（3 个 1 位字段）\n",
           sizeof(struct FlagsBit));

    printf("\n  ⭐ 位域把 3 个字段压到同一块内存，从 12 字节降到 4 字节。\n");
    printf("     注意是 4 而不是 1：位域的类型是 unsigned int，\n");
    printf("     编译器按 int 分配存储单元，剩余位留着没用。\n");
    printf("     想真的压到 1 字节，得写 unsigned char a : 1;\n");

    /* 验证一下用 unsigned char 的效果 */
    struct FlagsTiny {
        unsigned char isReady  : 1;
        unsigned char hasError : 1;
        unsigned char isActive : 1;
    };
    printf("\n  用 unsigned char 作位域类型：%zu 字节\n", sizeof(struct FlagsTiny));

    /* ---------- ② 位域的读写 ---------- */
    printf("\n=== ② 位域的读写 ===\n");
    struct FlagsBit f;
    memset(&f, 0, sizeof(f));           /* ⚠️ 位域成员不能整体初始化，先清零 */

    f.isReady = 1;
    f.hasError = 0;
    f.isActive = 1;

    printf("  isReady = %u, hasError = %u, isActive = %u\n",
           f.isReady, f.hasError, f.isActive);
    printf("  用法和普通成员一样：f.isReady 直接赋值\n");

    printf("\n  ⚠️ 位域不能取地址：\n");
    printf("     &f.isReady 是编译错误 —— 它不是字节对齐的，无法用指针指向\n");

    /* ---------- ③ 日期压缩 ---------- */
    printf("\n=== ③ 日期压缩 ===\n");
    struct PackedDate d;
    d.year  = 2026;
    d.month = 10;
    d.day   = 24;

    printf("  %u-%u-%u\n", d.year, d.month, d.day);
    printf("  sizeof(struct PackedDate) = %zu 字节\n", sizeof(d));
    printf("\n  ⭐ 年 12 位 + 月 4 位 + 日 5 位 = 21 位，理论只需 3 字节，\n");
    printf("     实际按 int 分配，占 4 字节。比 3 个 int（12 字节）省得多。\n");

    /* ---------- ④ 溢出会怎样 ---------- */
    printf("\n=== ④ 位域装不下时会怎样 ===\n");
    struct Range r;
    memset(&r, 0, sizeof(r));

    r.a = 7;
    printf("  3 位无符号 a = 7（最大值）\n");
    r.a = 8;
    printf("  再赋 8 → a 变成 %u    ← 溢出被截断，只保留低 3 位\n", r.a);
    r.a = 15;
    printf("  赋 15 → a 变成 %u    ← 15 的低 3 位是 111\n", r.a);

    r.b = 3;
    printf("\n  3 位有符号 b = 3（最大值）\n");
    r.b = 4;
    printf("  再赋 4 → b 变成 %d    ← 变成负数了，这就是有符号溢出\n", r.b);

    printf("\n  ⭐ 位域的位数决定取值范围：\n");
    printf("     无符号 n 位：0 ~ 2^n - 1\n");
    printf("     有符号 n 位：-2^(n-1) ~ 2^(n-1) - 1\n");
    printf("     ⚠️ 赋值超出范围，gcc 会给 -Woverflow 警告（见本文件开头），\n");
    printf("        但只是警告不是错误，程序照跑、值照样被截断。\n");
    printf("        别的编译器可能连警告都没有 —— 所以位域赋值要自己保证范围。\n");

    /* ---------- ⑤ 位域 vs 位运算 ---------- */
    printf("\n=== ⑤ 位域 和 位运算，该用哪个 ===\n");
    printf("  %-14s %-26s %s\n", "", "位域", "位运算");
    printf("  %-14s %-26s %s\n", "可读性", "好（f.isReady）", "差（x & 0x01）");
    printf("  %-14s %-26s %s\n", "可移植性", "差（布局由编译器定）", "好");
    printf("  %-14s %-26s %s\n", "取地址", "不能", "能");
    printf("  %-14s %-26s %s\n", "适合", "内部状态、寄存器定义", "协议解析、跨平台");

    printf("\n  ⭐ 位域的致命缺陷：内存布局没有标准规定。\n");
    printf("     同一个 struct 在不同编译器上，字段可能从低位开始也可能从高位，\n");
    printf("     所以位域绝对不能用来解析网络协议 —— 那种场合必须手写位运算。\n");

    /* ---------- ⑥ 软考考点 ---------- */
    printf("\n=== ⑥ 考点速记 ===\n");
    printf("  1. 位域定义：类型 成员名 : 位数;\n");
    printf("  2. sizeof 按声明类型分配单元，不是按位精确计算\n");
    printf("  3. 不能对位域成员取地址（&f.x 非法）\n");
    printf("  4. 位数决定范围，超范围赋值会静默截断\n");
    printf("  5. 位域布局由实现定义，不可移植\n");

    return 0;
}
