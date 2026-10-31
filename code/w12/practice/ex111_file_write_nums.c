/* ex111_file_write_nums.c —— 写文件：1 到 n 的平方表
 *
 * 要求：
 *   1. 读入一个整数 n
 *   2. 把 1 到 n 每个数的「数值 平方」写入文件 out111.txt，每行一条
 *   3. 写完关闭文件，再从文件读回来打印，证明写成功
 *
 * 输入示例：
 *   5
 * 输出示例（屏幕）：
 *   已写入 5 行
 *   1 1
 *   2 4
 *   3 9
 *   4 16
 *   5 25
 *
 * 要点：
 *   - fopen 用 "w" 模式，返回值必须判 NULL
 *   - 写用 fprintf，记得传 fp
 *   - 写完必须 fclose，否则数据可能没落盘
 */

#include <stdio.h>

int main(void)
{
    int n;
    const char *path = "out111.txt";

    /* TODO 1：读入 n，判断 n > 0 */

    /* TODO 2：fopen 打开文件，判 NULL */

    /* TODO 3：循环 fprintf 写入，同时统计行数 */

    /* TODO 4：fclose */

    /* TODO 5：重新 fopen 用 "r" 打开，读回来打印 */

    return 0;
}
