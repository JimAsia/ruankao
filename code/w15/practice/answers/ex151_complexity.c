/* ex151_complexity.c —— 参考答案 */

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
    const char *c1 = "O(n)";
    const char *c2 = "O(log n)";
    const char *c3 = "O(n^2)";

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

    printf("\n=== 解析 ===\n");
    printf("段 1：n 变 3 倍，次数也变 3 倍 → 线性 O(n)\n");
    printf("  3 次 → 9 次 → 27 次，比值 3。步长是 3 只让次数除以 3，\n");
    printf("  除以常数不改变量级，所以还是 O(n)。\n");

    printf("\n段 2：n 变 3 倍，次数只多 1 → 对数 O(log n)\n");
    printf("  2 次 → 3 次 → 4 次。i 取 1,3,9,27,...，\n");
    printf("  次数是 log3(n)，底数不影响量级，统一写 O(log n)。\n");

    printf("\n段 3：n 变 3 倍，次数变约 9 倍 → 平方 O(n^2)\n");
    printf("  45 → 378 → 3321，比值约 8.4、8.8，接近 9。\n");
    printf("  精确公式：sum(n-i) for i=0..n-1 = n(n+1)/2，\n");
    printf("  n=9 时 45，n=27 时 378，n=81 时 3321，完全吻合。\n");

    printf("\n⚠️ 段 3 很多人会算错成 O(n log n)，因为内层次数在变。\n");
    printf("   正确做法是求和：0+1+2+...+(n-1) 再加 n 个 1，还是 n(n+1)/2。\n");
    printf("   ⭐ 内层边界依赖外层时，一律用求和公式，不要凭感觉。\n");

    return 0;
}
