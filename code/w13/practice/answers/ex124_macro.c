/* ex124_macro.c —— 参考答案 */

#include <stdio.h>

/* 每个参数加括号，整体再加一层 */
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define SQUARE(x)       ((x) * (x))

/* CLAMP 复用 MAX/MIN：先取 max(x, lo)，再和 hi 取 min */
#define CLAMP(x, lo, hi)  (MIN(MAX((x), (lo)), (hi)))

int main(void)
{
    int a = 3, b = 4;

    printf("MAX(3, 4) = %d\n", MAX(3, 4));
    printf("2 * MAX(3, 4) = %d   ← 如果宏没外层括号会变成 3*2=6\n", 2 * MAX(3, 4));

    printf("MIN(3, 4) = %d\n", MIN(3, 4));

    printf("MAX(a + 1, b) = %d   ← 参数括号的作用\n", MAX(a + 1, b));

    printf("SQUARE(1 + 2) = %d   ← 不带括号会算成 1+2*1+2=5\n", SQUARE(1 + 2));
    printf("SQUARE(3)     = %d\n", SQUARE(3));

    printf("CLAMP(15, 0, 10)  = %d\n", CLAMP(15, 0, 10));
    printf("CLAMP(-5, 0, 10)  = %d\n", CLAMP(-5, 0, 10));
    printf("CLAMP(5, 0, 10)   = %d\n", CLAMP(5, 0, 10));

    printf("\n⭐ 括号规则（背下来）：\n");
    printf("   每个参数都用 () 裹住\n");
    printf("   整个表达式再裹一层 ()\n");
    printf("   少了任何一层，都可能被外面的运算符拆开\n");

    printf("\n⚠️ 这个宏仍然有副作用问题：\n");
    printf("   MAX(i++, j) 会让 i 自增两次。\n");
    printf("   要绝对安全，用函数：\n");
    printf("     static inline int max(int a, int b) { return a > b ? a : b; }\n");

    printf("\n💡 CLAMP 这种「宏套宏」写法在头文件里很常见，\n");
    printf("   因为宏展开是递归的，MIN(MAX(...), hi) 会逐层展开成完整表达式。\n");

    return 0;
}
