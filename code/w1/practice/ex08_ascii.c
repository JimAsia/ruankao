/* ex08 —— 字符与 ASCII 码
 * 要求：读入一个大写字母，输出：
 *   它的 ASCII 码
 *   它对应的小写字母
 *
 * 提示：
 *   char 用 %c 输出是字符，用 %d 输出就是它的 ASCII 码。
 *   大写和小写的 ASCII 码差固定 32，即 'a' - 'A' == 32。
 *
 * 测试：输入 A
 *   期望输出：
 *     A 的 ASCII 码是 65
 *     对应小写字母是 a
 */
#include <stdio.h>

int main(void)
{
    char upper = 0;

    /* TODO */
	scanf("%c", &upper);
	printf("期望输出：\n");
	printf("%c 的 ASCII 码是 %d\n 对应小写字母是 %c", upper, upper, upper+32);
    return 0;
}
