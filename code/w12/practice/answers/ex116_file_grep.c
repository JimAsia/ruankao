/* ex116_file_grep.c —— 参考答案 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *path = "text116.txt";

    /* ---------- 写测试文件 ---------- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) { perror("fopen w"); return 1; }
    fprintf(fp, "The quick brown fox\n");
    fprintf(fp, "jumps over the lazy dog\n");
    fprintf(fp, "C programming is fun\n");
    fprintf(fp, "file io is easy\n");
    fclose(fp);

    /* ---------- 读关键字 ---------- */
    char key[20];
    printf("请输入关键字：");
    if (scanf("%19s", key) != 1) {
        printf("输入有误\n");
        return 1;
    }

    /* ---------- 逐行查找 ---------- */
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    char line[256];
    int lineno = 0, hits = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        lineno++;

        if (strstr(line, key) != NULL) {     /* 找到子串 */
            /* fgets 保留了 '\n'，原样输出正好换行 */
            printf("第 %d 行：%s", lineno, line);

            /* 如果最后一行没有 '\n'，手动补一个，避免输出粘在一起 */
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] != '\n') printf("\n");

            hits++;
        }
    }
    fclose(fp);

    printf("命中 %d 行\n", hits);

    printf("\n⭐ strstr 返回的是「第一次出现的地址」，不是下标\n");
    printf("   所以只能用 != NULL 或 == NULL 判断，不能直接打印\n");
    printf("   想要位置：int pos = (int)(strstr(line, key) - line);\n");

    return 0;
}
