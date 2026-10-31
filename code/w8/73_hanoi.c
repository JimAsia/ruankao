/* 73_hanoi.c —— 汉诺塔
 *
 * 规则：三根柱子，把 n 个盘子从 A 移到 C，每次只能移一个，
 *       且大盘不能放在小盘上面。
 *
 * 递归思路（这是递归思维的经典范例）：
 *   ① 把上面 n-1 个盘子从 A 移到 B（借助 C）
 *   ② 把最大的那个从 A 移到 C
 *   ③ 把 n-1 个盘子从 B 移到 C（借助 A）
 */

#include <stdio.h>

long long moveCount = 0;

/* from → to，via 是辅助柱 */
void hanoi(int n, char from, char to, char via)
{
    if (n == 1) {                       /* 出口：只有一个盘子，直接搬 */
        printf("  第 %2lld 步：把盘子 1 从 %c 移到 %c\n", ++moveCount, from, to);
        return;
    }

    hanoi(n - 1, from, via, to);        /* ① n-1 个：from → via */
    printf("  第 %2lld 步：把盘子 %d 从 %c 移到 %c\n", ++moveCount, n, from, to);
    hanoi(n - 1, via, to, from);        /* ③ n-1 个：via → to */
}

/* 只数步数、不打印过程的版本 */
long long hanoiCount(int n)
{
    if (n == 1) return 1;
    return 2 * hanoiCount(n - 1) + 1;
}

int main(void)
{
    /* ---------- ① 三个盘子的完整过程 ---------- */
    printf("=== ① 3 个盘子的移动过程 ===\n");
    printf("  柱子：A（起点）→ C（终点），B 作为辅助\n\n");

    moveCount = 0;
    hanoi(3, 'A', 'C', 'B');
    printf("\n  共 %lld 步\n", moveCount);

    /* ---------- ② 移动次数公式 ---------- */
    printf("\n=== ② 移动次数：递归计数 vs 公式 ===\n");
    printf("  %-4s %-12s %-14s %s\n", "n", "递归计数", "公式 2^n-1", "一致");

    for (int n = 1; n <= 10; n++) {
        long long byRec = hanoiCount(n);

        long long byFormula = 1;
        for (int i = 0; i < n; i++) byFormula *= 2;
        byFormula -= 1;

        printf("  %-4d %-12lld %-14lld %s\n",
               n, byRec, byFormula, (byRec == byFormula) ? "是" : "否");
    }

    printf("\n  ⭐ 公式：n 个盘子需要 2^n - 1 步\n");
    printf("  推导：f(n) = 2 × f(n-1) + 1，且 f(1) = 1\n");
    printf("        展开得 f(n) = 2^n - 1\n");

    printf("\n=== ③ 这个数字有多大 ===\n");
    printf("  64 个盘子需要 2^64 - 1 步 ≈ 1.8 × 10^19 步\n");
    printf("  一秒一步的话，要大约 5849 亿年 —— 比宇宙年龄还长\n");
    printf("  这就是传说中「世界末日」的由来\n");

    printf("\n=== ④ 递归思维的关键 ===\n");
    printf("  不要试图在脑子里模拟每一步（3 个盘子还行，5 个就晕了）\n");
    printf("  只要相信「hanoi(n-1, ...) 能把 n-1 个盘子正确搬过去」\n");
    printf("  然后把「搬 n 个」拆成「搬 n-1 个 + 搬 1 个 + 搬 n-1 个」\n");
    printf("  这叫「递归的信仰之跃」—— 先假设小问题已解决\n");

    return 0;
}
