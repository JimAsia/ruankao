/* 75_recursion_cost.c —— 递归的代价与转换
 */

#include <stdio.h>

/* ---------- ① 递归深度：栈空间是有限的 ---------- */
int depthOf(int n)
{
    if (n == 0) return 0;
    /* 每层递归都要在栈上开一个新的栈帧（存参数、返回地址、局部变量） */
    return 1 + depthOf(n - 1);
}

/* ---------- ② 递归转迭代：斐波那契 ---------- */
long long fibRec(int n)
{
    if (n <= 2) return 1;
    return fibRec(n - 1) + fibRec(n - 2);
}

long long fibIter(int n)
{
    if (n <= 2) return 1;
    long long a = 1, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/* ---------- ③ 递归转迭代：阶乘 ---------- */
long long factRec(int n)
{
    if (n <= 1) return 1;
    return n * factRec(n - 1);
}

long long factIter(int n)
{
    long long f = 1;
    for (int i = 1; i <= n; i++) f *= i;
    return f;
}

/* ---------- ④ 尾递归：递归调用是最后一步 ---------- */
/* 尾递归的求和：把累加结果当参数传下去 */
long long sumTail(int n, long long acc)
{
    if (n == 0) return acc;             /* 出口直接返回累积值 */
    return sumTail(n - 1, acc + n);     /* 递归调用是最后一步，没有后续计算 */
}

/* 对比：普通递归，递归返回后还要做加法 */
long long sumNormal(int n)
{
    if (n == 0) return 0;
    return n + sumNormal(n - 1);        /* 递归返回后还要 n + ... */
}

int main(void)
{
    /* ---------- ① 递归深度 ---------- */
    printf("=== ① 递归深度 ===\n");
    int depths[] = {10, 100, 1000, 10000};
    for (int i = 0; i < 4; i++) {
        printf("  depthOf(%d) = %d\n", depths[i], depthOf(depths[i]));
    }
    printf("  这几万层还撑得住，但再多就会「栈溢出」（Stack Overflow）\n");
    printf("  ⚠️ 常见原因：递归没有正确靠近出口，或者层数太深\n");
    printf("     本程序不演示崩溃，你可以自己把 depths 改成 1000000 试试\n");

    /* ---------- ② 斐波那契：递归 vs 迭代 ---------- */
    printf("\n=== ② 斐波那契 ===\n");
    printf("  %-6s %-14s %-14s %s\n", "n", "递归", "迭代", "一致");
    for (int n = 10; n <= 30; n += 10) {
        long long r = fibRec(n);        /* ⚠️ 先存起来，别调用两次 */
        long long it = fibIter(n);
        printf("  %-6d %-14lld %-14lld %s\n",
               n, r, it, (r == it) ? "是" : "否");
    }
    printf("  n=30 时递归已经调用了约 166 万次；n=40 会到 3 亿次，明显变慢\n");

    /* ---------- ③ 阶乘 ---------- */
    printf("\n=== ③ 阶乘 ===\n");
    printf("  %-6s %-16s %-16s %s\n", "n", "递归", "迭代", "一致");
    for (int n = 5; n <= 20; n += 5) {
        printf("  %-6d %-16lld %-16lld %s\n",
               n, factRec(n), factIter(n),
               (factRec(n) == factIter(n)) ? "是" : "否");
    }

    /* ---------- ④ 尾递归 ---------- */
    printf("\n=== ④ 尾递归 ===\n");
    printf("  sumNormal(100)    = %lld\n", sumNormal(100));
    printf("  sumTail(100, 0)   = %lld\n", sumTail(100, 0));
    printf("  结果一样，但 sumTail 的递归调用是「最后一步」\n");
    printf("  这叫尾递归。理论上编译器可以把它优化成循环，不占额外栈空间\n");
    printf("  ⚠️ 但 C 标准不要求编译器做这个优化，gcc 加 -O2 后才会\n");

    /* ---------- ⑤ 什么时候用递归 ---------- */
    printf("\n=== ⑤ 什么时候该用递归 ===\n");
    printf("  ✅ 适合：\n");
    printf("     问题是「自己包含自己」的结构（树、图、分治、汉诺塔）\n");
    printf("     递推关系天然清晰（gcd、快速排序）\n");
    printf("  ❌ 不适合：\n");
    printf("     简单的线性重复（求和、阶乘）—— 循环更高效\n");
    printf("     有大量重复子问题（斐波那契）—— 要么改迭代，要么加记忆化\n");
    printf("     深度可能很大（链表很长）—— 有栈溢出风险\n");

    return 0;
}
