/* ex34 —— 数字拆位综合
 * 要求：读入一个正整数 n，输出三行：
 *   它的位数
 *   各位数字之和
 *   它反转后的数
 *
 * 测试：输入 3725
 *   输出：位数 = 4
 *         各位和 = 17
 *         反转 = 5273
 *
 * 提示：
 *   位数可以在拆位循环里顺便数（每除一次 10 就加 1）
 *   反转用 rev = rev * 10 + n % 10
 *   注意循环会破坏 n 本身，需要先复制一份到 tmp
 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d", &n);
	// 
	int count = 0;
	int rev = 0;
	int sum = 0;
	while (n > 0) {
		rev = rev * 10 + n % 10;
		sum = sum + n % 10;
		n /= 10;
		++count;
	}
	printf("位数 = %d\n", count);
	printf("各位和 = %d\n", sum);
	printf("反转 = %d\n", rev);
    return 0;
}
