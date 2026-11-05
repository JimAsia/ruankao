/* ex42 —— 最大值、最小值及其下标
 * 要求：读入 n 个整数，输出最大值和它所在的下标、最小值和它所在的下标。
 *
 * 测试：输入 6
 *            72 45 91 38 66 88
 *   输出：最大值 = 91，下标 = 2
 *         最小值 = 38，下标 = 3
 *
 * 提示：max 用 a[0] 初始化，循环从 i = 1 开始（a[0] 已经当过擂主）。
 *       如果全负数还用 max = 0 初始化，结果就错了。
 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d", &n);
    /* TODO: 循环读入 n 个元素 */
	printf("输入 ");
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	//
	int max = a[0];
	int min = a[0];
	int index_max = -1;
	int index_min = -1;
	for (int i = 1; i < n; ++i) {
		if (max < a[i]) {
			max = a[i];
			index_max = i;
		}
		if (min > a[i]) {
			min = a[i];
			index_min = i;
		}
	}
	printf("\n");	
	printf("最大值 = %d，下标 = %d\n", max, index_max);
	printf("最大值 = %d，下标 = %d\n", min, index_min);
    return 0;
}
