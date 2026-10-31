/* ex105_nested.c —— 参考答案 */

#include <stdio.h>

struct Date {
    int y, m, d;
};

struct Person {
    char       name[20];
    struct Date birth;
};

int main(void)
{
    struct Person p;
    printf("姓名 出生年 月 日：");
    if (scanf("%19s %d %d %d", p.name, &p.birth.y, &p.birth.m, &p.birth.d) != 4) {
        printf("输入有误\n");
        return 1;
    }

    /* 基准日期：2026-10-24 */
    const int NOW_Y = 2026, NOW_M = 10, NOW_D = 24;

    int age = NOW_Y - p.birth.y;

    /* 今年生日还没到 → 减 1 */
    if (p.birth.m > NOW_M || (p.birth.m == NOW_M && p.birth.d > NOW_D)) {
        age--;
    }

    printf("%s %d-%02d-%02d 年龄 %d\n",
           p.name, p.birth.y, p.birth.m, p.birth.d, age);

    /* 两个常见错误演示 */
    printf("\n易错点：\n");
    printf("  1. 只算年份差 = %d，生日没到就会多算 1 岁\n", NOW_Y - p.birth.y);
    printf("  2. 条件写成 p.birth.m > NOW_M && p.birth.d > NOW_D 是错的\n");
    printf("     同月时要单独判断日，必须用 || 拆成两种情况\n");

    return 0;
}
