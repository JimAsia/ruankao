/* 56_matrix.c —— 矩阵的常见操作
 */
#include <stdio.h>

int main(void)
{
    int m[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    printf("=== 原矩阵 3×4 ===\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) printf("%4d", m[i][j]);
        printf("\n");
    }

    /* ---------- ① 转置：行变列 ---------- */
    printf("\n=== ① 转置成 4×3 ===\n");
    int t[4][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            t[j][i] = m[i][j];          /* 行列下标对调 */
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) printf("%4d", t[i][j]);
        printf("\n");
    }
    printf("  关键：t[j][i] = m[i][j]，下标对调即可\n");

    /* ---------- ② 方阵原地转置（不额外开数组） ---------- */
    printf("\n=== ② 方阵原地转置 ===\n");
    int s[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printf("  转置前：\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) printf("%4d", s[i][j]);
        printf("\n");
    }

    /* ⚠️ 内层从 i+1 开始，只处理右上半部分 */
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int tmp = s[i][j];
            s[i][j] = s[j][i];
            s[j][i] = tmp;
        }
    }
    printf("  转置后：\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) printf("%4d", s[i][j]);
        printf("\n");
    }
    printf("  ⚠️ 内层必须从 j = i+1 开始，否则每个位置被交换两次，等于没转\n");

    /* ---------- ③ 主对角线元素 ---------- */
    printf("\n=== ③ 主对角线与副对角线 ===\n");
    int d[4][4] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    printf("  主对角线（i == j）：");
    int mainDiag = 0;
    for (int i = 0; i < 4; i++) {
        printf("%d ", d[i][i]);
        mainDiag += d[i][i];
    }
    printf("  和 = %d\n", mainDiag);

    printf("  副对角线（i + j == n-1）：");
    int antiDiag = 0;
    for (int i = 0; i < 4; i++) {
        printf("%d ", d[i][4 - 1 - i]);
        antiDiag += d[i][4 - 1 - i];
    }
    printf("  和 = %d\n", antiDiag);
    printf("  两个公式记住：主对角线 i == j，副对角线 i + j == n - 1\n");

    /* ---------- ④ 上三角与下三角 ---------- */
    printf("\n=== ④ 上下三角 ===\n");
    int upperSum = 0, lowerSum = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i < j)       upperSum += d[i][j];   /* 上三角：行号 < 列号 */
            else if (i > j)  lowerSum += d[i][j];   /* 下三角：行号 > 列号 */
        }
    }
    printf("  上三角元素之和（不含对角线）= %d\n", upperSum);
    printf("  下三角元素之和（不含对角线）= %d\n", lowerSum);
    printf("  判断条件：i < j 在上三角，i > j 在下三角，i == j 在对角线\n");

    /* ---------- ⑤ 每行的最大值 ---------- */
    printf("\n=== ⑤ 每行最大值 ===\n");
    for (int i = 0; i < 3; i++) {
        int rowMax = m[i][0];
        for (int j = 1; j < 4; j++) {
            if (m[i][j] > rowMax) rowMax = m[i][j];
        }
        printf("  第 %d 行最大 = %d\n", i + 1, rowMax);
    }

    return 0;
}
