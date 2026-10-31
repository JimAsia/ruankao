/* ex42 参考答案 —— 最值及下标 */
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

    /* ⚠️ 关键：初值用 a[0]，不从 0 开始
     * 如果写 max = 0，遇到全负数数组就会得到 0（错） */
    int max = a[0], maxIdx = 0;
    int min = a[0], minIdx = 0;

    for (int i = 1; i < n; i++) {       /* 从 1 开始，a[0] 已经比过了 */
        if (a[i] > max) {
            max = a[i];
            maxIdx = i;                 /* 顺便记住位置 */
        }
        if (a[i] < min) {
            min = a[i];
            minIdx = i;
        }
    }

    printf("最大值 = %d，下标 = %d\n", max, maxIdx);
    printf("最小值 = %d，下标 = %d\n", min, minIdx);

    /* 补充：如果要找"最后一个"最大值出现的位置，
     * 把 a[i] > max 改成 a[i] >= max 即可。
     * 这类细节软考读程序题会考。 */

    return 0;
}
