/* ex86 参考答案 —— 指针与数组的等价性验证 */
#include <stdio.h>

int main(void)
{
    int a[6] = {10, 20, 30, 40, 50, 60};

    printf("=== ① 取 a[3] 的值 ===\n");
    printf("  写法 A：a[3]      = %d\n", a[3]);
    printf("  写法 B：*(a + 3)  = %d\n", *(a + 3));
    printf("  → 完全相同\n");

    printf("\n=== ② 取 a[3] 的地址 ===\n");
    printf("  写法 A：&a[3]     = %p\n", (void *)&a[3]);
    printf("  写法 B：a + 3     = %p\n", (void *)(a + 3));
    printf("  → 完全相同\n");

    printf("\n=== ③ 把 a[0] 改成 99 ===\n");
    printf("  改之前：a[0] = %d\n", a[0]);

    int *p = a;
    *p = 99;                            /* 用指针改 */

    printf("  执行 *p = 99 之后：a[0] = %d\n", a[0]);
    printf("  → 用指针改的就是数组本身\n");

    printf("\n=== ④ 求 a[2] 和 a[4] 的间隔 ===\n");
    printf("  写法 A：4 - 2              = %d\n", 4 - 2);
    printf("  写法 B：&a[4] - &a[2]      = %td\n", &a[4] - &a[2]);
    printf("  → 都是 2。注意指针相减得到的是【元素个数】，不是字节数\n");

    printf("\n=== ⑤ 用指针遍历 ===\n");
    printf("  写法 A（下标）：");
    for (int i = 0; i < 6; i++) printf("%d ", a[i]);
    printf("\n");

    printf("  写法 B（指针）：");
    for (int *q = a; q < a + 6; q++) printf("%d ", *q);
    printf("\n");

    printf("\n=== 结论 ===\n");
    printf("  a[i]  ==  *(a + i)\n");
    printf("  &a[i] ==  a + i\n");
    printf("  这不是「巧合」，而是 C 语言的定义：\n");
    printf("  下标写法只是指针运算的语法糖，编译器生成完全一样的代码。\n");

    return 0;
}
