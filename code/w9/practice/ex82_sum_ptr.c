/* ex82 —— 用指针遍历数组求和
 * 要求：写 int sumByPtr(int *a, int n)，用【指针移动】的方式遍历求和，
 *       循环条件不许用下标 a[i]。
 *
 * 测试：输入 5 / 3 7 1 9 4
 *   输出：和 = 24
 *
 * 提示：
 *   int *p = a;
 *   for (; p < a + n; p++) sum += *p;
 *   注意循环条件是 p < a + n（不是 p <= a + n，那会越界）
 */
#include <stdio.h>

int sumByPtr(int *a, int n)
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

    printf("和 = %d\n", sumByPtr(a, n));
    return 0;
}
