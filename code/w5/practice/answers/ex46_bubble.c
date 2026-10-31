/* ex46 参考答案 —— 冒泡排序 */
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

    /* 标准冒泡，带提前结束优化 */
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;                    /* 本轮是否交换过 */

        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {          /* 升序：前大后小就换 */
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                swapped = 1;
            }
        }

        if (!swapped) break;                /* 一趟没换 = 已有序，提前收工 */
    }

    printf("排序后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* 降序怎么改：把 a[j] > a[j+1] 改成 a[j] < a[j+1] 即可。 */

    return 0;
}
