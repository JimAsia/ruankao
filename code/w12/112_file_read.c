/* 112_file_read.c —— 读文件：fgets / fscanf / EOF 判断
 *
 * 两个核心问题：
 *   1. 怎么判断「读到末尾了」—— 用返回值，不用 feof
 *   2. fgets 会把换行符也读进来 —— 这是最常见的坑
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *path = "demo_read.txt";

    /* ---------- 先准备一个数据文件 ---------- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) { perror("fopen w"); return 1; }
    fprintf(fp, "2026001 张三 92.5\n");
    fprintf(fp, "2026002 李四 78.0\n");
    fprintf(fp, "2026003 王五 96.5\n");
    fclose(fp);

    /* ---------- ① fgets 逐行读：正确写法 ---------- */
    printf("=== ① fgets 逐行读 ===\n");
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    char line[128];
    int lineno = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {   /* ✅ 用返回值判结束 */
        lineno++;
        /* fgets 会保留换行符，这里去掉，否则输出会有空行 */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        printf("  第 %d 行：[%s]（%zu 字符）\n", lineno, line, strlen(line));
    }
    fclose(fp);

    /* ---------- ② 证明 fgets 保留了换行符 ---------- */
    printf("\n=== ② fgets 到底有没有留换行 ===\n");
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }
    fgets(line, sizeof(line), fp);              /* 只读一行 */
    printf("  读到的长度 = %zu（内容本身 19 字节，多出来的 1 字节就是 \\n）\n",
           strlen(line));
    printf("  ⚠️ 注意中文「张三」在 UTF-8 里占 3 字节，不是 1 个\n");
    printf("  最后一个字符的 ASCII = %d（10 就是 '\\n'）\n",
           (int)line[strlen(line) - 1]);
    fclose(fp);

    printf("\n  ⭐ 所以 fgets 之后常要手动去掉 '\\n'\n");
    printf("     不去掉的话，strcmp 比较会永远不相等\n");

    /* ---------- ③ fscanf 按格式读：适合解析数字 ---------- */
    printf("\n=== ③ fscanf 读结构化数据 ===\n");
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    int    id;
    char   name[32];
    double score;
    double total = 0;
    int    count = 0;

    /* ✅ 用返回值判断：读成功 3 个才继续 */
    while (fscanf(fp, "%d %31s %lf", &id, name, &score) == 3) {
        printf("  %d %s %.1f\n", id, name, score);
        total += score;
        count++;
    }
    fclose(fp);
    printf("  共 %d 条，平均 %.2f\n", count, total / count);

    printf("\n  ⭐ 为什么写 == 3，不写 != EOF？\n");
    printf("     fscanf 返回的是「成功读到的项数」，不是 EOF。\n");
    printf("     最后一行格式不对时，返回 1 或 2，!= EOF 会漏掉这种错。\n");

    /* ---------- ④ feof 的错误用法 ---------- */
    printf("\n=== ④ 不要用 feof 做循环条件 ===\n");
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    int badCount = 0;
    while (!feof(fp)) {                 /* ❌ 错误示范 */
        if (fgets(line, sizeof(line), fp) == NULL) break;   /* 靠这个才没死循环 */
        badCount++;
    }
    printf("  feof 写法读到 %d 行（结果碰巧对，但逻辑是错的）\n", badCount);
    printf("  问题：feof 只有在「读失败之后」才为真，\n");
    printf("        循环体会多跑一次，处理一条并不存在的数据。\n");
    printf("        如果里面是 sum += x，就会多加一次垃圾值。\n");
    fclose(fp);

    return 0;
}
