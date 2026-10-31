/* 25_branch_practice.c —— 分支的四个经典实战
 *
 * 这些题型在软考应用技术里反复出现，而且都是"不用循环就能写完"的短程序。
 */
#include <stdio.h>

int main(void)
{
    /* ========== ① 闰年判断 ==========
     * 规则：能被 4 整除且不能被 100 整除，或者能被 400 整除
     * 注意 (y % 4 == 0 && y % 100 != 0) 外面的括号不能少：
     *   || 优先级低于 &&，不写括号其实也对，
     *   但写出来能让人一眼看清两个条件的关系。
     */
    printf("=== ① 闰年判断 ===\n");

    int y;
    const char *r;

    y = 2024;
    r = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? "闰年" : "平年";
    printf("  %d → %s\n", y, r);

    y = 2023;
    r = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? "闰年" : "平年";
    printf("  %d → %s\n", y, r);

    y = 1900;
    r = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? "闰年" : "平年";
    printf("  %d → %s   （能被 100 整除但不能被 400 整除，所以是平年）\n", y, r);

    y = 2000;
    r = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? "闰年" : "平年";
    printf("  %d → %s   （能被 400 整除，所以是闰年）\n", y, r);

    /* ========== ② 成绩分级：两种写法对比 ========== */
    printf("\n=== ② 成绩分级 ===\n");
    int score = 85;

    /* 写法一：if - else if 链（适合范围判断） */
    printf("  if-else 链：");
    if (score >= 90)      printf("优秀\n");
    else if (score >= 80) printf("良好\n");
    else if (score >= 70) printf("中等\n");
    else if (score >= 60) printf("及格\n");
    else                  printf("不及格\n");

    /* 写法二：switch（先除 10 转成区间） */
    printf("  switch  ：");
    switch (score / 10) {
        case 10:
        case 9:  printf("优秀\n"); break;
        case 8:  printf("良好\n"); break;
        case 7:  printf("中等\n"); break;
        case 6:  printf("及格\n"); break;
        default: printf("不及格\n");
    }
    printf("  两种写法结果一样。范围判断用 if-else 更直观，\n");
    printf("  switch 要先想办法把范围变成离散值（这里用 /10）。\n");

    /* ========== ③ 三数排序（不用循环） ========== */
    printf("\n=== ③ 三数排序 ===\n");
    int a = 3, b = 1, c = 2, t;
    printf("  排序前：a=%d b=%d c=%d\n", a, b, c);

    /* 思路：三轮比较，保证 a 最小、c 最大 */
    if (a > b) { t = a; a = b; b = t; }   /* 保证 a <= b */
    if (a > c) { t = a; a = c; c = t; }   /* 保证 a <= c，此时 a 已是最小 */
    if (b > c) { t = b; b = c; c = t; }   /* 保证 b <= c */

    printf("  排序后：a=%d b=%d c=%d\n", a, b, c);
    printf("  这三行的顺序可以打乱吗？不行 —— 每行都依赖前一行建立的顺序。\n");

    /* ========== ④ 三角形判断 ========== */
    printf("\n=== ④ 三角形判断 ===\n");
    int x = 3, y1 = 4, z = 5;
    printf("  三边：%d %d %d\n", x, y1, z);

    if (x + y1 > z && x + z > y1 && y1 + z > x) {
        /* 能构成三角形，再判断类型 */
        if (x == y1 && y1 == z)
            printf("  → 等边三角形\n");
        else if (x == y1 || y1 == z || x == z)
            printf("  → 等腰三角形\n");
        else if (x * x + y1 * y1 == z * z ||
                 x * x + z * z == y1 * y1 ||
                 y1 * y1 + z * z == x * x)
            printf("  → 直角三角形\n");
        else
            printf("  → 普通三角形\n");
    } else {
        printf("  → 不能构成三角形\n");
    }
    printf("  注意外层先判「能不能构成」，再判「是什么类型」—— 两层逻辑不能合并。\n");

    /* ========== ⑤ 分支的三种写法怎么选 ========== */
    printf("\n=== 选型建议 ===\n");
    printf("  单条件、二选一        → if-else\n");
    printf("  多区间、有先后顺序    → if - else if 链（注意从大到小或从小到大排好）\n");
    printf("  等值匹配、分支多      → switch\n");
    printf("  简单二选一且要取值    → ?: 三元\n");

    return 0;
}
