/* ex76 —— 递归求数组最大值
 * 要求：写递归函数 int maxRec(int a[], int n)，返回数组前 n 个元素的最大值。
 *
 * 测试：输入 6 / 72 45 91 38 66 88
 *   输出：最大值 = 91
 *
 * 提示：出口 n == 1 返回 a[0]；
 *       递推：maxRec(a, n) = max( a[n-1], maxRec(a, n-1) )
 *       也就是「最后一个元素」和「前面所有元素的最大值」比大小。
 */
#include <stdio.h>

int maxRec(int a[], int n)
{
    /* TODO */
    return 0;
}

int main(void)
{
    int a[20], n = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    printf("最大值 = %d\n", maxRec(a, n));
    return 0;
}
