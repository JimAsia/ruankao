/* ============================================================================
 * ex256_hash_chain.c  —— 参考答案
 *
 * 【解题要点】
 *   insert：先在该桶的链上查重，没有就尾插
 *   find  ：从链头往后比，返回比较次数
 *   del   ：找到下标后，把后面的元素整体前移一格，chainLen--
 *
 * 【ASL 计算】
 *   链长：桶 0 有 6 个（22 33 44 55 11 66），桶 7 有 2 个（7 18）
 *   成功 = (1+2+3+4+5+6) + (1+2) = 21 + 3 = 24 → 24/8 = 3.0
 *   失败 = 平均链长 = 8/11 ≈ 0.727
 *
 *   ⚠️ 注意：沿用的是「成功时比较次数 = 在链上的位置」这个口径。
 *      如果按「找到后还要再比较一次确认」之类的口径，数字会不同，
 *      做题时看清题目怎么定义「比较次数」。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex256.exe ex256_hash_chain.c
 * ==========================================================================*/

#include <stdio.h>

#define M       11
#define CAP     16

static int bucket[M][CAP];
static int chainLen[M];

void initTable(void)
{
    for (int i = 0; i < M; i++) chainLen[i] = 0;
}

/* ---------- 1. 尾插 ---------- */
int insert(int key)
{
    int h = key % M;
    for (int i = 0; i < chainLen[h]; i++)
        if (bucket[h][i] == key) return -1;         /* 重复 */
    if (chainLen[h] >= CAP) return -2;              /* 桶满 */
    bucket[h][chainLen[h]++] = key;
    return chainLen[h];
}

/* ---------- 2. 查找 ---------- */
int find(int key, int *ok)
{
    int h = key % M;
    *ok = 0;
    for (int i = 0; i < chainLen[h]; i++) {
        if (bucket[h][i] == key) { *ok = 1; return i + 1; }
    }
    return chainLen[h];                             /* 走完整条链 */
}

/* ---------- 3. 删除 ---------- */
int del(int key)
{
    int h = key % M;
    for (int i = 0; i < chainLen[h]; i++) {
        if (bucket[h][i] == key) {
            for (int j = i; j < chainLen[h] - 1; j++)
                bucket[h][j] = bucket[h][j + 1];    /* 后面元素前移 */
            chainLen[h]--;
            return 1;
        }
    }
    return 0;
}

static void showBuckets(const char *title)
{
    printf("  %s\n", title);
    for (int b = 0; b < M; b++) {
        if (chainLen[b] == 0) continue;
        printf("    桶 %-2d : ", b);
        for (int i = 0; i < chainLen[b]; i++) printf("%d → ", bucket[b][i]);
        printf("NULL   (%d 个)\n", chainLen[b]);
    }
}

int main(void)
{
    int keys[] = {22, 33, 44, 55, 11, 66, 7, 18};
    int n = (int)(sizeof(keys) / sizeof(keys[0]));

    initTable();

    printf("=== ① 插入 ===\n");
    for (int i = 0; i < n; i++)
        printf("  insert(%2d) → 桶 %d 的第 %d 个\n", keys[i], keys[i] % M,
               insert(keys[i]));

    showBuckets("\n=== ② 桶结构 ===");

    printf("\n=== ③ 查找全部 ===\n");
    int total = 0;
    for (int i = 0; i < n; i++) {
        int ok;
        int c = find(keys[i], &ok);
        printf("  find(%2d) → %s，比较 %d 次\n", keys[i], ok ? "找到" : "没找到", c);
        total += c;
    }
    printf("  ASL(成功) = %d/%d = %.4f\n", total, n, (double)total / n);
    printf("  ASL(失败) = n/m = %d/%d = %.4f（失败时走完整条链）\n",
           n, M, (double)n / M);

    printf("\n=== ④ 删除 33 和 22 ===\n");
    printf("  del(33) = %d，del(22) = %d\n", del(33), del(22));
    showBuckets("删除后：");

    printf("\n=== ⑤ 删完再查 ===\n");
    for (int i = 0; i < n; i++) {
        int ok;
        int c = find(keys[i], &ok);
        printf("  find(%2d) → %-6s 比较 %d 次\n", keys[i], ok ? "找到" : "没找到", c);
    }

    printf("\n=== ⑥ 结论 ===\n");
    printf("  链地址法删除只需摘链，不用墓碑 —— 这是它相对开放定址法的一大优势。\n");
    printf("  代价：每个节点多一个指针；链表分散在堆上，缓存局部性差。\n");

    printf("\n=== ⑦ 同一组数据，线性探测的 ASL(失败) 是多少 ===\n");
    {
        int lin[M];
        for (int i = 0; i < M; i++) lin[i] = -1;
        for (int i = 0; i < n; i++) {
            int h = keys[i] % M;
            for (int j = 0; j < M; j++) {
                int p = (h + j) % M;
                if (lin[p] == -1) { lin[p] = keys[i]; break; }
                if (lin[p] == keys[i]) break;
            }
        }
        int sum = 0;
        for (int a = 0; a < M; a++) {
            int c = 0;
            for (int i = 0; i < M; i++) { c++; if (lin[(a + i) % M] == -1) break; }
            sum += c;
        }
        printf("  线性探测 ASL(失败) = %d/%d = %.4f\n", sum, M, (double)sum / M);
        printf("  链地址法 ASL(失败) = %.4f —— 快了 %.1f 倍。\n",
               (double)n / M, ((double)sum / M) / ((double)n / M));
        printf("  原因：线性探测的 0~5 是一条长堆积区，失败要扫穿它。\n");
    }
    return 0;
}
