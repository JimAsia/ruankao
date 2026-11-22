/* ex123_bit_tricks.c —— 三个位运算小技巧
 *
 * 要求：
 *   1. isOdd(x)：不用 % 判断奇偶（只能在二进制上看最低位）
 *   2. swapXor(a, b)：用异或交换两个数（不用临时变量）
 *   3. absBit(x)：用位运算求 int 的绝对值（不用 if、不用 abs）
 *
 * 提示：
 *   奇偶：(x & 1) != 0 就是奇数
 *   交换：a^=b; b^=a; a^=b;
 *   绝对值：int mask = x >> 31;  (x + mask) ^ mask
 *           负数右移 31 位得 -1（全 1），正数得 0
 *
 * 输出示例：
 *   7 是奇数
 *   -4 是偶数
 *   交换前 a=5 b=9 → 交换后 a=9 b=5
 *   |7| = 7    |-7| = 7
 */

#include <stdio.h>

/* TODO 1：isOdd */
unsigned int isOdd(int x) {
	return x & 1;
}
/* TODO 2：swapXor（用指针，因为要改外面的变量） */
void swapXor(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
/* TODO 3：absBit */
unsigned int absBit(int x) {
	int mask = x >> 31;
	return (x + mask) ^ mask;
}

int main(void)
{
    /* TODO 4：测试三个函数 */
	int x1 = 7, x2 = -4;
	int a = 5, b = 9;
	int x3 = -7;
	if (isOdd(x1)) {
		printf("%d 是奇数\n", x1);
	}
	else {
		printf("%d 是偶数\n", x1);
	}
	
	if (isOdd(x2)) {
		printf("%d 是奇数\n", x2);
	}
	else {
		printf("%d 是偶数\n", x2);
	}
	printf("交换前 a=%d b=%d → ", a, b);
	swapXor(&a, &b);
	printf("交换后 a=%d b=%d\n", a, b);
	
	printf("|%d| = %d,   |%d| = %d\n", x1, absBit(x1), x3, absBit(x3));
    /* 注意：负数取余 -7 % 2 == -1，所以不能用 % 判奇偶 */

    return 0;
}
