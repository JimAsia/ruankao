/* 121_bitmask.c —— 位掩码：四个操作 + 三个经典题
 *
 * W2 讲过位运算符「是什么」，这一节讲「怎么用」。
 * 位掩码是嵌入式、权限系统、状态标志的标准做法，也是软考的一个小考点。
 *
 * 四个基本操作（对一个位）：
 *   置位  set   : x |=  (1 << n)
 *   清位  clear : x &= ~(1 << n)
 *   取反  toggle: x ^=  (1 << n)
 *   测试  test  : (x >> n) & 1   或  (x & (1 << n)) != 0
 */

#include <stdio.h>

/* 打印一个数的二进制（8 位，方便看） */
void printBin(const char *label, unsigned int x, int bits)
{
    printf("  %-16s = ", label);
    for (int i = bits - 1; i >= 0; i--) {
        printf("%u", (x >> i) & 1u);
        if (i % 4 == 0 && i != 0) printf(" ");
    }
    printf("  (%u)\n", x);
}

/* ---------- 经典题 ① 统计二进制中 1 的个数 ---------- */
int countOnes(unsigned int x)
{
    int cnt = 0;
    while (x) {
        x &= x - 1;             /* 每次消掉最低位的 1 */
        cnt++;
    }
    return cnt;
}

/* ---------- 经典题 ② 判断是不是 2 的幂 ---------- */
int isPowerOfTwo(unsigned int x)
{
    /* 2 的幂的二进制只有一个 1，x-1 会把它变成 0 且后面全 1 */
    return x != 0 && (x & (x - 1)) == 0;
}

int main(void)
{
    /* ---------- ① 四个基本操作 ---------- */
    printf("=== ① 四个基本操作 ===\n");
    unsigned int x = 10;            /* 二进制 0000 1010 */

    printBin("初始 x", x, 8);

    /* 置位：把第 0 位设为 1 */
    x |= (1u << 0);
    printBin("置位 bit0", x, 8);

    /* 清位：把第 3 位清 0 */
    x &= ~(1u << 3);
    printBin("清位 bit3", x, 8);

    /* 取反：第 1 位翻转 */
    x ^= (1u << 1);
    printBin("翻转 bit1", x, 8);

    /* 测试 */
    printf("\n  测试 bit1 = %u\n", (x >> 1) & 1u);
    printf("  测试 bit0 = %u\n", (x & (1u << 0)) ? 1u : 0u);

    printf("\n  ⭐ 记忆表：\n");
    printf("    置位   x |=  (1 << n)    某一位置 1，其他位不变\n");
    printf("    清位   x &= ~(1 << n)    某一位置 0，其他位不变\n");
    printf("    取反   x ^=  (1 << n)    某一位翻转\n");
    printf("    测试   (x >> n) & 1      取某一位的值\n");
    printf("\n  为什么清位用 &= ~(1<<n)？\n");
    printf("    1 << n 是「只有第 n 位是 1」，取反后是「只有第 n 位是 0」，\n");
    printf("    再 & 上去，就只把这一位清了，其他位不受影响。\n");

    /* ---------- ② 位掩码管理权限 ---------- */
    printf("\n=== ② 位掩码做权限（一字节存 8 种权限）===\n");

    /* 每种权限占一位 */
    const unsigned int PERM_READ    = 1u << 0;   /* 0000 0001 */
    const unsigned int PERM_WRITE   = 1u << 1;   /* 0000 0010 */
    const unsigned int PERM_EXEC    = 1u << 2;   /* 0000 0100 */
    const unsigned int PERM_DELETE  = 1u << 3;   /* 0000 1000 */

    unsigned int perm = 0;

    /* 给用户加权限 */
    perm |= PERM_READ;
    perm |= PERM_WRITE;
    printBin("加了读+写", perm, 8);

    /* 撤销写权限 */
    perm &= ~PERM_WRITE;
    printBin("撤销写", perm, 8);

    /* 加删除权限，再用 XOR 取消（演示取反操作） */
    perm |= PERM_DELETE;
    printBin("加删除", perm, 8);
    perm ^= PERM_DELETE;                 /* 再按一次就取消了 */
    printBin("再按一次取消", perm, 8);

    /* 判断有没有读权限 */
    if (perm & PERM_READ) {
        printf("  有读权限 ✓\n");
    }
    if (!(perm & PERM_WRITE)) {
        printf("  没有写权限 ✓\n");
    }

    printf("\n  ⭐ 为什么用位掩码而不用 4 个 bool？\n");
    printf("     4 个 bool 占 4 字节（或 4 位但分散），一个 unsigned 装 32 种权限，\n");
    printf("     而且能一次判断多个：if ((perm & (R|W)) == (R|W)) 表示「读写都有」。\n");

    /* 一次判断多个权限 */
    unsigned int need = PERM_READ | PERM_EXEC;
    if ((perm & need) == need) {
        printf("  读写执行都有\n");
    } else {
        printf("  权限不足（需要 读+执行）\n");
    }
    printf("  ⚠️ 注意必须写 (perm & need) == need，不能写 perm & need\n");
    printf("     后者得到的是整数，只要非 0 就为真 —— 有一个就算通过，逻辑错。\n");

    /* ---------- ③ 统计 1 的个数 ---------- */
    printf("\n=== ③ 统计二进制中 1 的个数 ===\n");
    unsigned int tests[] = {0, 1, 7, 15, 255, 1023, 4294967295u};
    for (int i = 0; i < 7; i++) {
        printf("  %-12u → %d 个 1\n", tests[i], countOnes(tests[i]));
    }

    printf("\n  ⭐ 关键技巧：x &= x - 1 每次消掉最低位的 1\n");
    printf("     例：x = 12 (1100)\n");
    printf("        x-1 = 11 (1011)\n");
    printf("        x & (x-1) = 1000 = 8   ← 消掉了最低位的 1\n");
    printf("     循环次数 = 1 的个数，比逐位检查（固定 32 次）更快\n");

    /* ---------- ④ 判断 2 的幂 ---------- */
    printf("\n=== ④ 判断是不是 2 的幂 ===\n");
    unsigned int nums[] = {1, 2, 3, 4, 6, 8, 16, 100, 256, 1024};
    for (int i = 0; i < 10; i++) {
        printf("  %-6u %s\n", nums[i], isPowerOfTwo(nums[i]) ? "是" : "不是");
    }

    printf("\n  ⭐ 原理：2 的幂只有一个 1，减 1 之后变成「0 后面全 1」，\n");
    printf("     两者 & 必为 0。例：8 = 1000，7 = 0111，8 & 7 = 0\n");
    printf("     ⚠️ x 必须是正整数，x = 0 要单独排除（0 & -1 也是 0）\n");

    /* ---------- ⑤ 不用临时变量交换 ---------- */
    printf("\n=== ⑤ 异或交换（面试题，软考偶尔考）===\n");
    unsigned int a = 5, b = 9;
    printf("  交换前：a = %u, b = %u\n", a, b);
    a ^= b;
    b ^= a;
    a ^= b;
    printf("  交换后：a = %u, b = %u\n", a, b);

    printf("\n  ⭐ 原理：x ^ x = 0，x ^ 0 = x\n");
    printf("     但实际工程不要用：a、b 是同一个变量时会被清零，且可读性差。\n");
    printf("     用临时变量 t 才是最清楚的写法。\n");

    return 0;
}
