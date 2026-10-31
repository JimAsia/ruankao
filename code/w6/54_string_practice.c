/* 54_string_practice.c —— 四个字符串处理实战
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* ========== ① 统计各类字符个数 ========== */
    printf("=== ① 统计字符 ===\n");
    char text[] = "Hello, World! 2026";
    int upper = 0, lower = 0, digit = 0, space = 0, other = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z')      upper++;
        else if (c >= 'a' && c <= 'z') lower++;
        else if (c >= '0' && c <= '9') digit++;
        else if (c == ' ')             space++;
        else                           other++;
    }

    printf("  字符串：\"%s\"\n", text);
    printf("  大写字母 %d 个\n", upper);
    printf("  小写字母 %d 个\n", lower);
    printf("  数字     %d 个\n", digit);
    printf("  空格     %d 个\n", space);
    printf("  其他     %d 个\n", other);
    printf("  总长度   %zu\n", strlen(text));

    /* ========== ② 大小写转换 ========== */
    printf("\n=== ② 大小写转换 ===\n");
    char s1[] = "MiXeD CaSe";
    char toUpper[50], toLower[50];

    for (int i = 0; s1[i] != '\0'; i++) {
        /* 小写转大写：减 32；大写转小写：加 32 */
        if (s1[i] >= 'a' && s1[i] <= 'z')
            toUpper[i] = s1[i] - 32;
        else
            toUpper[i] = s1[i];
    }
    toUpper[strlen(s1)] = '\0';         /* ⚠️ 手动补结束符 */

    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] >= 'A' && s1[i] <= 'Z')
            toLower[i] = s1[i] + 32;
        else
            toLower[i] = s1[i];
    }
    toLower[strlen(s1)] = '\0';

    printf("  原串：  \"%s\"\n", s1);
    printf("  全大写：\"%s\"\n", toUpper);
    printf("  全小写：\"%s\"\n", toLower);
    printf("  原理：'a' - 'A' = 32，所以小写减 32 变大写\n");

    /* ========== ③ 判断回文字符串 ========== */
    printf("\n=== ③ 回文判断 ===\n");
    char words[4][20] = {"level", "hello", "abcba", "abcd"};
    /* 二维字符数组 = 多个字符串，每行一个 */

    for (int k = 0; k < 4; k++) {
        int i = 0;
        int j = (int)strlen(words[k]) - 1;
        int isPal = 1;

        while (i < j) {
            if (words[k][i] != words[k][j]) {
                isPal = 0;
                break;
            }
            i++;
            j--;
        }
        printf("  \"%-6s\" → %s\n", words[k], isPal ? "是回文" : "不是回文");
    }
    printf("  思路：首尾同时向中间走，碰到不同就否定\n");

    /* ========== ④ 统计单词个数 ========== */
    printf("\n=== ④ 统计单词个数 ===\n");
    char sentence[] = "I am learning C language";
    int wordCount = 0;
    int inWord = 0;                     /* 是否正处在一个单词内部 */

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] != ' ') {
            if (!inWord) {              /* 从空格进入非空格 = 一个新单词开始 */
                wordCount++;
                inWord = 1;
            }
        } else {
            inWord = 0;                 /* 遇到空格，离开单词 */
        }
    }
    printf("  句子：\"%s\"\n", sentence);
    printf("  单词数 = %d\n", wordCount);
    printf("  关键：用 inWord 标志记录「上一个字符是不是空格」\n");

    return 0;
}
