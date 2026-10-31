/* 95_const_pointer.c —— const 与指针的四种组合
 *
 * 这是最容易搞混的一组。诀窍：看 const 在 * 的哪一边。
 *   const 在 * 左边 → 指向的值不能改
 *   const 在 * 右边 → 指针本身不能改
 */

#include <stdio.h>

int main(void)
{
    int a = 10, b = 20;

    /* ---------- ① 指向常量的指针（值不能改） ---------- */
    printf("=== ① const int *p —— 值不能改 ===\n");

    const int *p1 = &a;
    printf("  *p1 = %d\n", *p1);

    /* *p1 = 99;         ❌ 编译错误：不能通过 p1 改值 */

    p1 = &b;                    /* ✅ 可以改指向 */
    printf("  p1 = &b 之后，*p1 = %d（改指向是可以的）\n", *p1);

    printf("  读法：const 在 * 左边 → 「指向的东西是常量」\n");

    /* ---------- ② 指针常量（指向不能改） ---------- */
    printf("\n=== ② int * const p —— 指向不能改 ===\n");

    int *const p2 = &a;
    printf("  *p2 = %d\n", *p2);

    *p2 = 99;                   /* ✅ 可以改值 */
    printf("  *p2 = 99 之后，a = %d（改值是可以的）\n", a);

    /* p2 = &b;          ❌ 编译错误：p2 是常量，不能改指向 */

    printf("  读法：const 在 * 右边 → 「指针自己是常量」\n");

    /* ---------- ③ 两者都不能改 ---------- */
    printf("\n=== ③ const int * const p —— 都不能改 ===\n");

    const int *const p3 = &a;
    printf("  *p3 = %d\n", *p3);
    /* *p3 = 5;   ❌ */
    /* p3 = &b;   ❌ */
    printf("  读法：两边都有 const → 完全锁死\n");

    /* ---------- ④ 四组对照表 ---------- */
    printf("\n=== ④ 四种写法一览 ===\n");
    printf("  %-24s %-16s %s\n", "写法", "能否改 *p", "能否改 p");
    printf("  %-24s %-16s %s\n", "int *p", "✅ 能", "✅ 能");
    printf("  %-24s %-16s %s\n", "const int *p", "❌ 不能", "✅ 能");
    printf("  %-24s %-16s %s\n", "int * const p", "✅ 能", "❌ 不能");
    printf("  %-24s %-16s %s\n", "const int * const p", "❌ 不能", "❌ 不能");

    /* ---------- ⑤ 实际用途 ---------- */
    printf("\n=== ⑤ 实际怎么用 ===\n");

    int arr[5] = {1, 2, 3, 4, 5};

    /* 只读函数参数：承诺不改调用者的数据 */
    const int *rp = arr;
    printf("  只读遍历：");
    for (int i = 0; i < 5; i++) printf("%d ", rp[i]);
    printf("\n");

    /* 字符串字面量：必须用 const char* */
    const char *msg = "Hello";
    printf("  字符串字面量：%s（必须用 const char*）\n", msg);

    /* 常量指针：指向固定位置，防止误改 */
    int *const fixed = &a;
    printf("  常量指针 fixed 永远指向 a\n");
    (void)fixed;

    /* ---------- ⑥ 记忆口诀 ---------- */
    printf("\n=== ⑥ 一句口诀 ===\n");
    printf("  看 const 在星号左边还是右边：\n");
    printf("    左边（const int *p）  → 锁【值】\n");
    printf("    右边（int * const p） → 锁【指针】\n");
    printf("    两边都有              → 全锁\n");

    printf("\n  另一种读法：从右往左读\n");
    printf("    const int *p        → p is a pointer to const int\n");
    printf("    int * const p       → p is a const pointer to int\n");

    return 0;
}
