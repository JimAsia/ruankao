/* ex43 参考答案 —— 数组逆序 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    /* 首尾交换：i 从头走，j 从尾走，相遇就停 */
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    printf("逆序后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* ⚠️ 两个常见错误：
     *   ① 条件写 i < n（而不是 i < j）：
     *      会交换两遍，等于又换回原样，白干。
     *   ② 条件写 i <= j：
     *      偶数个元素时没问题，奇数个元素时中间那个会和自己交换，
     *      虽然结果对，但多做一次无用功。
     *   用 i < j 最干净。 */

    return 0;
}
