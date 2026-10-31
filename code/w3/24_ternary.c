/* 24_ternary.c —— 条件运算符 ?:
 *
 * C 语言唯一的三元运算符，是 if-else 的表达式版本。
 * 差别在于：if-else 是语句，?: 是表达式，能直接参与运算。
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① 基本用法 ---------- */
    int a = 5, b = 3;

    int max = (a > b) ? a : b;
    printf("a = %d, b = %d\n", a, b);
    printf("max = (a > b) ? a : b  →  %d\n", max);

    /* ---------- ② 表达式 = 能嵌在别的地方 ---------- */
    printf("\n=== 它能直接参与运算，if-else 不行 ===\n");
    printf("10 + ((a > b) ? a : b) = %d\n", 10 + ((a > b) ? a : b));
    printf("  如果换成 if-else，你得先算出来存进变量再用\n");

    /* ---------- ③ 嵌套：从外往里判断 ---------- */
    printf("\n=== 嵌套（注意每个分支都要有值）===\n");
    int score = 72;
    const char *level = (score >= 90) ? "优秀"
                      : (score >= 80) ? "良好"
                      : (score >= 60) ? "及格"
                      :                 "不及格";
    printf("score = %d → %s\n", score, level);

    printf("\n嵌套超过两层就别用了，可读性崩坏，改写成 if-else 链更好\n");

    /* ---------- ④ 和 if-else 的等价转换 ---------- */
    printf("\n=== 等价改写 ===\n");
    int x = -7;

    /* 写法一：?: */
    const char *sign1 = (x > 0) ? "正数" : (x < 0) ? "负数" : "零";
    printf("三元写法：%s\n", sign1);

    /* 写法二：if-else 链 */
    const char *sign2;
    if (x > 0)      sign2 = "正数";
    else if (x < 0) sign2 = "负数";
    else            sign2 = "零";
    printf("if-else 写法：%s\n", sign2);

    printf("  两者结果相同。三元适合「短、单层」，if-else 适合「长、多层」。\n");

    /* ---------- ⑤ 常见误用 ---------- */
    printf("\n=== 三个常见误用 ===\n");
    printf("① 忘记写冒号后面的值：(a > b) ? a   ← 编译错误\n");
    printf("② 两边类型不一致导致隐式转换：(a > b) ? a : 3.5  ← 结果是 double\n");
    printf("③ 用 ?: 代替有副作用的语句：a > b ? printf(...) : ;  ← 难读\n");

    return 0;
}
