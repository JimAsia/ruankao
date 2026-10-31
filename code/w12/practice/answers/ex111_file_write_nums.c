/* ex111_file_write_nums.c —— 参考答案 */

#include <stdio.h>

int main(void)
{
    int n;
    const char *path = "out111.txt";

    printf("请输入 n：");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n 必须是正整数\n");
        return 1;
    }

    /* ---------- 写 ---------- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("fopen w");
        return 1;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        fprintf(fp, "%d %d\n", i, i * i);
        cnt++;
    }
    fclose(fp);                     /* 必须关，否则可能没落盘 */

    printf("已写入 %d 行\n", cnt);

    /* ---------- 读回来验证 ---------- */
    fp = fopen(path, "r");
    if (fp == NULL) {
        perror("fopen r");
        return 1;
    }

    int a, b;
    while (fscanf(fp, "%d %d", &a, &b) == 2) {
        printf("%d %d\n", a, b);
    }
    fclose(fp);

    return 0;
}
