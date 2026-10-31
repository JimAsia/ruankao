/* ============================================================================
 * ex252_binary_search.c  —— 练习 2：折半查找与判定树
 *
 * 【题目】
 *   表为 1..15 共 15 个整数（a[i] = i + 1）。
 *   1. 实现迭代版 binSearch()，返回下标，cmp 回传比较次数
 *   2. 实现递归版 binSearchRec()（同样统计比较次数）
 *   3. 对 1..15 每个元素查一遍，打印比较次数
 *   4. 统计各层的节点个数，验证「第 d 层最多 2^(d-1) 个」
 *   5. 算 ASL(成功)
 *
 * 【预期】
 *   层级分布：第1层 1 个、第2层 2 个、第3层 4 个、第4层 8 个
 *   ASL = (1*1 + 2*2 + 3*4 + 4*8) / 15 = 49/15 ≈ 3.2667
 *   迭代版与递归版的比较次数完全一致
 *
 * 【提示】
 *   mid = lo + (hi - lo) / 2；循环条件 while (lo <= hi)
 *   递归版：找不到时 return -1，边界是 lo > hi
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex252.exe ex252_binary_search.c
 * ==========================================================================*/

#include <stdio.h>

#define N 15

static int a[N];

/* ---------- 1. 迭代版 ---------- */
int binSearch(const int *arr, int n, int key, int *cmp)
{
    /* TODO */
    (void)arr; (void)n; (void)key; (void)cmp;
    return -1;
}

/* ---------- 2. 递归版 ---------- */
int binSearchRec(const int *arr, int lo, int hi, int key, int *cmp)
{
    /* TODO: 先判 lo > hi 返回 -1；算 mid；比较后决定往左还是往右递归 */
    (void)arr; (void)lo; (void)hi; (void)key; (void)cmp;
    return -1;
}

int main(void)
{
    for (int i = 0; i < N; i++) a[i] = i + 1;

    printf("=== ① 迭代版：每个元素的比较次数 ===\n");
    printf("  %-6s %-8s %-10s %s\n", "下标", "值", "比较次数", "迭代/递归是否一致");
    int total = 0, level[N + 1] = {0}, mismatch = 0;
    for (int i = 0; i < N; i++) {
        int c1 = 0, c2 = 0;
        binSearch(a, N, a[i], &c1);
        binSearchRec(a, 0, N - 1, a[i], &c2);
        if (c1 != c2) mismatch++;
        printf("  %-6d %-8d %-10d %s\n", i, a[i], c1, c1 == c2 ? "一致" : "不一致");
        total += c1;
        level[c1]++;
    }
    printf("  ASL(成功) = %d/%d = %.4f\n", total, N, (double)total / N);
    printf("  迭代与递归不一致的次数：%d\n", mismatch);

    printf("\n=== ② 判定树各层节点数 ===\n");
    int sum = 0;
    for (int d = 1; d <= 4; d++) {
        printf("  第 %d 层：%d 个（理论最多 %d 个）\n", d, level[d], 1 << (d - 1));
        sum += level[d] * d;
    }
    printf("  验算 Σ(层数*个数) = %d，与实测总比较次数 %d %s\n",
           sum, total, sum == total ? "一致 ✓" : "不一致 ✗");

    printf("\n=== ③ 失败查找 ===\n");
    int miss[] = {-3, 0, 16, 100};   /* 1..15 全在表里，所以失败只能来自表外 */
    for (int i = 0; i < 4; i++) {
        int c1 = 0, c2 = 0;
        binSearch(a, N, miss[i], &c1);
        binSearchRec(a, 0, N - 1, miss[i], &c2);
        printf("  查 %-4d → 迭代 %d 次，递归 %d 次\n", miss[i], c1, c2);
    }

    printf("\n=== ④ 结论 ===\n");
    printf("  满二叉树（n=15=2^4-1）时 ASL = 49/15 ≈ 3.27\n");
    printf("  近似公式 ((n+1)/n)*log2(n+1)-1 = (16/15)*4-1 = %.4f\n", 16.0 / 15 * 4 - 1);
    printf("  ⭐ 两者完全相等 —— 这就是这个公式的来历（只对满二叉树精确）。\n");
    return 0;
}
