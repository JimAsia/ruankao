/* ============================================================================
 * ex253_binary_bounds.c  —— 练习 3：折半查找的边界变体
 *
 * 【题目】
 *   表 a = {2, 3, 3, 3, 5, 7, 7, 9, 11, 13}（有重复元素，n = 10）
 *
 *   1. 实现 lowerBound(a, n, key)：返回【第一个 >= key】的下标，没有则返回 n
 *   2. 实现 upperBound(a, n, key)：返回【第一个 > key】的下标，没有则返回 n
 *   3. 用 upper - lower 算出 key 出现的次数
 *   4. 对 key = 3, 7, 1, 14 分别输出 lower / upper / count
 *
 * 【预期】
 *   key=3  → lower=1, upper=4, count=3
 *   key=7  → lower=5, upper=7, count=2
 *   key=1  → lower=0, upper=0, count=0
 *   key=14 → lower=10, upper=10, count=0
 *
 * 【为什么要专门的变体】
 *   普通折半「找到就 return」，遇到重复元素时返回的是其中任意一个，
 *   既不能保证是最左的，也不能统计个数。想统计就必须把区间缩到边界。
 *
 * 【提示】
 *   lowerBound：while (lo < hi) { mid; if (a[mid] < key) lo = mid + 1; else hi = mid; }
 *   upperBound：把上面的 a[mid] < key 改成 a[mid] <= key
 *   循环结束时 lo == hi，就是答案位置（可能等于 n）
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex253.exe ex253_binary_bounds.c
 * ==========================================================================*/

#include <stdio.h>

#define N 10

static const int a[N] = {2, 3, 3, 3, 5, 7, 7, 9, 11, 13};

/* ---------- 1. 第一个 >= key 的位置 ---------- */
int lowerBound(const int *arr, int n, int key)
{
    /* TODO */
    (void)arr; (void)n; (void)key;
    return -1;
}

/* ---------- 2. 第一个 > key 的位置 ---------- */
int upperBound(const int *arr, int n, int key)
{
    /* TODO */
    (void)arr; (void)n; (void)key;
    return -1;
}

int main(void)
{
    printf("表：");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("（n=%d，注意 3 和 7 各有重复）\n\n", N);

    printf("=== ① lower / upper / count ===\n");
    printf("  %-6s %-8s %-8s %s\n", "key", "lower", "upper", "count");
    int keys[] = {3, 7, 1, 14};
    for (int i = 0; i < 4; i++) {
        int lo = lowerBound(a, N, keys[i]);
        int hi = upperBound(a, N, keys[i]);
        printf("  %-6d %-8d %-8d %d\n", keys[i], lo, hi, hi - lo);
    }

    printf("\n=== ② 验证 count 是否真的对 ===\n");
    for (int i = 0; i < 4; i++) {
        int cnt = 0;
        for (int j = 0; j < N; j++) if (a[j] == keys[i]) cnt++;
        int fromBound = upperBound(a, N, keys[i]) - lowerBound(a, N, keys[i]);
        printf("  key=%-4d 暴力数=%d，边界相减=%d  %s\n",
               keys[i], cnt, fromBound, cnt == fromBound ? "✓" : "✗");
    }

    printf("\n=== ③ 用途：插入位置 ===\n");
    int x = 6;
    printf("  要把 %d 插进有序表并保持有序，应该插在下标 %d 处\n",
           x, upperBound(a, N, x));   /* 用 upper 插在重复元素之后，保持稳定 */
    printf("  （用 lower 会插在重复元素之前，两者都合法，看业务要求）\n");
    return 0;
}
