/* ex153_space.c —— 空间复杂度：看「额外」用了多少空间
 *
 * 要求：对下面三个函数，判断它们的时间复杂度和空间复杂度，填进字符串，然后运行验证。
 *
 * 空间复杂度的定义：算法运行时**额外**占用的空间（不含输入数据本身），
 * 随 n 增长的量级。
 *
 * 三个函数：
 *   f1：求和          → 只用了 sum、i 两个变量
 *   f2：复制数组      → 申请了 n 个元素
 *   f3：递归求和      → 递归 n 层，每层占一个栈帧
 *
 * 预期：
 *   f1：时间 O(n)   空间 O(1)
 *   f2：时间 O(n)   空间 O(n)
 *   f3：时间 O(n)   空间 O(n)   ← 递归的栈空间
 */

#include <stdio.h>
#include <stdlib.h>

/* TODO 1：判断 f1 的复杂度 */
static const char *t1 = "O(?)", *s1 = "O(?)";

static long long f1(const int a[], int n)
{
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

/* TODO 2：判断 f2 的复杂度 */
static const char *t2 = "O(?)", *s2 = "O(?)";

static int *f2(const int a[], int n)
{
    int *copy = (int *)malloc(sizeof(int) * (size_t)n);   /* 额外 n 个 int */
    if (copy == NULL) return NULL;
    for (int i = 0; i < n; i++) copy[i] = a[i];
    return copy;
}

/* TODO 3：判断 f3 的复杂度 */
static const char *t3 = "O(?)", *s3 = "O(?)";

static long long f3(const int a[], int n)
{
    if (n <= 0) return 0;
    return a[n - 1] + f3(a, n - 1);      /* 递归 n 层 */
}

/* 辅助：求数组中的最大值（用于估算栈帧大小） */
static int maxOf(const int a[], int n)
{
    int m = 0;
    for (int i = 1; i < n; i++) if (a[i] > m) m = a[i];
    return m;
}

int main(void)
{
    int n = 1000;
    int a[1000];
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
    free(copy);                          /* ⚠️ 申请了就要释放 */

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

    return 0;
}
