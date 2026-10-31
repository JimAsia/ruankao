/* ex91 参考答案 —— 用指针返回多个值 */
#include <stdio.h>

void minMax(int *a, int n, int *outMin, int *outMax)
{
    if (n <= 0) { *outMin = 0; *outMax = 0; return; }

    int mn = *a, mx = *a;               /* 用 a[0] 当初始擂主 */
    for (int *p = a + 1; p < a + n; p++) {
        if (*p < mn) mn = *p;
        if (*p > mx) mx = *p;
    }

    *outMin = mn;                       /* 通过指针写出去 */
    *outMax = mx;
}

int main(void)
{
    int a[20], n = 0;
    int mn = 0, mx = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    minMax(a, n, &mn, &mx);

    printf("最小值 = %d，最大值 = %d\n", mn, mx);
    return 0;
}

/* 为什么需要这种写法：
 *   C 函数只能 return 一个值。
 *   想同时给出最小和最大，有两条路：
 *     ① 定义一个结构体打包（W11 会讲）
 *     ② 用指针当「输出参数」（本答案）
 *
 * 调用时传 &mn、&mx，函数就能直接写到这两个变量里。
 * 这和 scanf("%d", &n) 是同一个原理 —— scanf 也是用指针"返回"读到的值。
 *
 * ⚠️ 注意 outMin/outMax 这两个参数在函数返回前必须被赋值，
 *    否则调用者的 mn/mx 还是初始值（这里初始化为 0，看不出问题，
 *    但如果是垃圾值就会出 bug）。 */
