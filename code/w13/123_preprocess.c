/* 123_preprocess.c —— 条件编译与预定义宏
 *
 * 预处理阶段做的事：去掉注释、展开 #include、替换宏、处理条件编译。
 * 它是「文本层面」的操作，完全不懂 C 语法。
 *
 * 编译时可以用 -D 定义宏，观察不同分支：
 *   gcc -std=c17 -DDEBUG -o 123 123_preprocess.c && ./123
 */

#include <stdio.h>

/* ---------- ① 头文件保护（include guard）---------- */
/* 正式头文件必须写这三行，防止同一个文件被包含两次导致重复定义 */
#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int id;
    char name[20];
} Student_t;

#endif /* STUDENT_H */

/* ---------- ② 调试开关：最常用的条件编译 ---------- */
/* 用 -DDEBUG 打开；不开的时候，所有 DBG 语句在预处理阶段就被删掉了，
   不产生任何运行时代价 —— 这是它优于 if (debug) 的地方 */

#ifdef DEBUG
    #define DBG(fmt, ...)  printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define DBG(fmt, ...)  ((void)0)     /* 展开成空语句 */
#endif

/* ---------- ③ 平台相关代码 ---------- */
#ifdef _WIN32
    #define PLATFORM "Windows"
#elif defined(__linux__)
    #define PLATFORM "Linux"
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
#else
    #define PLATFORM "未知平台"
#endif

/* ---------- ④ 用宏做「编译期断言」 ---------- */
#define STATIC_ASSERT(cond, msg) typedef char static_assert_##msg[(cond) ? 1 : -1]

/* 编译期检查：int 必须是 4 字节。如果是 2 字节，这行会编译失败 */
STATIC_ASSERT(sizeof(int) == 4, int_must_be_4_bytes);

/* ---------- ⑤ 版本号条件编译 ---------- */
#define VERSION 2

int main(void)
{
    /* ---------- ① 预定义宏 ---------- */
    printf("=== ① 编译器给你的预定义宏 ===\n");
    printf("  __FILE__  = %s\n", __FILE__);
    printf("  __LINE__  = %d（这行的行号）\n", __LINE__);
    printf("  __DATE__  = %s\n", __DATE__);
    printf("  __TIME__  = %s\n", __TIME__);
    printf("  __func__  = %s\n", __func__);
    printf("  __STDC__  = %d\n", __STDC__);
    printf("  __STDC_VERSION__ = %ldL（201710 = C17）\n", __STDC_VERSION__);

    printf("\n  ⭐ __LINE__ 是排查问题的利器：\n");
    printf("     #define LOG(msg) printf(\"[%%s:%%d] %%s\\n\", __FILE__, __LINE__, msg)\n");
    printf("     每条日志自动带文件名和行号。\n");

    /* ---------- ② 调试开关 ---------- */
    printf("\n=== ② 调试开关 ===\n");
#ifdef DEBUG
    printf("  DEBUG 已定义，调试输出会生效\n");
#else
    printf("  DEBUG 未定义，DBG 展开成 ((void)0)，一行都不会输出\n");
#endif

    int x = 42;
    DBG("x 的值 = %d", x);
    DBG("这行在未定义 DEBUG 时完全消失");

    /* 不开 DEBUG 时 x 没被用过，编译器会警告 unused variable。
       加这一句告诉编译器「我知道，故意不用」—— 这也算一个小技巧。 */
    (void)x;

    printf("\n  重新编译试试：\n");
    printf("    gcc -std=c17 -DDEBUG -o 123 123_preprocess.c && ./123\n");

    /* ---------- ③ 平台判断 ---------- */
    printf("\n=== ③ 当前平台 ===\n");
    printf("  PLATFORM = %s\n", PLATFORM);

    /* ---------- ④ 版本分支 ---------- */
    printf("\n=== ④ 按版本走不同代码 ===\n");
    printf("  VERSION = %d\n", VERSION);
#if VERSION >= 2
    printf("  VERSION >= 2：启用新接口\n");
#elif VERSION == 1
    printf("  VERSION == 1：使用旧接口\n");
#else
    printf("  VERSION 无效\n");
#endif

    /* ---------- ⑤ 条件编译 vs if ---------- */
    printf("\n=== ⑤ 条件编译 和 if 的本质区别 ===\n");
    printf("  %-14s %-24s %s\n", "", "#if", "if");
    printf("  %-14s %-24s %s\n", "处理时机", "预处理（编译前）", "运行时");
    printf("  %-14s %-24s %s\n", "不成立的代码", "根本不进编译", "编译了，只是不执行");
    printf("  %-14s %-24s %s\n", "类型检查", "不做", "做");
    printf("  %-14s %-24s %s\n", "运行开销", "没有", "一次判断");

    printf("\n  ⭐ 所以「平台相关代码」必须用 #if：\n");
    printf("     Windows 的 API 在 Linux 上根本不存在，\n");
    printf("     写成 if (isWindows) { 调WindowsAPI(); } 会编译失败。\n");

    /* ---------- ⑥ #undef ---------- */
    printf("\n=== ⑥ #undef 取消宏 ===\n");
#define TEMP 100
    printf("  TEMP = %d\n", TEMP);
#undef TEMP
#ifdef TEMP
    printf("  TEMP 还在\n");
#else
    printf("  已 #undef，TEMP 不再存在（再用会报「未声明」）\n");
#endif

    /* ---------- ⑦ 预处理不懂语法 ---------- */
    printf("\n=== ⑦ 预处理是纯文本操作 ===\n");
#define BAD_MACRO int x = 1
    printf("  #define BAD_MACRO int x = 1 —— 宏体可以是半句语句\n");
    printf("  预处理阶段不检查它是不是合法 C，只有展开后才由编译器管\n");
    printf("  所以宏写错时，报错信息常指向展开后的位置，非常难读\n");

    printf("\n  ⭐ 这也是为什么「宏要短、要带括号、要用大写命名」：\n");
    printf("     大写是为了让人一眼看出这是宏，不是函数。\n");

    return 0;
}
