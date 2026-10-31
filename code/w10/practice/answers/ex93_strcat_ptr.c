/* ex93 参考答案 —— 手写 strcat（指针版） */
#include <stdio.h>

void myStrcat(char *dst, const char *src)
{
    /* ① 先走到 dst 末尾 */
    while (*dst != '\0') {
        dst++;
    }

    /* ② 从那里开始把 src 抄过去（含 '\0'） */
    while ((*dst++ = *src++) != '\0') {
        ;
    }
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

/* 为什么必须先走到末尾：
 *   strcat 的语义是「接在 dst 后面」，所以要先把 dst 指针推到 '\0' 的位置。
 *   那之后每写一个字符，就覆盖掉原来的 '\0'；
 *   最后 src 的 '\0' 又被写进去，于是新字符串自然结束。
 *
 * 内存变化示意（dst = "Hi", src = "abc"）：
 *
 *   初始：  H  i  \0  ?  ?  ?  ?
 *                  ↑ dst 先走到这
 *   写 'a'：H  i  a   ?  ?  ?  ?
 *   写 'b'：H  i  a   b  ?  ?  ?
 *   写 'c'：H  i  a   b  c  ?  ?
 *   写 '\0'：H  i  a   b  c  \0 ?
 *   结果："Hiabc" ✓
 *
 * ⚠️ 和库函数 strcat 一样，不检查 dst 空间够不够。
 *    dst 必须有足够余量，否则越界写入。 */
