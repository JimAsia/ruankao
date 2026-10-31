/* ex115_file_student.c —— 参考答案 */

#include <stdio.h>

typedef struct {
    int    id;
    char   name[20];
    double score;
} Student;

int main(void)
{
    const char *path = "scores.txt";

    Student src[4] = {
        {1, "张三", 85.5},
        {2, "李四", 92.0},
        {3, "王五", 78.0},
        {4, "赵六", 90.5}
    };

    /* ---------- 写 ---------- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) { perror("fopen w"); return 1; }

    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d %s %.1f\n", src[i].id, src[i].name, src[i].score);
    }
    fclose(fp);                             /* 关了再读，保证内容落盘 */

    /* ---------- 读回并统计 ---------- */
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    Student s;
    double total = 0;
    int    n = 0;

    while (fscanf(fp, "%d %19s %lf", &s.id, s.name, &s.score) == 3) {
        printf("读入：%d %s %.1f\n", s.id, s.name, s.score);
        total += s.score;
        n++;
    }
    fclose(fp);

    printf("\n共 %d 人，总分 %.2f，平均 %.2f\n", n, total, total / n);

    printf("\n⭐ 结构体 ↔ 文件的对应关系：\n");
    printf("   一个结构体变量 = 文件里的一行 = 一条记录\n");
    printf("   结构体数组   = 整个文件      = 记录序列\n");
    printf("   所以「读文件」就是「把每行 fscanf 进一个结构体」\n");

    return 0;
}
