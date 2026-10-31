/* ex64 参考答案 —— 用函数处理数组 */
#include <stdio.h>

int sumArray(int a[], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
    }
    return s;
}

double avgArray(int a[], int n)
{
    if (n <= 0) return 0.0;             /* ⚠️ 防御：避免除零 */

    /* 复用 sumArray，而不是再写一遍循环
     * 这就是函数最大的价值：同样的逻辑只写一次 */
    return (double)sumArray(a, n) / n;
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

    printf("总和 = %d\n", sumArray(a, n));
    printf("平均 = %.2f\n", avgArray(a, n));

    /* 三个要点：
     *   ① 数组参数必须传长度 n —— 函数里 sizeof 拿不到真实长度
     *   ② avgArray 里调用 sumArray，是"函数调函数"
     *   ③ (double) 转换必须在除法之前，否则整数除法会截断 */

    return 0;
}
