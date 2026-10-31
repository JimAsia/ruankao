/* 111_file_write.c —— 写文件：fopen / fprintf / fclose
 *
 * 文件操作四步固定流程：
 *   1. fopen 打开（拿 FILE*，必须判 NULL）
 *   2. 读写
 *   3. fclose 关闭
 *
 * 模式：w 覆盖写、a 追加写、r 读
 */

#include <stdio.h>

int main(void)
{
    const char *path = "demo_write.txt";

    /* ---------- ① 打开：必须判 NULL ---------- */
    printf("=== ① fopen 的返回值必须检查 ===\n");
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {                       /* ⚠️ 这一步绝对不能省 */
        printf("  打开失败！\n");
        perror("  fopen");                  /* perror 会打印系统给的原因 */
        return 1;
    }
    printf("  打开 %s 成功，fp = %p\n", path, (void *)fp);

    /* ---------- ② 写：fprintf 和 printf 用法一样，只是多一个 fp ---------- */
    printf("\n=== ② 写入三行 ===\n");
    fprintf(fp, "2026001 张三 92.5\n");
    fprintf(fp, "2026002 李四 78.0\n");
    fprintf(fp, "2026003 王五 96.5\n");
    printf("  已写入 3 行\n");

    /* ---------- ③ 关闭：不关会丢数据 ---------- */
    fclose(fp);
    printf("  已 fclose\n");

    printf("\n  ⭐ 为什么必须 fclose？\n");
    printf("     fprintf 写的是「缓冲区」，不是直接写磁盘。\n");
    printf("     缓冲区满了或 fclose 时才真正落盘。\n");
    printf("     不关就退出，数据可能丢 —— 尤其是程序崩溃时。\n");

    /* ---------- ④ 追加模式 a ---------- */
    printf("\n=== ③ 追加模式 a ===\n");
    fp = fopen(path, "a");
    if (fp == NULL) { perror("  fopen a"); return 1; }
    fprintf(fp, "2026004 赵六 65.0\n");
    fclose(fp);
    printf("  用 a 模式追加了一行，原内容保留\n");

    /* ---------- ⑤ w 模式会清空！ ---------- */
    printf("\n=== ④ 危险提醒 ===\n");
    printf("  w 模式打开一个已有文件，会立刻把内容清空！\n");
    printf("  哪怕你一个字都不写，文件也变 0 字节。\n");
    printf("  这是新手丢数据的头号原因。\n");

    /* 用 r 模式打开验证一下，r 是只读，不会清空 */
    fp = fopen(path, "r");
    if (fp == NULL) { perror("  fopen r"); return 1; }
    char line[128];
    printf("\n  当前文件内容：\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("    %s", line);
    }
    fclose(fp);

    return 0;
}
