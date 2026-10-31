/* ex52 参考答案 —— 矩阵转置 */
#include <stdio.h>

int main(void)
{
    int a[10][10], t[10][10];
    int r = 0, c = 0;

    printf("请输入行数和列数: ");
    if (scanf("%d %d", &r, &c) != 2 || r <= 0 || c <= 0 || r > 10 || c > 10) return 1;

    printf("请输入 %d×%d 个整数:\n", r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (scanf("%d", &a[i][j]) != 1) return 1;
        }
    }

    /* 转置：行列下标对调
     * 原矩阵是 r 行 c 列，转置后是 c 行 r 列 */
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            t[j][i] = a[i][j];
        }
    }

    /* 输出转置结果 */
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            printf("%d ", t[i][j]);
        }
        printf("\n");
    }

    /* 补充：如果是方阵（r == c），可以不开新数组，原地转置：
     *   for (int i = 0; i < n; i++)
     *       for (int j = i + 1; j < n; j++)     ← ⚠️ 从 i+1 开始
     *           交换 a[i][j] 和 a[j][i]
     * 内层从 i+1 开始很关键，从 0 开始的话每个位置会被换两次，等于没转。 */

    return 0;
}
