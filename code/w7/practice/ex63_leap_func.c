/* ex63 —— 用函数判断闰年
 * 要求：写 int isLeap(int y)，是闰年返回 1，否则返回 0。
 *       在 main 里输出 2000~2010 年间所有闰年。
 *
 * 测试：输出 2000 2004 2008
 */
#include <stdio.h>

int isLeap(int y)
{
    /* TODO */
	if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {
		return 1;
	}
    return 0;
}

int main(void)
{
    /* TODO */
	printf("输出 ");
	for (int i = 2000; i <= 2010; ++i) {
		if (isLeap(i)) {
			printf("%d ", i);
		}
	}
    return 0;
}
