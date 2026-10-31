/* 101_struct_basic.c —— 结构体的定义、初始化与成员访问
 *
 * 结构体把「逻辑上属于一起」的多个变量打包成一个整体。
 * 这是 C 语言唯一的自定义复合类型手段。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 101 101_struct_basic.c
 */

#include <stdio.h>
#include <string.h>

/* ---------- ① 定义：只是「声明一种类型」，不占内存 ---------- */
struct Student {
    int    id;          /* 学号 */
    char   name[20];    /* 姓名（字符数组，不是 char*） */
    int    age;         /* 年龄 */
    double score;       /* 成绩 */
};                      /* ← 这个分号绝对不能丢，丢了报错很难看懂 */

int main(void)
{
    /* ---------- ② 三种初始化方式 ---------- */
    printf("=== ① 三种初始化 ===\n");

    /* 方式一：按顺序赋值（最易错，位置错了编译器未必报错） */
    struct Student s1 = {2026001, "张三", 18, 92.5};

    /* 方式二：指定成员名（C99，最安全，顺序无关） */
    struct Student s2 = {
        .score = 88.0,
        .id    = 2026002,
        .name  = "李四",
        .age   = 19
    };

    /* 方式三：先声明再逐个赋值 */
    struct Student s3;
    s3.id    = 2026003;
    strcpy(s3.name, "王五");    /* 字符数组不能用 = 赋值，必须 strcpy */
    s3.age   = 20;
    s3.score = 76.5;

    printf("  s1: %d %s %d %.1f\n", s1.id, s1.name, s1.age, s1.score);
    printf("  s2: %d %s %d %.1f\n", s2.id, s2.name, s2.age, s2.score);
    printf("  s3: %d %s %d %.1f\n", s3.id, s3.name, s3.age, s3.score);

    /* ---------- ③ 成员访问：点运算符 ---------- */
    printf("\n=== ② 成员访问 ===\n");
    printf("  s1.name 长度 = %zu\n", strlen(s1.name));
    printf("  s1 占 %zu 字节\n", sizeof(s1));
    printf("  成员之和 = %zu 字节\n",
           sizeof(s1.id) + sizeof(s1.name) + sizeof(s1.age) + sizeof(s1.score));

    int sum = sizeof(s1.id) + (int)sizeof(s1.name) + (int)sizeof(s1.age) + (int)sizeof(s1.score);
    printf("  差值 = %d 字节 ← 这叫「内存对齐」，不是浪费\n", (int)sizeof(s1) - sum);

    /* ---------- ④ 结构体可以整体赋值 ---------- */
    printf("\n=== ③ 结构体整体赋值 ===\n");
    struct Student s4 = s1;                 /* ✅ 合法：逐字节拷贝 */
    s4.score = 100.0;                       /* 改副本，不影响 s1 */
    printf("  s4 = s1 之后，改 s4.score = 100\n");
    printf("  s1.score = %.1f（没变）\n", s1.score);
    printf("  s4.score = %.1f\n", s4.score);

    printf("\n  ⚠️ 整体赋值只对「结构体变量之间」成立\n");
    printf("     数组之间不能 a = b，结构体可以 s1 = s2 —— 这是重要区别\n");

    /* ---------- ⑤ 内存对齐规则 ---------- */
    printf("\n=== ④ 为什么会有对齐 ===\n");
    struct A { char c; int i; };            /* char 后要补 3 字节 */
    struct B { char a; double d; char b; }; /* 最坏排列：a 后补 7，b 后补 7 */
    struct C { double d; char a; char b; }; /* 最好排列：a、b 挨着，尾部补 6 */

    printf("  { char c; int i; }            → %2zu 字节（1 + 3 填充 + 4）\n", sizeof(struct A));
    printf("  { char a; double d; char b; } → %2zu 字节（1 + 7填充 + 8 + 1 + 7填充）\n", sizeof(struct B));
    printf("  { double d; char a; char b; } → %2zu 字节（8 + 1 + 1 + 6填充）\n", sizeof(struct C));

    printf("\n  ⭐ 同样三个成员，只是顺序不同：%zu 字节 vs %zu 字节\n",
           sizeof(struct B), sizeof(struct C));
    printf("     差 %zu 字节，一点用都没有 —— 这就是对齐的代价。\n",
           sizeof(struct B) - sizeof(struct C));

    printf("\n  两条规则：\n");
    printf("    1. 每个成员的偏移量，必须是它自身大小的整数倍；不够就补空字节\n");
    printf("    2. 结构体总大小，必须是最大成员大小的整数倍\n");
    printf("  软考问 sizeof(struct) 时，按这两条算，不能简单相加。\n");

    return 0;
}
