/* ex25 参考答案 —— 字符类型判断 */
#include <stdio.h>

int main(void)
{
    char ch = 0;

    printf("请输入一个字符: ");
    if (scanf(" %c", &ch) != 1) {   /* 前面的空格跳过残留空白 */
        printf("输入格式不对\n");
        return 1;
    }

    /* 字符比较本质是 ASCII 码比较，所以可以直接用 >= 'A' && <= 'Z' */
    if (ch >= 'A' && ch <= 'Z')
        printf("'%c' 是大写字母\n", ch);
    else if (ch >= 'a' && ch <= 'z')
        printf("'%c' 是小写字母\n", ch);
    else if (ch >= '0' && ch <= '9')
        printf("'%c' 是数字\n", ch);
    else if (ch == ' ')
        printf("这个字符是空格\n");
    else
        printf("'%c' 是其他字符\n", ch);

    /* 顺便验证一下 ASCII 值的连续性：
     * 'A'=65, 'Z'=90 是连续的；'a'=97, 'z'=122 是连续的；
     * '0'=48, '9'=57 是连续的。所以范围判断才成立。 */

    return 0;
}
