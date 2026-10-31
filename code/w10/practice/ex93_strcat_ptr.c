/* ex93 —— 手写 strcat（指针版）
 * 要求：写 void myStrcat(char *dst, const char *src)，把 src 接到 dst 末尾。
 *       必须用指针。
 *
 * 测试：输入 Hello 和 World
 *   输出：Hello World
 *
 * 提示：
 *   ① 先让 dst 指针走到末尾：while (*dst) dst++;
 *   ② 再把 src 一个个抄过去：while ((*dst++ = *src++) != '\0') ;
 */
#include <stdio.h>

void myStrcat(char *dst, const char *src)
{
    /* TODO */
}

int main(void)
{
    char dst[200] = "Hello ";
    char src[100];

    printf("请输入要拼接的字符串: ");
    if (scanf("%99s", src) != 1) return 1;

    myStrcat(dst, src);
    printf("%s\n", dst);

    return 0;
}
