/* ex92 参考答案 —— 手写 strcpy（指针版） */
#include <stdio.h>

void myStrcpy(char *dst, const char *src)
{
    while ((*dst++ = *src++) != '\0') {
        ;                               /* 循环体是空的，所有工作都在条件里 */
    }
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

/* 那一行到底在干什么：while ((*dst++ = *src++) != '\0') ;
 *
 * 拆成四步（每一步都按 C 的求值顺序）：
 *   ① *dst = *src    把 src 当前字符写到 dst 当前位置
 *   ② 判断赋值表达式的值（就是刚写的那个字符）是不是 '\0'
 *   ③ dst++          dst 后移一位
 *   ④ src++          src 后移一位
 *   然后重复，直到复制了 '\0' 才停。
 *
 * ⭐ 为什么'\0' 也被复制了？
 *    条件是「!= '\0'」，看起来不复制 '\0'。但赋值发生在判断之前 ——
 *    '\0' 已经写进 dst 了，只是判断后退出循环。
 *    所以 dst 天然以 '\0' 结尾，不用手动补。
 *
 * 等价但更易读的写法：
 *   while (*src != '\0') {
 *       *dst = *src;
 *       dst++;
 *       src++;
 *   }
 *   *dst = '\0';        ← 这种写法必须手动补
 *
 * 考试时如果怕写错，用易读版；理解了原理再用一行版。 */
