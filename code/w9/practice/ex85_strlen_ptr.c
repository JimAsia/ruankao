/* ex85 —— 用指针手写 strlen
 * 要求：写 int myStrlen(const char *s)，返回字符串长度（不含 '\0'）。
 *       必须用指针移动，不能用下标。
 *
 * 测试：输入 Programming
 *   输出：长度 = 11
 *
 * 提示：
 *   const char *p = s;
 *   while (*p != '\0') p++;
 *   return (int)(p - s);         ← 指针相减得到字符个数
 *
 * 或者更简洁的写法：
 *   const char *p = s;
 *   while (*p) p++;              ← 非 0 即真，'\0' 的 ASCII 就是 0
 *   return p - s;
 */
#include <stdio.h>

int myStrlen(const char *s)
{
    /* TODO */
    return 0;
}

int main(void)
{
    char s[100];

    printf("请输入一个字符串: ");
    if (scanf("%99s", s) != 1) return 1;

    printf("长度 = %d\n", myStrlen(s));
    return 0;
}
