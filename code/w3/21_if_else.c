/* 21_if_else.c —— if / else 的全部形态
 *
 * ⚠️ 本文件故意保留 1 处 -Wdangling-else 警告。
 *    「悬空 else」那一节就是故意写出缩进骗人的代码来演示陷阱，
 *    编译器同样识别出了这个歧义并出言提醒 —— 这正是警告该有的样子。
 *    真实代码里请加括号消除它。
 *
 * 注意：本文件不用循环（那是 W4 的内容）。
 */
#include <stdio.h>

int main(void)
{
    int score = 85;

    /* ---------- ① 单分支：条件成立才做事 ---------- */
    printf("=== 单分支 ===\n");
    if (score >= 60)
        printf("及格\n");

    /* ---------- ② 双分支：二选一 ---------- */
    printf("\n=== 双分支 ===\n");
    if (score >= 60)
        printf("及格\n");
    else
        printf("不及格\n");

    /* ---------- ③ 多条语句必须加大括号 ---------- */
    printf("\n=== 多条语句加大括号 ===\n");
    if (score >= 60) {
        printf("及格\n");
        printf("恭喜\n");
    }
    /* 如果省掉大括号：
     *   if (score >= 60)
     *       printf("及格\n");
     *       printf("恭喜\n");     ← 这句不受 if 控制，永远执行！
     * 这就是"少写一个括号"的代价。所以建议【永远写大括号】。 */

    /* ---------- ④ 条件可以是任意标量（非 0 即真） ---------- */
    printf("\n=== 非 0 即真 ===\n");
    int n = -3;
    if (n)
        printf("n = %d 被判为真\n", n);

    n = 0;
    if (n)
        printf("这句不会执行\n");
    else
        printf("n = 0 被判为假\n");

    printf("\n=== 所以不需要写 if (x == 1) 来表示「为真」 ===\n");
    int flag = 5;
    if (flag)          printf("if (flag)       → 执行\n");
    if (flag != 0)     printf("if (flag != 0)  → 也执行，意思一样\n");

    /* ---------- ⑤ 嵌套 ---------- */
    printf("\n=== 嵌套 ===\n");
    int a = 5, b = 3;
    if (a > 0) {
        if (b > 0)
            printf("a、b 都是正数\n");
        else
            printf("a 是正数，b 不是\n");
    } else {
        printf("a 不是正数\n");
    }

    /* ---------- ⑥ 悬空 else（重点陷阱） ---------- */
    printf("\n=== 悬空 else ===\n");
    a = 1;
    b = -5;
    printf("a = %d, b = %d\n", a, b);
    printf("执行下面这段（注意缩进骗人）：\n");
    printf("    if (a > 0)\n");
    printf("        if (b > 0)\n");
    printf("            printf(\"both\\n\");\n");
    printf("    else\n");
    printf("        printf(\"a <= 0\\n\");\n");
    printf("实际输出：");

    if (a > 0) {
        if (b > 0)
            printf("both\n");
		else
			printf("a > 0 但 b <= 0\n");
	}
	else {
        printf("a <= 0\n");
	}

    printf("↑ 打印了 a <= 0，可 a 明明是 1！\n");
    printf("  因为 else 就近匹配内层 if，不是外层。\n");
    printf("  想表达「a 不大于 0 时才走 else」，必须给外层加括号：\n");
    printf("    if (a > 0) {\n        if (b > 0) printf(\"both\\n\");\n    } else {\n        printf(\"a <= 0\\n\");\n    }\n");

    /* 正确写法 */
    printf("加括号后的实际输出：");
    if (a > 0) {
        if (b > 0)
            printf("both\n");
        else
            printf("a > 0 但 b <= 0\n");
    } else {
        printf("a <= 0\n");
    }
	printf("%.17f\n", 0.1 + 0.2);
    return 0;
}
