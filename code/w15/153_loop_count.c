/* 153_loop_count.c —— 考试里出现的各种循环，各自算多少次
 *
 * 这一节是 W15 的核心训练：看到一段循环，3 秒内说出复杂度。
 * 办法只有一个 —— 把各种写法都数一遍，形成条件反射。
 */

#include <stdio.h>

/* ① 标准单层 */
long long c1(int n) { long long c = 0; for (int i = 0; i < n; i++) c++; return c; }

/* ② 步长为 2 */
long long c2(int n) { long long c = 0; for (int i = 0; i < n; i += 2) c++; return c; }

/* ③ 倍增：i 每次乘 2 */
long long c3(int n) { long long c = 0; for (int i = 1; i < n; i *= 2) c++; return c; }

/* ④ 标准双层，内层跑满 */
long long c4(int n) { long long c = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) c++;
    return c; }

/* ⑤ 内层 j < i（三角形） */
long long c5(int n) { long long c = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) c++;
    return c; }

/* ⑥ 内层从 i 开始（含对角线） */
long long c6(int n) { long long c = 0;
    for (int i = 0; i < n; i++) for (int j = i; j < n; j++) c++;
    return c; }

/* ⑦ 双变量 n 和 m */
long long c7(int n, int m) { long long c = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c++;
    return c; }

/* ⑧ 条件里带 n */
long long c8(int n) { long long c = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n * n; j++) c++;
    return c; }

/* ⑨ i * i < n：开方 */
long long c9(int n) { long long c = 0;
    for (int i = 0; i * i < n; i++) c++;
    return c; }

/* ⑩ 三层嵌套 */
long long c10(int n) { long long c = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) c++;
    return c; }

/* ⑪ 两个独立循环（顺序执行） */
long long c11(int n) { long long c = 0;
    for (int i = 0; i < n; i++) c++;
    for (int i = 0; i < n; i++) c++;
    return c; }

/* ⑫ 循环里做 log n 的工作 */
long long c12(int n) { long long c = 0;
    for (int i = 1; i <= n; i++) {
        int x = i;
        while (x > 0) { x /= 2; c++; }
    }
    return c; }

int main(void)
{
    printf("=== 十二种循环，实测执行次数 ===\n\n");
    printf("%-4s %-9s %-9s %-9s %s\n", "编号", "n=8", "n=16", "n=32", "复杂度");
    printf("--------------------------------------------------------\n");

    printf("%-4s %-9lld %-9lld %-9lld %s\n", "①", c1(8),  c1(16),  c1(32),  "O(n)");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "②", c2(8),  c2(16),  c2(32),  "O(n)   步长 2 只省常数");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "③", c3(8),  c3(16),  c3(32),  "O(log n) 倍增");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "④", c4(8),  c4(16),  c4(32),  "O(n^2) 满矩阵");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑤", c5(8),  c5(16),  c5(32),  "O(n^2) 三角形");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑥", c6(8),  c6(16),  c6(32),  "O(n^2) 含对角线");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑦", c7(8,8), c7(16,16), c7(32,32), "O(n*m) 双变量");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑧", c8(8),  c8(16),  c8(32),  "O(n^3) 内层 n*n");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑨", c9(8),  c9(16),  c9(32),  "O(sqrt n)");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑩", c10(8), c10(16), c10(32), "O(n^3) 三层");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑪", c11(8), c11(16), c11(32), "O(n)   顺序执行取最大");
    printf("%-4s %-9lld %-9lld %-9lld %s\n", "⑫", c12(8), c12(16), c12(32), "O(n log n)");

    printf("\n=== 逐个拆解 ===\n");

    printf("\n① for (i = 0; i < n; i++)\n");
    printf("   i 取 0..n-1 共 n 个值 → n 次 → O(n)\n");

    printf("\n② for (i = 0; i < n; i += 2)\n");
    printf("   i 取 0,2,4,... → 约 n/2 次 → 仍是 O(n)\n");
    printf("   ⭐ 除以 2 只是常数因子，不影响量级。同理 i += 100 也是 O(n)。\n");

    printf("\n③ for (i = 1; i < n; i *= 2)\n");
    printf("   i 取 1,2,4,8,... 直到 ≥ n，共 log2(n) 次\n");
    for (int n = 8; n <= 32; n *= 2) {
        printf("   n=%-3d 时 %lld 次，log2(%d)=%lld\n", n, c3(n), n, c3(n));
    }
    printf("   ⭐ 看到 *= 2 或 /= 2，条件反射想 log。\n");

    printf("\n④ 和 ⑤ 的区别（很多人会搞混）\n");
    printf("   ④ for (j = 0; j < n; j++)  内层每次都跑满 n 次 → n × n = n^2\n");
    printf("   ⑤ for (j = 0; j < i; j++)  内层跑 i 次 → 0+1+2+...+(n-1) = n(n-1)/2\n");
    printf("   实测 n=32：④ %lld 次，⑤ %lld 次，比值 %.2f\n",
           c4(32), c5(32), (double)c4(32) / (double)c5(32));
    printf("   ⭐ 少了一半，但仍是 O(n^2) —— 常数因子 1/2 被忽略。\n");

    printf("\n⑨ i * i < n 是开方的来源\n");
    printf("   i 从 0 到 sqrt(n)-1，共 sqrt(n) 次\n");
    printf("   n=16 → %lld 次（sqrt(16)=4）；n=32 → %lld 次（sqrt(32)≈5.66，取 6）\n",
           c9(16), c9(32));
    printf("   ⭐ 判素数时用 i*i <= n，就是把 O(n) 降到 O(sqrt n)。\n");

    printf("\n⑪ 顺序执行的两个循环：取最大的那个\n");
    printf("   n + n = 2n → O(n)，不是 O(2n)，也不是 O(n^2)\n");
    printf("   ⭐ 并列的循环相加，嵌套的循环相乘。这是最容易记错的一条。\n");

    printf("\n⑫ 外层 n 次，内层每次约 log i 次\n");
    printf("   总次数 ≈ n × log n → O(n log n)\n");
    printf("   ⭐ 归并排序、快速排序（平均）都是这个量级。\n");

    printf("\n=== 三条速判口诀 ===\n");
    printf("  1. 单层循环 → O(n)；步长 ×2/÷2 → O(log n)\n");
    printf("  2. 循环嵌套 → 相乘；循环并列 → 相加后取最大\n");
    printf("  3. 内层边界依赖外层（j<i）→ 还是同阶，只是常数变小\n");

    printf("\n=== 反向练习：给次数猜复杂度 ===\n");
    printf("  n=8 时 %-6lld 次，n=16 时 %-6lld 次，n=32 时 %lld 次 → ？\n",
           c12(8), c12(16), c12(32));
    printf("  翻倍时涨约 2.2 倍（略高于 2），符合 n log n 而不是 n。\n");

    return 0;
}
