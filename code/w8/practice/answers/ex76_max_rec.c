/* ex76 参考答案 —— 递归求数组最大值 */
#include <stdio.h>

int maxRec(int a[], int n)
{
    if (n == 1) return a[0];            /* 出口：只剩一个元素 */

    int maxOfRest = maxRec(a, n - 1);   /* 前面 n-1 个的最大值 */

    /* 拿它和最后一个元素比 */
    return (a[n - 1] > maxOfRest) ? a[n - 1] : maxOfRest;
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

    printf("最大值 = %d\n", maxRec(a, n));
    return 0;
}

/* 递推式：
 *   maxRec(a, n) = max( a[n-1], maxRec(a, n-1) )
 *
 * 以 {3, 7, 1} 为例：
 *   maxRec(a,3) = max(1, maxRec(a,2))
 *   maxRec(a,2) = max(7, maxRec(a,1))
 *   maxRec(a,1) = 3                              ← 出口
 *   回代：max(7,3) = 7 → max(1,7) = 7
 *
 * 两种写法对照（结果一样）：
 *   写法一（本答案）：从末尾往前看
 *     maxRec(a,n) = max(a[n-1], maxRec(a,n-1))
 *   写法二：从前往后看
 *     maxRec(a,n) = max(a[0], maxRec(a+1, n-1))   ← 需要指针，W9 才学
 *
 * ⚠️ 递归版比循环版慢（每次调用都有开销），实际工程里求最大值用循环。
 *    这题的目的是练习「把问题拆成 1 个元素 + 剩下所有」。 */
