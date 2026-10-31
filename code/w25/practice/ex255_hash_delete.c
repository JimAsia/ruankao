/* ============================================================================
 * ex255_hash_delete.c  —— 练习 5：线性探测的删除（墓碑标记）
 *
 * 【题目】
 *   表长 11，H(k) = k % 11。依次插入：22 33 44 55 11 66 7 18
 *   注意 22/33/44/55/11/66 的哈希值全是 0，会挤成一片。
 *
 *   1. 实现 insert()（线性探测）：成功返回落位，重复返回 -2，表满返回 -1
 *   2. 实现 find()：找到返回下标，否则 -1；cmp 回传比较次数
 *   3. 实现 del()：把 key 所在槽改成【墓碑】TOMB，找不到返回 0
 *   4. 做完 3 之后查 55，看还能不能找到
 *   5. 【关键的对照实验】另复制一份表，把 33 直接置成 EMPTY，
 *      再查 55 —— 观察它为什么找不到了
 *
 * 【预期】
 *   删除 33 后查 55 仍然成功（探测 0,1,2,3 共 4 次，跳过墓碑）
 *   若把 33 置成 EMPTY，查 55 会在下标 1 就停下，判定「不存在」
 *
 * 【为什么】
 *   线性探测靠「遇到空槽就停」来判断不存在。删掉的槽如果变成空槽，
 *   它后面的同义词就被「截断」了 —— 明明还挂着，却再也找不到。
 *   墓碑的作用：告诉查找「这里曾经有人，继续往后找」。
 *
 * 【提示】
 *   三个状态：EMPTY(-1) 空、TOMB(-2) 墓碑、>=0 真实关键字
 *   插入时可以复用墓碑位；查找时遇到 TOMB 要继续，遇到 EMPTY 才停。
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
    /* TODO: 线性探测；顺路可以复用墓碑位 */
    (void)key;
    return -1;
}

/* ---------- 2. 查找 ---------- */
int find(int key, int *cmp)
{
    /* TODO: 遇 EMPTY 停（返回 -1）；遇 TOMB 跳过继续；命中返回值 */
    (void)key; (void)cmp;
    return -1;
}

/* ---------- 3. 删除（墓碑） ---------- */
int del(int key)
{
    /* TODO: 先 find 到位置，再置成 TOMB；找不到返回 0 */
    (void)key;
    return 0;
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
    /* 复制一份当前表，模拟「错误删除」：把墓碑也当成空槽 */
    int bad[M];
    for (int i = 0; i < M; i++) bad[i] = (table[i] == TOMB) ? EMPTY : table[i];

    printf("  表形态：    ");
    for (int i = 0; i < M; i++) {
        if (bad[i] == EMPTY) printf("%4s", "-");
        else                 printf("%4d", bad[i]);
    }
    printf("\n");

    /* 用同一套查找逻辑在 bad 上找 55 */
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
    return 0;
}
