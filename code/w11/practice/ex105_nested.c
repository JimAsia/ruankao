/* ex105_nested.c —— 嵌套结构体：生日与年龄
 *
 * 要求：
 *   1. 定义 struct Date { int y, m, d; };
 *   2. 定义 struct Person { char name[20]; struct Date birth; };
 *   3. 读入姓名和生日，计算到 2026 年 10 月 24 日的周岁年龄
 *
 * 输入示例：
 *   李四 2008 3 15
 * 输出示例：
 *   李四 2008-03-15 年龄 18
 *
 * 年龄算法：先算年份差，如果今年生日还没过（月日小于 10-24），再减 1
 */

#include <stdio.h>

struct Date {
    int y, m, d;
};

/* TODO 1：定义 struct Person */

int main(void)
{
    /* TODO 2：读入姓名和生日 */

    /* TODO 3：算年龄（注意生日没到要减 1） */

    /* TODO 4：输出，月份和日期补零到 2 位（%02d） */

    return 0;
}
