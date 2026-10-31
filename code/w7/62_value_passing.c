/* 62_value_passing.c —— 值传递的本质
 *
 * ⚠️ 本文件故意保留 1 处 -Wsizeof-array-argument 警告。
 *    第 ② 段在函数里对数组参数用 sizeof，编译器提醒"你拿到的是指针大小，不是数组大小"。
 *    这正是要演示的现象 —— 数组作参数会退化成指针。
 *
 * C 语言只有一种参数传递方式：值传递。
 * 意思是：调用时把实参的【值】复制一份给形参，两者此后毫无关系。
 */

#include <stdio.h>

void tryToChange(int x)
{
    printf("  函数内：收到 x = %d，地址 %p\n", x, (void *)&x);
    x = 999;
    printf("  函数内：改成 x = %d\n", x);
}

void changeArray(int arr[], int n)
{
    printf("  函数内：arr 的地址 %p，sizeof(arr) = %zu\n", (void *)arr, sizeof(arr));
    /* ⚠️ 数组传进来后会"退化"成指针，sizeof 得到的是指针大小（8），不是数组大小 */
    for (int i = 0; i < n; i++) {
        arr[i] = arr[i] * 10;       /* 但能改内容！因为传的是地址 */
    }
}

int main(void)
{
    /* ---------- ① 基本类型：改不动实参 ---------- */
    printf("=== ① 基本类型是拷贝 ===\n");
    int a = 10;
    printf("  调用前：a = %d，地址 %p\n", a, (void *)&a);

    tryToChange(a);

    printf("  调用后：a = %d（没变！）\n", a);
    printf("  原因：形参 x 是 a 的副本，存在另一个地址上，改它不影响 a\n");

    /* ---------- ② 数组：能改内容 ---------- */
    printf("\n=== ② 数组传的是地址，所以能改 ===\n");
    int nums[5] = {1, 2, 3, 4, 5};
    printf("  调用前：");
    for (int i = 0; i < 5; i++) printf("%d ", nums[i]);
    printf("\n");

    changeArray(nums, 5);

    printf("  调用后：");
    for (int i = 0; i < 5; i++) printf("%d ", nums[i]);
    printf("\n");
    printf("  ⚠️ 数组变了！因为数组作参数时传的是首地址\n");

    /* ---------- ③ 结论表 ---------- */
    printf("\n=== ③ C 语言的参数传递 ===\n");
    printf("  基本类型（int/double/char）：传值，函数内改不动外面\n");
    printf("  数组（int a[]）：传地址，函数内能改内容\n");
    printf("  结构体（W11 会讲）：传值，整个结构体被拷贝\n");
    printf("  指针（W9 会讲）：传地址，能改它指向的东西\n");

    printf("\n  💡 一句话：C 语言【只有值传递】。\n");
    printf("     所谓「传地址」，也是把地址这个值复制过去而已。\n");

    return 0;
}
