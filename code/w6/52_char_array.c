/* 52_char_array.c —— 字符数组与字符串
 *
 * C 语言没有专门的"字符串类型"，字符串就是"以 '\0' 结尾的字符数组"。
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* ---------- ① 两种写法，差别很大 ---------- */
    printf("=== ① 字符数组 vs 字符串 ===\n");

    char s1[] = "abc";                  /* 字符串：4 字节，末尾自动加 '\0' */
    char s2[] = {'a', 'b', 'c'};        /* 字符数组：3 字节，没有 '\0'，不是字符串 */
    char s3[] = {'a', 'b', 'c', '\0'};  /* 手动加 '\0' 才是字符串 */

    printf("  char s1[] = \"abc\"             → sizeof = %zu\n", sizeof(s1));
    printf("  char s2[] = {'a','b','c'}      → sizeof = %zu\n", sizeof(s2));
    printf("  char s3[] = {'a','b','c','\\0'} → sizeof = %zu\n", sizeof(s3));

    printf("\n  s1 用 %%s 打印：%s\n", s1);
    printf("  s2 用 %%s 打印：");
    for (int i = 0; i < 3; i++) printf("%c", s2[i]);
    printf("   ← 只能逐字符打印，因为它没有结束标志\n");

    printf("\n  如果用 %%s 打印 s2，printf 会一直往后读内存找 '\\0'，\n");
    printf("  读到什么打印什么 —— 这就是未定义行为。本程序不演示，怕崩。\n");

    /* ---------- ② '\0' 是字符串的结束标志 ---------- */
    printf("\n=== ② '\\0' 的位置 ===\n");
    printf("  s1 的每个字节（用 %%d 看 ASCII 码）：");
    for (int i = 0; i < 4; i++) {
        printf("%d ", s1[i]);
    }
    printf("\n  97='a', 98='b', 99='c', 0='\\0' —— 最后一个 0 就是结束标志\n");

    /* ---------- ③ sizeof 与 strlen 的区别 ---------- */
    printf("\n=== ③ sizeof vs strlen ===\n");
    printf("  sizeof(s1)  = %zu   整个数组占几字节（含 '\\0'）\n", sizeof(s1));
    printf("  strlen(s1)  = %zu   字符个数（不含 '\\0'）\n", strlen(s1));
    printf("  记住：strlen 数到 '\\0' 就停，不包括它\n");

    /* ---------- ④ 字符数组可以修改，字面量不行 ---------- */
    printf("\n=== ④ 能不能改 ===\n");
    s1[0] = 'X';
    printf("  s1[0] = 'X' 之后：%s   ← 数组在栈上，可以改\n", s1);

    char *p = "abc";                    /* 指向只读的字面量区 */
    printf("  char *p = \"abc\" 这种写法，p 指向只读区，内容是：%s\n", p);
    printf("  写 p[0] = 'X' 会崩溃（段错误），本程序不演示\n");
    printf("  想改就用数组，不想改就用指针并加 const\n");

    /* ---------- ⑤ 遍历字符串的标准写法 ---------- */
    printf("\n=== ⑤ 遍历字符串的三种写法 ===\n");

    char text[] = "Hello";

    printf("  写法一：用下标 + strlen\n    ");
    for (size_t i = 0; i < strlen(text); i++) printf("%c", text[i]);
    printf("\n");

    printf("  写法二：遇到 '\\0' 停\n    ");
    for (int i = 0; text[i] != '\0'; i++) printf("%c", text[i]);
    printf("\n");

    printf("  写法三：指针边走边取\n    ");
    for (const char *q = text; *q != '\0'; q++) printf("%c", *q);
    printf("\n");

    printf("\n  写法二最好：不依赖 strlen（每次调用都要重数一遍），也不涉及指针\n");

    /* ---------- ⑥ 倒着打印 ---------- */
    printf("\n=== ⑥ 倒序打印 ===\n");
    printf("  正序：%s\n", text);
    printf("  倒序：");
    for (int i = (int)strlen(text) - 1; i >= 0; i--) {
        printf("%c", text[i]);
    }
    printf("\n");

    return 0;
}
