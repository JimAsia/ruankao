/* ex83 —— 用指针找数组最大值
 * 要求：写 int maxByPtr(int *a, int n)，返回最大值。
 *       必须用指针，不用下标。
 *
 * 测试：输入 6 / 72 45 91 38 66 88
 *   输出：最大值 = 91
 *
 * 提示：max 用 *a 初始化（就是 a[0]），指针从 a+1 开始走。
 */
#include <stdio.h>

int maxByPtr(int *a, int n)
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

    printf("最大值 = %d\n", maxByPtr(a, n));
    return 0;
}
