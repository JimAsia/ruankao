/* ex54 —— 字符串反转（不用库函数）
 * 要求：读入一个字符串，原地反转后输出。
 *      【不许用 strrev，也不许开第二个数组】—— 用首尾交换。
 *
 * 测试：输入 hello
 *   输出：olleh
 *
 * 提示：
 *   ① 先找到末尾：int right = 0; while (s[right] != '\0') right++;
 *   ② 然后 right--，退到最后一个真实字符（不是 '\0'）
 *   ③ left = 0，while (left < right) 交换并 i++, j--
 */
#include <stdio.h>

int main(void)
{
    char s[100];

    /* TODO */
	printf("输入 ");
	if (scanf("%99s", s) != 1) {
		printf("error");
		return 1;
	}
	int right = 0;
	while (s[right] != '\0') {
		++right;
	}
	--right;
	printf("%d\n", right);
	int left = 0;
	while (left < right) {
		char t = s[left];
		s[left] = s[right];
		s[right] = t;
		++left;
		--right;
	}
	printf("输出： ");
	printf("%s\n", s);
    return 0;
}
