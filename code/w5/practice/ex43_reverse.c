/* ex43 —— 数组逆序
 * 要求：读入 n 个整数，原地逆序（不许开第二个数组），输出结果。
 *
 * 测试：输入 6
 *            1 2 3 4 5 6
 *   输出：逆序后：6 5 4 3 2 1
 *
 * 提示：首尾交换，i 从头走、j 从尾走，条件是 i < j。
 *       写成 i < n 的话会交换两次，等于没换。
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
	for (int i = 0, j = n-1; i < j; ++i, --j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	printf("逆序后： ");
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
    return 0;
}
