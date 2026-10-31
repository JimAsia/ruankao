/* ex83 参考答案 —— 用指针找数组最大值 */
#include <stdio.h>

int maxByPtr(int *a, int n)
{
    if (n <= 0) return 0;

    int max = *a;                       /* *a 就是 a[0] */
    for (int *p = a + 1; p < a + n; p++) {   /* 从 a[1] 开始 */
        if (*p > max) max = *p;
    }
    return max;
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

/* ⚠️ 初值陷阱在指针版里同样存在：
 *   int max = 0;              ← 全负数数组会得到 0（错）
 *   int max = *a;             ← 正确，用第一个元素当擂主
 *
 * 指针版的地址对应关系：
 *   a + 1   等价于 &a[1]
 *   *a      等价于  a[0]
 *   *(a+1)  等价于  a[1]
 *
 * 所以 p < a + n 就是「p 还没走到末尾之后」。 */
