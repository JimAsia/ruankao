/* ex51 —— 二维数组的行和与列和
 * 要求：读入行数 r、列数 c（都不超过 10），再读入 r×c 个整数，输出：
 *   逐行输出每行的和
 *   逐列输出每列的和
 *
 * 测试：输入 2 3
 *            1 2 3
 *            4 5 6
 *   输出：第 1 行之和 = 6
 *         第 2 行之和 = 15
 *         第 1 列之和 = 5
 *         第 2 列之和 = 7
 *         第 3 列之和 = 9
 *
 * 提示：求列和时，外层循环必须是列（j），内层是行（i）。
 */
#include <stdio.h>

int main(void)
{
    int a[10][10];
    int r = 0, c = 0;

    /* TODO: 读入 r 和 c */
	printf("输入 ");
	scanf("%d%d", &r, &c);
	
	
    /* TODO: 双层循环读入矩阵 */
	printf("输入\n");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
    /* TODO: 输出每行的和 */
	
	for (int i = 0; i < r; ++i) {
		int sum = 0;
		for (int j = 0; j < c; ++j) {
			sum += a[i][j];
		}
		printf("第 %d 行之和 = %d\n", i + 1, sum);
	}

    /* TODO: 输出每列的和 */

	for (int j = 0; j < c; ++j) {
		int sum = 0;
		for (int i = 0; i < r; ++i) {
			sum += a[i][j];
		}
		printf("第 %d 列之和 = %d\n", j + 1, sum);
	}
    return 0;
}
