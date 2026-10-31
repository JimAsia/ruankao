/* ex104_struct_ptr.c —— 传指针修改结构体：批量加分
 *
 * 要求：
 *   1. 定义结构体 Student（学号、姓名、成绩）
 *   2. 写一个函数 void addBonus(struct Student *p, double bonus)
 *      给一个学生的成绩加分，加分后不超过 100
 *   3. 主函数读入 n 个学生，对每人加 bonus 分，输出结果
 *
 * 输入示例：
 *   3 5
 *   1 张三 85
 *   2 李四 98
 *   3 王五 60
 * 输出示例：
 *   1 张三 90.0
 *   2 李四 100.0
 *   3 王五 65.0
 *
 * 关键：函数必须能改到外面的结构体 → 必须传地址 &
 *       函数内用 p->score 访问成员
 */

#include <stdio.h>

#define MAXN 100

/* TODO 1：定义结构体 */

/* TODO 2：写 addBonus 函数，注意上限 100 */

int main(void)
{
    int n;
    double bonus;
    /* TODO 3：读入 n 和 bonus，再读 n 个学生 */

    /* TODO 4：对每个学生调用 addBonus(&arr[i], bonus) */

    /* TODO 5：输出，成绩保留 1 位小数 */

    return 0;
}
