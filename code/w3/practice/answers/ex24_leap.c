/* ex24 参考答案 —— 闰年判断 */
#include <stdio.h>

int main(void)
{
    int year = 0;

    printf("请输入年份: ");
    if (scanf("%d", &year) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    /* 规则拆开看：
     *   条件一：能被 4 整除，且不能被 100 整除
     *   条件二：能被 400 整除
     *   两者是"或"的关系
     *
     * 括号不能随便省 —— 虽然 && 优先级高于 ||，省掉外层括号结果也对，
     * 但写出来能让读代码的人一眼看清逻辑分组。 */
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        printf("%d 是闰年\n", year);
    else
        printf("%d 是平年\n", year);

    return 0;
}
