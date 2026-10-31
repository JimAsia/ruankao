/* ============================================================================
 * ex255_hash_delete.c  —— 参考答案
 *
 * 【解题要点】
 *   insert：从 H(key) 往后线性探测，遇到 EMPTY【或 TOMB】都可以放进去
 *   find  ：遇 EMPTY 停（一定不存在），遇 TOMB 跳过继续
 *   del   ：置成 TOMB，不是 EMPTY
 *
 * 【本组数据的形态】
 *   22 33 44 55 11 66 的哈希值全是 0，会依次落到 0,1,2,3,4,5
 *   7 和 18 的哈希值都是 7，落到 7,8
 *   删除 33（下标 1）后，55 在下标 3，查找要跨过墓碑
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex255.exe ex255_hash_delete.c
 * ==========================================================================*/

#include <stdio.h>

#define M 11
#define EMPTY (-1)
#define TOMB  (-2)

static int table[M];

void initTable(void)
{
    for (int i = 0; i < M; i++) table[i] = EMPTY;
}

/* ---------- 1. 插入 ---------- */
int insert(int key)
{
    int h = key % M;
    int firstTomb = -1;
    for (int i = 0; i < M; i++) {
        int p = (h + i) % M;
        if (table[p] == key) return -2;             /* 重复 */
        if (table[p] == TOMB && firstTomb < 0) firstTomb = p;   /* 记下第一个墓碑 */
        if (table[p] == EMPTY) {
            int pos = (firstTomb >= 0) ? firstTomb : p;          /* 优先复用墓碑 */
            table[pos] = key;
            return pos;
        }
    }
    if (firstTomb >= 0) { table[firstTomb] = key; return firstTomb; }
    return -1;                                      /* 表满 */
}

/* ---------- 2. 查找 ---------- */
int find(int key, int *cmp)
{
    int h = key % M;
    *cmp = 0;
    for (int i = 0; i < M; i++) {
        int p = (h + i) % M;
        (*cmp)++;
        if (table[p] == EMPTY) return -1;           /* 真空槽 → 到此为止 */
        if (table[p] == key)   return p;            /* TOMB 自动被跳过 */
    }
    return -1;
}

/* ---------- 3. 删除（墓碑） ---------- */
int del(int key)
{
    int cmp;
    int p = find(key, &cmp);
    if (p < 0) return 0;
    table[p] = TOMB;
    return 1;
}

static void showTable(const char *title)
{
    printf("  %s\n    下标:", title);
    for (int i = 0; i < M; i++) printf("%4d", i);
    printf("\n    内容:");
    for (int i = 0; i < M; i++) {
        if (table[i] == EMPTY)      printf("%4s", "-");
        else if (table[i] == TOMB)  printf("%4s", "T");
        else                        printf("%4d", table[i]);
    }
    printf("\n");
}

int main(void)
{
    int keys[] = {22, 33, 44, 55, 11, 66, 7, 18};
    int n = (int)(sizeof(keys) / sizeof(keys[0]));

    initTable();

    printf("=== ① 插入 ===\n");
    for (int i = 0; i < n; i++) {
        int pos = insert(keys[i]);
        printf("  insert(%2d) → 落位 %2d（H=%d）%s\n", keys[i], pos, keys[i] % M,
               pos == keys[i] % M ? "" : "  ← 冲突");
    }
    showTable("插入后：");

    printf("\n=== ② 查找全部 ===\n");
    int total = 0;
    for (int i = 0; i < n; i++) {
        int cmp = 0;
        int pos = find(keys[i], &cmp);
        printf("  find(%2d) → %2d，比较 %d 次\n", keys[i], pos, cmp);
        total += cmp;
    }
    printf("  ASL(成功) = %d/%d = %.4f\n", total, n, (double)total / n);

    printf("\n=== ③ 删除 33（用墓碑）===\n");
    int ok = del(33);
    printf("  del(33) 返回 %d（1 表示删成功）\n", ok);
    showTable("删除后：");

    int cmp = 0;
    int pos = find(55, &cmp);
    printf("  再查 55 → %d，比较 %d 次  %s\n", pos, cmp,
           pos >= 0 ? "仍然能找到 ✓" : "找不到了 ✗");

    printf("\n=== ④ 对照实验：如果直接把 33 置成 EMPTY ===\n");
    int bad[M];
    for (int i = 0; i < M; i++) bad[i] = (table[i] == TOMB) ? EMPTY : table[i];

    printf("  表形态：    ");
    for (int i = 0; i < M; i++) {
        if (bad[i] == EMPTY) printf("%4s", "-");
        else                 printf("%4d", bad[i]);
    }
    printf("\n");

    int h = 55 % M, cnt = 0, found = -1;
    for (int i = 0; i < M; i++) {
        int p = (h + i) % M;
        cnt++;
        if (bad[p] == EMPTY) break;
        if (bad[p] == 55) { found = p; break; }
    }
    printf("  查 55 → %d，比较 %d 次  %s\n", found, cnt,
           found >= 0 ? "找到了" : "★ 明明在表里，却报「不存在」");
    printf("\n  ⭐ 这就是开放定址法不能「真删除」的原因。\n");
    printf("     墓碑的代价：删得越多，探测链越长，所以墓碑攒多了要重建表。\n");

    printf("\n=== ⑤ 墓碑的代价 ===\n");
    printf("  单次查找不会因为墓碑变慢（墓碑和真实元素一样，占一次探测）。\n");
    printf("  但墓碑会累积：删得越多，越多的槽「看起来有人」，\n");
    printf("  插入时要么复用墓碑、要么继续往后找；只删不插就会让探测链变长。\n");
    printf("  工程做法：统计墓碑比例，超过阈值就 rehash 整张表。\n");
    return 0;
}
