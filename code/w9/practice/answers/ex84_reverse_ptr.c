/* ex84 参考答案 —— 用指针反转数组 */
#include <stdio.h>

void reverseByPtr(int *a, int n)
{
    int *left  = a;
    int *right = a + n - 1;             /* ⚠️ 是 a + n - 1，不是 a + n */

    while (left < right) {
        int t = *left;
        *left = *right;
        *right = t;

        left++;
        right--;
    }
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

/* 两个关键点：
 *
 * ① right 必须初始化为 a + n - 1
 *    如果写 a + n，那是指向"最后一个元素之后"的位置，
 *    解引用它会读到越界内存。
 *
 * ② while (left < right) 而不是 left <= right
 *    单数个元素时，用 <= 会让中间那个元素和自己交换一次 ——
 *    结果对，但多做一次无用功。
 *
 * 这个算法和 W5 的下标版完全对应：
 *   下标版：i = 0, j = n - 1, while (i < j)
 *   指针版：left = a, right = a + n - 1, while (left < right)
 *   两者是同一个逻辑的两种表达。
 *
 * 指针版的好处：不用维护下标，直接操作地址，语义更直接。 */
