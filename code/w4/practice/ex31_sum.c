/* ex31 —— 求和
 * 要求：读入一个正整数 n，输出两行：
 *   1 + 2 + ... + n 的和
 *   1 ~ n 之间所有偶数的和
 *
 * 测试：输入 10   输出：1~10 的和 = 55
 *                      1~10 的偶数和 = 30
 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    /* TODO: 读入 n */
	scanf("%d", &n);
    /* TODO: 累加求和 */
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += i;
	}
	printf("i~%d 的和 = %d\n", n, sum);
    /* TODO: 累加偶数和 */
	sum = 0;
	for (int i = 0; i <= n; i+=2) {
		sum += i;
	}
	printf("i~%d 的偶数和 = %d\n", n, sum);
    return 0;
}
