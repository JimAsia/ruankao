/* ex21 —— 判断奇偶与正负
 * 要求：读入一个整数 n，输出两行：
 *   第一行：n 是奇数 / 偶数
 *   第二行：n 是正数 / 负数 / 零
 *
 * 测试：输入 7      输出：7 是奇数    / 7 是正数
 *       输入 -4     输出：-4 是偶数   / -4 是负数
 *       输入 0      输出：0 是偶数    / 0 是零
 *
 * 提示：判断奇偶可以用 n % 2，也可以用 n & 1（W2 学过）
 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    /* TODO: 读入 n */
	printf("输入 ");
	scanf("%d", &n);
    /* TODO: 两段 if-else */
	if ((n & 1) == 0) {
		printf("%d 是偶数", n);
	}
	else {
		printf("%d 是奇数", n);
	}
	if (n > 0) {
		printf("/ %d 是正数", n);
	}
	else if (n == 0){
		printf("/ %d 是零", n);
	}
	else {
		printf("/ %d 是负数", n);
	}
    return 0;
}
