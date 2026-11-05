/* ex46 —— 冒泡排序
 * 要求：读入 n 个整数，用冒泡排序从小到大排序后输出。
 *
 * 测试：输入 6
 *            72 45 91 38 66 88
 *   输出：排序后：38 45 66 72 88 91
 *
 * 提示：
 *   外层 for (i = 0; i < n - 1; i++)
 *   内层 for (j = 0; j < n - 1 - i; j++)
 *   内层判断 a[j] > a[j+1] 就交换
 *
 * 写完可以试着加"提前结束"优化：某轮没有交换就直接 break。
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
	for (int i = 0; i < n - 1; ++i) {
		int swapped = 0;
		for (int j = 0; j < n - i - 1; ++j) {
			if (a[j] > a[j + 1]) {
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
			swapped = 1;
		}
		if (!swapped) break;
	}
	printf("输出：排序后： ");
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
    return 0;
}
