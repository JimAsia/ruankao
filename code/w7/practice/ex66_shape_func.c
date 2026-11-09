/* ex66 —— 用函数打印图形
 * 要求：写两个函数：
 *   void printTriangle(int n)    打印 n 行左对齐直角三角形
 *   void printDiamond(int n)     打印菱形（上半 n 行 + 下半 n-1 行）
 * 在 main 里读入 n 后分别调用。
 *
 * 测试：输入 4
 *   printTriangle(4) 输出：
 *   *
 *   **
 *   ***
 *   ****
 *
 *   printDiamond(4) 输出：
 *      *
 *     ***
 *    *****
 *   *******
 *    *****
 *     ***
 *      *
 *
 * 提示：菱形 = 等腰三角形（上半） + 倒过来的等腰三角形（下半，少一行）
 *       等腰三角第 i 行：先打 n-i 个空格，再打 2i-1 个星
 */
#include <stdio.h>

void printTriangle(int n)
{
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			printf("*");
		}
		printf("\n");
	}
	/* TODO */
}

void printDiamond(int n)
{
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; ++j) {
			printf("*");
		}
		printf("\n");
	}
	for (int i = n - 1; i > 0; --i) {
		for (int j = 0; j < n - i; ++j) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i - 1; ++j) {
			printf("*");
		}
		printf("\n");
	}
	/* TODO */
}

int main(void)
{
    int n = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d", &n);
	printTriangle(n);
	printf("\n");
	printDiamond(n);
    return 0;
}
