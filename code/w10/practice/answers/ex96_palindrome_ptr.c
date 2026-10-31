/* ex96 参考答案 —— 用指针判断回文 */
#include <stdio.h>

int isPalindrome(const char *s)
{
    const char *left = s;
    const char *right = s;

    while (*right != '\0') right++;     /* 走到末尾 */
    right--;                            /* 退回最后一个字符 */

    while (left < right) {
        if (*left != *right) return 0;  /* 一发现不同就否定 */
        left++;
        right--;
    }
    return 1;
}

int main(void)
{
    const char *tests[] = {"level", "hello", "abcba", "a", "ab"};

    for (int i = 0; i < 5; i++) {
        printf("%-8s → %s\n", tests[i],
               isPalindrome(tests[i]) ? "是回文" : "不是回文");
    }

    return 0;
}

/* 边界情况自动正确：
 *   空串 ""   → right 先指向 '\0'，right-- 后变成 s-1，
 *               left(s) < right(s-1) 为假，循环不执行 → 返回 1（是回文）
 *   单字符 "a" → right 停在 'a'，left == right，循环不执行 → 返回 1
 *   两字符 "ab" → 比较一次 'a' != 'b' → 返回 0
 *
 * ⚠️ 空串时 right 会减到 s-1，这是「指向数组前面一个位置」。
 *    C 标准严格来说不允许指针指到数组开头之前，
 *    但实际编译器不会出问题。想更严谨可以加 if 判空：
 *      if (*s == '\0') return 1;
 *
 * 指针版和 W6 的下标版对照：
 *   下标版：i = 0, j = strlen(s)-1, while (i < j)
 *   指针版：left = s, right = s+strlen(s)-1, while (left < right)
 *   完全同一个逻辑，只是操作地址而不是下标。 */
