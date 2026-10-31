/* ============================================================================
 * ex253_binary_bounds.c  —— 参考答案
 *
 * 【核心差别】
 *   普通折半：a[mid] == key 就 return，区间里有重复时返回哪个不确定。
 *   边界折半：从不「命中即返回」，而是不断把区间收缩到边界上，
 *             循环结束时 lo == hi，那个位置就是答案。
 *
 *   lowerBound：a[mid] <  key → lo = mid + 1；否则 hi = mid
 *   upperBound：a[mid] <= key → lo = mid + 1；否则 hi = mid
 *
 *   两者只差一个等号，但语义完全不同。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex253.exe ex253_binary_bounds.c
 * ==========================================================================*/

#include <stdio.h>

#define N 10

static const int a[N] = {2, 3, 3, 3, 5, 7, 7, 9, 11, 13};

/* ---------- 1. 第一个 >= key 的位置 ---------- */
int lowerBound(const int *arr, int n, int key)
{
    int lo = 0, hi = n;                 /* 注意 hi = n：答案可能是 n */
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < key) lo = mid + 1;
        else                hi = mid;
    }
    return lo;
}

/* ---------- 2. 第一个 > key 的位置 ---------- */
int upperBound(const int *arr, int n, int key)
{
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= key) lo = mid + 1;
        else                 hi = mid;
    }
    return lo;
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

    printf("\n=== ④ 逐步追踪 key=3 的 lowerBound ===\n");
    {
        int lo = 0, hi = N, step = 0;
        printf("  %-6s %-6s %-8s %-8s %s\n", "步骤", "mid", "a[mid]", "动作", "区间");
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            char action[32];
            if (a[mid] < 3) { lo = mid + 1; snprintf(action, sizeof action, "a[mid]<3 → lo=mid+1"); }
            else            { hi = mid;     snprintf(action, sizeof action, "a[mid]>=3 → hi=mid"); }
            printf("  %-6d %-6d %-8d %-8s [%d, %d)\n", ++step, mid, a[mid], action, lo, hi);
            if (step > 10) break;
        }
        printf("  结束时 lo = %d → 第一个 >=3 的位置就是 %d（值为 %d）\n", lo, lo, a[lo]);
    }

    printf("\n=== ⑤ 两个易错点 ===\n");
    printf("  1. hi 必须初始化为 n（不是 n-1）—— 答案可能是「末尾之后」，\n");
    printf("     查比所有元素都大的值时，lower 和 upper 都返回 n。\n");
    printf("  2. 循环条件是 lo < hi（不是 lo <= hi）—— 区间是左闭右开，\n");
    printf("     写成 <= 会多转一圈，甚至死循环。\n");
    return 0;
}
