/* ============================================================================
 * ex252_binary_search.c  —— 参考答案
 *
 * 【解题要点】
 *   迭代版：while (lo <= hi)，mid = lo + (hi - lo) / 2
 *   递归版：边界 lo > hi 时返回 -1，其余同迭代
 *   两者比较次数必然完全一致 —— 因为走的是同一棵判定树
 *
 * 【为什么 n=15 时 ASL 正好等于公式】
 *   n = 15 = 2^4 - 1，判定树是一棵【满】二叉树，
 *   第 d 层恰好 2^(d-1) 个节点，所以
 *   ASL = Σ d*2^(d-1) / n = (1+4+12+32)/15 = 49/15
 *   而 ((n+1)/n)*log2(n+1) - 1 = (16/15)*4 - 1 = 49/15，完全相等。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex252.exe ex252_binary_search.c
 * ==========================================================================*/

#include <stdio.h>

#define N 15

static int a[N];

/* ---------- 1. 迭代版 ---------- */
int binSearch(const int *arr, int n, int key, int *cmp)
{
    int lo = 0, hi = n - 1;
    *cmp = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        (*cmp)++;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) lo = mid + 1;
        else                hi = mid - 1;
    }
    return -1;
}

/* ---------- 2. 递归版 ---------- */
int binSearchRec(const int *arr, int lo, int hi, int key, int *cmp)
{
    if (lo > hi) return -1;                 /* 边界：区间空了 */
    int mid = lo + (hi - lo) / 2;
    (*cmp)++;
    if (arr[mid] == key) return mid;
    if (arr[mid] < key) return binSearchRec(arr, mid + 1, hi, key, cmp);
    return binSearchRec(arr, lo, mid - 1, key, cmp);
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

    /* 补充：判定树的形状，用下标表示 */
    printf("\n=== ⑤ 判定树（存的是下标，中序正好是 0..14）===\n");
    printf("              7\n");
    printf("           /     \\\n");
    printf("         3         11\n");
    printf("       /   \\      /   \\\n");
    printf("     1      5    9     13\n");
    printf("    / \\    / \\  / \\   / \\\n");
    printf("   0   2  4  6  8 10 12 14\n");
    printf("  ⭐ 每个节点的中序遍历位置就是它的下标 —— 这保证了「左小右大」。\n");
    return 0;
}
