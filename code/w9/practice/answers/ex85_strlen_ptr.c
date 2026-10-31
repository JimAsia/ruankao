/* ex85 参考答案 —— 用指针手写 strlen */
#include <stdio.h>

int myStrlen(const char *s)
{
    const char *p = s;
    while (*p != '\0') {
        p++;
    }
    return (int)(p - s);        /* 指针相减 = 相隔几个元素 */
}

int main(void)
{
    char s[100];

    printf("请输入一个字符串: ");
    if (scanf("%99s", s) != 1) return 1;

    printf("长度 = %d\n", myStrlen(s));
    return 0;
}

/* 三个要点：
 *
 * ① 参数是 const char *
 *    const 表示"我不会改它"，这是一个承诺，也保护调用者的数据。
 *
 * ② while (*p != '\0') 可以简写成 while (*p)
 *    因为 '\0' 的 ASCII 码就是 0，而「非 0 即真」。
 *
 * ③ 为什么 return p - s 能拿到长度
 *    p 最后停在 '\0' 的位置，s 是开头。
 *    两个指针相减得到「它们之间隔了几个元素」——
 *    对 char* 来说，元素就是字符，所以正好是字符个数。
 *
 *    "Programming" 共 11 个字符：
 *    地址：  s  s+1  ...  s+10  s+11
 *    字符：  P   r   ...   g    '\0'
 *                               ↑ p 最终停在这
 *    p - s = 11 ✓
 *
 * ⚠️ 注意不要写成 return (int)(p - s) + 1 —— 那就把 '\0' 也算进去了。 */
