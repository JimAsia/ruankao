/* 94_pointer_array_ptr.c —— 指针数组 vs 数组指针
 *
 * 这两个名字只差一个字，含义完全不同：
 *   指针数组：是一个数组，元素是指针      int *a[10]
 *   数组指针：是一个指针，指向一个数组    int (*b)[10]
 *
 * 读法的关键是「先看变量名和谁结合」。
 */

#include <stdio.h>

int main(void)
{
    /* ---------- ① 指针数组 ---------- */
    printf("=== ① 指针数组 int *a[3] ===\n");

    int x = 10, y = 20, z = 30;
    int *a[3] = {&x, &y, &z};           /* 3 个元素，每个都是 int* */

    printf("  a 是个数组，有 3 个元素，每个元素都是指针\n");
    printf("  sizeof(a)      = %zu 字节（3 × 8）\n", sizeof(a));
    printf("  sizeof(a[0])   = %zu 字节（一个指针）\n", sizeof(a[0]));

    printf("  各个元素指向：\n");
    for (int i = 0; i < 3; i++) {
        printf("    *a[%d] = %d\n", i, *a[i]);
    }

    /* 最常用法：字符串数组 */
    const char *names[3] = {"Alice", "Bob", "Cathy"};
    printf("  实际最常用它存字符串：");
    for (int i = 0; i < 3; i++) printf("%s ", names[i]);
    printf("\n");

    /* ---------- ② 数组指针 ---------- */
    printf("\n=== ② 数组指针 int (*b)[4] ===\n");

    int m[2][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    int (*b)[4] = m;                    /* b 指向「含 4 个 int 的数组」 */

    printf("  b 是个指针，指向「int[4]」这种类型\n");
    printf("  sizeof(b)      = %zu 字节（它是一个指针）\n", sizeof(b));
    printf("  sizeof(*b)     = %zu 字节（它指向的东西：4 个 int）\n", sizeof(*b));

    printf("  用 b 访问二维数组：\n");
    for (int i = 0; i < 2; i++) {
        printf("    ");
        for (int j = 0; j < 4; j++) {
            printf("%d ", b[i][j]);     /* b[i] 就是第 i 行 */
        }
        printf("\n");
    }
    printf("  ⚠️ b[i] 的类型是 int[4]，所以 b[i][j] 才合法\n");

    /* ---------- ③ 怎么读这两种声明 ---------- */
    printf("\n=== ③ 读声明的口诀 ===\n");
    printf("  规则：从变量名开始，先看右边，再看左边；括号优先\n");
    printf("\n");
    printf("  int *a[10];\n");
    printf("      a 先和 [10] 结合 → a 是数组\n");
    printf("      再和 * 结合      → 元素是指针\n");
    printf("      结论：a 是「10 个 int* 的数组」 = 指针数组\n");
    printf("\n");
    printf("  int (*b)[10];\n");
    printf("      括号先        → b 是指针\n");
    printf("      指向 int[10]  → 指向「10 个 int 的数组」\n");
    printf("      结论：b 是「指向 int[10] 的指针」 = 数组指针\n");

    /* ---------- ④ 优先级演示 ---------- */
    printf("\n=== ④ 为什么括号不能省 ===\n");
    printf("  [] 的优先级高于 *\n");
    printf("  所以 int *a[10]   中 a 先被 [] 拿走 → 数组\n");
    printf("  想让它是指针，必须用括号把 * 提前：int (*b)[10]\n");
    printf("  ⚠️ int *b[10] 和 int (*b)[10] 是完全不同的两个类型\n");

    /* ---------- ⑤ 二维数组作参数时到底传的是什么 ---------- */
    printf("\n=== ⑤ 二维数组传参的真相 ===\n");
    printf("  int m[2][4] 的数组名 m，类型是 int (*)[4]\n");
    printf("  所以函数参数写 int m[][4]，等价于 int (*m)[4]\n");
    printf("  这就是为什么列数不能省 —— 它是指针类型的一部分\n");

    return 0;
}
