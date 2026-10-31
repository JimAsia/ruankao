/* ============================================================================
 * 254_hash_chain.c  —— 链地址法（拉链法）与三种冲突处理的对比
 *
 * 线性探测的毛病是「堆积」：一个槽被占，后来者只能往后挪，越挤越长。
 * 链地址法换了个思路：同义词不抢别人的位置，而是挂在同一条链上。
 *
 * 本文件：
 *   ① 同一组关键字，用链地址法再存一遍，看链的形状
 *   ② 链地址法 vs 线性探测：成功/失败 ASL 差多少
 *   ③ 大规模实测：α 从 0.1 到 0.9，三种冲突处理的平均探测长度
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 254.exe 254_hash_chain.c
 * ==========================================================================*/

#include <stdio.h>

#define P 13        /* 哈希函数模数 */

/* ==========================================================================
 * 第一部分：11 个关键字的小表，两种方法都用表长 16 / 13 个桶
 * ========================================================================*/

static int lin[16];                 /* 线性探测用的表 */
static int chain[13][8];            /* 13 个桶，每桶最多 8 个节点 */
static int chainLen[13];

static void resetSmall(void)
{
    for (int i = 0; i < 16; i++) lin[i] = -1;
    for (int i = 0; i < 13; i++) { chainLen[i] = 0; }
}

/* 线性探测插入，返回探测次数 */
static int linInsert(int key)
{
    int h = key % P;
    for (int i = 0; i < 16; i++) {
        int pos = (h + i) % 16;
        if (lin[pos] == -1) { lin[pos] = key; return i + 1; }
        if (lin[pos] == key) return 0;
    }
    return -1;
}

/* 线性探测查找，返回比较次数；找不到返回 -1 次数的负值不采用，用 *ok 区分 */
static int linFind(int key, int *ok)
{
    int h = key % P;
    *ok = 0;
    for (int i = 0; i < 16; i++) {
        int pos = (h + i) % 16;
        if (lin[pos] == -1) return i + 1;
        if (lin[pos] == key) { *ok = 1; return i + 1; }
    }
    return 16;
}

/* 链地址法插入：头插还是尾插？这里用尾插，保证链上顺序 = 插入顺序，便于数位置 */
static int chainInsert(int key)
{
    int h = key % P;
    for (int i = 0; i < chainLen[h]; i++)
        if (chain[h][i] == key) return 0;           /* 已存在 */
    chain[h][chainLen[h]++] = key;
    return chainLen[h];                             /* 本次插入后的位置 */
}

static int chainFind(int key, int *ok)
{
    int h = key % P;
    *ok = 0;
    for (int i = 0; i < chainLen[h]; i++) {
        if (chain[h][i] == key) { *ok = 1; return i + 1; }
    }
    return chainLen[h];                             /* 走完整条链仍没找到 */
}

int main(void)
{
    int keys[] = {25, 38, 51, 12, 24, 36, 48, 60, 7, 19, 31};
    int n = (int)(sizeof(keys) / sizeof(keys[0]));

    resetSmall();

    /* ---------------- ① 链地址法的形状 ---------------- */
    printf("=== ① 链地址法（13 个桶，H(k) = k %% %d）===\n", P);
    for (int i = 0; i < n; i++) chainInsert(keys[i]);

    printf("  %-6s %s\n", "桶号", "链上的关键字（从左到右 = 插入顺序）");
    for (int b = 0; b < 13; b++) {
        if (chainLen[b] == 0) continue;
        printf("  %-6d ", b);
        for (int i = 0; i < chainLen[b]; i++) printf("%d ", chain[b][i]);
        printf("   （%d 个）\n", chainLen[b]);
    }

    int sumChain = 0;
    for (int i = 0; i < n; i++) {
        int ok, c = chainFind(keys[i], &ok);
        sumChain += c;
    }
    double aslChain = (double)sumChain / n;
    double aslChainFail = (double)n / P;     /* 失败 = 平均链长 = α */

    /* ---------------- ② 与线性探测对比 ---------------- */
    for (int i = 0; i < n; i++) linInsert(keys[i]);
    int sumLin = 0, okCnt = 0;
    for (int i = 0; i < n; i++) {
        int ok;
        sumLin += linFind(keys[i], &ok);
        okCnt += ok;
    }
    double aslLin = (double)sumLin / n;
    if (okCnt != n) printf("  ⚠️ 线性探测只找到 %d/%d 个\n", okCnt, n);

    int sumLinFail = 0;
    for (int a = 0; a < 16; a++) {
        int cnt = 0;
        for (int i = 0; i < 16; i++) {
            cnt++;
            if (lin[(a + i) % 16] == -1) break;
        }
        sumLinFail += cnt;
    }
    double aslLinFail = (double)sumLinFail / 16;

    printf("\n=== ② 同一组关键字，两种方法对比 ===\n");
    printf("  %-16s %-14s %-14s %s\n", "指标", "线性探测", "链地址法", "谁更好");
    const char *win = (aslLin - aslChain < 1e-9 && aslChain - aslLin < 1e-9)
                      ? "两者相同" : (aslLin < aslChain ? "线性略好" : "链地址略好");
    printf("  %-16s %-14.4f %-14.4f %s\n", "ASL(成功)", aslLin, aslChain, win);
    printf("  %-16s %-14.4f %-14.4f %s\n", "ASL(失败)", aslLinFail, aslChainFail,
           aslChainFail < aslLinFail ? "★ 链地址明显好" : "线性好");
    printf("  %-16s %-14s %-14s %s\n", "最坏情况", "要扫穿堆积区", "走完整条链", "链地址更可控");
    printf("  %-16s %-14s %-14s %s\n", "额外空间", "0（就地）", "n 个指针", "线性省空间");
    printf("\n  ⭐ 成功查找两者差不多，失败查找链地址快 %.1f 倍。\n",
           aslLinFail / aslChainFail);
    printf("     原因：线性探测失败要一直扫到空槽；链地址只要挂的那条链走完就停。\n");

    /* ---------------- ③ 大规模对比 ---------------- */
    printf("\n=== ③ 实测：α 从 0.1 到 0.9（表长 1013，随机关键字，样本 1000）===\n");
    enum { TM = 1013, CAP = 24 };
    static int tLin[TM];
    static int tQuad[TM];
    static int tChain[TM][CAP];
    static int tChainLen[TM];

    printf("  %-6s %-16s %-16s %-16s\n", "α", "线性探测", "二次探测", "链地址法");
    printf("  %-6s %-16s %-16s %-16s\n", "", "成功/失败", "成功/失败", "成功/失败");

    for (int step = 1; step <= 9; step++) {
        double lf = step * 0.1;
        int target = (int)(lf * TM);

        /* ---- 线性探测 ---- */
        for (int i = 0; i < TM; i++) tLin[i] = -1;
        unsigned s = 2024u;
        int inserted = 0;
        long sumProbe = 0;
        while (inserted < target) {
            s = s * 1103515245u + 12345u;
            int key = (int)((s >> 8) % 1000000u) + 1;
            int h = key % TM;
            for (int i = 0; i < TM; i++) {
                int pos = (h + i) % TM;
                if (tLin[pos] == -1) { tLin[pos] = key; sumProbe += i + 1; inserted++; break; }
                if (tLin[pos] == key) break;
            }
        }
        double linOk = (double)sumProbe / inserted;
        long sumFail = 0;
        for (int a = 0; a < TM; a++) {
            int cnt = 0;
            for (int i = 0; i < TM; i++) { cnt++; if (tLin[(a + i) % TM] == -1) break; }
            sumFail += cnt;
        }
        double linBad = (double)sumFail / TM;

        /* ---- 二次探测（只在 α <= 0.5 时可用，见下面的说明）---- */
        double qOk = -1, qBad = -1;
        if (lf <= 0.5) {
            for (int i = 0; i < TM; i++) tQuad[i] = -1;
            s = 2024u;
            inserted = 0;
            sumProbe = 0;
            while (inserted < target) {
                s = s * 1103515245u + 12345u;
                int key = (int)((s >> 8) % 1000000u) + 1;
                int h = key % TM;
                int placed = 0;
                for (int i = 0; i < TM; i++) {
                    int pos = (h + i * i) % TM;     /* 二次探测：h, h+1, h+4, h+9 ... */
                    if (tQuad[pos] == -1) { tQuad[pos] = key; sumProbe += i + 1; inserted++; placed = 1; break; }
                    if (tQuad[pos] == key) { placed = 1; break; }
                }
                if (!placed) break;
            }
            qOk = (double)sumProbe / inserted;
            sumFail = 0;
            for (int a = 0; a < TM; a++) {
                int cnt = 0, hitEmpty = 0;
                for (int i = 0; i < TM; i++) {
                    cnt++;
                    if (tQuad[(a + i * i) % TM] == -1) { hitEmpty = 1; break; }
                }
                sumFail += hitEmpty ? cnt : TM;
            }
            qBad = (double)sumFail / TM;
        }

        /* ---- 链地址法 ---- */
        for (int i = 0; i < TM; i++) tChainLen[i] = 0;
        s = 2024u;
        inserted = 0;
        sumProbe = 0;
        while (inserted < target) {
            s = s * 1103515245u + 12345u;
            int key = (int)((s >> 8) % 1000000u) + 1;
            int h = key % TM;
            int dup = 0;
            for (int i = 0; i < tChainLen[h]; i++)
                if (tChain[h][i] == key) { dup = 1; break; }
            if (dup) continue;
            if (tChainLen[h] < CAP) {
                tChain[h][tChainLen[h]++] = key;
                sumProbe += tChainLen[h];
                inserted++;
            }
        }
        double cOk = (double)sumProbe / inserted;
        double cBad = (double)inserted / TM;      /* 失败 = 平均链长 */

        char lCell[40], qCell[40], cCell[40];
        snprintf(lCell, sizeof lCell, "%.3f/%.3f", linOk, linBad);
        if (lf <= 0.5) snprintf(qCell, sizeof qCell, "%.3f/%.3f", qOk, qBad);
        else           snprintf(qCell, sizeof qCell, "不可用");
        snprintf(cCell, sizeof cCell, "%.3f/%.3f", cOk, cBad);
        printf("  %-6.1f %-16s %-16s %-16s\n", lf, lCell, qCell, cCell);
    }

    return 0;
}
