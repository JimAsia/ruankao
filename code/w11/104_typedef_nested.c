/* 104_typedef_nested.c —— typedef / 嵌套结构体 / 枚举 / 共用体
 *
 * 这四个是结构体的四个搭档，软考选择题常考它们的大小和取值。
 */

#include <stdio.h>
#include <string.h>

/* ---------- ① typedef：给类型起别名 ---------- */
struct Student {
    int    id;
    char   name[20];
    double score;
};

typedef struct Student Student;            /* 老写法：先定义再起别名 */

/* 更常见的合并写法 */
typedef struct {
    int   year;
    int   month;
    int   day;
} Date;

typedef unsigned int uint;                 /* 基本类型也能起别名 */

/* ---------- ② 嵌套结构体 ---------- */
typedef struct {
    int   id;
    char  name[20];
    Date  birthday;                        /* 结构体作成员 */
    double scores[3];                      /* 数组作成员 */
} Person;

/* ---------- ③ 枚举：本质是 int ---------- */
enum Weekday {
    MON = 1,                               /* 从 1 开始 */
    TUE, WED, THU, FRI, SAT, SUN           /* 依次 +1 */
};

enum Color {
    RED,                                   /* 不写就从 0 开始 */
    GREEN = 5,                             /* 手动跳到 5 */
    BLUE                                   /* 接着就是 6 */
};

enum Status {
    OK = 0,
    ERR_FILE = -1,
    ERR_MEM  = -2
};

/* ---------- ④ 共用体：所有成员共用一块内存 ---------- */
union Data {
    int    i;                              /* 4 字节 */
    float  f;                              /* 4 字节 */
    char   c[8];                           /* 8 字节 */
};

int main(void)
{
    /* ---------- ① typedef 的效果 ---------- */
    printf("=== ① typedef ===\n");
    Student s1 = {2026001, "张三", 92.5};  /* 不用写 struct 了 */
    uint    n  = 4000000000u;

    printf("  Student s1 = {%d, %s, %.1f}\n", s1.id, s1.name, s1.score);
    printf("  uint n = %u（能到 42 亿，int 只能到 21 亿）\n", n);
    printf("\n  ⭐ typedef 只是起别名，不产生新类型。\n");
    printf("     Student 和 struct Student 是两个名字、同一个类型，\n");
    printf("     编译器完全当成一样的东西处理。\n");

    /* ---------- ② 嵌套结构体 ---------- */
    printf("\n=== ② 嵌套结构体 ===\n");
    Person p = {
        .id = 2026002,
        .name = "李四",
        .birthday = {2008, 3, 15},
        .scores = {88.0, 92.5, 79.0}
    };

    printf("  %s 生日 %d-%02d-%02d\n",
           p.name, p.birthday.year, p.birthday.month, p.birthday.day);
    printf("  三门成绩：%.1f %.1f %.1f\n",
           p.scores[0], p.scores[1], p.scores[2]);
    printf("  嵌套后整个结构体占 %zu 字节\n", sizeof(Person));
    printf("\n  ⚠️ 访问嵌套成员要一层一层点：p.birthday.year\n");
    printf("     不是写成 p.year —— 那是另一个成员，编译报错\n");

    /* ---------- ③ 枚举 ---------- */
    printf("\n=== ③ 枚举 ===\n");
    printf("  MON = %d, TUE = %d, SUN = %d\n", MON, TUE, SUN);
    printf("  RED = %d, GREEN = %d, BLUE = %d\n", RED, GREEN, BLUE);
    printf("  OK = %d, ERR_FILE = %d, ERR_MEM = %d\n", OK, ERR_FILE, ERR_MEM);
    printf("  sizeof(enum Weekday) = %zu 字节（就是 int 的大小）\n",
           sizeof(enum Weekday));

    printf("\n  枚举变量的用法：\n");
    enum Weekday today = WED;
    if (today == WED) {
        printf("    today == WED 成立（today = %d）\n", today);
    }
    printf("\n  ⭐ 枚举的三个考点：\n");
    printf("     1. 默认从 0 开始，逐个 +1\n");
    printf("     2. 可以手动赋值，后面的接着 +1（GREEN=5 → BLUE=6）\n");
    printf("     3. 本质是 int，sizeof 是 4，能和整数直接比较\n");

    /* 用枚举当 switch 的分支，比数字可读性好得多 */
    printf("\n  枚举配 switch：\n");
    enum Status st = ERR_FILE;
    switch (st) {
        case OK:       printf("    成功\n"); break;
        case ERR_FILE: printf("    文件错误（code %d）\n", st); break;
        case ERR_MEM:  printf("    内存错误（code %d）\n", st); break;
        default:       printf("    未知错误\n"); break;
    }

    /* ---------- ④ 共用体 ---------- */
    printf("\n=== ④ 共用体 ===\n");
    printf("  union Data 占 %zu 字节 = 最大成员的大小\n", sizeof(union Data));
    printf("  （int 4、float 4、char[8] 8 → 取最大 8）\n");

    union Data d;
    d.i = 0x41424344;
    printf("\n  d.i = 0x41424344 之后：\n");
    printf("    d.i = 0x%X\n", d.i);
    printf("    d.c = %c%c%c%c  ← 同一块内存，按 char 读出来\n",
           d.c[0], d.c[1], d.c[2], d.c[3]);
    printf("\n  然后写 d.f = 3.14f：\n");
    d.f = 3.14f;
    printf("    d.f = %.2f\n", d.f);
    printf("    d.i = %d  ← 已经被踩坏，原来的 0x41424344 没了\n", d.i);

    printf("\n  ⭐ 共用体三个成员共用同一块内存，同一时刻只能用一个\n");
    printf("     写一个成员，其他成员的值就失效了\n");
    printf("     和结构体的区别：\n");
    printf("       结构体 struct：各成员各占位置，总大小 ≈ 之和\n");
    printf("       共用体 union ：各成员叠在一起，总大小 = 最大成员\n");

    /* ---------- ⑤ 结构体 vs 共用体，一张表说清 ---------- */
    printf("\n=== ⑤ 对比 ===\n");
    struct S { int i; double d; };
    union  U { int i; double d; };
    printf("  %-22s %-10s %s\n", "类型", "大小", "特点");
    printf("  %-22s %-10zu %s\n", "struct { int; double; }", sizeof(struct S), "成员各占位置");
    printf("  %-22s %-10zu %s\n", "union  { int; double; }", sizeof(union U),  "成员共用一块");
    printf("\n  软考常问：这两个 sizeof 各是多少 —— 答案是 %zu 和 %zu\n",
           sizeof(struct S), sizeof(union U));

    return 0;
}
