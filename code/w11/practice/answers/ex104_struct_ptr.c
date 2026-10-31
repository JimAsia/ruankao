/* ex104_struct_ptr.c —— 参考答案 */

#include <stdio.h>

#define MAXN 100

struct Student {
    int    id;
    char   name[20];
    double score;
};

/* 传指针：能改到调用者的结构体 */
void addBonus(struct Student *p, double bonus)
{
    p->score += bonus;
    if (p->score > 100.0) {
        p->score = 100.0;                   /* 封顶，防止加到 105 */
    }
}

int main(void)
{
    int n;
    double bonus;
    struct Student a[MAXN];

    printf("人数 和 加分：");
    if (scanf("%d %lf", &n, &bonus) != 2 || n <= 0 || n > MAXN) {
        printf("输入不合法\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %19s %lf", &a[i].id, a[i].name, &a[i].score);
    }

    for (int i = 0; i < n; i++) {
        addBonus(&a[i], bonus);             /* 传地址 */
    }

    printf("\n加分后：\n");
    for (int i = 0; i < n; i++) {
        printf("%d %s %.1f\n", a[i].id, a[i].name, a[i].score);
    }

    printf("\n对比：如果 addBonus 的形参写成 struct Student p（不传指针），\n");
    printf("     分数一分都不会变 —— 改的是函数内的副本。\n");

    return 0;
}
