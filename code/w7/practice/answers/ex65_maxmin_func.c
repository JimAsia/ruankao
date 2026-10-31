/* ex65 参考答案 —— 用函数找数组最值 */
#include <stdio.h>

int maxArray(int a[], int n)
{
    if (n <= 0) return 0;               /* 防御：空数组没有最大值 */

    int max = a[0];                     /* ⚠️ 用第一个元素当擂主 */
    for (int i = 1; i < n; i++) {       /* 从 1 开始 */
        if (a[i] > max) max = a[i];
    }
    return max;
}

int minArray(int a[], int n)
{
    if (n <= 0) return 0;

    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) min = a[i];
    }
    return min;
}

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

    printf("最大值 = %d，最小值 = %d\n", maxArray(a, n), minArray(a, n));

    /* ⚠️ 上面这一行看似简洁，但有个隐患：
     *    maxArray 和 minArray 谁先执行，C 标准没有规定。
     *    这两个函数都没有副作用（只是读数组），所以这里没问题。
     *    但如果函数有副作用（比如都去改全局变量），就必须拆成两句。
     *
     * 稳妥写法：
     *    int mx = maxArray(a, n);
     *    int mn = minArray(a, n);
     *    printf("最大值 = %d，最小值 = %d\n", mx, mn); */

    return 0;
}
