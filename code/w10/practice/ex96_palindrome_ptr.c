/* ex96 —— 用指针判断回文
 * 要求：写 int isPalindrome(const char *s)，是回文返回 1，否则 0。
 *       必须用指针。
 *
 * 测试：level → 1，hello → 0，abcba → 1，a → 1
 *
 * 提示：
 *   const char *left = s;
 *   const char *right = s;
 *   while (*right) right++;      // 走到 '\0'
 *   right--;                     // 退回最后一个字符
 *   while (left < right) {
 *       if (*left != *right) return 0;
 *       left++; right--;
 *   }
 *   return 1;
 */
#include <stdio.h>

int isPalindrome(const char *s)
{
    /* TODO */
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
