/* 113_file_process.c —— 文件处理的三个经典任务
 *
 * ① 统计：行数、字符数、单词数（就是 Linux 的 wc 命令）
 * ② 复制：逐字符 / 逐块
 * ③ 合并：把两个文件拼成一个
 *
 * 这三个是软考「文件操作」大题的常见形态。
 */

#include <stdio.h>

/* ---------- ① 统计 ---------- */
void countFile(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL) { perror("countFile"); return; }

    /* fgetc 一次读一个字符，读不到返回 EOF（-1） */
    int ch;
    long chars = 0, lines = 0, words = 0;
    int inWord = 0;                     /* 标记「当前是否在单词内」 */

    while ((ch = fgetc(fp)) != EOF) {
        chars++;

        if (ch == '\n') lines++;

        /* 空白字符：空格、换行、制表符 */
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            inWord = 0;
        } else if (!inWord) {
            /* 从「不在单词」变成「在单词」→ 新单词开始 */
            inWord = 1;
            words++;
        }
    }
    fclose(fp);

    printf("  %-18s 行 %ld  字符 %ld  单词 %ld\n", path, lines, chars, words);
}

/* ---------- ② 复制：逐字符版 ---------- */
int copyByChar(const char *src, const char *dst)
{
    FILE *in  = fopen(src, "r");
    if (in == NULL) { perror("copy 源文件"); return -1; }

    FILE *out = fopen(dst, "w");
    if (out == NULL) { perror("copy 目标文件"); fclose(in); return -1; }

    int ch;
    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}

/* ---------- ② 复制：逐块版（更快） ---------- */
int copyByBlock(const char *src, const char *dst)
{
    FILE *in  = fopen(src, "rb");
    if (in == NULL) { perror("copy 源文件"); return -1; }

    FILE *out = fopen(dst, "wb");
    if (out == NULL) { perror("copy 目标文件"); fclose(in); return -1; }

    char buf[512];
    size_t n;
    /* fread 返回实际读到的字节数，读到 0 说明结束 */
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        fwrite(buf, 1, n, out);         /* ⚠️ 写 n 个，不是 sizeof(buf) */
    }

    fclose(in);
    fclose(out);
    return 0;
}

/* ---------- ③ 合并 ---------- */
int mergeFiles(const char *a, const char *b, const char *out)
{
    FILE *fa = fopen(a, "r");
    FILE *fb = fopen(b, "r");
    if (fa == NULL || fb == NULL) {
        perror("merge");
        if (fa) fclose(fa);
        if (fb) fclose(fb);
        return -1;
    }

    FILE *fo = fopen(out, "w");
    if (fo == NULL) { perror("merge 输出"); fclose(fa); fclose(fb); return -1; }

    int ch;
    while ((ch = fgetc(fa)) != EOF) fputc(ch, fo);
    while ((ch = fgetc(fb)) != EOF) fputc(ch, fo);

    fclose(fa); fclose(fb); fclose(fo);
    return 0;
}

int main(void)
{
    /* ---------- 准备两个测试文件 ---------- */
    FILE *fp = fopen("part1.txt", "w");
    if (fp == NULL) { perror("fopen"); return 1; }
    fprintf(fp, "hello world\n");
    fprintf(fp, "C language is fun\n");
    fclose(fp);

    fp = fopen("part2.txt", "w");
    if (fp == NULL) { perror("fopen"); return 1; }
    fprintf(fp, "file io\n");
    fprintf(fp, "the end\n");
    fclose(fp);

    /* ---------- ① 统计 ---------- */
    printf("=== ① 统计三个文件 ===\n");
    countFile("part1.txt");
    countFile("part2.txt");
    countFile("113_file_process.c");

    printf("\n  ⭐ 单词数统计的技巧：用 inWord 标记\n");
    printf("     空格 → inWord = 0\n");
    printf("     非空格且 inWord == 0 → 新单词，words++，inWord = 1\n");
    printf("     连续多个空格只会算一次，这是关键\n");

    /* ---------- ② 复制 ---------- */
    printf("\n=== ② 复制文件 ===\n");
    if (copyByChar("part1.txt", "copy1.txt") == 0)
        printf("  逐字符复制 → copy1.txt\n");
    if (copyByBlock("part1.txt", "copy2.txt") == 0)
        printf("  逐块复制   → copy2.txt\n");

    printf("\n  对比两种复制：\n");
    printf("    逐字符：调用 1 次/字节，简单但慢\n");
    printf("    逐块  ：一次 512 字节，快得多\n");
    printf("    实际工程都用逐块，只有演示才用逐字符\n");

    printf("\n  ⚠️ fwrite 必须写 n，不能写 sizeof(buf)\n");
    printf("     最后一块可能只读了 100 字节，写 512 会把垃圾写进去\n");

    /* ---------- ③ 合并 ---------- */
    printf("\n=== ③ 合并文件 ===\n");
    if (mergeFiles("part1.txt", "part2.txt", "merged.txt") == 0) {
        printf("  part1 + part2 → merged.txt，内容：\n");
        fp = fopen("merged.txt", "r");
        if (fp != NULL) {
            char line[128];
            while (fgets(line, sizeof(line), fp) != NULL) {
                printf("    %s", line);
            }
            fclose(fp);
        }
    }

    /* ---------- ④ 二进制和文本模式的差别 ---------- */
    printf("\n=== ④ 文本模式 vs 二进制模式 ===\n");
    printf("  Windows 上：\n");
    printf("    \"r\" / \"w\"   文本模式，写 \\n 时自动变成 \\r\\n\n");
    printf("    \"rb\" / \"wb\" 二进制模式，写什么就是什么\n");
    printf("  Linux 上两者没区别（这也是跨平台代码常见的坑）\n");
    printf("\n  软考只要记住：模式字符串共 12 种组合\n");
    printf("    读写 × 文本/二进制 × 存在要求\n");
    printf("    最常用：r  w  a  r+  w+  a+  rb  wb\n");

    return 0;
}
