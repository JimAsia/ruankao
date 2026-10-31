/* ex102_struct_stat.c —— 参考答案 */

#include <stdio.h>

#define MAXN 100

struct Student {
    int    id;
    char   name[20];
    double score;
};

int main(void)
{
    int n;
    struct Student a[MAXN];

    printf("学生人数：");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAXN) {
        printf("人数不合法\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %19s %lf", &a[i].id, a[i].name, &a[i].score);
    }

    /* 平均分：必须 double 累加 */
    double sum = 0;
    for (int i = 0; i < n; i++) sum += a[i].score;

    /* 最高分：存下标，不存值 */
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].score > a[maxIdx].score) maxIdx = i;   /* > 保证并列取先出现的 */
    }

    printf("\n平均分 = %.2f\n", sum / n);
    printf("最高分 = %s（%.1f）\n", a[maxIdx].name, a[maxIdx].score);

    return 0;
}
