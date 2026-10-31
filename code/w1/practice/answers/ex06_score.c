/* ex06 参考答案 —— 三门课成绩统计 */
#include <stdio.h>

int main(void)
{
    int s1 = 0, s2 = 0, s3 = 0, sum = 0;

    printf("请输入三门成绩(空格分隔): ");
    if (scanf("%d %d %d", &s1, &s2, &s3) != 3) {
        printf("输入格式不对\n");
        return 1;
    }

    sum = s1 + s2 + s3;

    /* 关键：(double)sum / 3
     * 如果写 sum / 3，两个 int 相除，结果先截断成整数，再赋给 double 已经晚了 */
    printf("总分 = %d，平均分 = %.2f\n", sum, (double)sum / 3);

    return 0;
}
