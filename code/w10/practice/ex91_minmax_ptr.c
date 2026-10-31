/* ex91 —— 用指针返回多个值
 * 要求：写 void minMax(int *a, int n, int *outMin, int *outMax)，
 *       找出数组的最小值和最大值，通过指针写出去。
 *
 * 测试：输入 6 / 72 45 91 38 66 88
 *   输出：最小值 = 38，最大值 = 91
 */
#include <stdio.h>

void minMax(int *a, int n, int *outMin, int *outMax)
{
    /* TODO */
}

int main(void)
{
    int a[20], n = 0;
    int mn = 0, mx = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    minMax(a, n, &mn, &mx);

    printf("最小值 = %d，最大值 = %d\n", mn, mx);
    return 0;
}
