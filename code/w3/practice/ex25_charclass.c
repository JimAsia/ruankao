/* ex25 —— 字符类型判断
 * 要求：读入一个字符，输出它属于哪一类：
 *   大写字母 / 小写字母 / 数字 / 空格 / 其他字符
 *
 * 测试：A → 大写字母 ｜ z → 小写字母 ｜ 7 → 数字 ｜ 空格 → 空格 ｜ @ → 其他字符
 *
 * 提示：字符可以直接和 'A'、'Z' 比较，因为比较的是 ASCII 码。
 *       if (ch >= 'A' && ch <= 'Z')
 *       注意 scanf 读字符时前面要加空格：scanf(" %c", &ch)
 */
#include <stdio.h>

int main(void)
{
    char ch = 0;

    /* TODO */
	scanf("%c", &ch);
	if ((ch >= 'A') &&  (ch <= 'Z')) {
		printf("大写字母\n");
	}
	else if ((ch >= 'a') &&  (ch <= 'z')) {
		printf("小写字母\n");
	}
	else if ((ch >= '0') &&  (ch <= '9')) {
		printf("数字\n");
	}
	else if (ch == ' ') {
		printf("空格\n");
	}
	else {
		printf("其他字符\n");
	}
    return 0;
}
