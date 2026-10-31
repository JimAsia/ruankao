/* ex103_struct_sort.c —— 参考答案 */

#include <stdio.h>
#include <string.h>

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

    /* 冒泡，按姓名升序 */
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(a[j].name, a[j + 1].name) > 0) {
                struct Student t = a[j];        /* 整体交换，不能逐字段 */
                a[j]     = a[j + 1];
                a[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break;                    /* 本趟无交换 → 已有序 */
    }

    printf("\n按姓名升序：\n");
    for (int i = 0; i < n; i++) {
        printf("%d %s %.1f\n", a[i].id, a[i].name, a[i].score);
    }

    return 0;
}
