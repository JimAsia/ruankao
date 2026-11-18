/* ex115_file_student.c —— 结构体 + 文件：成绩表存取
 *
 * 要求：
 *   1. 定义 struct Student { int id; char name[20]; double score; };
 *   2. 把 4 个学生写入 scores.txt（每行：学号 姓名 成绩）
 *   3. 关闭后重新打开读回，计算总分和平均分，输出平均分（2 位小数）
 *
 * 固定数据：
 *   1 张三 85.5
 *   2 李四 92.0
 *   3 王五 78.0
 *   4 赵六 90.5
 * 预期输出：
 *   共 4 人，总分 346.00，平均 86.50
 *
 * 要点：
 *   - 写：fprintf(fp, "%d %s %.1f\n", ...)
 *   - 读：fscanf(fp, "%d %19s %lf", &s.id, s.name, &s.score) == 3
 *   - 结构体是「一条记录」，文件是「记录序列」，这个对应关系要建立起来
 */

#include <stdio.h>

typedef struct {
    int    id;
    char   name[20];
    double score;
} Student;

int main(void)
{
    const char *path = "scores.txt";

    /* TODO 1：准备 4 条数据，写入文件 */
	Student stus[4] = { {1, "张三", 85.5}, {2, "李四", 92.0}, {3, "王五", 78.0}, {4, "赵六", 90.5} };
	FILE *fp = fopen(path, "w");
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}
	for (int i = 0; i < 4; ++i) {
		fprintf(fp, "%d %s %.1lf\n", stus[i].id, stus[i].name, stus[i].score);
	}
	fclose(fp);
    /* TODO 2：关闭后重新打开读回 */
	FILE *in = fopen(path, "r");
    /* TODO 3：边读边累加，统计人数，输出 */
	int countNum = 0;
	double sum = 0;
	double aver = 0;
	int id;
	char  name[20];
    double score;
	while (fscanf(in, "%d%19s%lf", &id, name, &score) == 3) {
		++countNum;
		sum += score;
	}
	aver = sum / countNum;
	printf("预期输出：\n");
	printf("共 %d 人，总分 %.2lf，平均 %.2lf\n", countNum, sum, aver);
	fclose(in);
    return 0;
}
