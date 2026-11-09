/* ex55 —— 回文字符串判断
 * 要求：读入一个字符串，判断它是不是回文（正着读和倒着读一样）。
 *       输出「是回文」或「不是回文」。
 *
 * 测试：level  → 是回文
 *       hello  → 不是回文
 *       abcba  → 是回文
 *       a      → 是回文（单个字符）
 *       ab     → 不是回文
 *
 * 提示：首尾同时向中间走，一发现不同就判定不是，可以直接 break。
 *       别忘了考虑空串和单字符的情况。
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
	//
	int right = 0;
	while (s[right] != '\0') ++right;
	--right;
	if (right == 0) {
		printf("%s是回文（单个字符）\n", s);
		return 0;
	}
	//
	int left = 0;
	bool found = 1;
	while (left < right) {
		if (s[left] == s[right]) {
			++left;
			--right;
		}
		else {
			found = 0;
			break;
		}
	}
	if (found) {
		printf("%s是回文\n", s);
	}
	else {
		printf("%s不是回文\n", s);
	}
	
    return 0;
}
