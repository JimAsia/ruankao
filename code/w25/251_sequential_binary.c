/* ============================================================================
 * 251_sequential_binary.c  —— 顺序查找 与 折半查找
 *
 * 本文件要回答三个问题：
 *   ① 顺序查找的 ASL 到底等于多少？（用计数验证 (n+1)/2）
 *   ② 折半查找每个元素比较几次？（画出判定树）
 *   ③ 折半查找的 ASL 为什么是 log2(n+1)-1 量级？
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 251.exe 251_sequential_binary.c
 * ==========================================================================*/

#include <stdio.h>

#define N 11

/* 待查表（已升序）。注意：折半查找的前提就是【有序】 */
static const int a[N] = {8, 15, 22, 27, 33, 41, 55, 60, 73, 84, 96};

/* ---------------------------------------------------------------------------
 * ① 顺序查找（带哨兵法）
 *
 * 把 a[0] 空出来放哨兵，数据放在 1..N。
 * 从后往前找，因为目标值一定会停在 a[0]，所以循环里【不需要判断越界】，
 * 少一次比较 —— 这是「哨兵」的全部价值。
 *
 * 返回值：找到返回下标 1..N，没找到返回 0（停在哨兵处）
 * -------------------------------------------------------------------------*/
static int seqSearchSentinel(const int *arr, int n, int key, int *cmp)
{
    /* arr 指向 a[1]，也允许直接传含哨兵位的数组；这里用局部副本说明原理 */
    static int buf[N + 1];
    for (int i = 1; i <= n; i++) buf[i] = arr[i - 1];
    buf[0] = key;                       /* 哨兵 */

    *cmp = 0;
    int i = n;
    while (buf[i] != key) {             /* 只判断值，不判断 i >= 0 */
        (*cmp)++;
        i--;
    }
    (*cmp)++;                           /* 最后命中那次也算一次比较 */
    return (i == 0) ? 0 : i;            /* 停在 0 说明是哨兵，即没找到 */
}

/* ---------------------------------------------------------------------------
 * ② 折半查找
 *
 * 每比较一次，区间缩小一半。只适用于【顺序存储 + 有序】。
 * cmp 记录比较次数，用于算 ASL 和画判定树。
 * -------------------------------------------------------------------------*/
static int binSearch(const int *arr, int n, int key, int *cmp)
{
    int lo = 0, hi = n - 1;
    *cmp = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;   /* 防溢出写法，等价 (lo+hi)/2 */
        (*cmp)++;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) lo = mid + 1;
        else                hi = mid - 1;
    }
    return -1;
}

int main(void)
{
    printf("待查表（n=%d，已升序）：\n  ", N);
    for (int i = 0; i < N; i++) printf("%3d", a[i]);
    printf("\n\n");

    /* ================= ① 顺序查找 ================= */
    printf("=== ① 顺序查找（带哨兵，从后往前）===\n");
    printf("  %-8s %-10s %s\n", "下标", "值", "比较次数");
    int total = 0;
    for (int i = N - 1; i >= 0; i--) {
        int cmp;
        seqSearchSentinel(a, N, a[i], &cmp);
        printf("  %-8d %-10d %d\n", i + 1, a[i], cmp);
        total += cmp;
    }
    printf("  总比较次数 = %d，ASL(成功) = %d/%d = %.2f\n",
           total, total, N, (double)total / N);
    printf("  公式 (n+1)/2 = (%d+1)/2 = %.2f  %s\n",
           N, (N + 1) / 2.0,
           (double)total / N == (N + 1) / 2.0 ? "✓ 完全相等" : "✗");

    int cmpFail;
    seqSearchSentinel(a, N, 100, &cmpFail);
    printf("  查一个不存在的 100：比较 %d 次 = n+1（含哨兵那一次）\n", cmpFail);
    printf("  去掉哨兵的话是 n=%d 次 —— 两种写法教材都有，看清题目问哪个。\n\n", N);

    /* ================= ② 折半查找 ================= */
    printf("=== ② 折半查找（每个元素的比较次数 = 它在判定树上的层数）===\n");
    printf("  %-8s %-8s %-10s %s\n", "下标", "值", "比较次数", "判定树层级");
    int totalB = 0, levelCnt[8] = {0};
    for (int i = 0; i < N; i++) {
        int cmp;
        binSearch(a, N, a[i], &cmp);
        printf("  %-8d %-8d %-10d 第 %d 层\n", i, a[i], cmp, cmp);
        totalB += cmp;
        levelCnt[cmp]++;
    }
    printf("  总比较次数 = %d，ASL(成功) = %d/%d = %.4f\n",
           totalB, totalB, N, (double)totalB / N);

    printf("\n  各层节点数：");
    for (int d = 1; d <= 4; d++) printf("第%d层 %d 个  ", d, levelCnt[d]);
    printf("\n  验算：");
    for (int d = 1; d <= 4; d++)
        printf("%d*%d%s", levelCnt[d], d, d == 4 ? " = " : " + ");
    printf("%d\n", totalB);
    printf("  ⭐ 第 d 层最多 2^(d-1) 个节点：1 / 2 / 4 / 4（最后一层没满）\n");

    /* ================= ③ 失败的情况 ================= */
    printf("\n=== ③ 折半查找失败时比较几次？（12 个空隙）===\n");
    /* 每个空隙取一个不存在的值：a[i]+1（最后一个空隙取 a[N-1]+1） */
    int totalF = 0;
    printf("  %-6s %-12s %-10s %s\n", "空隙", "查的值", "比较次数", "说明");
    for (int i = 0; i <= N; i++) {
        int key = (i == 0) ? a[0] - 1 : (i == N ? a[N - 1] + 1 : a[i - 1] + 1);
        int cmp;
        binSearch(a, N, key, &cmp);
        totalF += cmp;
        char *where;
        if (i == 0)      where = "比第一个还小";
        else if (i == N) where = "比最后一个还大";
        else             where = "夹在相邻两元素之间";
        printf("  %-6d %-12d %-10d %s\n", i, key, cmp, where);
    }
    printf("  总比较次数 = %d，ASL(失败) = %d/%d = %.4f\n",
           totalF, totalF, N + 1, (double)totalF / (N + 1));

    printf("\n=== ④ 结论 ===\n");
    printf("  顺序查找：ASL(成功) = (n+1)/2 = %.1f，O(n)\n", (N + 1) / 2.0);
    printf("  折半查找：ASL(成功) 精确值 = 各层(节点数*层数)之和 / n\n");
    printf("            n=%d 时 = %d/%d = %.4f\n", N, totalB, N, (double)totalB / N);
    printf("  近似公式（满二叉树推导，n 大时很准）：\n");
    printf("            ASL ≈ ((n+1)/n) * log2(n+1) - 1\n");
    printf("            n=%d 时 = (12/11)*log2(12)-1 = %.4f\n",
           N, ((N + 1.0) / N) * (3.5849625) - 1);
    printf("            与实测 3.0000 差 %.4f，因为最后一层只有 4 个节点、没满。\n",
           3.0 - (((N + 1.0) / N) * (3.5849625) - 1));
    printf("  时间复杂度 O(log n)，但代价是：必须【有序 + 顺序存储】。\n");
    printf("  链表做不到折半 —— 找不到「中间」在哪里。\n");
    return 0;
}
