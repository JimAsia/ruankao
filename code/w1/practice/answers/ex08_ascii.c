/* ex08 参考答案 —— 字符与 ASCII 码 */
#include <stdio.h>

int main(void)
{
    char upper = 0;

    printf("请输入一个大写字母: ");
    if (scanf(" %c", &upper) != 1) {   /* 前面的空格跳过残留空白 */
        printf("输入格式不对\n");
        return 1;
    }

    printf("%c 的 ASCII 码是 %d\n", upper, upper);
    /* ↑ 同一个变量，%c 打字符，%d 打 ASCII 码 */

    printf("对应小写字母是 %c\n", upper + 32);
    /* ↑ 'a' - 'A' == 32，大写加 32 就是小写 */

    return 0;
}
