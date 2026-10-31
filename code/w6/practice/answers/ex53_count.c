/* ex53 参考答案 —— 统计字符类型 */
#include <stdio.h>

int main(void)
{
    char s[100];

    printf("请输入一个字符串(不含空格): ");
    if (scanf("%99s", s) != 1) {            /* 99 限长，防止溢出 */
        printf("输入格式不对\n");
        return 1;
    }

    int upper = 0, lower = 0, digit = 0, other = 0;

    /* 遍历到 '\0' 就停，不需要 strlen */
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z')       upper++;
        else if (c >= 'a' && c <= 'z')  lower++;
        else if (c >= '0' && c <= '9')  digit++;
        else                            other++;
    }

    printf("大写 = %d，小写 = %d，数字 = %d，其他 = %d\n",
           upper, lower, digit, other);

    /* 为什么用字符区间而不是 isupper() 之类的库函数：
     *   ① 软考的应用题通常假定"不用库函数自己实现"
     *   ② 字符比较本质是 ASCII 码比较，能这样写的前提是：
     *      'A'~'Z' 是连续的（65~90）
     *      'a'~'z' 是连续的（97~122）
     *      '0'~'9' 是连续的（48~57） */

    return 0;
}
