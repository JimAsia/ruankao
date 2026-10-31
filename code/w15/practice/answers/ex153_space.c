/* ex153_space.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

static const char *t1 = "O(n)", *s1 = "O(1)";

static long long f1(const int a[], int n)
{
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

static const char *t2 = "O(n)", *s2 = "O(n)";

static int *f2(const int a[], int n)
{
    int *copy = (int *)malloc(sizeof(int) * (size_t)n);
    if (copy == NULL) return NULL;
    for (int i = 0; i < n; i++) copy[i] = a[i];
    return copy;
}

static const char *t3 = "O(n)", *s3 = "O(n)";

static long long f3(const int a[], int n)
{
    if (n <= 0) return 0;
    return a[n - 1] + f3(a, n - 1);
}

static int maxOf(const int a[], int n)
{
    int m = 0;
    for (int i = 1; i < n; i++) if (a[i] > m) m = a[i];
    return m;
}

int main(void)
{
    int n = 1000;
    static int a[1000];
    for (int i = 0; i < n; i++) a[i] = i + 1;

    printf("=== 三个函数的复杂度判断 ===\n\n");

    (void)f1(a, n);
    printf("f1 求和      ：时间 %-10s 空间 %-10s\n", t1, s1);
    printf("               额外变量只有 sum 和 i，与 n 无关 → 空间 O(1)\n");

    int *copy = f2(a, n);
    printf("f2 复制数组  ：时间 %-10s 空间 %-10s\n", t2, s2);
    printf("               malloc 了 n 个 int = %d 字节 → 空间 O(n)\n",
           (int)(sizeof(int) * (size_t)n));
    printf("               最大值验证：%d\n", copy ? maxOf(copy, n) : -1);
    free(copy);

    printf("f3 递归求和  ：时间 %-10s 空间 %-10s\n", t3, s3);
    printf("               递归 %d 层，每层一个栈帧 → 空间 O(n)\n", n);
    printf("               结果 = %lld（1+2+...+%d）\n", f3(a, n), n);

    printf("\n=== 为什么递归的空间是 O(n) ===\n");
    printf("  每调用一次 f3，就要在栈上保存「返回地址 + 参数 + 局部变量」，\n");
    printf("  这一层还没返回，下一层又压上来 —— 一共压 n 层。\n");
    printf("  n=100000 时，每层假设 48 字节，就是 4.8 MB，\n");
    printf("  而默认栈大小通常只有 1~8 MB → 栈溢出（Stack Overflow）。\n");

    printf("\n=== 空间复杂度的三条判断规则 ===\n");
    printf("  1. 只用了固定几个变量（含循环变量）→ O(1)\n");
    printf("  2. 开了长度与 n 成正比的数组/链表 → O(n)\n");
    printf("  3. 递归深度为 d → 至少 O(d) 的栈空间\n");
    printf("\n  ⭐ 注意：输入数组本身不算额外空间。\n");
    printf("     f1 参数 a[] 有 n 个元素，但它不是 f1 申请的，所以 f1 是 O(1)。\n");

    printf("\n=== 常见算法的空间复杂度（软考高频）===\n");
    printf("  %-16s %-10s %s\n", "算法", "空间", "额外用了什么");
    printf("  --------------------------------------------------\n");
    printf("  %-16s %-10s %s\n", "冒泡/选择/插入", "O(1)",  "只要临时变量");
    printf("  %-16s %-10s %s\n", "归并排序",      "O(n)",  "合并要临时数组");
    printf("  %-16s %-10s %s\n", "快速排序",      "O(log n)", "递归栈深度");
    printf("  %-16s %-10s %s\n", "堆排序",        "O(1)",  "原地调整");
    printf("  %-16s %-10s %s\n", "二分查找（迭代）","O(1)", "只要 lo/hi/mid");
    printf("  %-16s %-10s %s\n", "二分查找（递归）","O(log n)", "递归栈");

    return 0;
}
