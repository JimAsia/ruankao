/* 65_array_param.c —— 数组作参数
 *
 * ⚠️ 本文件故意保留 1 处 -Wsizeof-array-argument 警告。
 *    sumArray 里对数组参数用 sizeof，编译器提醒「你拿到的是指针大小」。
 *    这正是本节要证明的事：数组作参数会退化成指针。
 *
 * 核心：数组作参数时会「退化」成指针，函数内拿不到数组长度。
 * 所以必须额外传一个长度参数 —— 这是 C 语言的硬规矩。
 */

#include <stdio.h>

/* ---------- ① 一维数组：必须同时传长度 ---------- */
int sumArray(int arr[], int n)      /* int arr[] 等价于 int *arr */
{
    printf("    函数内：sizeof(arr) = %zu 字节（这是指针的大小，不是数组的）\n",
           sizeof(arr));

    int s = 0;
    for (int i = 0; i < n; i++) {
        s += arr[i];
    }
    return s;
}

/* ---------- ② 求最大值：同样需要长度 ---------- */
int maxArray(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

/* ---------- ③ 修改数组内容：能改，因为传的是地址 ---------- */
void doubleAll(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] *= 2;
    }
}

/* ---------- ④ 二维数组作参数：必须指定列数 ---------- */
/* ⚠️ 第二维不能省！因为编译器要靠它算 m[i][j] 的地址偏移 */
int sumMatrix(int m[][4], int rows)
{
    int s = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            s += m[i][j];
        }
    }
    return s;
}

/* ---------- ⑤ 只读数组：加 const 更安全 ---------- */
int sumReadOnly(const int arr[], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += arr[i];
        /* arr[i] = 0;   ❌ 编译错误：const 保护了它，改不了 */
    }
    return s;
}

int main(void)
{
    int a[6] = {3, 7, 1, 9, 4, 6};
    int n = sizeof(a) / sizeof(a[0]);

    /* ---------- ① ---------- */
    printf("=== ① 一维数组作参数 ===\n");
    printf("  main 里：sizeof(a) = %zu 字节，n = %d\n", sizeof(a), n);
    int s = sumArray(a, n);
    printf("  求和结果 = %d\n", s);
    printf("  ⚠️ 函数里的 sizeof(arr) 只有 %zu —— 数组退化成指针了\n", sizeof(int *));
    printf("  所以长度必须另外传，这就是为什么每个数组函数都要多一个 n 参数\n");

    /* ---------- ② ---------- */
    printf("\n=== ② 求最大值 ===\n");
    printf("  maxArray(a, %d) = %d\n", n, maxArray(a, n));

    /* ---------- ③ ---------- */
    printf("\n=== ③ 修改数组内容 ===\n");
    printf("  调用前：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    doubleAll(a, n);

    printf("  调用后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n  ← 每个元素都翻倍了，因为函数拿到的是首地址\n");

    /* ---------- ④ ---------- */
    printf("\n=== ④ 二维数组作参数 ===\n");
    int m[2][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};
    printf("  sumMatrix(m, 2) = %d\n", sumMatrix(m, 2));
    printf("  ⚠️ 参数必须写 int m[][4] —— 第二维（列数）不能省\n");
    printf("  因为编译器要靠列数算地址：m[i][j] 偏移 = (i × 列数 + j)\n");
    printf("  写成 int m[][] 会编译错误\n");

    /* ---------- ⑤ ---------- */
    printf("\n=== ⑤ const 保护只读 ===\n");
    printf("  sumReadOnly(a, %d) = %d\n", n, sumReadOnly(a, n));
    printf("  加了 const，函数内想改 arr[i] 会直接编译失败 —— 这是好事\n");
    printf("  好习惯：只读的数组参数都加 const\n");

    return 0;
}
