/* ============================================================================
 * 253_hash_linear.c  —— 哈希表：除留余数法 + 线性探测
 *
 * 哈希表要解决两个问题：
 *   ① 怎么把关键字变成下标？  —— 哈希函数
 *   ② 两个关键字算出同一个下标怎么办？ —— 冲突处理
 *
 * 本文件用【线性探测法】演示：
 *   ① 插入过程与每个关键字的探测次数
 *   ② ASL(成功) 与 ASL(失败) 的实际计算
 *   ③ 堆积（聚集）现象：为什么失败查找要扫穿一整片
 *   ④ 装填因子从 0.1 涨到 0.9 时，平均探测长度怎么恶化
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 253.exe 253_hash_linear.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

#define M 16        /* 表长（实际工程里取素数） */
#define P 13        /* 哈希函数的模数：不超过表长的最大素数 */
#define EMPTY (-1)

static int table[M];
static int probeCnt[M];     /* 每个槽位里那个key当初探测了几次 */

static void initTable(void)
{
    for (int i = 0; i < M; i++) { table[i] = EMPTY; probeCnt[i] = 0; }
}

static int hash(int key) { return key % P; }

/* ---------------------------------------------------------------------------
 * 插入：线性探测
 * 返回最终落位；探测次数写入 *probes；重复关键字返回 -2
 * -------------------------------------------------------------------------*/
static int insertKey(int key, int *probes)
{
    int h = hash(key);
    for (int i = 0; i < M; i++) {
        int pos = (h + i) % M;      /* 线性探测：h, h+1, h+2, ... 循环 */
        (*probes)++;
        if (table[pos] == EMPTY) {
            table[pos] = key;
            probeCnt[pos] = *probes;
            return pos;
        }
        if (table[pos] == key) return -2;   /* 已存在，不重复插入 */
    }
    return -1;                      /* 表满 */
}

/* 查找：返回下标，-1 表示不存在；*probes 回传比较次数 */
static int findKey(int key, int *probes)
{
    int h = hash(key);
    *probes = 0;
    for (int i = 0; i < M; i++) {
        int pos = (h + i) % M;
        (*probes)++;
        if (table[pos] == EMPTY) return -1;     /* 遇到空槽 → 一定不存在 */
        if (table[pos] == key)  return pos;
    }
    return -1;
}

int main(void)
{
    /* 特意选的一组关键字：25/38/51/12 的哈希值全是 12，必然堆在一起 */
    int keys[] = {25, 38, 51, 12, 24, 36, 48, 60, 7, 19, 31};
    int n = (int)(sizeof(keys) / sizeof(keys[0]));

    initTable();

    printf("=== ① 插入过程（H(k) = k %% %d，表长 %d）===\n", P, M);
    printf("  %-6s %-10s %-10s %-8s %s\n", "key", "H(key)", "实际落位", "探测次数", "说明");
    int totalProbe = 0;
    for (int i = 0; i < n; i++) {
        int probes = 0;
        int pos = insertKey(keys[i], &probes);
        totalProbe += probes;
        printf("  %-6d %-10d %-10d %-8d %s\n", keys[i], hash(keys[i]), pos, probes,
               (pos == hash(keys[i])) ? "" : "冲突，往后挪");
    }
    printf("  总探测次数 = %d，ASL(成功) = %d/%d = %.4f\n",
           totalProbe, totalProbe, n, (double)totalProbe / n);

    /* ---------------- ② 看表形态 ---------------- */
    printf("\n=== ② 哈希表当前形态 ===\n");
    printf("  下标 :");
    for (int i = 0; i < M; i++) printf("%4d", i);
    printf("\n  值   :");
    for (int i = 0; i < M; i++) {
        if (table[i] == EMPTY) printf("%4s", "-");
        else                   printf("%4d", table[i]);
    }
    printf("\n  探测 :");
    for (int i = 0; i < M; i++) {
        if (table[i] == EMPTY) printf("%4s", "");
        else                   printf("%4d", probeCnt[i]);
    }
    printf("\n  ⭐ 下标 12~15 挤着 25/38/51/12 四个同哈希值的关键字，探测次数 1→2→3→4；\n");
    printf("     再加上 5~11 连续被占，整张表出现了一条 5~15 的长堆积区。\n");

    /* ---------------- ③ 查找实测 ---------------- */
    printf("\n=== ③ 查找实测：COUNT 与插入时的探测次数是否一致 ===\n");
    printf("  %-8s %-8s %-10s %s\n", "查的key", "结果", "比较次数", "说明");
    int okSame = 1;
    for (int i = 0; i < n; i++) {
        int probes = 0;
        int pos = findKey(keys[i], &probes);
        int same = (pos >= 0 && probes == probeCnt[pos]);
        if (!same) okSame = 0;
        printf("  %-8d %-8d %-10d %s\n", keys[i], pos, probes,
               same ? "与插入时一致" : "不一致！");
    }
    printf("  %s\n", okSame ? "  ✓ 全部一致：查找走的路和插入走的路完全相同。"
                           : "  ✗ 有偏差，需要检查。");

    printf("\n  查不存在的值（会一直走到空槽才停）：\n");
    int missKeys[] = {6, 13, 200};
    for (int i = 0; i < 3; i++) {
        int probes = 0;
        int pos = findKey(missKeys[i], &probes);
        printf("    key=%-5d → 返回 %-3d，比较 %d 次\n", missKeys[i], pos, probes);
    }

    /* ---------------- ④ ASL(失败) ---------------- */
    printf("\n=== ④ ASL(失败)：从每个哈希地址出发，要探几次才遇到空槽 ===\n");
    int totalFail = 0;
    printf("  起始地址 : 探测次数\n");
    for (int a = 0; a < M; a++) {
        int cnt = 0;
        for (int i = 0; i < M; i++) {
            int pos = (a + i) % M;
            cnt++;
            if (table[pos] == EMPTY) break;     /* 空槽也要看一眼，算 1 次 */
        }
        totalFail += cnt;
        printf("    %-3d : %d\n", a, cnt);
    }
    printf("  ASL(失败) = %d/%d = %.4f\n", totalFail, M, (double)totalFail / M);
    printf("  ⭐ 成功只要 %.2f 次，失败却要 %.2f 次 —— 差 %.1f 倍。\n",
           (double)totalProbe / n, (double)totalFail / M,
           ((double)totalFail / M) / ((double)totalProbe / n));
    printf("     原因：失败必须一路扫到空槽，堆积区有多长就要扫多长。\n");

    /* ---------------- ④ 装填因子对性能的影响 ---------------- */
    printf("\n=== ⑤ 装填因子 α 与平均探测长度（表长 1021，随机关键字实测）===\n");
    printf("  %-8s %-10s %-12s %s\n", "α", "成功ASL", "失败ASL", "最长堆积");
    {
        enum { TM = 1021 };
        static int t[TM];
        unsigned seed = 12345u;
        for (int step = 1; step <= 9; step++) {
            double lf = step * 0.1;
            int target = (int)(lf * TM);
            for (int i = 0; i < TM; i++) t[i] = EMPTY;

            unsigned s = seed;
            int inserted = 0;
            long sumProbe = 0;
            int maxProbe = 0;
            while (inserted < target) {
                s = s * 1103515245u + 12345u;
                int key = (int)((s >> 8) % 1000000u) + 1;
                int h = key % TM;
                int probes = 0, ok = 0;
                for (int i = 0; i < TM; i++) {
                    int pos = (h + i) % TM;
                    probes++;
                    if (t[pos] == EMPTY) { t[pos] = key; ok = 1; break; }
                    if (t[pos] == key) break;           /* 重复，跳过 */
                }
                if (ok) {
                    inserted++;
                    sumProbe += probes;
                    if (probes > maxProbe) maxProbe = probes;
                }
            }

            /* 失败 ASL：从每个地址出发扫到空槽 */
            long sumFail = 0;
            for (int a = 0; a < TM; a++) {
                int cnt = 0;
                for (int i = 0; i < TM; i++) {
                    cnt++;
                    if (t[(a + i) % TM] == EMPTY) break;
                }
                sumFail += cnt;
            }
            printf("  %-8.1f %-10.3f %-12.3f %d\n",
                   lf, (double)sumProbe / inserted,
                   (double)sumFail / TM, maxProbe);
        }
    }
    printf("\n  ⭐ 三个结论：\n");
    printf("     1. α 越大，成功/失败 ASL 都上升，且失败上升得更快。\n");
    printf("     2. α 超过 0.7 后性能明显恶化 —— 这就是要「扩容再哈希」的原因。\n");
    printf("     3. 线性探测的堆积会让最长探测长度远超平均值。\n");
    return 0;
}
