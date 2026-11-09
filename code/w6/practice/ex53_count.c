/* ex53 —— 统计字符串里的字符类型
 * 要求：读入一个不含空格的字符串，统计并输出：
 *   大写字母、小写字母、数字、其他字符 各多少个
 *
 * 测试：输入 Abc123!@#
 *   输出：大写 = 1，小写 = 2，数字 = 3，其他 = 3
 *
 * 提示：
 *   遍历用 while (s[i] != '\0') 或 for (; s[i]; i++)
 *   字符比较直接用 ASCII 区间：c >= 'A' && c <= 'Z'
 *   不需要 #include <string.h>（不用 strlen 也能遍历）
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
	int countBig = 0;
	int countSmall = 0;
	int countNum = 0;
	int countOther = 0;
	for (int i = 0; s[i] != '\0'; ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			++countBig;
		}
		else if (s[i] >= 'a' && s[i] <= 'z') {
			++countSmall;
		}
		else if (s[i] >= '0' && s[i] <= '9') {
			++countNum;
		}
		else {
			++countOther;
		}
	}
	printf("大写 = %d\n", countBig);
	printf("小写 = %d\n", countSmall);
	printf("数字 = %d\n", countNum);
	printf("其他 = %d\n", countOther);
    return 0;
}
