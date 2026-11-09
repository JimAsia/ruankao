/* ex64 —— 用函数处理数组：求和与平均
 * 要求：写两个函数：
 *   int    sumArray(int a[], int n)      返回总和
 *   double avgArray(int a[], int n)      返回平均值
 * 在 main 里读入 n 个数，调用这两个函数输出结果。
 *
 * 测试：输入 5 / 3 7 1 9 4
 *   输出：总和 = 24，平均 = 4.80
 *
 * 提示：数组作参数必须同时传长度 n（W7 学过）。
 *       avgArray 里调用 sumArray 可以复用代码。
 */
#include <stdio.h>

int sumArray(int a[], int n)
{
    /* TODO */
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += a[i];
	}
    return sum;
}

double avgArray(int a[], int n)
{
    /* TODO: 调用 sumArray */
	
    return (double)sumArray(a, n) / n;
}

int main(void)
{
    int a[20], n = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d", &n);
	if (n == 0) {
		printf("No number.");
		return 1;
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	printf("输出：总和 = %d，平均 = %.2f", sumArray(a, n), avgArray(a, n));
    return 0;
}
