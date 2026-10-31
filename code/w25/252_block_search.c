/* ============================================================================
 * 252_block_search.c  —— 分块查找（索引顺序查找）
 *
 * 分块查找是「顺序查找」和「折半查找」的折中：
 *   块间有序  → 可以先定位到块（像查目录）
 *   块内无序  → 插入删除容易，不用整体搬动
 *
 * 本文件验证：
 *   ① ASL = ASL(索引) + ASL(块内) = (b+1)/2 + (s+1)/2
 *   ② 为什么「n 固定时，b 和 s 越接近越好」
 *   ③ 索引表用折半查找能快多少
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 252.exe 252_block_search.c
 * ==========================================================================*/

#include <stdio.h>
#include <math.h>

#define N       18      /* 总元素个数 */
#define BLOCKS   3      /* 块数 */
#define PER      6      /* 每块元素个数 */

/* 数据：块间有序（第 2 块全大于第 1 块），块内故意打乱 —— 这正是分块查找的典型场景 */
static const int data[N] = {
    22,  8, 15,  3, 19, 11,      /* 块 0，最大值 22 */
    41, 30, 36, 27, 44, 33,      /* 块 1，最大值 44 */
    60, 55, 66, 51, 63, 58       /* 块 2，最大值 66 */
};

typedef struct {
    int maxKey;     /* 本块最大关键字 —— 索引表只存这个 */
    int start;      /* 本块在 data 里的起始下标 */
    int len;        /* 本块长度 */
} IndexItem;

static IndexItem idx[BLOCKS];

/* 建索引表：扫一遍每块，记下最大值 */
static void buildIndex(void)
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

/* ---------------------------------------------------------------------------
 * 分块查找
 *   useBinaryIndex = 0 → 索引表顺序扫（教材默认）
 *   useBinaryIndex = 1 → 索引表折半查（索引表本身是有序的，可以用）
 *
 * cmpIndex / cmpBlock 分别回传两阶段的比较次数，方便算 ASL
 * -------------------------------------------------------------------------*/
static int blockSearch(int key, int useBinaryIndex,
                       int *cmpIndex, int *cmpBlock,
                       int *hitBlock)
{
    *cmpIndex = *cmpBlock = 0;
    *hitBlock = -1;

    int b = -1;
    if (!useBinaryIndex) {
        /* 顺序扫索引：第一个 maxKey >= key 的块就是目标块 */
        for (int i = 0; i < BLOCKS; i++) {
            (*cmpIndex)++;
            if (idx[i].maxKey >= key) { b = i; break; }
        }
    } else {
        /* 折半查索引 */
        int lo = 0, hi = BLOCKS - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            (*cmpIndex)++;
            if (idx[mid].maxKey >= key) {
                b = mid;
                hi = mid - 1;           /* 继续往左找，取最靠前的可行块 */
            } else {
                lo = mid + 1;
            }
        }
    }

    if (b < 0) return -1;               /* 比所有块的最大值都大 → 不存在 */
    *hitBlock = b;

    /* 块内顺序查找 */
    for (int i = 0; i < idx[b].len; i++) {
        (*cmpBlock)++;
        if (data[idx[b].start + i] == key)
            return idx[b].start + i;
    }
    return -1;                          /* 块对了但块里没有 */
}

int main(void)
{
    buildIndex();

    /* ---------------- 打印数据与索引 ---------------- */
    printf("=== 数据（块间有序，块内无序）===\n");
    for (int b = 0; b < BLOCKS; b++) {
        printf("  块 %d：", b);
        for (int i = 0; i < PER; i++) printf("%3d", data[idx[b].start + i]);
        printf("   ← 最大值 %d\n", idx[b].maxKey);
    }

    printf("\n=== 索引表 ===\n");
    printf("  %-6s %-10s %-8s %s\n", "块号", "maxKey", "start", "len");
    for (int b = 0; b < BLOCKS; b++)
        printf("  %-6d %-10d %-8d %d\n", b, idx[b].maxKey, idx[b].start, idx[b].len);

    /* ---------------- ① 逐个查，统计 ASL ---------------- */
    printf("\n=== ① 查每个元素，两阶段各比较几次 ===\n");
    printf("  %-6s %-8s %-10s %-10s %s\n", "值", "命中块", "索引比较", "块内比较", "合计");
    int total = 0;
    for (int i = 0; i < N; i++) {
        int ci, cb, hb;
        blockSearch(data[i], 0, &ci, &cb, &hb);
        printf("  %-6d %-8d %-10d %-10d %d\n", data[i], hb, ci, cb, ci + cb);
        total += ci + cb;
    }
    printf("  总比较 = %d，ASL(成功) = %d/%d = %.2f\n", total, total, N, (double)total / N);

    double formula = (BLOCKS + 1) / 2.0 + (PER + 1) / 2.0;
    printf("  公式 (b+1)/2 + (s+1)/2 = (3+1)/2 + (6+1)/2 = %.2f  %s\n",
           formula, fabs((double)total / N - formula) < 1e-9 ? "✓ 完全相等" : "✗");

    /* ---------------- ② 索引表改用折半 ---------------- */
    printf("\n=== ② 索引表改用折半查找 ===\n");
    int total2 = 0;
    for (int i = 0; i < N; i++) {
        int ci, cb, hb;
        blockSearch(data[i], 1, &ci, &cb, &hb);
        total2 += ci + cb;
    }
    printf("  ASL(成功) = %d/%d = %.2f（顺序索引是 %.2f）\n",
           total2, N, (double)total2 / N, (double)total / N);
    printf("  b=3 时索引只有 3 项，折半也要 2 次左右，优势不明显；\n");
    printf("  b 很大时才值得 —— 例如 b=1000，顺序平均 500 次，折半只要 10 次。\n");

    /* ---------------- ③ b 和 s 怎么分最省 ---------------- */
    printf("\n=== ③ n 固定为 36 时，块数怎么分 ASL 最小？===\n");
    printf("  %-8s %-8s %-10s %s\n", "块数 b", "块长 s", "ASL", "说明");
    int bestB = 0;
    double best = 1e9;
    for (int b = 1; b <= 36; b++) {
        if (36 % b) continue;
        int s = 36 / b;
        double asl = (b + 1) / 2.0 + (s + 1) / 2.0;
        if (asl < best) { best = asl; bestB = b; }
        if (b <= 6 || b >= 18 || b == 9 || b == 12)
            printf("  %-8d %-8d %-10.2f %s\n", b, s, asl,
                   (b == 6) ? "← b == s，理论最优" : "");
    }
    printf("  ⭐ 最优块数 b = %d（块长 %d），ASL = %.2f ≈ √n + 1 = %.2f\n",
           bestB, 36 / bestB, best, sqrt(36) + 1);
    printf("     推导：ASL = (b+s)/2 + 1，b*s = n，b=s=√n 时 b+s 最小。\n");

    /* ---------------- ④ 真实规模：b=64 时折半索引到底快多少 ---------------- */
    printf("\n=== ④ 实测：n=4096，b=64，s=64 ===\n");
    {
        enum { BN = 64, SN = 64, TN = BN * SN };
        static int big[TN];
        static IndexItem bidx[BN];

        /* 块 i 存 (i*64+1) .. (i*64+64)，块内做一个固定置换让顺序打乱 */
        for (int b = 0; b < BN; b++) {
            for (int i = 0; i < SN; i++) {
                int j = (i * 37 + 11) % SN;          /* 37 与 64 互质 → 是一个置换 */
                big[b * SN + j] = b * SN + i + 1;
            }
            bidx[b].start = b * SN;
            bidx[b].len = SN;
            bidx[b].maxKey = b * SN + SN;
        }

        long sumSeq = 0, sumBin = 0;
        int cases = 0, missSeq = 0, missBin = 0;

        /* 均匀覆盖全部 64 个块，每块抽 3 个 */
        for (int q = 0; q < BN; q++) {
            for (int r = 0; r < 3; r++) {
                int key = q * SN + (r * 21) % SN + 1;

                /* --- 索引顺序扫 --- */
                int ci = 0, tb = -1;
                for (int t = 0; t < BN; t++) { ci++; if (bidx[t].maxKey >= key) { tb = t; break; } }
                sumSeq += ci;
                int hit = 0;
                if (tb >= 0)
                    for (int i = 0; i < bidx[tb].len; i++)
                        if (big[bidx[tb].start + i] == key) { hit = 1; break; }
                if (!hit) missSeq++;

                /* --- 索引折半查 --- */
                int lo = 0, hi = BN - 1, pos = -1; ci = 0;
                while (lo <= hi) {
                    int mid = lo + (hi - lo) / 2;
                    ci++;
                    if (bidx[mid].maxKey >= key) { pos = mid; hi = mid - 1; }
                    else lo = mid + 1;
                }
                sumBin += ci;
                hit = 0;
                if (pos >= 0)
                    for (int i = 0; i < bidx[pos].len; i++)
                        if (big[bidx[pos].start + i] == key) { hit = 1; break; }
                if (!hit) missBin++;
                cases++;
            }
        }
        printf("  抽取 %d 个查询（均匀分布在各块），两种索引都查错 %d / %d 次\n",
               cases, missSeq, missBin);
        printf("  索引顺序查找：平均 %.2f 次（理论 (b+1)/2 = %.1f）\n",
               (double)sumSeq / cases, (BN + 1) / 2.0);
        printf("  索引折半查找：平均 %.2f 次（理论 log2(b+1) ≈ 6.0）\n",
               (double)sumBin / cases);
        printf("  ⭐ 索引阶段快了 %.1f 倍。b 越大差距越大。\n",
               ((double)sumSeq / cases) / ((double)sumBin / cases));
        printf("     但块内仍是 O(s) 顺序扫 —— 分块查找的瓶颈最终落在块内。\n");
    }
    return 0;
}
