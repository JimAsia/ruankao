/* ex102_struct_stat.c —— 结构体数组：统计成绩
 *
 * 要求：
 *   1. 定义一个能存学号、姓名、成绩的结构体
 *   2. 读入 n 个学生（n 由输入给出，n <= 100）
 *   3. 输出：平均分（2 位小数）、最高分学生的姓名
 *
 * 输入示例：
 *   4
 *   1 张三 85.5
 *   2 李四 92.0
 *   3 王五 78.5
 *   4 赵六 92.0
 * 输出示例：
 *   平均分 = 87.00
 *   最高分 = 李四
 *
 * 注意：最高分并列时输出先出现的那个（用 > 而不是 >=）
 */

#include <stdio.h>

#define MAXN 100

/* TODO 1：定义结构体类型 */
struct Student {
	int num;
	char name[MAXN];
	double score;	
};

int main(void)
{
    int n;
    /* TODO 2：声明结构体数组 */
	printf("输入示例：\n");
	scanf("%d", &n);
	struct Student stus[n];
    /* TODO 3：读入 n 和 n 个学生 */
	for (int i = 0; i < n; ++i) {
		scanf("%d", &stus[i].num);
		scanf("%99s", stus[i].name);
		scanf("%lf", &stus[i].score);
	}
	
    /* TODO 4：求平均分（注意用 double 累加） */
	double sum = 0;
	int index = 0;
	double max = 0;
	for (int i = 0; i < n; ++i) {
		sum += stus[i].score;
		if (max < stus[i].score) {
			max = stus[i].score;
			index = i;
		}
	}
	double aver = sum / n;
	printf("输出示例：\n");
	printf("平均分 = %.2lf\n", aver);
	
    /* TODO 5：找最高分下标，输出姓名 */
	printf("最高分 = %s\n", stus[index].name);
    return 0;
}
