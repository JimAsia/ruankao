/* 122_macro.c —— 宏：文本替换的艺术与陷阱
 *
 * 宏不是函数，是【预处理阶段的文本替换】。编译器根本没见到宏。
 * 这一句话解释了宏的所有坑。
 */

#include <stdio.h>

/* ---------- ① 常量宏 ---------- */
#define PI       3.14159
#define MAXN     100
#define NAME     "软考程序员"

/* ---------- ② 带参宏：括号决定生死 ---------- */
#define SQ_BAD(x)    x * x                  /* ❌ 参数没括号 */
#define SQ_OK(x)     ((x) * (x))            /* ✅ 参数 + 整体都裹住 */

#define ADD_BAD(x, y)   (x) + (y)           /* ❌ 只有参数括号 */
#define ADD_OK(x, y)    ((x) + (y))         /* ✅ 整体也裹住 */

/* ---------- ③ do-while(0) 包裹多语句 ---------- */
#define SWAP(a, b) do {          \
    int _t = (a);                \
    (a) = (b);                   \
    (b) = _t;                    \
} while (0)

/* ---------- ④ # 转字符串，## 拼接 ---------- */
#define STR(x)      #x
#define CAT(a, b)   a##b

/* ---------- ⑤ 带副作用的参数 ---------- */
#define TWICE(x)    ((x) + (x))

int g_calls = 0;
int bump(void) { g_calls++; return 1; }

/* 对照：函数版，参数只求值一次 */
int twice_func(int x) { return x + x; }

int main(void)
{
    /* ---------- ① 常量宏 ---------- */
    printf("=== ① 常量宏 ===\n");
    printf("  PI = %.5f, MAXN = %d, NAME = %s\n", PI, MAXN, NAME);
    printf("\n  ⚠️ 宏没有类型，也不需要分号\n");
    printf("     如果写成 #define MAXN 100;\n");
    printf("     那么 MAXN * 2 会展开成 100; * 2 —— 直接编译错误\n");

    /* ---------- ② 括号陷阱 ---------- */
    printf("\n=== ② 括号陷阱（本节最重要）===\n");

    int a = 3;
    printf("  SQ_BAD(a + 1) = %d    ← 展开成 a + 1 * a + 1 = 3 + 3 + 1\n",
           SQ_BAD(a + 1));
    printf("  SQ_OK (a + 1) = %d   ← 展开成 ((a + 1) * (a + 1))\n",
           SQ_OK(a + 1));
    printf("  ⭐ 期望都是 16，SQ_BAD 却给出 %d\n", SQ_BAD(a + 1));

    printf("\n  只给参数加括号还不够：\n");
    printf("  2 * ADD_BAD(1, 2) = %d   ← 展开成 2 * (1) + (2)\n",
           2 * ADD_BAD(1, 2));
    printf("  2 * ADD_OK (1, 2) = %d   ← 展开成 2 * ((1) + (2))\n",
           2 * ADD_OK(1, 2));

    printf("\n  ⭐ 两条规矩：\n");
    printf("     1. 每个参数都要用括号裹住\n");
    printf("     2. 整个表达式还要再裹一层（防止和外面的运算符打架）\n");

    /* ---------- ③ 多语句宏必须 do-while(0) ---------- */
    printf("\n=== ③ do-while(0) 包裹多语句 ===\n");
    int m = 1, n = 2;
    printf("  交换前：m = %d, n = %d\n", m, n);

    if (m < n) SWAP(m, n);              /* 带分号调用，也正确 */
    printf("  交换后：m = %d, n = %d\n", m, n);

    printf("\n  ⭐ 如果 SWAP 只用 { } 包裹而不套 do-while(0)：\n");
    printf("     if (m < n) SWAP(m, n);\n");
    printf("     展开后 {} 后面的分号变成一条空语句，\n");
    printf("     紧跟其后的 else 就会「找不到配对的 if」，编译报错。\n");
    printf("     do { ... } while (0) 让整体成为一条完整语句，\n");
    printf("     调用处的分号正好结束这个 do-while。\n");

    /* ---------- ④ # 和 ## ---------- */
    printf("\n=== ④ # 转字符串 / ## 拼接 ===\n");
    printf("  STR(hello)  = %s\n", STR(hello));
    printf("  STR(1 + 2)  = %s   ← 原样变字符串，不计算\n", STR(1 + 2));
    printf("  STR(MAXN)   = %s   ← 不会展开成 100！这就是 # 的规矩\n", STR(MAXN));

    int CAT(my, var) = 42;
    printf("  CAT(my, var) 拼出变量名 myvar = %d\n", myvar);

    printf("\n  ⭐ # 的实际用途：调试时打印表达式本身\n");
    printf("     #define SHOW(x) printf(#x \" = %%d\\n\", x)\n");
    printf("     SHOW(a + 1) 输出：a + 1 = 4\n");

    /* ---------- ⑤ 参数被求值多次 ---------- */
    printf("\n=== ⑤ 参数可能被求值多次 ===\n");

    g_calls = 0;
    int r1 = twice_func(bump());
    printf("  函数版：参数求值 %d 次，结果 %d\n", g_calls, r1);

    g_calls = 0;
    int r2 = TWICE(bump());            /* 展开成 bump() + bump() */
    printf("  宏版  ：参数求值 %d 次，结果 %d\n", g_calls, r2);

    printf("\n  ⭐ 宏的参数被替换到每个出现的位置，出现两次就求值两次。\n");
    printf("     所以 #define MAX(a,b) ((a)>(b)?(a):(b)) 是有风险的：\n");
    printf("     MAX(i++, j) 会让 i 加两次，标准里属于未定义行为。\n");
    printf("     需要这种功能，用 static inline 函数代替。\n");

    /* ---------- ⑥ 宏 vs 函数 ---------- */
    printf("\n=== ⑥ 宏 vs 函数 ===\n");
    printf("  %-12s %-24s %s\n", "对比项", "宏", "函数");
    printf("  %-12s %-24s %s\n", "处理阶段", "预处理（编译前替换）", "编译后调用");
    printf("  %-12s %-24s %s\n", "类型检查", "没有", "有");
    printf("  %-12s %-24s %s\n", "参数求值", "可能多次", "只一次");
    printf("  %-12s %-24s %s\n", "运行开销", "无", "有栈帧开销");
    printf("  %-12s %-24s %s\n", "调试", "看不到符号", "能打断点");
    printf("  %-12s %-24s %s\n", "代码体积", "每次展开各一份", "只一份");

    printf("\n  ⭐ 现代 C 的取舍：\n");
    printf("     小工具（MAX、SQ）  → static inline 函数，安全且无开销\n");
    printf("     需要文本能力（#、##）→ 只能用宏\n");
    printf("     常量              → const 变量 或 enum，类型更安全\n");

    return 0;
}
