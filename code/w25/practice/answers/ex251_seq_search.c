/* ============================================================================
 * ex251_seq_search.c  —— 参考答案
 *
 * 【解题要点】
 *   1. 普通版：for 循环从 0 到 n-1，每比较一次 (*cmp)++
 *   2. 哨兵版：a[0] = key，i 从 n 往前，循环条件只有 a[i] != key
 *      —— 因为 a[0] 一定等于 key，循环必然停，不用写 i >= 0
 *   3. 失败时哨兵本身也比了一次，所以是 n+1 次
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex251.exe ex251_seq_search.c
 * ==========================================================================*/

#include <stdio.h>

#define N 10

static const int data[N] = {5, 12, 23, 34, 45, 56, 67, 78, 89, 100};

/* ---------- 1. 普通顺序查找 ---------- */
int seqSearch(const int *a, int n, int key, int *cmp)
{
    *cmp = 0;
    for (int i = 0; i < n; i++) {
        (*cmp)++;
        if (a[i] == key) return i;
    }
    return -1;
}

/* ---------- 2. 带哨兵的顺序查找 ---------- */
int seqSearchSentinel(int *a, int n, int key, int *cmp)
{
    *cmp = 0;
    a[0] = key;                     /* 放哨兵 */
    int i = n;
    while (a[i] != key) {           /* 只比值，不判越界 */
        (*cmp)++;
        i--;
    }
    (*cmp)++;                       /* 命中（含撞上哨兵）那一次 */
    return (i == 0) ? 0 : i;        /* 停在 0 = 只有哨兵 = 没找到 */
}

int main(void)
{
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

    /* 补充：哨兵省的到底是什么 */
    printf("\n=== ⑤ 哨兵省了什么 ===\n");
    printf("  普通版每轮要判两个条件：i < n 和 a[i] == key\n");
    printf("  哨兵版每轮只判一个：a[i] == key\n");
    printf("  对 n=%d 的失败查找：省掉 %d 次下标比较。\n", N, N);
    printf("  n 很大时这是实打实的加速 —— 这就是「哨兵」在工程里的价值。\n");
    return 0;
}
