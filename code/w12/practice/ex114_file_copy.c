/* ex114_file_copy.c —— 复制文件
 *
 * 要求：
 *   1. 让程序先写一个源文件 src114.txt，内容随便几行
 *   2. 把它复制成 dst114.txt（逐字符 fgetc/fputc）
 *   3. 输出：复制了多少字节；源文件与目标文件的内容是否一致
 *
 * 预期输出（示例）：
 *   复制完成，共 53 字节
 *   两个文件内容一致
 *
 * 要点：
 *   - 同时打开两个文件，用完都要 fclose
 *   - 如果第二个 fopen 失败，第一个也要关掉，否则句柄泄漏
 *   - 逐字符读要用 int ch，不能用 char ch（char 可能装不下 EOF）
 */

#include <stdio.h>

int main(void)
{
    const char *src = "src114.txt";
    const char *dst = "dst114.txt";

    /* TODO 1：写源文件 */

    /* TODO 2：打开 src 读、dst 写，各自判 NULL */

    /* TODO 3：fgetc → fputc 循环，统计字节数 */

    /* TODO 4：关闭两个文件，输出字节数 */

    /* TODO 5：轮流读两个文件比较内容，输出是否一致 */

    return 0;
}
