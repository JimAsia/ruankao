/* ex243_merge.c —— 参考答案 */

#include <stdio.h>

#define N 8

static int g_tmp[N];
static long long g_inv = 0;
static long long g_cmp = 0;

/* 归并 + 顺便统计逆序对 */
static void merge(int a[], int lo, int mid, int hi)
{
    int i = lo, j = mid + 1, k = lo;

    while (i <= mid && j <= hi) {
        g_cmp++;
        if (a[i] <= a[j]) {
            g_tmp[k++] = a[i++];
        } else {
            /* ⭐ 关键：a[i] > a[j]，说明左边 i..mid 全都 > a[j] */
            g_inv += (mid - i + 1);
            g_tmp[k++] = a[j++];
        }
    }
    while (i <= mid) g_tmp[k++] = a[i++];
    while (j <= hi)  g_tmp[k++] = a[j++];

    for (int t = lo; t <= hi; t++) a[t] = g_tmp[t];
}

void mergeSort(int a[], int lo, int hi)
{
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    mergeSort(a, lo, mid);
    mergeSort(a, mid + 1, hi);
    merge(a, lo, mid, hi);
}

long long countInversions(int a[], int n)
{
    g_inv = 0;
    mergeSort(a, 0, n - 1);
    return g_inv;
}

/* 暴力法对照 */
static long long bruteInversions(const int a[], int n)
{
    long long cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) cnt++;
    return cnt;
}

static void printArr(const char *label, const int a[], int n)
{
    printf("  %-14s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49};
    int work[N];

    /* ---------- 归并排序 ---------- */
    printf("=== ① 归并排序 ===\n");
    for (int i = 0; i < N; i++) work[i] = src[i];
    printArr("原始", work, N);
    g_cmp = 0;
    mergeSort(work, 0, N - 1);
    printArr("排序后", work, N);
    printf("  比较 %lld 次\n", g_cmp);

    /* ---------- 逆序对 ---------- */
    printf("\n=== ② 逆序对统计 ===\n");
    printf("  暴力法（O(n^2)）：%lld 个\n", bruteInversions(src, N));

    for (int i = 0; i < N; i++) work[i] = src[i];
    long long inv = countInversions(work, N);
    printf("  归并法（O(nlogn)）：%lld 个\n", inv);

    printf("  %s\n", (inv == bruteInversions(src, N)) ? "两者一致 ✓" : "不一致 ✗");

    printf("\n  逆序对的定义：前面的数 > 后面的数的对数。\n");
    printf("  本例里：(49,38)(49,13)(49,27)(38,13)(38,27)(65,13)(65,27)(65,49)\n");
    printf("            (97,76)(97,13)(97,27)(97,49)(76,13)(76,27)(76,49)(13 之后...)\n");

    printf("\n=== ③ 归并统计逆序对的原理 ===\n");
    printf("  归并时，如果取右边元素（说明 a[i] > a[j]），\n");
    printf("  那么左边从 i 到 mid 的【所有】元素都 > a[j]，\n");
    printf("  一次就能统计出 (mid - i + 1) 个逆序对。\n");
    printf("  ⭐ 这是把 O(n^2) 的暴力统计降到 O(n log n) 的关键。\n");
    printf("  📌 软考/面试常考「怎么快速统计逆序对」→ 归并排序。\n");

    printf("\n=== ④ 归并排序的性质 ===\n");
    printf("  时间 O(n log n)（最好=最坏=平均）\n");
    printf("  空间 O(n)（辅助数组）\n");
    printf("  稳定（用 <= 保证）\n");
    printf("  ⭐ 最适合链表排序和外部排序。\n");

    return 0;
}
