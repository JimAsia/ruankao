/* 61_func_basic.c —— 函数的三种形态
 *
 * 函数 = 有名字、能重复调用的一段代码。
 * 三要素：返回类型、函数名、参数列表。
 */

#include <stdio.h>

/* ---------- ① 声明（原型）：告诉编译器"有这么个函数" ---------- */
/* 声明可以写在 main 前面，或者放进头文件 */
void   sayHello(void);
void   printLine(int n);
int    add(int a, int b);
int    maxOf(int a, int b);
double average(int sum, int count);

/* ---------- ② 定义：给出具体实现 ---------- */

/* 无参数、无返回值 */
void sayHello(void)
{
    printf("Hello, Function!\n");
}

/* 有参数、无返回值 */
void printLine(int n)
{
    for (int i = 0; i < n; i++) {
        printf("-");
    }
    printf("\n");
}

/* 有参数、有返回值 */
int add(int a, int b)
{
    return a + b;           /* return 把值交回调用者 */
}

int maxOf(int a, int b)
{
    if (a > b) return a;
    return b;
    /* 也可以写 return (a > b) ? a : b; */
}

double average(int sum, int count)
{
    if (count == 0) return 0.0;     /* ⚠️ 防御：除数为 0 时不能算 */
    return (double)sum / count;
}

/* ---------- ③ 调用 ---------- */
int main(void)
{
    printf("=== ① 无参无返回 ===\n");
    sayHello();

    printf("\n=== ② 有参无返回 ===\n");
    printLine(30);

    printf("\n=== ③ 有参有返回 ===\n");
    int s = add(3, 4);
    printf("add(3, 4) = %d\n", s);
    printf("add(10, 20) + 5 = %d\n", add(10, 20) + 5);   /* 返回值能直接参与运算 */

    printf("\n=== ④ 返回值的用途 ===\n");
    printf("maxOf(7, 3) = %d\n", maxOf(7, 3));
    printf("maxOf(-1, -5) = %d\n", maxOf(-1, -5));

    printf("\n=== ⑤ 声明与定义分离 ===\n");
    printf("  main 在定义之前就调用了这些函数，靠的就是开头的声明\n");
    printf("  如果删掉声明，编译器会报 'implicit declaration of function'\n");
    printf("  C99 之后这是错误，不是警告\n");

    printf("\n=== ⑥ 函数可以嵌套调用，但【不能嵌套定义】 ===\n");
    int total = add(add(1, 2), add(3, 4));      /* 嵌套调用：合法 */
    printf("  add(add(1,2), add(3,4)) = %d\n", total);
    printf("  但在一个函数内部【定义】另一个函数是非法的\n");

    printf("\n=== ⑦ 提前 return ===\n");
    printf("  average(10, 4) = %.2f\n", average(10, 4));
    printf("  average(10, 0) = %.2f  ← 被 count==0 的提前 return 拦住了\n", average(10, 0));
    printf("  提前 return 能让代码少一层嵌套，是好习惯\n");

    return 0;
}
