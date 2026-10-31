/* ex113_file_count.c —— 参考答案 */

#include <stdio.h>

int main(void)
{
    const char *path = "test113.txt";

    /* ---------- 写测试文件 ---------- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) { perror("fopen w"); return 1; }
    fprintf(fp, "hello world\n");
    fprintf(fp, "C programming 2026\n");
    fprintf(fp, "file io is easy\n");
    fclose(fp);

    /* ---------- 逐字符统计 ---------- */
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    int ch;                                 /* ⚠️ int，不是 char */
    long chars = 0, lines = 0, words = 0;
    int inWord = 0;

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }
    fclose(fp);

    printf("行 %ld  字符 %ld  单词 %ld\n", lines, chars, words);

    printf("\n为什么 ch 必须是 int：\n");
    printf("  fgetc 读不到时返回 EOF（通常是 -1）\n");
    printf("  如果 ch 是 unsigned char，-1 会变成 255，永远不等于 EOF → 死循环\n");

    return 0;
}
