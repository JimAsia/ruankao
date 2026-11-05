/* ex41 —— 数组的输入、输出、求和、平均
 * 要求：先读入元素个数 n（不超过 20），再读入 n 个整数，输出：
 *   数组内容（空格分隔）
 *   总和
 *   平均值（保留 2 位小数）
 *
 * 测试：输入 5
 *            3 7 1 9 4
 *   输出：数组：3 7 1 9 4
 *         总和 = 24
 *         平均 = 4.80
 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0;

    /* TODO: 读入 n */
	printf("输入 ");
	scanf("%d", &n);
    /* TODO: 循环读入 n 个元素 */
	printf("输入 ");
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
    /* TODO: 输出数组 */
	int sum = 0;
	double ave;
	printf("\n数组： ");
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
		sum += a[i];
	}
	printf("\n");
    /* TODO: 求和与平均 */
	printf("总和 = %d\n", sum);
	ave = (double)sum / n;
	printf("平均 = %.2f\n", ave);
    return 0;
}
