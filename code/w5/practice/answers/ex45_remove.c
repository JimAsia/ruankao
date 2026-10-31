/* ex45 参考答案 —— 删除所有等于 x 的元素 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0, x = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    printf("请输入要删除的数: ");
    if (scanf("%d", &x) != 1) return 1;

    /* 覆盖法：k 指向"新数组"下一个要写入的位置
     * 遇到不等于 x 的元素，就把它搬到 a[k] 并让 k 前进
     * 等于 x 的元素自然就被跳过了 */
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != x) {
            a[k] = a[i];
            k++;
        }
    }

    printf("删除后：");
    for (int i = 0; i < k; i++) printf("%d ", a[i]);
    printf("\n剩余个数 = %d\n", k);

    /* 为什么这个方法好：
     *   一趟循环 O(n)，不需要反复搬动
     *   如果写成"找到一个就整体前移"，最坏是 O(n²)
     *
     * 注意 i 和 k 的关系：
     *   k <= i 恒成立，所以 a[k] = a[i] 不会覆盖掉还没读的数据。
     *   这是这个算法的正确性关键。 */

    return 0;
}
