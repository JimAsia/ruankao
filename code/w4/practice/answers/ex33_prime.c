/* ex33 参考答案 —— 素数判断 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    printf("请输入一个正整数: ");
    if (scanf("%d", &n) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    /* 先处理特殊情况：小于 2 的数都不是素数 */
    if (n < 2) {
        printf("%d 不是素数\n", n);
        return 0;
    }

    /* 试除法：从 2 试到 √n
     * 为什么到 √n 就够？因为因子成对出现：
     *   如果 n = a × b 且 a <= √n <= b，
     *   那 a 和 b 里必定有一个不超过 √n。
     *   所以试到 √n 还没找到因子，就一定是素数。
     * 条件写 i * i <= n 而不是 i <= sqrt(n)，避免引入浮点数。 */
    int isPrime = 1;                    /* 先假设是素数 */
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            isPrime = 0;
            break;                      /* 找到一个因子就够了 */
        }
    }

    if (isPrime)
        printf("%d 是素数\n", n);
    else
        printf("%d 不是素数\n", n);

    return 0;
}
