/* ex151_complexity.c —— 判断三段的复杂度，并用计数器验证
 *
 * 要求：把每段的复杂度填在下面的字符串里（如 "O(n)"、"O(log n)"、"O(n^2)"）
 *       然后运行程序，看实际次数是否符合你的判断
 *
 * 提示：
 *   步长 i += 3        → 次数约 n/3，仍是同一阶
 *   倍增 i *= 3        → 次数约 log3(n)，仍是 O(log n)
 *   内层 j 从 n 递减到 i → 每层次数不同，但求和后仍是平方级
 *
 * 预期输出（n=9/27/81）：
 *   段 1：3 次 / 9 次 / 27 次        → 复杂度 O(n)
 *   段 2：2 次 / 3 次 / 4 次          → 复杂度 O(log n)
 *   段 3：45 次 / 378 次 / 3321 次    → 复杂度 O(n^2)
 */

#include <stdio.h>

/* 段 1：步长为 3 */
static long long seg1(int n)
{
    long long c = 0;
    for (int i = 0; i < n; i += 3) c++;
    return c;
}

/* 段 2：每次乘 3 */
static long long seg2(int n)
{
    long long c = 0;
    for (int i = 1; i < n; i *= 3) c++;
    return c;
}

/* 段 3：内层从 n 递减到 i */
static long long seg3(int n)
{
    long long c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = n; j > i; j--) c++;
    }
    return c;
}

int main(void)
{
    /* TODO 1：填入你判断的复杂度 */
    const char *c1 = "O(?)";
    const char *c2 = "O(?)";
    const char *c3 = "O(?)";

    int ns[] = {9, 27, 81};

    printf("=== 段 1（i += 3）===\n");
    for (int k = 0; k < 3; k++) {
        printf("  n=%-4d %lld 次\n", ns[k], seg1(ns[k]));
    }
    printf("  我的判断：%s\n", c1);

    printf("\n=== 段 2（i *= 3）===\n");
    for (int k = 0; k < 3; k++) {
        printf("  n=%-4d %lld 次\n", ns[k], seg2(ns[k]));
    }
    printf("  我的判断：%s\n", c2);

    printf("\n=== 段 3（内层 j 从 n 到 i）===\n");
    for (int k = 0; k < 3; k++) {
        printf("  n=%-4d %lld 次\n", ns[k], seg3(ns[k]));
    }
    printf("  我的判断：%s\n", c3);

    /* TODO 2：根据实际次数，检查你的判断对不对
     * 判断方法：n 变成 3 倍时，次数变成几倍？
     *   3 倍 → 线性
     *   只多 1  → 对数
     *   9 倍 → 平方
     */

    return 0;
}
