/* 32_for_trace.c —— 追踪循环的执行顺序
 *
 * 读程序题的核心技能：把每一轮循环里每个变量的值列成表。
 * 本文件把"表格"打印出来，让你看清循环是怎么走的。
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① 单层循环逐轮追踪 ---------- */
    printf("=== ① 单层循环：sum 是怎么累加的 ===\n");
    int sum = 0;
    printf("  轮次 | i  | sum（累加前）-> sum（累加后）\n");
    printf("  -----|----|------------------------------\n");
    for (int i = 1; i <= 5; i++) {
        int before = sum;
        sum += i;
        printf("   %d   | %d  | %d -> %d\n", i, i, before, sum);
    }
    printf("  最终 sum = %d\n", sum);

    /* ---------- ② 嵌套循环：外层 1 次，内层跑一整轮 ---------- */
    printf("\n=== ② 嵌套循环：外层动一次，内层跑一圈 ===\n");
    for (int i = 1; i <= 3; i++) {
        printf("  外层 i = %d：", i);
        for (int j = 1; j <= 4; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("  外层 3 次 × 内层 4 次 = 共执行 12 次循环体\n");

    /* ---------- ③ 内层依赖外层：三角形 ---------- */
    printf("\n=== ③ 内层上限依赖外层 ===\n");
    for (int i = 1; i <= 4; i++) {
        printf("  i=%d: ", i);
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("  执行次数 = 1+2+3+4 = 10 = n(n+1)/2\n");

    /* ---------- ④ 打印完整九九乘法表 ---------- */
    printf("\n=== ④ 九九乘法表 ===\n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d×%d=%-2d ", j, i, i * j);
        }
        printf("\n");
    }

    /* ---------- ⑤ 倒三角（内层上限递减） ---------- */
    printf("\n=== ⑤ 倒三角 ===\n");
    for (int i = 5; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
