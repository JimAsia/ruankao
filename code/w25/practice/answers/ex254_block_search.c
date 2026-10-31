/* ============================================================================
 * ex254_block_search.c  —— 参考答案
 *
 * 【解题要点】
 *   建索引：每块扫一遍求最大值
 *   查找：阶段一 扫索引找第一个 maxKey >= key 的块
 *         阶段二 在该块内顺序比较
 *
 *   ASL = ASL(索引) + ASL(块内)
 *       = (b+1)/2 + (s+1)/2
 *       = (4+1)/2 + (5+1)/2 = 2.5 + 3.0 = 5.5
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex254.exe ex254_block_search.c
 * ==========================================================================*/

#include <stdio.h>

#define N      20
#define BLOCKS  4
#define PER     5

static const int data[N] = {
    9,  3,  7,  1,  5,
    14, 10, 18, 12, 16,
    23, 21, 27, 25, 29,
    32, 36, 30, 34, 38
};

typedef struct {
    int maxKey;
    int start;
    int len;
} IndexItem;

static IndexItem idx[BLOCKS];

/* ---------- 1. 建索引 ---------- */
void buildIndex(void)
{
    for (int b = 0; b < BLOCKS; b++) {
        idx[b].start = b * PER;
        idx[b].len   = PER;
        int mx = data[idx[b].start];
        for (int i = 1; i < PER; i++) {
            int v = data[idx[b].start + i];
            if (v > mx) mx = v;
        }
        idx[b].maxKey = mx;
    }
}

/* ---------- 2. 分块查找 ---------- */
int blockSearch(int key, int *cmpIndex, int *cmpBlock)
{
    *cmpIndex = *cmpBlock = 0;

    /* 阶段一：定位块 */
    int b = -1;
    for (int i = 0; i < BLOCKS; i++) {
        (*cmpIndex)++;
        if (idx[i].maxKey >= key) { b = i; break; }
    }
    if (b < 0) return -1;               /* 比所有块的最大值都大 */

    /* 阶段二：块内顺序查 */
    for (int i = 0; i < idx[b].len; i++) {
        (*cmpBlock)++;
        if (data[idx[b].start + i] == key)
            return idx[b].start + i;
    }
    return -1;                          /* 块对了，但块里没有 */
}

int main(void)
{
    buildIndex();

    printf("=== ① 索引表 ===\n");
    printf("  %-6s %-8s %-8s %-6s %s\n", "块号", "maxKey", "start", "len", "内容");
    for (int b = 0; b < BLOCKS; b++) {
        printf("  %-6d %-8d %-8d %-6d ", b, idx[b].maxKey, idx[b].start, idx[b].len);
        for (int i = 0; i < idx[b].len; i++) printf("%d ", data[idx[b].start + i]);
        printf("\n");
    }

    printf("\n=== ② 逐个查找 ===\n");
    printf("  %-6s %-6s %-10s %-10s %s\n", "值", "下标", "索引比较", "块内比较", "合计");
    int total = 0;
    for (int i = 0; i < N; i++) {
        int ci = 0, cb = 0;
        int pos = blockSearch(data[i], &ci, &cb);
        printf("  %-6d %-6d %-10d %-10d %d\n", data[i], pos, ci, cb, ci + cb);
        total += ci + cb;
    }
    printf("  总比较 = %d，ASL(成功) = %d/%d = %.2f\n", total, total, N, (double)total / N);
    printf("  公式 (b+1)/2 + (s+1)/2 = %.1f + %.1f = %.1f\n",
           (BLOCKS + 1) / 2.0, (PER + 1) / 2.0,
           (BLOCKS + 1) / 2.0 + (PER + 1) / 2.0);

    printf("\n=== ③ 查不存在的值 ===\n");
    int miss[] = {100, 13, 0};
    for (int i = 0; i < 3; i++) {
        int ci = 0, cb = 0;
        int pos = blockSearch(miss[i], &ci, &cb);
        printf("  查 %-4d → 返回 %-3d，索引 %d 次，块内 %d 次\n",
               miss[i], pos, ci, cb);
    }

    printf("\n=== ④ 结论 ===\n");
    printf("  分块查找 = O(√n) 级别，介于顺序 O(n) 和折半 O(log n) 之间。\n");
    printf("  它的价值不在速度，而在【插入删除比顺序表便宜】——\n");
    printf("  只需在块内调整，不必整体搬移。\n");

    printf("\n=== ⑤ 三组对比（n=20）===\n");
    printf("  %-10s %-14s %-12s %s\n", "方法", "ASL(成功)", "时间复杂度", "前提");
    printf("  %-10s %-14s %-12s %s\n", "顺序查找", "10.50", "O(n)", "无");
    printf("  %-10s %-14s %-12s %s\n", "分块查找", "5.50", "O(√n)", "块间有序");
    printf("  %-10s %-14s %-12s %s\n", "折半查找", "3.70", "O(log n)", "整体有序");
    printf("  ⭐ 分块的 ASL 5.5 < 顺序 10.5，但明显不如折半 3.70。\n");
    printf("     它真正的卖点是「块内无序也能查」—— 插入时不用挪整表。\n");
    return 0;
}
