/* ex116_file_grep.c —— 在文件里查找关键字
 *
 * 要求：
 *   1. 程序先写一个文件 text116.txt，内容固定四行：
 *        The quick brown fox
 *        jumps over the lazy dog
 *        C programming is fun
 *        file io is easy
 *   2. 读入一个关键字，逐行查找包含它的行
 *   3. 输出行号和该行内容；统计命中行数
 *
 * 输入示例：
 *   is
 * 输出示例：
 *   第 3 行：C programming is fun
 *   第 4 行：file io is easy
 *   命中 2 行
 *
 * 要点：
 *   - 用 fgets 逐行读，用 strstr 判断是否包含子串
 *   - strstr(line, key) 返回第一次出现的位置，NULL 表示没找到
 *   - fgets 会把 '\n' 留在行末，输出时注意别多空一行
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *path = "text116.txt";

    /* TODO 1：写测试文件 */

    /* TODO 2：读入关键字（用 %19s） */

    /* TODO 3：fgets 循环，用 strstr 判断，输出行号 */

    /* TODO 4：输出命中行数 */

    return 0;
}
