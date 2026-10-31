/* 83_pointer_array.c —— 指针与数组
 *
 * 核心一句话：数组名就是首元素的地址。
 * 由此推出：a[i] 等价于 *(a + i)。
 */

#include <stdio.h>

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};

    /* ---------- ① 数组名就是首地址 ---------- */
    printf("=== ① 数组名 = 首元素地址 ===\n");
    printf("  a       = %p\n", (void *)a);
    printf("  &a[0]   = %p\n", (void *)&a[0]);
    printf("  两者完全相同\n");

    /* ---------- ② 三种访问元素的方式 ---------- */
    printf("\n=== ② 三种写法完全等价 ===\n");
    printf("  下标法   指针法      指针运算\n");
    for (int i = 0; i < 5; i++) {
        printf("  a[%d]=%-3d  p[%d]=%-3d   *(a+%d)=%-3d\n",
               i, a[i],
               i, (&a[0])[i],         /* 指针用下标 */
               i, *(a + i));          /* 指针运算 */
    }
    printf("\n  a[i]、*(a+i)、p[i] 三者等价，编译器生成一样的代码\n");

    /* ---------- ③ 用指针遍历 ---------- */
    printf("=== ③ 用指针遍历 ===\n");

    /* 方式一：指针变量一步步走 */
    printf("  方式一（p++）：");
    for (int *p = a; p < a + 5; p++) {
        printf("%d ", *p);
    }
    printf("\n");

    /* 方式二：指针 + 下标 */
    printf("  方式二（p[i]）：");
    int *p = a;
    for (int i = 0; i < 5; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");

    /* 方式三：直接用数组名 */
    printf("  方式三（a[i]）：");
    for (int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("  三种都能用。日常用 a[i] 最清楚，处理链表时才必须用指针\n");

    /* ---------- ④ 指针运算：加 1 走几字节 ---------- */
    printf("\n=== ④ 指针 + 1 到底走多远 ===\n");
    printf("  sizeof(int) = %zu\n", sizeof(int));
    printf("  &a[0] = %p\n", (void *)&a[0]);
    printf("  &a[1] = %p\n", (void *)&a[1]);
    printf("  差 %ld 字节 —— 正好是一个 int 的大小\n",
           (long)((char *)&a[1] - (char *)&a[0]));
    printf("  ⚠️ 指针 +1 走的是【一个元素】的距离，不是 1 字节\n");
    printf("     这正是「指针类型」的意义所在\n");

    /* ---------- ⑤ 数组名不能改，指针可以 ---------- */
    printf("\n=== ⑤ 数组名 vs 指针变量 ===\n");
    printf("  a    是常量地址，a = p 或 a++ 都是编译错误\n");
    printf("  p    是变量，p = a + 2 或 p++ 都合法\n");

    p = a + 2;
    printf("  执行 p = a + 2 之后：*p = %d（就是 a[2]）\n", *p);
    p++;
    printf("  再 p++ 之后：*p = %d（就是 a[3]）\n", *p);

    /* ---------- ⑥ 数组作参数的真相 ---------- */
    printf("\n=== ⑥ 为什么函数里 sizeof 拿不到数组大小 ===\n");
    printf("  数组作参数时会【退化】成指针\n");
    printf("  int arr[] 在参数位置上等价于 int *arr\n");
    printf("  所以函数内 sizeof(arr) 是 8（指针大小），不是数组大小\n");
    printf("  这就是为什么每个数组函数都要多传一个长度参数\n");

    return 0;
}
