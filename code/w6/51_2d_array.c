/* 51_2d_array.c —— 二维数组
 *
 * 二维数组在内存里仍然是一条直线，只是我们按"行"去理解它。
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① 定义与初始化 ---------- */
    int m[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    printf("=== ① 3 行 4 列的矩阵 ===\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d", m[i][j]);
        }
        printf("\n");
    }

    /* ---------- ② 按行存储：内存是连续的 ---------- */
    printf("\n=== ② 内存是按行连续排列的 ===\n");
    printf("  把二维数组当一维看，顺序是：\n  ");
    int *p = &m[0][0];                  /* 指向第一个元素 */
    for (int k = 0; k < 12; k++) {
        printf("%d ", p[k]);            /* p[k] 等价于 *(p + k) */
    }
    printf("\n");
    printf("  所以 m[i][j] 的地址 = 首地址 + (i × 列数 + j) × sizeof(int)\n");

    /* 验证这个公式 */
    printf("\n  验证 m[1][2] 的地址：\n");
    printf("    &m[1][2]          = %p\n", (void *)&m[1][2]);
    printf("    &m[0][0] + 1*4+2  = %p\n", (void *)(&m[0][0] + 1 * 4 + 2));
    printf("    两者相同，公式成立\n");

    /* ---------- ③ 行数与列数 ---------- */
    printf("\n=== ③ 求行数和列数 ===\n");
    printf("  sizeof(m)       = %zu 字节（整个数组）\n", sizeof(m));
    printf("  sizeof(m[0])    = %zu 字节（一整行）\n", sizeof(m[0]));
    printf("  sizeof(m[0][0]) = %zu 字节（一个元素）\n", sizeof(m[0][0]));
    printf("  行数 = sizeof(m) / sizeof(m[0])          = %zu\n", sizeof(m) / sizeof(m[0]));
    printf("  列数 = sizeof(m[0]) / sizeof(m[0][0])    = %zu\n", sizeof(m[0]) / sizeof(m[0][0]));

    /* ---------- ④ 各行的和 ---------- */
    printf("\n=== ④ 每行的和 ===\n");
    for (int i = 0; i < 3; i++) {
        int rowSum = 0;
        for (int j = 0; j < 4; j++) {
            rowSum += m[i][j];
        }
        printf("  第 %d 行之和 = %d\n", i + 1, rowSum);
    }

    /* ---------- ⑤ 各列的和：注意循环顺序反过来 ---------- */
    printf("\n=== ⑤ 每列的和 ===\n");
    for (int j = 0; j < 4; j++) {           /* 外层是列 */
        int colSum = 0;
        for (int i = 0; i < 3; i++) {       /* 内层是行 */
            colSum += m[i][j];
        }
        printf("  第 %d 列之和 = %d\n", j + 1, colSum);
    }
    printf("  求列和时，外层必须是列：这样才能按列顺序累加\n");

    /* ---------- ⑥ 部分初始化 ---------- */
    printf("\n=== ⑥ 部分初始化 ===\n");
    int n[3][3] = {{1}, {2, 3}};
    printf("  int n[3][3] = {{1}, {2,3}};\n");
    for (int i = 0; i < 3; i++) {
        printf("  ");
        for (int j = 0; j < 3; j++) printf("%d ", n[i][j]);
        printf("\n");
    }
    printf("  没写到的位置全部补 0\n");

    return 0;
}
