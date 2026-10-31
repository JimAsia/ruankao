/* ex92 —— 手写 strcpy（指针版）
 * 要求：写 void myStrcpy(char *dst, const char *src)，把 src 复制到 dst。
 *       必须用指针，不用下标。
 *
 * 测试：输入 Programming
 *   输出：复制结果：Programming
 *
 * 提示：最经典的写法只有一行：
 *   while ((*dst++ = *src++) != '\0') ;
 * 拆开理解：
 *   ① *dst = *src     复制一个字符
 *   ② 判断这个字符是不是 '\0'
 *   ③ dst++ 和 src++  两个指针都后移
 * 注意最后要保证 dst 以 '\0' 结尾（上面的写法天然满足）
 */
#include <stdio.h>

void myStrcpy(char *dst, const char *src)
{
    /* TODO */
}

int main(void)
{
    char s[100];
    char t[100];

    printf("请输入一个字符串: ");
    if (scanf("%99s", s) != 1) return 1;

    myStrcpy(t, s);
    printf("复制结果：%s\n", t);

    return 0;
}
