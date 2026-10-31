/* ex123_bit_tricks.c —— 参考答案 */

#include <stdio.h>

/* 判奇偶：只看最低位 */
int isOdd(int x)
{
    return (x & 1) != 0;
}

/* 异或交换 */
void swapXor(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

/* 位运算求绝对值 */
int absBit(int x)
{
    int mask = x >> 31;        /* 负数得 -1（全 1），正数得 0 */
    return (x + mask) ^ mask;
}

int main(void)
{
    /* ---------- 奇偶 ---------- */
    int nums[] = {7, -4, 0, 3, -9};
    for (int i = 0; i < 5; i++) {
        printf("%d 是%s\n", nums[i], isOdd(nums[i]) ? "奇数" : "偶数");
    }

    printf("\n⚠️ 为什么不能用 %% 判断：\n");
    printf("   -7 %% 2 = %d，不是 1。写成 x %% 2 == 1 的话，\n", -7 % 2);
    printf("   -7 会被判成偶数。必须写 x %% 2 != 0 或 x & 1。\n");

    /* ---------- 异或交换 ---------- */
    printf("\n交换前 a=5 b=9\n");
    int a = 5, b = 9;
    swapXor(&a, &b);
    printf("交换后 a=%d b=%d\n", a, b);

    printf("\n⚠️ 异或交换有个隐藏陷阱：如果 a 和 b 是同一个变量，\n");
    printf("   a ^= a 会把它清零。实际工程一律用临时变量，别炫技。\n");

    /* ---------- 绝对值 ---------- */
    printf("\n");
    int tests[] = {7, -7, 0, -1, 100, -2147483647};
    for (int i = 0; i < 6; i++) {
        printf("|%d| = %d\n", tests[i], absBit(tests[i]));
    }

    printf("\n⭐ (x + mask) ^ mask 的原理（以 x = -7 为例）：\n");
    printf("   mask = x >> 31 = -1（全 1）\n");
    printf("   x + mask = -7 + (-1) = -8\n");
    printf("   -8 ^ -1 相当于按位取反 → 7\n");
    printf("   对正数：mask = 0，x + 0 ^ 0 = x，原样返回\n");

    printf("\n⚠️ 注意 INT_MIN（-2147483648）没有对应的正数，\n");
    printf("   任何写法求它的绝对值都会溢出。\n");

    return 0;
}
