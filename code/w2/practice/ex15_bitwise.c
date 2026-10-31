/* ex15 —— 位运算实战
 * 要求：读入两个非负整数 a、b，输出：
 *   a & b、a | b、a ^ b 的十进制结果
 *   a 的最低位（用 a & 1），并说明它是奇数还是偶数
 *   a 左移 1 位、右移 1 位的结果
 *
 * 测试数据：输入 12 10
 *   期望输出：
 *     a = 12, b = 10
 *     a & b = 8
 *     a | b = 14
 *     a ^ b = 6
 *     a 的最低位 = 0，所以 a 是偶数
 *     a << 1 = 24
 *     a >> 1 = 6
 *
 * 提示：判断奇偶不用 if，直接把 (a & 1) 的值输出，
 *       然后在注释里写一句「0 是偶数，1 是奇数」即可。
 */
#include <stdio.h>

int main(void)
{
    unsigned int a = 0, b = 0;

    /* TODO: 读入 a 和 b（用 %u） */
	scanf("%u%u", &a, &b);
    /* TODO: 输出按位与、或、异或 */
	printf("%d\n%d\n%d\n", a & b, a | b, a ^ b);
    /* TODO: 输出最低位与奇偶结论 */
	printf("%d\n", a & 1);
    /* TODO: 输出左移、右移结果 */
	printf("%d\n%d\n", a << 1, a >> 1);
    return 0;
}
