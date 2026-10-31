/* ex51 参考答案 —— 二维数组的行和与列和 */
#include <stdio.h>

int main(void)
{
    int a[10][10];
    int r = 0, c = 0;

    printf("请输入行数和列数: ");
    if (scanf("%d %d", &r, &c) != 2 || r <= 0 || c <= 0 || r > 10 || c > 10) {
        printf("行列数必须在 1~10 之间\n");
        return 1;
    }

    printf("请输入 %d×%d 个整数:\n", r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (scanf("%d", &a[i][j]) != 1) return 1;
        }
    }

    /* 行和：外层是行，内层是列 —— 正好按行顺序累加 */
    for (int i = 0; i < r; i++) {
        int sum = 0;
        for (int j = 0; j < c; j++) sum += a[i][j];
        printf("第 %d 行之和 = %d\n", i + 1, sum);
    }

    /* 列和：外层换成列，内层是行 —— ⚠️ 顺序必须反过来 */
    for (int j = 0; j < c; j++) {
        int sum = 0;
        for (int i = 0; i < r; i++) sum += a[i][j];
        printf("第 %d 列之和 = %d\n", j + 1, sum);
    }

    /* 为什么列和要反过来：
     * 内存里是按行存的，a[0][0], a[0][1], a[0][2], a[1][0]...
     * 外层用列的话，访问顺序是 a[0][j], a[1][j], a[2][j]，跨度大
     * 虽然结果一样，但缓存不友好 —— 这一点在 S2 讲性能时会提到 */

    return 0;
}
