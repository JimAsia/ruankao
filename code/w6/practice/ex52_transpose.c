/* ex52 —— 矩阵转置
 * 要求：读入 r 行 c 列的矩阵，输出它的转置（c 行 r 列）。
 *
 * 测试：输入 2 3
 *            1 2 3
 *            4 5 6
 *   输出：1 4
 *         2 5
 *         3 6
 *
 * 提示：用另一个数组 t[c][r]，t[j][i] = a[i][j]。
 */
#include <stdio.h>

int main(void)
{
    int a[10][10], t[10][10];
    int r = 0, c = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d%d", &r, &c);
	//
	printf("输入\n");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	//
	
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			t[j][i] = a[i][j];
		}
	}
	printf("输出： \n");
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < r; ++j) {
			printf("%d ", t[i][j]);
		}
		printf("\n");
	}
    return 0;
}