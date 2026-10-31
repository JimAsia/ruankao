/* ex56 —— 大小写互换
 * 要求：读入一个字符串，把里面的大写变小写、小写变大写，其他字符不变，输出结果。
 *
 * 测试：输入 Hello World 2026
 *   输出：hELLO wORLD 2026
 *
 * 注意：这题要读入【带空格】的整行，scanf("%s") 遇到空格就停了。
 *       用 fgets(s, sizeof(s), stdin) 读整行。
 *       注意 fgets 会把末尾的换行符 '\n' 也读进来，需要处理掉。
 *
 * 提示：
 *   大写→小写：c + 32
 *   小写→大写：c - 32
 *   或者直接用库函数 toupper / tolower（需要 #include <ctype.h>）
 */
#include <stdio.h>

int main(void)
{
    char s[200];

    /* TODO */

    return 0;
}
