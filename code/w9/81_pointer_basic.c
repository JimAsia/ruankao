/* 81_pointer_basic.c —— 指针的三件套：& * 类型
 *
 * 指针就是「存地址的变量」。
 * 理解指针只需要记住三件事：
 *   &  取地址
 *   *  解引用（按地址去找那块内存）
 *   指针的类型决定「一次读几个字节」
 */

#include <stdio.h>

int main(void)
{
    /* ---------- ① 变量的值 vs 变量的地址 ---------- */
    printf("=== ① 值 与 地址 ===\n");
    int a = 42;

    printf("  a 的值   = %d\n", a);
    printf("  a 的地址 = %p\n", (void *)&a);
    printf("  &a 就是「a 那块内存在哪」\n");

    /* ---------- ② 定义指针变量 ---------- */
    printf("\n=== ② 指针变量 ===\n");
    int *p = &a;            /* p 存着 a 的地址 */

    printf("  int *p = &a;  之后：\n");
    printf("    p     = %p   （p 的值就是 a 的地址）\n", (void *)p);
    printf("    &a    = %p   （两者相同）\n", (void *)&a);
    printf("    *p    = %d     （解引用，取出 p 指向的那个值）\n", *p);
    printf("    &p    = %p   （p 自己也有地址，是另一回事）\n", (void *)&p);

    /* ---------- ③ 通过指针修改原变量 ---------- */
    printf("\n=== ③ 通过指针改值 ===\n");
    printf("  改之前：a = %d\n", a);
    *p = 100;               /* 顺着 p 找到 a，改它的值 */
    printf("  执行 *p = 100 之后：a = %d\n", a);
    printf("  ⚠️ 我们没写 a = 100，但 a 确实变了 —— 因为 p 指向它\n");

    /* ---------- ④ 指针的类型很重要 ---------- */
    printf("\n=== ④ 指针类型决定「一次读几字节」 ===\n");
    printf("  sizeof(int *)    = %zu\n", sizeof(int *));
    printf("  sizeof(char *)   = %zu\n", sizeof(char *));
    printf("  sizeof(double *) = %zu\n", sizeof(double *));
    printf("  指针本身大小都一样（都是存地址），\n");
    printf("  但 int* 解引用读 4 字节，char* 只读 1 字节，double* 读 8 字节\n");

    /* 演示：用不同类型的指针读同一块内存 */
    int num = 0x41424344;   /* 0x41='A', 0x42='B', 0x43='C', 0x44='D' */

    int    *pi = &num;
    char   *pc = (char *)&num;      /* 把同一地址按 char* 解释 */

    printf("\n  同一块内存（0x41424344），不同指针读出来：\n");
    printf("    *pi（按 int 读）  = 0x%X\n", *pi);
    printf("    *pc（按 char 读） = 0x%X  （只读了最低 1 字节）\n",
           (unsigned char)*pc);
    printf("  ↑ 小端机器上最低字节是 0x44，正好是 'D'\n");

    /* ---------- ⑤ 三个容易混的写法 ---------- */
    printf("\n=== ⑤ 三种写法的区别 ===\n");
    int x = 7;
    int *q = &x;

    printf("  q   = %p     指针本身（地址）\n", (void *)q);
    printf("  *q  = %d      指向的值\n", *q);
    printf("  &q  = %p     指针自己的地址\n", (void *)&q);
    printf("  记法：* 是「顺着走一趟」，& 是「问它在哪」\n");

    /* ---------- ⑥ 指针可以改指向 ---------- */
    printf("\n=== ⑥ 指针可以改指向 ===\n");
    int m = 1, n = 2;
    int *r = &m;

    printf("  初始：*r = %d（指向 m）\n", *r);
    r = &n;
    printf("  执行 r = &n 后：*r = %d（改指向 n 了）\n", *r);
    printf("  ⚠️ 注意：r = &n 改的是指针本身，*r = n 改的是它指向的值\n");

    return 0;
}
