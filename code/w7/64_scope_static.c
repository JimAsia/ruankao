/* 64_scope_static.c —— 作用域、生命周期、static
 */

#include <stdio.h>

/* ---------- 全局变量：整个文件可见，程序结束才销毁 ---------- */
int gCount = 0;
int gDefault;               /* 不初始化时，全局变量自动为 0 */

void incrementGlobal(void)
{
    gCount++;
}

/* ---------- static 局部：只初始化一次，函数退出后仍保留 ---------- */
int nextId(void)
{
    static int id = 0;      /* ⚠️ 这行只在第一次调用时执行 */
    id++;
    return id;
}

/* 对比：普通局部变量每次调用都从头开始 */
int nextIdBad(void)
{
    int id = 0;             /* 每次进来都重新置 0 */
    id++;
    return id;
}

/* ---------- 变量遮蔽 ---------- */
int shadow = 100;           /* 全局 */

void showShadow(void)
{
    printf("    全局 shadow = %d\n", shadow);

    int shadow = 50;        /* 局部变量把全局盖住了 */
    printf("    局部 shadow = %d（同名的局部优先）\n", shadow);
}

int main(void)
{
    /* ---------- ① 局部变量的作用域 ---------- */
    printf("=== ① 局部变量：出了大括号就没了 ===\n");
    {
        int inner = 10;
        printf("  块内：inner = %d\n", inner);
    }
    printf("  块外再访问 inner 会编译错误，所以这里没法演示\n");
    printf("  这就是作用域：名字只在声明它的那对大括号里有效\n");

    /* ---------- ② 全局变量 ---------- */
    printf("\n=== ② 全局变量 ===\n");
    printf("  gDefault = %d（没初始化，但自动是 0）\n", gDefault);
    printf("  调用 incrementGlobal 之前 gCount = %d\n", gCount);
    incrementGlobal();
    incrementGlobal();
    printf("  调用两次后 gCount = %d\n", gCount);
    printf("  全局变量能被任何函数修改，所以能跨函数记住状态\n");
    printf("  ⚠️ 也正因为如此，全局变量多了很难追踪谁改的 —— 少用\n");

    /* ---------- ③ static 局部：函数的记忆 ---------- */
    printf("\n=== ③ static 局部变量（重点）===\n");

    /* ⚠️ 必须分开调用！写在同一个 printf 里，三个函数谁先执行
     *    C 标准没有规定（未定义行为），结果可能不符合预期。 */
    int a1 = nextId();
    int a2 = nextId();
    int a3 = nextId();
    printf("  连续调用 nextId() 三次：%d, %d, %d\n", a1, a2, a3);
    printf("  值是 1、2、3 —— 因为 static int id 只初始化一次，之后一直保留\n");

    int b1 = nextIdBad();
    int b2 = nextIdBad();
    int b3 = nextIdBad();
    printf("\n  对比 nextIdBad() 三次：%d, %d, %d\n", b1, b2, b3);
    printf("  永远是 1、1、1 —— 因为每次调用都重新执行 int id = 0\n");

    printf("\n  ⚠️ 这就是「同一个 printf 里多次调用带副作用的函数」的坑：\n");
    printf("     printf(\"%%d %%d\", f(), g()) 的求值顺序 C 标准没规定，\n");
    printf("     所以上面的调用都拆成独立语句，结果才可靠。\n");

    /* ---------- ④ 变量遮蔽 ---------- */
    printf("\n=== ④ 变量遮蔽 ===\n");
    showShadow();
    printf("    函数返回后，全局 shadow 仍是 %d（没被改）\n", shadow);

    /* ---------- ⑤ 四种存储类别对照 ---------- */
    printf("\n=== ⑤ 存储类别对照 ===\n");
    printf("  %-14s %-14s %-16s %s\n", "类别", "作用域", "生命周期", "默认初值");
    printf("  %-14s %-14s %-16s %s\n", "局部变量", "函数内", "函数调用期间", "不确定");
    printf("  %-14s %-14s %-16s %s\n", "static 局部", "函数内", "整个程序", "0");
    printf("  %-14s %-14s %-16s %s\n", "全局变量", "本文件全部", "整个程序", "0");
    printf("  %-14s %-14s %-16s %s\n", "extern 全局", "跨文件", "整个程序", "—");

    printf("\n  ⚠️ 只记住两条：\n");
    printf("     ① 局部变量不初始化是垃圾值，全局和 static 是 0\n");
    printf("     ② static 修饰局部 = 记住值；static 修饰全局/函数 = 只本文件可见\n");

    return 0;
}
