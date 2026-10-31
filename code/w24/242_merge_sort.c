/* 242_merge_sort.c —— 归并排序
 *
 * 思路（分治）：
 *   ① 把数组从中间一分为二
 *   ② 分别递归排序左右两半
 *   ③ 把两个有序的半边「归并」成一个有序整体
 *
 * 关键结论（软考必考）：
 *   时间：最好/最坏/平均 都是 O(n log n) —— 不受数据影响！
 *   空间：O(n)（归并要辅助数组）—— 这是它最大的缺点
 *   稳定性：【稳定】
 *
 * 对比快排：归并稳定且最坏也是 O(n log n)，但要额外 O(n) 空间。
 */

#include <stdio.h>

#define N 8

static long long g_cmp  = 0;
static long long g_copy = 0;

/* 辅助数组（全局，避免每次递归都 malloc） */
static int g_tmp[N];

/* ==================== 归并：把 a[lo..mid] 和 a[mid+1..hi] 合并 ==================== */
static void merge(int a[], int lo, int mid, int hi)
{
    int i = lo, j = mid + 1, k = lo;

    printf("    归并 [%d..%d] 和 [%d..%d] → ", lo, mid, mid + 1, hi);

    /* 双指针取小 */
    while (i <= mid && j <= hi) {
        g_cmp++;
        if (a[i] <= a[j]) {
            g_tmp[k++] = a[i++];
        } else {
            g_tmp[k++] = a[j++];
        }
        g_copy++;
    }
    /* 剩下的直接接上 */
    while (i <= mid) { g_tmp[k++] = a[i++]; g_copy++; }
    while (j <= hi)  { g_tmp[k++] = a[j++]; g_copy++; }

    /* 拷回原数组 */
    for (int t = lo; t <= hi; t++) a[t] = g_tmp[t];

    printf("[");
    for (int t = lo; t <= hi; t++) {
        printf("%d", a[t]);
        if (t != hi) printf(" ");
    }
    printf("]\n");
}

/* ==================== 归并排序 ==================== */
static void mergeSortRec(int a[], int lo, int hi, int depth)
{
    if (lo >= hi) return;

    int mid = (lo + hi) / 2;

    printf("  %*s拆分 [%d..%d] → [%d..%d] 和 [%d..%d]\n",
           depth * 2, "", lo, hi, lo, mid, mid + 1, hi);

    mergeSortRec(a, lo, mid, depth + 1);
    mergeSortRec(a, mid + 1, hi, depth + 1);

    merge(a, lo, mid, hi);
}

static void printArr(const char *label, const int a[], int n)
{
    printf("  %-16s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49};

    printf("=== ① 归并排序的完整过程 ===\n");
    printArr("原始", src, N);
    printf("\n");

    int a[N];
    for (int i = 0; i < N; i++) a[i] = src[i];

    g_cmp = g_copy = 0;
    mergeSortRec(a, 0, N - 1, 0);

    printf("\n=== ② 结果 ===\n");
    printArr("排序后", a, N);
    printf("  比较 %lld 次，拷贝 %lld 次\n", g_cmp, g_copy);

    printf("\n=== ③ 归并排序的骨架 ===\n");
    printf("  void mergeSort(int a[], int lo, int hi) {\n");
    printf("      if (lo >= hi) return;              // 递归基：0 或 1 个元素\n");
    printf("      int mid = (lo + hi) / 2;           // 从中间切\n");
    printf("      mergeSort(a, lo, mid);             // 排左半\n");
    printf("      mergeSort(a, mid + 1, hi);         // 排右半\n");
    printf("      merge(a, lo, mid, hi);             // 合并\n");
    printf("  }\n");
    printf("\n  ⭐ 和快排的区别：\n");
    printf("     快排：先分区（大事化小），再递归 —— 从上往下\n");
    printf("     归并：先递归（化到最小），再合并 —— 从下往上\n");

    printf("\n=== ④ 为什么归并是稳定的 ===\n");
    printf("  归并时的关键一行：\n");
    printf("     if (a[i] <= a[j]) 取 a[i]     ← 注意是 <=\n");
    printf("  相等时【优先取左边的】，所以左边相同元素永远排在前面。\n");
    printf("  ⚠️ 如果写成 if (a[i] < a[j])，相等时取右边，就变【不稳定】了！\n");
    printf("  📌 这一行是软考改错题的高频点。\n");

    printf("\n=== ⑤ 归并的复杂度推导 ===\n");
    printf("  树的高度 = log2(n) = log2(8) = 3 层\n");
    printf("  每层归并的总工作量 = n（每个元素被搬一次）\n");
    printf("  总时间 = n × log2(n) = O(n log n)\n");
    printf("\n  ⭐ 每层都是 n，所以：\n");
    printf("     最好 = 最坏 = 平均 = O(n log n)\n");
    printf("     这是它比快排「稳」的地方（快排最坏会退化）。\n");

    printf("\n=== ⑥ 空间为什么是 O(n) ===\n");
    printf("  归并两个有序段时，必须借一个和原数组同样大的辅助数组。\n");
    printf("  本例辅助数组 g_tmp[%d]。\n", N);
    printf("  ⚠️ 这是归并排序的最大缺点。\n");
    printf("     快排 O(log n) 空间、堆排 O(1) 空间，都比归并省。\n");

    printf("\n=== ⑦ 关键性质 ===\n");
    printf("  %-16s %s\n", "项", "值");
    printf("  ----------------------------------------\n");
    printf("  %-16s %s\n", "时间", "O(n log n)（最好=最坏）");
    printf("  %-16s %s\n", "空间", "O(n) ← 缺点");
    printf("  %-16s %s\n", "稳定性", "稳定（<= 保证）");
    printf("  %-16s %s\n", "适合", "链表排序、外部排序");

    printf("\n=== ⑧ 归并排序的两个独特用途 ===\n");
    printf("  1. 链表排序 —— 链表不能用快排（无法随机访问），归并最合适\n");
    printf("     而且链表归并不需要额外空间（只改指针）\n");
    printf("  2. 外部排序 —— 数据大到内存装不下时，\n");
    printf("     分块排好写回磁盘，再多路归并\n");
    printf("  📌 软考选择题问「链表最适合的排序」→ 归并排序。\n");

    return 0;
}
