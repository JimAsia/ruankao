/* 63_swap_problem.c —— 为什么 swap(a, b) 交换不了
 *
 * 这是 C 语言最经典的"想不通"问题，也是 W9 指针的引子。
 */

#include <stdio.h>

/* ---------- 错误版本：值传递 ---------- */
void swapWrong(int x, int y)
{
    printf("    函数内：收到 x = %d（地址 %p），y = %d（地址 %p）\n",
           x, (void *)&x, y, (void *)&y);

    int t = x;
    x = y;
    y = t;

    printf("    函数内：交换后 x = %d，y = %d  ← 函数内部确实换了\n", x, y);
}

int main(void)
{
    int a = 1, b = 2;

    printf("=== 错误版本：值传递 ===\n");
    printf("  调用前：a = %d（地址 %p），b = %d（地址 %p）\n",
           a, (void *)&a, b, (void *)&b);

    swapWrong(a, b);

    printf("  调用后：a = %d，b = %d  ← 外面根本没变\n", a, b);

    printf("\n=== 为什么？ ===\n");
    printf("  函数收到的 x、y 是 a、b 的【副本】，存在另外两个地址上\n");
    printf("  【复制】的过程：\n");
    printf("      x = a 的值   →  x 里存着 1，但它和 a 是两块不同的内存\n");
    printf("      y = b 的值   →  y 里存着 2\n");
    printf("  函数里交换的是 x 和 y 这两个副本\n");
    printf("  函数一结束，x、y 就销毁了，a、b 从头到尾没被碰过\n");

    printf("\n=== 关键洞察 ===\n");
    printf("  函数内改的是「复印件」，不是「原件」。\n");
    printf("  这是 C 语言参数传递的铁律：所有参数都是值传递，都会拷贝。\n");

    printf("\n=== 怎么修？ ===\n");
    printf("  思路：不传值，传【地址】，让函数直接去原件上改。\n");
    printf("  这需要【指针】，是 W9 的内容。\n");
    printf("  现在只要记住这个结论就行：\n");
    printf("    想通过函数修改调用者的变量 → 必须传地址\n");
    printf("    否则函数只能「看到」值，改不动原变量\n");

    printf("\n=== 那数组为什么能改？（对比一下）===\n");
    printf("  数组作参数时传的是首地址，不是整个数组的拷贝\n");
    printf("  所以函数能直接操作原数组（见 62_value_passing.c）\n");
    printf("  ⚠️ 但注意：这是「地址被拷贝了一份」，不是「没有拷贝」\n");

    return 0;
}
