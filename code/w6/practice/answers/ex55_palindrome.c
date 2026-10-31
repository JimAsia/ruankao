/* ex55 参考答案 —— 回文字符串判断 */
#include <stdio.h>

int main(void)
{
    char s[100];

    printf("请输入一个字符串: ");
    if (scanf("%99s", s) != 1) return 1;

    /* 找末尾 */
    int right = 0;
    while (s[right] != '\0') right++;
    right--;

    int left = 0;
    int isPal = 1;

    while (left < right) {
        if (s[left] != s[right]) {
            isPal = 0;
            break;                      /* 一发现不同就可以收工 */
        }
        left++;
        right--;
    }

    if (isPal)
        printf("是回文\n");
    else
        printf("不是回文\n");

    /* 边界情况自动正确：
     *   空串：right 变成 -1，left(0) < right(-1) 为假，循环不执行 → 是回文
     *   单字符：right = 0，left(0) < right(0) 为假 → 是回文
     *   两个字符：正常比较一次
     *
     * 补充：如果要忽略大小写和标点（比如 "A man, a plan, a canal: Panama"），
     * 需要先把字符串"清洗"一遍：只保留字母数字并转成小写，再做回文判断。 */

    return 0;
}
