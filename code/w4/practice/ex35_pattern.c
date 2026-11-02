/* ex35 —— 打印图案
 * 要求：读入一个正整数 n，打印一个 n 行的直角三角形（左对齐）：
 *
 *   输入 4，输出：
 *   *
 *   **
 *   ***
 *   ****
 *
 * 进阶（做出来再试）：再打印一个倒三角形和一个菱形。
 *
 * 提示：外层控制行数，内层控制每行打几个星号。
 *       每行打完记得 printf("\n")
 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    /* TODO */
	// 直角三角形
	scanf("%d", &n);
	printf("直角三角形\n");
	printf("\n");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			printf("*");
		}
		printf("\n");
	}
	
	
	
	// 菱形
	printf("\n");
	printf("菱形\n");
	printf("\n");
	for (int i = n; i > 1; --i) {
		
		
		
		for (int j = i; j > 1; --j) {
			printf(" ");
		}
		
		for (int j = 2*n; j >= 2*i-1; --j) {
			printf("*");
		}
		
		
		
		printf("\n");
	}
	for (int i = n; i > 0; --i) {
		for (int j = 0; j < n-i; ++j) {
			printf(" ");
		}
		for (int j = 0; j <= 2*i-1; ++j) {
			printf("*");
		}
		printf("\n");
	}
	
	// 倒三角形
	printf("\n");
	printf("倒三角形\n");
	printf("\n");
	for (int i = n; i > 0; --i) {
		for (int k = 0; k < n-i; ++k) {
			printf(" ");
		}
		for (int j = 0; j <= 2*i-1; ++j) {
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
	
    return 0;
}
