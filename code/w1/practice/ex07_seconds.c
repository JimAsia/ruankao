/* ex07 —— 秒数转换
 * 要求：读入一个整数总秒数，输出"几时几分几秒"。
 *   用 / 求商，用 % 求余。
 *
 * 思路：
 *   hour = total / 3600
 *   rest = total % 3600
 *   min  = rest / 60
 *   sec  = rest % 60
 *
 * 测试：输入 3725
 *   期望输出：1 时 2 分 5 秒
 */
#include <stdio.h>

int main(void)
{
    int total = 0;

    /* TODO */
	scanf("%d", &total);
	int hour = 0;
	int minute = 0;
	int second = 0;
	hour = total / 3600;
	minute = (total - hour * 3600) / 60;
	second = (total - minute * 60 - hour * 3600) % 60;
	printf("期望输出： %d 时 %d 分 %d 秒\n", hour, minute, second);
    return 0;
}
