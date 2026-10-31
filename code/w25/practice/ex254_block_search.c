/* ============================================================================
 * ex254_block_search.c  —— 练习 4：分块查找
 *
 * 【题目】
 *   20 个元素分成 4 块，每块 5 个。块间有序、块内无序：
 *     块 0： 9  3  7  1  5     （最大 9）
 *     块 1：14 10 18 12 16     （最大 18）
 *     块 2：23 21 27 25 29     （最大 29）
 *     块 3：32 36 30 34 38     （最大 38）
 *
 *   1. 建索引表：每块记 maxKey、start、len
 *   2. 实现 blockSearch(key, &ci, &cb)：先扫索引定位块，再块内顺序查
 *      ci = 索引阶段比较次数，cb = 块内比较次数
 *   3. 对 20 个元素逐个查，打印两阶段次数，算 ASL(成功)
 *   4. 查 2 个不存在的值（比最大值大 / 块内没有）
 *
 * 【预期】
 *   ASL(成功) = 5.50 = (b+1)/2 + (s+1)/2 = 2.5 + 3.0
 *   查 100：索引扫完 4 次，直接判定不存在，块内 0 次
 *   查 13：索引 2 次（落在块 1），块内扫 5 次仍未找到
 *
 * 【提示】
 *   定位块的条件是 idx[b].maxKey >= key，第一个满足的就是目标块。
 *   块内比较次数取决于元素在块内的位置 —— 所以「块内有序」能让 ASL 稳定，
 *   「块内无序」则插入删除更方便，这是分块查找的取舍。
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
    /* TODO: 每块扫一遍求最大值，填 start / len / maxKey */
}

/* ---------- 2. 分块查找 ---------- */
int blockSearch(int key, int *cmpIndex, int *cmpBlock)
{
    /* TODO: 阶段一 扫索引；阶段二 在块内顺序找
     * 返回下标，-1 表示不存在；两块比较次数分别写入两个指针 */
    (void)key; (void)cmpIndex; (void)cmpBlock;
    return -1;
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
    return 0;
}
