/* 53_string_func.c —— <string.h> 里的核心函数
 *
 * ⚠️ 本文件故意保留 1 处 -Warray-compare 警告。
 *    第 ⑤ 段用 x == y 演示「新手的经典错误写法」，
 *    编译器同样识别出来并提醒：比较数组请用 strcmp，别用 ==。
 *
 * C 没有字符串类型，所以这些函数都是在"字符数组 + '\0'"上操作。
 * 它们不检查目标空间够不够 —— 这是最大的安全隐患。
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* ---------- ① strlen：长度（不含 '\0'） ---------- */
    printf("=== ① strlen ===\n");
    char s[] = "Programming";
    printf("  s = \"%s\"\n", s);
    printf("  strlen(s) = %zu\n", strlen(s));
    printf("  sizeof(s) = %zu（含 '\\0'）\n", sizeof(s));
    printf("  区别：strlen 数有效字符，sizeof 数分配的字节数\n");

    /* ---------- ② strcpy：复制 ---------- */
    printf("\n=== ② strcpy ===\n");
    char dst[50];
    strcpy(dst, s);
    printf("  strcpy(dst, s) 之后 dst = \"%s\"\n", dst);
    printf("  ⚠️ 不检查 dst 够不够大，dst 只有 10 字节就会溢出\n");

    /* 更安全的写法：strncpy 限长 */
    char dst2[50];
    strncpy(dst2, s, sizeof(dst2) - 1);
    dst2[sizeof(dst2) - 1] = '\0';      /* ⚠️ 手动补结束符 */
    printf("  strncpy 版本 dst2 = \"%s\"\n", dst2);
    printf("  注意：strncpy 在源串太长时不保证补 '\\0'，要手动补\n");

    /* ---------- ③ strcat：拼接 ---------- */
    printf("\n=== ③ strcat ===\n");
    char full[50] = "Hello, ";
    strcat(full, "World");
    printf("  \"Hello, \" + \"World\" = \"%s\"\n", full);
    printf("  同样不检查空间，full 必须有足够余量\n");

    /* ---------- ④ strcmp：比较（重点） ---------- */
    printf("\n=== ④ strcmp：返回值不是布尔！ ===\n");
    printf("  strcmp(\"abc\", \"abc\")  = %d    相等\n", strcmp("abc", "abc"));
    printf("  strcmp(\"abc\", \"abd\")  = %d    小于（c < d）\n", strcmp("abc", "abd"));
    printf("  strcmp(\"abd\", \"abc\")  = %d    大于\n", strcmp("abd", "abc"));
    printf("  strcmp(\"abc\", \"ab\")   = %d    长的大\n", strcmp("abc", "ab"));
    printf("  strcmp(\"Z\", \"a\")      = %d    'Z'=90 < 'a'=97，大写字母反而小\n", strcmp("Z", "a"));

    printf("\n  规则：逐个字符按 ASCII 码比，第一个不同就定胜负\n");
    printf("  返回值：<0 表示前者小，0 表示相等，>0 表示前者大\n");
    printf("  ⚠️ 不要写成 if (strcmp(a, b))，那样是「不相等」，不是「相等」\n");

    /* 正确用法 */
    printf("\n  正确用法：\n");
    if (strcmp("abc", "abc") == 0)
        printf("    strcmp(a,b) == 0  →  相等 ✓\n");
    if (strcmp("abc", "abd") != 0)
        printf("    strcmp(a,b) != 0  →  不相等 ✓\n");
    if (strcmp("abc", "abd") < 0)
        printf("    strcmp(a,b) < 0   →  a 在前 ✓\n");

    /* ---------- ⑤ 不能用 == 比较字符串 ---------- */
    printf("\n=== ⑤ ⚠️ 不能用 == 比较字符串内容 ===\n");
    char x[] = "abc";
    char y[] = "abc";
    printf("  x 和 y 内容相同，但 x == y 的结果是 %d（假）\n", x == y);
    printf("  因为 == 比的是地址，x 和 y 是两个不同的数组，地址当然不同\n");
    printf("  要比内容必须用 strcmp\n");

    /* ---------- ⑥ 其他常用函数 ---------- */
    printf("\n=== ⑥ 其他常用函数 ===\n");
    printf("  strchr(\"hello\", 'l')   → 返回指向第一个 'l' 的指针\n");
    printf("  strstr(\"hello\", \"ll\") → 返回指向子串 \"ll\" 的指针\n");

    const char *pos = strchr("hello", 'l');
    if (pos != NULL) {
        printf("  实测：strchr(\"hello\",'l') 之后，剩余部分是 \"%s\"\n", pos);
    }

    const char *sub = strstr("hello world", "world");
    if (sub != NULL) {
        printf("  实测：strstr(\"hello world\",\"world\") 之后是 \"%s\"\n", sub);
    }

    return 0;
}
