/* ex84 —— 用指针反转数组
 * 要求：写 void reverseByPtr(int *a, int n)，原地反转数组。
 *       用两个指针（一个从头、一个从尾）向中间走，不能用下标。
 *
 * 测试：输入 6 / 1 2 3 4 5 6
 *   输出：6 5 4 3 2 1
 *
 * 提示：
 *   int *left = a, *right = a + n - 1;
 *   while (left < right) {
 *       交换 *left 和 *right;
 *       left++; right--;
 *   }
 */
#include <stdio.h>

void reverseByPtr(int *a, int n)
{
    /* TODO */
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

    reverseByPtr(a, n);

    printf("反转后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    return 0;
}
