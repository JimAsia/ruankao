/* ex33 —— 素数判断
 * 要求：读入一个正整数 n，输出「n 是素数」或「n 不是素数」。
 *
 * 测试：97  → 是
 *       91  → 不是（7 × 13）
 *       1   → 不是（1 不是素数）
 *       2   → 是（2 是最小的素数）
 *
 * 提示：
 *   ① 先处理 n < 2 的情况（0 和 1 都不是素数）
 *   ② 循环从 2 开始，条件写 i * i <= n（只试到 √n）
 *   ③ 找到因子就 break
 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    /* TODO */
	scanf("%d", &n);
	
	if (n <= 1) {
		printf("不是");
	}
	else {
		for (int i = 2; i*i <= n; ++i) {
			if (n % i == 0) {
				printf("不是");
				return 0;
			}
			
		}
		printf("是");
	}
    return 0;
}
