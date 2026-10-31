/* ex06 —— 三门课成绩统计
 * 要求：读入三门课成绩（整数），输出总分和平均分。
 *   总分按整数输出，平均分保留 2 位小数。
 *
 * 坑：avg 如果是 int，sum / 3 会截断成整数。
 *     必须让其中一个变成 double，比如 (double)sum / 3。
 *
 * 测试：输入 85 90 78
 *   期望输出：总分 = 253，平均分 = 84.33
 */
#include <stdio.h>

int main(void)
{
    int s1 = 0, s2 = 0, s3 = 0;

    /* TODO */
    scanf("%d%d%d", &s1, &s2, &s3);
    printf("%.2f", (s1+s2+s3) / 3.0);
    return 0;
}
