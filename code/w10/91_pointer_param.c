/* 91_pointer_param.c —— 指针作函数参数
 *
 * 指针传参解决两个问题：
 *   ① 让函数能修改调用者的变量
 *   ② 让函数能「返回」多个结果
 */

#include <stdio.h>

/* ---------- ① 修改实参：swap ---------- */
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* ---------- ② 「返回」多个值：用输出参数 ---------- */
/* C 函数只能 return 一个值，想要多个结果就得靠指针 */
void minMax(int a[], int n, int *outMin, int *outMax)
{
    int mn = a[0], mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
    *outMin = mn;               /* 写到调用者提供的内存里 */
    *outMax = mx;
}

/* ---------- ③ 除法：同时返回商和余数 ---------- */
int divide(int a, int b, int *remainder)
{
    if (b == 0) {
        *remainder = 0;
        return -1;              /* 用返回值表示出错 */
    }
    *remainder = a % b;
    return a / b;
}

/* ---------- ④ 把指针当普通变量传 ---------- */
void redirect(int **pp, int *target)
{
    *pp = target;               /* 修改「指针的指向」 */
}

int main(void)
{
    /* ---------- ① ---------- */
    printf("=== ① 修改实参 ===\n");
    int x = 1, y = 2;
    printf("  交换前：x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("  交换后：x = %d, y = %d\n", x, y);

    /* ---------- ② ---------- */
    printf("\n=== ② 返回多个值 ===\n");
    int a[6] = {72, 45, 91, 38, 66, 88};
    int mn, mx;

    minMax(a, 6, &mn, &mx);

    printf("  最小值 = %d，最大值 = %d\n", mn, mx);
    printf("  一个 return 只能交回一个值，所以用指针「写出去」\n");

    /* ---------- ③ ---------- */
    printf("\n=== ③ 商和余数 ===\n");
    int rem;

    int q = divide(17, 5, &rem);
    printf("  17 / 5 = %d 余 %d\n", q, rem);

    q = divide(10, 0, &rem);
    printf("  10 / 0 → 返回值 = %d（-1 表示出错）\n", q);
    printf("  这个模式很常用：返回值表示成功/失败，结果通过指针带出\n");

    /* ---------- ④ 二级指针 ---------- */
    printf("\n=== ④ 修改「指针的指向」要用二级指针 ===\n");
    int m = 10, n = 20;
    int *p = &m;

    printf("  初始：*p = %d（指向 m）\n", *p);
    redirect(&p, &n);           /* 传 p 的地址，才能改 p 本身 */
    printf("  redirect 之后：*p = %d（改指向 n 了）\n", *p);
    printf("  ⚠️ 想改指针的【指向】，必须传指针的地址，也就是二级指针\n");

    /* ---------- ⑤ 对照表 ---------- */
    printf("\n=== ⑤ 传什么取决于想改什么 ===\n");
    printf("  %-28s %s\n", "想做的事", "参数类型");
    printf("  %-28s %s\n", "只读一个 int", "int");
    printf("  %-28s %s\n", "要改一个 int", "int *");
    printf("  %-28s %s\n", "只读一个数组", "const int a[]");
    printf("  %-28s %s\n", "要改一个数组", "int a[]");
    printf("  %-28s %s\n", "要改一个指针的指向", "int **");

    return 0;
}
