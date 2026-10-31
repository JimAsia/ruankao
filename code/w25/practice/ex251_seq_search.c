/* ============================================================================
 * ex251_seq_search.c  —— 练习 1：顺序查找与 ASL 实测
 *
 * 【题目】
 *   1. 实现普通顺序查找 seqSearch()：从下标 0 往后扫，count 记录比较次数
 *   2. 实现带哨兵的 seqSearchSentinel()：a[0] 放哨兵，数据在 1..n，
 *      从后往前扫，循环里不判越界
 *   3. n = 10 的表 {5, 12, 23, 34, 45, 56, 67, 78, 89, 100}
 *      a) 对每个存在的元素查一遍，打印比较次数，算 ASL(成功)
 *      b) 查 3 个不存在的值，算 ASL(失败)（带哨兵口径 = n+1）
 *
 * 【预期】
 *   ASL(成功) = 5.50（正好 (n+1)/2）
 *   查不存在的值统一 11 次
 *
 * 【提示】
 *   哨兵的作用：省掉「i >= 0」这个判断，每轮少一次比较。
 *   但失败时哨兵自身也要比一次，所以是 n+1 而不是 n。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex251.exe ex251_seq_search.c
 * ==========================================================================*/

#include <stdio.h>

#define N 10

static const int data[N] = {5, 12, 23, 34, 45, 56, 67, 78, 89, 100};

/* ---------- 1. 普通顺序查找 ---------- */
int seqSearch(const int *a, int n, int key, int *cmp)
{
    /* TODO: 从头扫到 n-1，每次比较 (*cmp)++；找到返回下标，否则 -1 */
    (void)a; (void)n; (void)key; (void)cmp;
    return -1;
}

/* ---------- 2. 带哨兵的顺序查找 ---------- */
/* 注意：a[0] 被当作哨兵位，真实数据在 a[1]..a[n] */
int seqSearchSentinel(int *a, int n, int key, int *cmp)
{
    /* TODO: a[0] = key；从 i = n 往前扫，while (a[i] != key) { (*cmp)++; i--; }
     *       循环结束后 (*cmp)++（命中那次），i == 0 说明没找到 */
    (void)a; (void)n; (void)key; (void)cmp;
    return 0;
}

int main(void)
{
    /* 造一个带哨兵位的数组：buf[0] 空着，buf[1..N] 是数据 */
    int buf[N + 1];
    for (int i = 0; i < N; i++) buf[i + 1] = data[i];

    printf("=== ① 普通顺序查找 ===\n");
    printf("  %-6s %-8s %s\n", "下标", "值", "比较次数");
    int total = 0;
    for (int i = 0; i < N; i++) {
        int cmp = 0;
        seqSearch(data, N, data[i], &cmp);
        printf("  %-6d %-8d %d\n", i, data[i], cmp);
        total += cmp;
    }
    printf("  ASL(成功) = %d/%d = %.2f\n", total, N, (double)total / N);

    printf("\n=== ② 带哨兵的顺序查找（从后往前）===\n");
    printf("  %-6s %-8s %s\n", "下标", "值", "比较次数");
    total = 0;
    for (int i = N - 1; i >= 0; i--) {
        int cmp = 0;
        seqSearchSentinel(buf, N, buf[i + 1], &cmp);
        printf("  %-6d %-8d %d\n", i + 1, buf[i + 1], cmp);
        total += cmp;
    }
    printf("  ASL(成功) = %d/%d = %.2f\n", total, N, (double)total / N);

    printf("\n=== ③ 失败查找 ===\n");
    int miss[] = {1, 50, 200};
    for (int i = 0; i < 3; i++) {
        int cmp = 0;
        seqSearchSentinel(buf, N, miss[i], &cmp);
        printf("  查 %-4d → 比较 %d 次\n", miss[i], cmp);
    }

    printf("\n=== ④ 结论 ===\n");
    printf("  成功：平均 (n+1)/2 = %.2f 次\n", (N + 1) / 2.0);
    printf("  失败：%d 次（n+1，含哨兵）。去掉哨兵是 n = %d 次。\n", N + 1, N);
    return 0;
}
