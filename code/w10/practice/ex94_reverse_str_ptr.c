/* ex94 —— 用指针反转字符串
 * 要求：写 void reverseStr(char *s)，原地反转字符串。
 *       必须用指针，不用下标。
 *
 * 测试：输入 hello
 *   输出：olleh
 *
 * 提示：
 *   ① 找到末尾：char *right = s; while (*right) right++; right--;
 *   ② 首尾交换：while (s < right) { ... s++; right--; }
 *   ⚠️ right 必须先 --，否则会把 '\0' 卷进来
 */
#include <stdio.h>

void reverseStr(char *s)
{
    /* TODO */
}

int main(void)
{
    char s[100];

    printf("请输入一个字符串: ");
    if (scanf("%99s", s) != 1) return 1;

    reverseStr(s);
    printf("%s\n", s);

    return 0;
}
