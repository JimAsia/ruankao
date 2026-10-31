/* ex22 参考答案 —— 三个数的最大值与最小值 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0, c = 0;

    printf("请输入三个整数(空格分隔): ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("输入格式不对\n");
        return 1;
    }

    /* 求最大值：先假设 a 最大，再依次挑战 */
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;

    /* 求最小值：同样的套路 */
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;

    printf("最大值 = %d，最小值 = %d\n", max, min);

    /* 另一种写法：用三目嵌套（本题要求不用，但要知道等价形式）
     * int max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
     * 可读性明显更差，这就是为什么求最值适合用"打擂台"的写法。 */

    return 0;
}
