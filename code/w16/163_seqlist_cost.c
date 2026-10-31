/* 163_seqlist_cost.c —— 顺序表插入删除的平均移动次数（软考必考）
 *
 * 软考原题：
 *   「在长度为 n 的顺序表中插入一个元素，平均需要移动多少个元素？」
 *   答案：n/2
 *
 *   「删除一个元素，平均需要移动多少个元素？」
 *   答案：(n-1)/2
 *
 * 这两个数字不是背的，是可以推出来、也可以量出来的。本程序两种都做。
 */

#include <stdio.h>

/* 模拟一次插入，返回移动次数 */
static int movesForInsert(int n, int pos)
{
    /* 从 pos 到 n-1 的元素都要后移一格，共 n - pos 个 */
    return n - pos;
}

/* 模拟一次删除，返回移动次数 */
static int movesForDelete(int n, int pos)
{
    /* pos 之后的元素都要前移一格，共 n - 1 - pos 个 */
    return n - 1 - pos;
}

int main(void)
{
    /* ---------- ① 插入：逐个位置数移动次数 ---------- */
    printf("=== ① 长度 n=10 的表，在哪个位置插入要移动几次 ===\n");
    printf("  %-8s %-12s %s\n", "插入位置", "移动次数", "说明");
    printf("  -------------------------------------------------\n");

    int n = 10;
    long long total = 0;
    for (int pos = 0; pos <= n; pos++) {
        int m = movesForInsert(n, pos);
        total += m;
        printf("  %-8d %-12d %s\n", pos, m,
               pos == 0 ? "插表头：全部后移" :
               pos == n ? "插表尾：不用挪" :
                          "中间：后面部分后移");
    }

    /* ---------- ② 插入的平均值 ---------- */
    printf("\n=== ② 插入的平均移动次数 ===\n");
    printf("  插入位置一共 %d 种（0 到 %d，注意末尾也算一种）\n", n + 1, n);
    printf("  总移动次数 = %lld\n", total);
    printf("  平均 = %lld / %d = %.2f\n", total, n + 1, (double)total / (n + 1));
    printf("  公式 n/2 = %.2f\n", (double)n / 2);

    printf("\n  ⭐ 推导：\n");
    printf("     插在第 i 个位置要移 n-i 个，i 从 0 到 n 共 n+1 种等概率\n");
    printf("     平均值 = [n + (n-1) + ... + 1 + 0] / (n+1)\n");
    printf("            = [n(n+1)/2] / (n+1)\n");
    printf("            = n/2\n");
    printf("\n  ⚠️ 注意分母是 n+1 而不是 n —— 因为能插的位置有 n+1 个。\n");
    printf("     但教材通常把 n+1 种位置近似成 n 种，也给出 n/2。\n");
    printf("     软考答案写 n/2。\n");

    /* ---------- ③ 删除：逐个位置数移动次数 ---------- */
    printf("\n=== ③ 长度 n=10 的表，删除哪个位置要移动几次 ===\n");
    printf("  %-8s %-12s %s\n", "删除位置", "移动次数", "说明");
    printf("  -------------------------------------------------\n");

    total = 0;
    for (int pos = 0; pos < n; pos++) {
        int m = movesForDelete(n, pos);
        total += m;
        printf("  %-8d %-12d %s\n", pos, m,
               pos == 0     ? "删表头：后面全部前移" :
               pos == n - 1 ? "删表尾：不用挪" :
                              "中间：后面部分前移");
    }

    /* ---------- ④ 删除的平均值 ---------- */
    printf("\n=== ④ 删除的平均移动次数 ===\n");
    printf("  删除位置一共 %d 种（0 到 %d，末尾也算）\n", n, n - 1);
    printf("  总移动次数 = %lld\n", total);
    printf("  平均 = %lld / %d = %.2f\n", total, n, (double)total / n);
    printf("  公式 (n-1)/2 = %.2f\n", (double)(n - 1) / 2);

    printf("\n  ⭐ 推导：\n");
    printf("     删第 i 个要移 n-1-i 个，i 从 0 到 n-1 共 n 种等概率\n");
    printf("     平均值 = [(n-1) + (n-2) + ... + 1 + 0] / n\n");
    printf("            = [(n-1)n/2] / n\n");
    printf("            = (n-1)/2\n");
    printf("\n  ⚠️ 分母是 n（不是 n+1）—— 因为能删的位置只有 n 个。\n");
    printf("     插入和删除的分母不同，这是最容易混的一点。\n");

    /* ---------- ⑤ 不同 n 的实测验证 ---------- */
    printf("\n=== ⑤ 换几个 n 验证公式 ===\n");
    printf("  %-6s %-16s %-12s %-16s %s\n",
           "n", "插入平均", "n/2", "删除平均", "(n-1)/2");
    printf("  ------------------------------------------------------------------\n");

    int ns[] = {10, 50, 100, 1000, 10000};
    for (int k = 0; k < 5; k++) {
        int m = ns[k];

        long long insTotal = 0;
        for (int pos = 0; pos <= m; pos++) insTotal += movesForInsert(m, pos);
        double insAvg = (double)insTotal / (m + 1);

        long long delTotal = 0;
        for (int pos = 0; pos < m; pos++) delTotal += movesForDelete(m, pos);
        double delAvg = (double)delTotal / m;

        printf("  %-6d %-16.2f %-12.2f %-16.2f %.2f\n",
               m, insAvg, m / 2.0, delAvg, (m - 1) / 2.0);
    }

    printf("\n  ⭐ 注意：实测值和公式【完全相等】，不是「接近」。\n");
    printf("     因为 n/2 和 (n-1)/2 就是精确平均值，不是近似。\n");
    printf("     之所以写成 n/2 而不是 n/2+0.5，是因为大 O 要丢掉常数项。\n");

    /* ---------- ⑥ 为什么这是 O(n) ---------- */
    printf("\n=== ⑥ 结论：插入删除都是 O(n) ===\n");
    printf("  平均要挪 n/2 个元素，最坏要挪 n 个。\n");
    printf("  按大 O 规则去掉常数 1/2，就是 O(n)。\n");
    printf("\n  ⭐ 对比：链表插入删除是 O(1)（找到位置之后），但查找是 O(n)。\n");
    printf("     顺序表查找（按位置）是 O(1)，插入删除是 O(n)。\n");
    printf("     两者正好互补 —— 这就是为什么两种都要学。\n");

    return 0;
}
