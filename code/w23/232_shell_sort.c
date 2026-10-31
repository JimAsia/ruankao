/* 232_shell_sort.c —— 希尔排序（缩小增量排序）
 *
 * 希尔排序 = 插入排序的改进版。
 *
 * 改进思路：
 *   直接插入排序有个弱点：如果最小的数在最末尾，它要一步步往前挪 n-1 次。
 *   希尔排序先按「较大增量」分组做插入排序，让元素能【大步】跳跃，
 *   再逐步缩小增量，最后增量 = 1 时基本有序，几乎不用挪。
 *
 * 关键结论（软考必背）：
 *   复杂度：O(n^1.3) 左右（和增量序列有关，不是严格的 n^1.3）
 *   空间  ：O(1)
 *   稳定性：【不稳定】（相同元素可能被分到不同组，相对顺序会变）
 */

#include <stdio.h>

#define N 10

static long long g_cmp  = 0;
static long long g_move = 0;

/* 希尔排序：gap 序列用 gap = gap/2 */
void shellSort(int a[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        printf("\n  === gap = %d ===\n", gap);

        /* 对每个「增量分组」做插入排序
         * 注意：不是先分组再排，而是「按 gap 跳跃着做插入」 */
        for (int i = gap; i < n; i++) {
            int key = a[i];
            int j = i - gap;

            /* 在每个组内做插入排序（步长是 gap） */
            while (j >= 0) {
                g_cmp++;
                if (a[j] > key) {
                    a[j + gap] = a[j];
                    g_move++;
                    j -= gap;
                } else {
                    break;
                }
            }
            a[j + gap] = key;
            g_move++;
        }

        /* 打印这一趟的结果 */
        printf("  ");
        for (int k = 0; k < n; k++) printf("%d ", a[k]);
        printf("\n");
    }
}

/* 对照：直接插入排序（gap 恒为 1） */
void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            g_cmp++;
            if (a[j] > key) { a[j + 1] = a[j]; g_move++; j--; }
            else break;
        }
        a[j + 1] = key;
        g_move++;
    }
}

int main(void)
{
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};

    printf("=== 原始数据 ===\n  ");
    for (int i = 0; i < N; i++) printf("%d ", src[i]);
    printf("\n");

    /* ---------- 希尔排序 ---------- */
    int a[N];
    for (int i = 0; i < N; i++) a[i] = src[i];
    g_cmp = g_move = 0;

    printf("\n=== ① 希尔排序过程 ===");
    shellSort(a, N);

    long long shellCmp = g_cmp, shellMove = g_move;
    printf("\n  结果：");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("\n  比较 %lld 次，移动 %lld 次\n", shellCmp, shellMove);

    /* ---------- 直接插入排序对照 ---------- */
    int b[N];
    for (int i = 0; i < N; i++) b[i] = src[i];
    g_cmp = g_move = 0;
    insertionSort(b, N);

    printf("\n=== ② 直接插入排序（对照）===\n");
    printf("  结果：");
    for (int i = 0; i < N; i++) printf("%d ", b[i]);
    printf("\n  比较 %lld 次，移动 %lld 次\n", g_cmp, g_move);

    printf("\n=== ③ 对比 ===\n");
    printf("  %-12s %-12s %-12s\n", "排序", "比较", "移动");
    printf("  ----------------------------------\n");
    printf("  %-12s %-12lld %-12lld\n", "希尔", shellCmp, shellMove);
    printf("  %-12s %-12lld %-12lld\n", "直接插入", g_cmp, g_move);
    printf("\n  ⭐ 希尔排序用更少的比较和移动完成了同样的排序。\n");
    printf("     原因：大增量时元素能「大步跳跃」，很快接近最终位置。\n");

    printf("\n=== ④ 为什么要缩小增量 ===\n");
    printf("  假设最小数在末尾：\n");
    printf("    直接插入：要往前挪 n-1 次\n");
    printf("    希尔 gap=n/2：只挪 1 次就到前半区，之后每趟都更省力\n");
    printf("  ⭐ 希尔排序的本质：先让数据「大致有序」，再用插入排序收尾。\n");

    printf("\n=== ⑤ 关键结论（必背）===\n");
    printf("  %-12s %-16s %-12s %s\n", "项", "值", "空间", "稳定");
    printf("  ----------------------------------------------------------\n");
    printf("  %-12s %-16s %-12s %s\n", "希尔排序", "O(n^1.3) 左右", "O(1)", "不稳定");
    printf("\n  ⚠️ 三处最容易错：\n");
    printf("     1. 复杂度不是 O(n log n)，约 O(n^1.3)，和增量序列有关\n");
    printf("     2. 【不稳定】—— 相同元素被分到不同组后，相对顺序可能变\n");
    printf("     3. 增量必须最后减到 1，否则不保证有序\n");

    printf("\n=== ⑥ 为什么不稳定：一个例子 ===\n");
    printf("  数据：[2a, 2b, 1, 3]，gap = 2\n");
    printf("  分组：{2a, 1} 和 {2b, 3}\n");
    printf("  组内排序后：{1, 2a} 和 {2b, 3}\n");
    printf("  拼回数组：[1, 2b, 2a, 3]\n");
    printf("  ⭐ 2a 和 2b 的相对顺序变了 → 不稳定。\n");
    printf("     因为 2a 和 2b 从头到尾【没有直接比较过】。\n");

    printf("\n=== ⑦ 增量序列的选择 ===\n");
    printf("  常见序列：\n");
    printf("    n/2, n/4, ..., 1              ← 最简单，本程序用这个\n");
    printf("    1, 3, 7, 15, ...(2^k - 1)     ← Hibbard 序列\n");
    printf("    1, 5, 19, 41, 109, ...        ← Sedgewick 序列\n");
    printf("  ⭐ 增量序列的选择会影响性能，但【最后一个必须是 1】。\n");
    printf("     软考只考「希尔排序的复杂度约 O(n^1.3)」和「不稳定」，\n");
    printf("     不考具体序列。\n");

    return 0;
}
