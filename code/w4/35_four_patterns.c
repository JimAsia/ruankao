/* 35_four_patterns.c —— 循环的四大范式
 *
 * 几乎所有循环题都是这四个模式的组合：
 *   ① 累加（求和）
 *   ② 累乘（求积）
 *   ③ 计数（数个数）
 *   ④ 找最值（打擂台）
 * 把这四个背到条件反射，W5 的数组题就只是换个数据来源而已。
 */
#include <stdio.h>

int main(void)
{
    /* ========== ① 累加：1 + 2 + ... + n ========== */
    printf("=== ① 累加 ===\n");
    int sum = 0;                        /* ⚠️ 初值必须是 0 */
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }
    printf("  1+2+...+100 = %d\n", sum);
    printf("  用公式验算：n(n+1)/2 = 100×101/2 = %d\n", 100 * 101 / 2);

    /* 变体：求偶数和 */
    int evenSum = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 2 == 0) evenSum += i;
    }
    printf("  1~100 的偶数和 = %d\n", evenSum);

    /* ========== ② 累乘：n! ========== */
    printf("\n=== ② 累乘 ===\n");
    long long fac = 1;                  /* ⚠️ 初值必须是 1，不能是 0 */
    for (int i = 1; i <= 20; i++) {
        fac *= i;
    }
    printf("  20! = %lld\n", fac);
    printf("  注意：必须用 long long，int 到 13! 就溢出了\n");

    /* 验算溢出边界 */
    int badFac = 1;
    for (int i = 1; i <= 13; i++) {
        badFac *= i;
    }
    printf("  用 int 算 13! 得到 %d（已经溢出了，正确值是 6227020800）\n", badFac);

    /* ========== ③ 计数：数满足条件的个数 ========== */
    printf("\n=== ③ 计数 ===\n");
    int cnt = 0;                        /* ⚠️ 初值必须是 0 */
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0) cnt++;
    }
    printf("  1~100 中能被 3 整除的数有 %d 个\n", cnt);

    /* 变体：统计位数为 5 且是回文数的三位数？—— 先数三位数里有几个水仙花数 */
    int flower = 0;
    printf("\n  三位数中的水仙花数（各位立方和等于本身）：\n  ");
    for (int n = 100; n <= 999; n++) {
        int a = n / 100;                /* 百位 */
        int b = n / 10 % 10;            /* 十位 */
        int c = n % 10;                 /* 个位 */
        if (a*a*a + b*b*b + c*c*c == n) {
            printf("%d ", n);
            flower++;
        }
    }
    printf("\n  共 %d 个\n", flower);

    /* ========== ④ 找最值：打擂台 ========== */
    printf("\n=== ④ 找最值（打擂台）===\n");

    /* 例一：找 1~100 中能被 7 整除的最大数 */
    int max = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0 && i > max) max = i;
    }
    printf("  1~100 中能被 7 整除的最大数 = %d\n", max);

    /* 例二：⚠️ 初值陷阱 —— 找 -5 ~ -1 中的最大值 */
    int max2 = 0;
    for (int i = -5; i <= -1; i++) {
        if (i > max2) max2 = i;
    }
    printf("  -5~-1 中的最大值，初值写 0 时得到 %d\n", max2);

    int max3 = -2147483647;             /* ✅ 取一个足够小的初值 */
    for (int i = -5; i <= -1; i++) {
        if (i > max3) max3 = i;
    }
    printf("  初值取足够小的数，才是正确答案 %d\n", max3);
    printf("  ↑ 这个 bug 极隐蔽：全是正数时看不出问题，一遇到负数就错\n");

    /* ========== ⑤ 组合使用：累加 + 计数 = 平均值 ========== */
    printf("\n=== ⑤ 组合：累加 + 计数 = 平均值 ===\n");
    int total = 0, num = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 2 != 0) {               /* 只统计奇数 */
            total += i;
            num++;
        }
    }
    printf("  1~100 的奇数和 = %d，个数 = %d，平均 = %.2f\n",
           total, num, (double)total / num);
    printf("  验算：奇数和 = 50² = 2500，个数 50，平均 50.00\n");

    return 0;
}
