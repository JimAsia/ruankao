/* 93_string_pointer.c —— 字符指针 vs 字符数组
 *
 * 这是 W6 那个「能不能改」问题的完整答案。
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    /* ---------- ① 两种定义方式 ---------- */
    printf("=== ① 字符数组 vs 字符指针 ===\n");

    char arr[] = "Hello";       /* 数组：在栈上分配 6 字节，内容可改 */
    char *ptr  = "Hello";       /* 指针：指向只读区的字面量，内容不可改 */

    printf("  char arr[] = \"Hello\";   sizeof(arr) = %zu\n", sizeof(arr));
    printf("  char *ptr  = \"Hello\";   sizeof(ptr) = %zu（指针大小）\n", sizeof(ptr));
    printf("  两者用 %%s 打印都是：%s / %s\n", arr, ptr);

    /* ---------- ② 内存在哪 ---------- */
    printf("\n=== ② 存储位置不同 ===\n");
    printf("  arr 的地址 = %p（栈）\n", (void *)arr);
    printf("  ptr 的值   = %p（只读数据段）\n", (void *)ptr);
    printf("  ptr 自己的地址 = %p（栈，它是变量）\n", (void *)&ptr);

    /* ---------- ③ 能不能改 ---------- */
    printf("\n=== ③ 一个能改，一个不能 ===\n");

    arr[0] = 'h';               /* ✅ 数组在栈上，是自己的内存 */
    printf("  arr[0] = 'h' 之后：arr = \"%s\"  ✅ 成功\n", arr);

    printf("  ptr[0] = 'h' 会崩溃（段错误），因为字面量在只读区\n");
    printf("  本程序不演示崩溃\n");

    /* ---------- ④ 指针可以移动，数组名不行 ---------- */
    printf("\n=== ④ 指针能移动，数组名不能 ===\n");
    char text[] = "Programming";
    char *p = text;

    printf("  p = text 之后，*p = '%c'\n", *p);
    p++;
    printf("  p++ 之后，*p = '%c'（指向第二个字符）\n", *p);
    p += 3;
    printf("  p += 3 之后，*p = '%c'（现在指向第 5 个字符）\n", *p);
    printf("  数组名 text 不能这样：text++ 是编译错误\n");

    /* ---------- ⑤ 用指针遍历字符串 ---------- */
    printf("\n=== ⑤ 用指针遍历字符串 ===\n");

    printf("  写法一（数组下标）：");
    for (int i = 0; text[i] != '\0'; i++) printf("%c", text[i]);
    printf("\n");

    printf("  写法二（指针移动）：");
    for (char *q = text; *q != '\0'; q++) printf("%c", *q);
    printf("\n");

    printf("  写法三（指针 + 自增）：");
    char *r = text;
    while (*r) {                /* 非 0 即真 */
        printf("%c", *r);
        r++;
    }
    printf("\n");

    /* ---------- ⑥ 字符串数组：两种写法 ---------- */
    printf("\n=== ⑥ 多个字符串的两种存法 ===\n");

    /* 写法一：二维字符数组（每个字符串定长，浪费空间但可改） */
    char names1[3][10] = {"Alice", "Bob", "Cathy"};
    printf("  二维数组版：");
    for (int i = 0; i < 3; i++) printf("%s ", names1[i]);
    printf("\n  占用 30 字节，每个字符串最多 9 个字符\n");

    /* 写法二：指针数组（只存地址，省空间但字符串不可改） */
    const char *names2[3] = {"Alice", "Bob", "Cathy"};
    printf("  指针数组版：");
    for (int i = 0; i < 3; i++) printf("%s ", names2[i]);
    printf("\n  只占 24 字节（3 个指针），字符串长度不受限\n");
    printf("  ⚠️ 但 names2[0][0] = 'a' 会崩溃，因为字符串在只读区\n");

    /* ---------- ⑦ 怎么选 ---------- */
    printf("\n=== ⑦ 怎么选 ===\n");
    printf("  需要修改字符串内容      → char arr[]\n");
    printf("  只读，且字符串很多/很长 → const char *\n");
    printf("  要动态改变指向          → char *\n");
    printf("  作为函数参数（只读）    → const char *\n");

    return 0;
}
