/* 92_array_param.c —— 数组参数与指针的等价性
 *
 * ⚠️ 本文件故意保留 1 处 -Wstringop-overflow 警告。
 *    sum3 的参数写成 int a[10]，但实际传入的是 6 个元素的数组，
 *    编译器按 [10] 推断边界并提醒「可能越界」——
 *    这正好证明：参数里的 10 虽然不影响类型，但编译器会拿它做检查，
 *    而你传给函数的真实长度可能远小于它。
 *
 * int a[] 和 int *a 作为函数参数是完全等价的。
 * 这不是"类似"，是【完全一样】—— 编译器把它们当成同一个类型。
 */

#include <stdio.h>

/* 这三种写法在参数位置上完全等价 */
int sum1(int a[], int n);
int sum2(int *a, int n);
int sum3(int a[10], int n);         /* 括号里的 10 被忽略！ */

int sum1(int a[], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    return s;
}

int sum2(int *a, int n)             /* 和 sum1 是同一个函数签名 */
{
    int s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    return s;
}

int sum3(int a[10], int n)          /* 那个 10 毫无作用 */
{
    int s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    return s;
}

/* 只读版本 */
int sumConst(const int *a, int n)
{
    int s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    /* a[i] = 0;   ❌ const 保护，编译错误 */
    return s;
}

/* 二维数组：必须指定列数 */
int sumMatrix(int m[][4], int rows)
{
    int s = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 4; j++)
            s += m[i][j];
    return s;
}

int main(void)
{
    int a[6] = {3, 7, 1, 9, 4, 6};

    /* ---------- ① 三种写法结果相同 ---------- */
    printf("=== ① 三种参数写法完全等价 ===\n");
    printf("  sum1(a, 6) = %d\n", sum1(a, 6));
    printf("  sum2(a, 6) = %d\n", sum2(a, 6));
    printf("  sum3(a, 6) = %d\n", sum3(a, 6));
    printf("  编译器把 int a[]、int *a、int a[10] 都当成 int *a\n");

    printf("\n  ⚠️ 注意 sum3 的 int a[10] —— 那个 10 被编译器【完全忽略】\n");
    printf("     传进去一个只有 3 个元素的数组也不会报错\n");
    printf("     所以长度必须单独传 n，这就是原因\n");

    /* ---------- ② sizeof 的坑 ---------- */
    printf("\n=== ② 函数内 sizeof 拿不到数组大小 ===\n");
    printf("  main 里：sizeof(a) = %zu 字节\n", sizeof(a));
    printf("  （函数里 sizeof(a) 只会得到 8，因为 a 已经是指针了）\n");
    printf("  这就是为什么每个数组函数都要多一个 n 参数\n");

    /* ---------- ③ const 参数 ---------- */
    printf("\n=== ③ const 表示「我只读」 ===\n");
    printf("  sumConst(a, 6) = %d\n", sumConst(a, 6));
    printf("  只读的数组参数都该加 const —— 这是给调用者的承诺\n");

    /* ---------- ④ 二维数组必须指定列数 ---------- */
    printf("\n=== ④ 二维数组作参数 ===\n");
    int m[2][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    printf("  sumMatrix(m, 2) = %d\n", sumMatrix(m, 2));
    printf("  参数写 int m[][4]，列数 4 不能省\n");
    printf("  因为编译器要靠它算 m[i][j] 的地址：偏移 = (i × 4 + j)\n");
    printf("  写成 int m[][] 编译错误，写成 int **m 也不对（类型不同）\n");

    /* ---------- ⑤ 为什么数组传参不拷贝整个数组 ---------- */
    printf("\n=== ⑤ 为什么数组传参不拷贝整个数组 ===\n");
    printf("  如果拷贝：传一个 100 万元的数组就要复制 100 万次\n");
    printf("  实际做法：只传首地址（8 字节），函数顺着地址访问原数组\n");
    printf("  好处：快，且能改原数组\n");
    printf("  代价：函数拿不到长度，也不知道边界 —— 全靠你传对 n\n");

    return 0;
}
