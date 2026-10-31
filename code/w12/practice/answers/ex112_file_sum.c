/* ex112_file_sum.c —— 参考答案 */

#include <stdio.h>

int main(void)
{
    const char *path = "nums.txt";
    int data[10] = {12, 7, 30, 5, 88, 43, 21, 9, 66, 100};

    /* ---------- 写 ---------- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) { perror("fopen w"); return 1; }

    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%d\n", data[i]);
    }
    fclose(fp);

    /* ---------- 读 + 统计 ---------- */
    fp = fopen(path, "r");
    if (fp == NULL) { perror("fopen r"); return 1; }

    int x, sum = 0, max = 0, count = 0;
    int first = 1;

    while (fscanf(fp, "%d", &x) == 1) {      /* ✅ ==1 判断读成功 */
        if (first) { max = x; first = 0; }   /* ⚠️ max 初值要用第一个数 */
        if (x > max) max = x;
        sum += x;
        count++;
    }
    fclose(fp);

    printf("共读 %d 个数\n", count);
    printf("总和 = %d\n", sum);
    printf("平均 = %.2f\n", (double)sum / count);
    printf("最大 = %d\n", max);

    printf("\n注意：max 初值写 0 时，如果数据全是负数就会错\n");
    printf("      正确做法是用读到的第一个数作为初值\n");

    return 0;
}
