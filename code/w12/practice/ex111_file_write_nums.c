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
	printf("输入示例：\n");
	scanf("%d", &n);
	if (n <= 0) {
        printf("n 必须大于 0\n");
        return 1;
    }
    /* TODO 2：fopen 打开文件，判 NULL */
	FILE *fp = fopen(path, "w");
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}
    /* TODO 3：循环 fprintf 写入，同时统计行数 */
	int countLine = 0;
	for (int i = 1; i <= n; ++i) {
		fprintf(fp, "%d %d\n", i, i*i);
		++countLine;
	}
    /* TODO 4：fclose */
	fclose(fp);
    /* TODO 5：重新 fopen 用 "r" 打开，读回来打印 */
	FILE *fpIn = fopen(path, "r");
	if (fpIn == NULL) {
		perror("fopen");
		return 1;
	}
	char lines[128];
	// int a, b;
	printf("输出示例（屏幕）\n");
	printf("已写入 %d 行\n", countLine);
	while (fgets(lines, sizeof(lines), fpIn) != NULL) {
		/* sscanf 常用于：先读一整行，再从这一行里解析数据 
		sscanf 就是“从字符串里按格式读取数据”的函数。
		
		if (sscanf(lines, "%d %d", &a, &b) == 2) {
			printf("%d %d\n", a, b);
		}
		*/
		
		printf("%s", lines);
	}
	fclose(fpIn);
    return 0;
}
