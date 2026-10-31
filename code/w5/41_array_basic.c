/* 41_array_basic.c —— 数组的定义、初始化、遍历
 *
 * 数组 = 一串连续存放的同类型变量，用一个名字 + 下标访问。
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① 三种初始化方式 ---------- */
    printf("=== ① 三种初始化 ===\n");

    int a[5] = {1, 2, 3, 4, 5};     /* 全部给出 */
    int b[5] = {1, 2};              /* 只给前两个，其余自动为 0 */
    int c[]  = {10, 20, 30};        /* 不给长度，编译器数出来是 3 */
    int d[5] = {0};                 /* 只写一个 0：全部元素都变成 0 */

    printf("a[5] = {1,2,3,4,5} → ");
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");

    printf("b[5] = {1,2}       → ");
    for (int i = 0; i < 5; i++) printf("%d ", b[i]);
    printf("  ← 后面三个自动补 0\n");

    printf("c[]  = {10,20,30}  → ");
    for (int i = 0; i < 3; i++) printf("%d ", c[i]);
    printf("  ← 长度自动推导为 3\n");

    printf("d[5] = {0}         → ");
    for (int i = 0; i < 5; i++) printf("%d ", d[i]);
    printf("  ← 全 0\n");

    /* ---------- ② 下标从 0 开始 ---------- */
    printf("\n=== ② 下标从 0 开始 ===\n");
    printf("a 的 5 个元素分别是：\n");
    for (int i = 0; i < 5; i++) {
        printf("  a[%d] = %d\n", i, a[i]);
    }
    printf("  合法下标范围：0 ~ %d（不是 1 ~ 5）\n", 5 - 1);

    /* ---------- ③ 求数组长度的标准写法 ---------- */
    printf("\n=== ③ 求长度：sizeof(a) / sizeof(a[0]) ===\n");
    printf("  sizeof(a)    = %zu 字节（整个数组）\n", sizeof(a));
    printf("  sizeof(a[0]) = %zu 字节（一个元素）\n", sizeof(a[0]));
    printf("  长度 = %zu / %zu = %zu\n", sizeof(a), sizeof(a[0]), sizeof(a) / sizeof(a[0]));

    /* ---------- ④ 数组名代表首地址 ---------- */
    printf("\n=== ④ 数组名就是首元素地址 ===\n");
    printf("  a     = %p\n", (void *)a);
    printf("  &a[0] = %p\n", (void *)&a[0]);
    printf("  两者相同，所以 a[i] 等价于 *(a + i)（W9 指针会细讲）\n");

    /* ---------- ⑤ 相邻元素的地址差 = 元素大小 ---------- */
    printf("\n=== ⑤ 内存是连续的 ===\n");
    printf("  &a[0] = %p\n", (void *)&a[0]);
    printf("  &a[1] = %p\n", (void *)&a[1]);
    printf("  &a[2] = %p\n", (void *)&a[2]);
    printf("  每次相差 %zu 字节，正好是一个 int 的大小\n", sizeof(int));

    /* ---------- ⑥ 越界不报错，这才是最危险的 ---------- */
    printf("\n=== ⑥ 越界警告 ===\n");
    printf("  a[5] 已经越界（合法下标只到 4）\n");
    printf("  C 语言【不会检查】越界，可能读到垃圾值、可能改坏别的变量、可能直接崩溃\n");
    printf("  编译器只在能静态看出来时才警告，运行时毫无保护\n");

    return 0;
}
