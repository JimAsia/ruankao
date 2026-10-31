/* ============================================================================
 * ex262_maxsub.c  —— 参考答案
 *
 * 【动规版要点】
 *   cur 表示「以 i 结尾的最大子段和」。
 *   若 cur > 0 就接上；否则从 i 重新开始 —— 此时左端点必须改成 i。
 *   这是本题最容易漏的一步：只更新 cur 不更新 lo，区间就是错的。
 *
 * 【分治版要点】
 *   左半、右半、跨中点三者取最大。
 *   跨中点要同时记录左边从哪开始、右边到哪结束。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o ex262.exe ex262_maxsub.c
 * ==========================================================================*/

#include <stdio.h>
#include <limits.h>

/* ---------- 1. 动规版 ---------- */
long long maxSubDP(const int *a, int n, int *lo, int *hi)
{
    long long cur = a[0], best = a[0];
    int curLo = 0;
    *lo = *hi = 0;

    for (int i = 1; i < n; i++) {
        if (cur > 0) {
            cur += a[i];                    /* 接着前面 */
        } else {
            cur = a[i];                     /* 从 i 重新开始 */
            curLo = i;                      /* ← 左端点必须跟着改 */
        }
        if (cur > best) { best = cur; *lo = curLo; *hi = i; }
    }
    return best;
}

/* ---------- 2. 分治版 ---------- */
typedef struct { long long sum; int lo, hi; } Res;

static Res dc(const int *a, int lo, int hi)
{
    if (lo == hi) { Res r = {a[lo], lo, lo}; return r; }

    int mid = lo + (hi - lo) / 2;
    Res L = dc(a, lo, mid);
    Res R = dc(a, mid + 1, hi);

    /* 跨中点：从中点往左的最大后缀 + 往右的最大前缀 */
    long long ls = 0, lbest = LLONG_MIN;
    int lstart = mid;
    for (int i = mid; i >= lo; i--) {
        ls += a[i];
        if (ls > lbest) { lbest = ls; lstart = i; }
    }
    long long rs = 0, rbest = LLONG_MIN;
    int rend = mid + 1;
    for (int i = mid + 1; i <= hi; i++) {
        rs += a[i];
        if (rs > rbest) { rbest = rs; rend = i; }
    }
    Res C = {lbest + rbest, lstart, rend};

    Res best = L;
    if (R.sum > best.sum) best = R;
    if (C.sum > best.sum) best = C;
    return best;
}

long long maxSubDC(const int *a, int n, int *lo, int *hi)
{
    Res r = dc(a, 0, n - 1);
    *lo = r.lo; *hi = r.hi;
    return r.sum;
}

/* ---------- 3. 暴力版（只用来对答案）---------- */
long long maxSubBrute(const int *a, int n, int *lo, int *hi)
{
    long long best = a[0];
    *lo = *hi = 0;
    for (int i = 0; i < n; i++) {
        long long s = 0;
        for (int j = i; j < n; j++) {
            s += a[j];
            if (s > best) { best = s; *lo = i; *hi = j; }
        }
    }
    return best;
}

static void runCase(const char *name, const int *a, int n)
{
    int l1, h1, l2, h2, l3, h3;
    long long v1 = maxSubDP(a, n, &l1, &h1);
    long long v2 = maxSubDC(a, n, &l2, &h2);
    long long v3 = maxSubBrute(a, n, &l3, &h3);

    printf("  %-22s 动规 %lld [%d,%d]  分治 %lld [%d,%d]  暴力 %lld [%d,%d]  %s\n",
           name, v1, l1, h1, v2, l2, h2, v3, l3, h3,
           (v1 == v3 && v2 == v3) ? "✓" : "✗");
}

int main(void)
{
    int a1[] = {-2, 11, -4, 13, -5, -2};
    int a2[] = {-5, -2, -8};
    int a3[] = {5, -100, 5, 5};
    int a4[] = {1, 2, 3, 4, 5};
    int a5[] = {-1, 2, -1, 3, -10, 4};

    printf("=== ① 五组数据，三版对照 ===\n");
    runCase("{-2,11,-4,13,-5,-2}", a1, 6);
    runCase("{-5,-2,-8}", a2, 3);
    runCase("{5,-100,5,5}", a3, 4);
    runCase("{1,2,3,4,5}", a4, 5);
    runCase("{-1,2,-1,3,-10,4}", a5, 6);

    printf("\n  ⭐ 最后一组出现了【多解】：动规得 [1,3]，分治得 [5,5]，和都是 4。\n");
    printf("     只问「最大和」时两者都对；若题目还要求区间最短/最靠左，\n");
    printf("     就要在比较时加第二关键字（长度、起点），否则答案不唯一。\n");

    printf("\n=== ② 分治的跨中点分支 ===\n");
    printf("  以 {-2,11,-4,13,-5,-2} 为例：mid=2，左半最大 11、右半最大 13，\n");
    printf("  但答案 20 来自跨中点（11 + (-4) + 13）。\n");
    printf("  ⭐ 所以分治的合并必须算三种情况的最大值，漏掉跨中点就错。\n");

    printf("\n=== ③ 复杂度对照 ===\n");
    printf("  %-12s %-10s %-10s %s\n", "方法", "时间", "空间", "说明");
    printf("  %-12s %-10s %-10s %s\n", "暴力", "O(n^2)", "O(1)", "最好写");
    printf("  %-12s %-10s %-10s %s\n", "分治", "O(n log n)", "O(log n)", "递归栈");
    printf("  %-12s %-10s %-10s %s\n", "动规", "O(n)", "O(1)", "最优");

    printf("\n=== ④ 动规版最容易写错的地方 ===\n");
    printf("  只写 cur = (cur > 0) ? cur + a[i] : a[i]; 而忘了更新左端点。\n");
    printf("  结果和是 20，但输出区间可能是 [0,3]，多带了 -2。\n");
    printf("  ⭐ 凡是要「输出方案/区间」的题，动规的每个状态都要多存一个「从哪来」。\n");
    return 0;
}
