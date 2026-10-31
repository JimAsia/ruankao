/* ex114_file_copy.c —— 参考答案 */

#include <stdio.h>

int main(void)
{
    const char *src = "src114.txt";
    const char *dst = "dst114.txt";

    /* ---------- 写源文件 ---------- */
    FILE *fp = fopen(src, "w");
    if (fp == NULL) { perror("fopen w"); return 1; }
    fprintf(fp, "C programming\n");
    fprintf(fp, "file io is easy\n");
    fprintf(fp, "practice makes perfect\n");
    fclose(fp);

    /* ---------- 复制 ---------- */
    FILE *in = fopen(src, "r");
    if (in == NULL) { perror("open src"); return 1; }

    FILE *out = fopen(dst, "w");
    if (out == NULL) {
        perror("open dst");
        fclose(in);                         /* ⚠️ 别忘了关 in */
        return 1;
    }

    int ch;
    long bytes = 0;
    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
        bytes++;
    }

    fclose(in);
    fclose(out);
    printf("复制完成，共 %ld 字节\n", bytes);

    /* ---------- 比较两个文件 ---------- */
    FILE *f1 = fopen(src, "r");
    FILE *f2 = fopen(dst, "r");
    if (f1 == NULL || f2 == NULL) {
        perror("open for compare");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 1;
    }

    int c1, c2;
    int same = 1;
    while ((c1 = fgetc(f1)) != EOF) {
        c2 = fgetc(f2);
        if (c1 != c2) { same = 0; break; }
    }
    /* 如果 f1 到末尾了 f2 还没到，长度不同，也不一致 */
    if (same && fgetc(f2) != EOF) same = 0;

    fclose(f1);
    fclose(f2);

    printf(same ? "两个文件内容一致\n" : "两个文件内容不同\n");

    return 0;
}
