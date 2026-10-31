/* ex94 参考答案 —— 用指针反转字符串 */
#include <stdio.h>

void reverseStr(char *s)
{
    char *right = s;
    while (*right != '\0') right++;     /* 走到 '\0' */
    right--;                            /* ⚠️ 退回最后一个真实字符 */

    while (s < right) {
        char t = *s;
        *s = *right;
        *right = t;
        s++;
        right--;
    }
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

/* 以 "hello" 为例追踪一遍：
 *
 *   s                    right
 *   ↓                       ↓
 *   h  e  l  l  o  \0
 *
 * 第 1 轮：交换 h 和 o → o e l l h，s++ right--
 *   o  e  l  l  h  \0
 *      ↑     ↑
 * 第 2 轮：交换 e 和 l → o l l e h，s++ right--
 *   o  l  l  e  h  \0
 *         ↑
 *       s > right，循环结束
 *
 * 结果："olleh" ✓
 *
 * ⚠️ 两个坑：
 *   ① right-- 不能省：不 -- 的话会拿 '\0' 和 'h' 交换，
 *      结果字符串从第一个字符就是终止符，变成空串。
 *   ② 条件写 s < right 而不是 s <= right：
 *      单数个字符时，中间那个会和自己交换一次，结果对但多做无用功。
 *
 * 注意函数内直接修改了 s 指向的内容，所以 s 必须指向可写的内存。
 * 如果调用者传的是字面量（如 reverseStr("hello")），会崩溃。 */
