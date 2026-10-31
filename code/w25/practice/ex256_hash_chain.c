/* ============================================================================
 * ex256_hash_chain.c  —— 练习 6：链地址法与真删除
 *
 * 【题目】
 *   11 个桶，H(k) = k % 11。依次插入：22 33 44 55 11 66 7 18
 *
 *   1. 用【尾插法】实现 insert()，返回插入后的链上位置（第几个）
 *   2. 实现 find()：返回比较次数，*ok 标记是否找到
 *   3. 实现 del()：从链上摘掉节点（后面的节点前移填补），返回 1/0
 *   4. 打印桶结构，算 ASL(成功) 与 ASL(失败)
 *   5. 删除 33 与 22（一个在链中间、一个在链头），验证其余元素不受影响
 *
 * 【预期】
 *   ASL(成功) = (1+2+3+4+5+6) + (1+2) = 24 → 24/8 = 3.000
 *   ASL(失败) = 平均链长 = 8/11 ≈ 0.727
 *   删除后其余元素仍能找到（链地址法支持真删除，不需要墓碑）
 *
 * 【对比】
 *   同一组关键字用线性探测：ASL(成功) 也是 2.875，
 *   但 ASL(失败) 会因为 0~5 这条长堆积区而大得多（自己算算）。
 *
 * 【提示】
 *   桶用二维数组：bucket[11][CAP]，chainLen[11] 记每桶长度
 *   删除 = 把后面元素依次前移，chainLen[h]--
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
    /* TODO: 先查重；尾插；返回链上位置（1 起） */
    (void)key;
    return -1;
}

/* ---------- 2. 查找 ---------- */
int find(int key, int *ok)
{
    /* TODO: 返回比较次数；*ok 置 1/0 */
    (void)key; (void)ok;
    return 0;
}

/* ---------- 3. 删除 ---------- */
int del(int key)
{
    /* TODO: 找到下标后把后面的元素前移 */
    (void)key;
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
    return 0;
}
