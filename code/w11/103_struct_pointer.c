/* 103_struct_pointer.c —— 结构体指针与 -> 运算符
 *
 * 三个核心：
 *   1. p->score 就是 (*p).score 的简写（而且 . 优先级高于 *，括号不能省）
 *   2. 结构体作参数：传值 = 整个拷贝，传指针 = 只传 8 字节
 *   3. 结构体可以整体返回，数组不行
 */

#include <stdio.h>
#include <string.h>

struct Student {
    int    id;
    char   name[20];
    double score;
};

/* ---------- 传值：函数内的修改不影响外面 ---------- */
void addScoreByValue(struct Student s, double add)
{
    s.score += add;
    printf("  函数内（传值）：score = %.1f\n", s.score);
}

/* ---------- 传指针：能改到外面 ---------- */
void addScoreByPointer(struct Student *p, double add)
{
    p->score += add;                        /* 等价于 (*p).score += add */
    printf("  函数内（传指针）：score = %.1f\n", p->score);
}

/* ---------- 只读访问：加 const，防止误改 ---------- */
void printStudent(const struct Student *p)
{
    printf("  %d %s %.1f\n", p->id, p->name, p->score);
    /* p->score = 0;    ← ❌ 加了 const 就改不了，编译期报错 */
}

/* ---------- 结构体可以整体返回（数组不行） ---------- */
struct Student makeStudent(int id, const char *name, double score)
{
    struct Student s;
    s.id = id;
    strcpy(s.name, name);                   /* 不能用 = */
    s.score = score;
    return s;                               /* ✅ 合法：整个结构体拷贝返回 */
}

int main(void)
{
    struct Student s = {2026001, "张三", 92.5};

    /* ---------- ① 定义结构体指针 ---------- */
    printf("=== ① 结构体指针 ===\n");
    struct Student *p = &s;                 /* & 取结构体地址 */

    printf("  s.score      = %.1f\n", s.score);
    printf("  (*p).score   = %.1f   ← 先解引用再取成员，括号不能省\n", (*p).score);
    printf("  p->score     = %.1f   ← 上面那行的简写，最常用\n", p->score);
    printf("  sizeof(p)    = %zu 字节（指针本身）\n", sizeof(p));
    printf("  sizeof(*p)   = %zu 字节（指向的对象）\n", sizeof(*p));

    printf("\n  ⚠️ *p.score 是错的：. 的优先级高于 *，会被理解成 *(p.score)\n");
    printf("     而 p 是结构体指针，没有 score 成员 —— 编译直接报错\n");

    /* ---------- ② 传值 vs 传指针 ---------- */
    printf("\n=== ② 传值 vs 传指针 ===\n");
    printf("  调用前：score = %.1f\n", s.score);

    addScoreByValue(s, 5);
    printf("  传值返回后：score = %.1f  ← 没变\n", s.score);

    addScoreByPointer(&s, 5);
    printf("  传指针返回后：score = %.1f  ← 变了\n", s.score);

    printf("\n  ⭐ 这就是 W7 那个 swap 问题的同一个道理：\n");
    printf("     要让函数改到外面的变量，必须传地址。\n");

    /* ---------- ③ 为什么要用指针传结构体 ---------- */
    printf("\n=== ③ 传值到底贵在哪 ===\n");
    printf("  struct Student 占 %zu 字节\n", sizeof(struct Student));
    printf("  传值：每次调用拷贝 %zu 字节\n", sizeof(struct Student));
    printf("  传指针：每次调用拷贝 %zu 字节\n", sizeof(struct Student *));
    printf("\n  如果这个结构体是嵌套的（结构体里套结构体），\n");
    printf("  比如学生表里带 10 门课成绩，可能几百字节，\n");
    printf("  一次排序要调用交换函数上万次，差别就出来了。\n");
    printf("\n  ⭐ 工程惯例：结构体作参数，一律传指针 + const\n");
    printf("     只有「需要修改」时才去掉 const\n");

    /* ---------- ④ 结构体可以返回 ---------- */
    printf("\n=== ④ 结构体可以整体返回 ===\n");
    struct Student s2 = makeStudent(2026002, "李四", 88.0);
    printStudent(&s2);

    printf("\n  ⚠️ 数组不能这样返回！\n");
    printf("     数组名作返回值，返回的是局部数组的地址，函数结束就失效\n");
    printf("     结构体整体返回是「值拷贝」，安全\n");

    /* ---------- ⑤ 指针遍历结构体数组 ---------- */
    printf("\n=== ⑤ 用指针遍历结构体数组 ===\n");
    struct Student arr[3] = {
        {2026003, "王五", 96.5},
        {2026004, "赵六", 65.0},
        {2026005, "钱七", 88.0}
    };

    /* 写法一：下标 */
    printf("  [下标写法]\n");
    for (int i = 0; i < 3; i++) {
        printf("    %s %.1f\n", arr[i].name, arr[i].score);
    }

    /* 写法二：指针 */
    printf("  [指针写法]\n");
    for (struct Student *q = arr; q < arr + 3; q++) {
        printf("    %s %.1f\n", q->name, q->score);
    }

    printf("\n  ⭐ q++ 走的是 sizeof(struct Student) = %zu 字节，不是 1 字节\n",
           sizeof(struct Student));
    printf("     指针类型决定步长 —— 和 W9 讲的完全一致\n");

    return 0;
}
