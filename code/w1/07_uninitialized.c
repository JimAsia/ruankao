/* 07_uninitialized.c —— 未初始化变量：合法，但危险
 *
 * ⚠️ 本文件是【反面教材】，故意让编译器发出警告。
 *    运行它只在实验课上用，写真实代码时不要模仿。
 *
 * 核心结论：
 *   1. 不初始化【不违法】，C 语言没有这条强制要求，编译能通过；
 *   2. 但【读取】未初始化的局部变量是未定义行为，值是垃圾；
 *   3. 全局变量和 static 变量例外 —— 它们会被自动清零。
 */
#include <stdio.h>

int g_count;        /* 全局变量，不初始化 → 标准保证自动为 0 */

int main(void)
{
    static int s_count;     /* static 局部变量，不初始化 → 自动为 0 */
    int local;              /* 普通局部变量，不初始化 → 值不确定 */

    printf("g_count = %d   全局变量，标准保证为 0\n", g_count);
    printf("s_count = %d   static 局部，标准保证为 0\n", s_count);

    printf("local   = %d   普通局部，值不确定\n", local);
    /* ↑ 这一行会触发编译警告：
     *   warning: 'local' is used uninitialized [-Wuninitialized]
     *
     *   警告不是错误，程序照样跑出结果。但你看到的那串数字没有任何意义：
     *   它是这块内存上一次被谁用过留下的残渣 —— 可能是上一次函数调用的局部变量、
     *   可能是栈上别的数据。换台机器、换个编译优化级别，结果都可能不同。
     *   这就是【未定义行为】：C 标准不管这种写法会发生什么。 */

    /* 正确的写法：先给值，再读 */
    int good = 0;
    printf("good    = %d   先初始化再读，永远可控\n", good);

    /* 或者：先声明，再赋值，之后就能放心读了 */
    int also_good;
    also_good = 42;
    printf("also_good = %d  声明后赋值，同样正确\n", also_good);

    return 0;
}
