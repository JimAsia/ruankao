/* ex31 参考答案 —— 求和 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    printf("请输入正整数 n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入格式不对\n");
        return 1;
    }

    /* 累加：初值必须是 0 */
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("1~%d 的和 = %d\n", n, sum);

    /* 偶数和：初值也是 0 */
    int evenSum = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            evenSum += i;
        }
    }
    printf("1~%d 的偶数和 = %d\n", n, evenSum);

    /* 也可以直接以 2 为步长，少一半循环：
     *   for (int i = 2; i <= n; i += 2) evenSum += i;
     */

    return 0;
}
