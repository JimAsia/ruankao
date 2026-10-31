/* 241_quick_sort.c —— 快速排序
 *
 * 思路（分治）：
 *   ① 选一个「基准」（pivot），把数组分成两半：
 *      左边都 <= 基准，右边都 >= 基准（这叫「分区 partition」）
 *   ② 基准就位（它的最终位置确定了）
 *   ③ 对左右两部分递归做同样的事
 *
 * 关键结论（软考必考）：
 *   平均 O(n log n)，最坏 O(n^2)（已有序 + 取首元素为基准）
 *   空间 O(log n)（递归栈）
 *   【不稳定】
 *   一趟分区后，基准元素的位置就【最终确定】了
 */

#include <stdio.h>

#define N 8

static long long g_cmp  = 0;
static long long g_swap = 0;
static int g_depth_max  = 0;

static void show(const char *label, const int a[], int lo, int hi)
{
    printf("  %-14s [", label);
    for (int i = lo; i <= hi; i++) {
        printf("%d", a[i]);
        if (i != hi) printf(" ");
    }
    printf("]\n");
}

/* ==================== 分区（Hoare 挖坑法）==================== */
/* 返回基准的最终位置 */
int partition(int a[], int lo, int hi)
{
    int pivot = a[lo];                  /* 取第一个元素为基准 */
    int i = lo, j = hi;
    int step = 0;

    printf("    基准 = %d\n", pivot);

    while (i < j) {
        /* ① j 从右往左找「比基准小」的 */
        while (i < j && a[j] >= pivot) { g_cmp++; j--; }
        if (i < j) {
            a[i] = a[j];                /* 填到左边的坑 */
            g_swap++;
            printf("      第 %d 步：a[%d]=%d 填到 i=%d\n", ++step, j, a[j], i);
        }

        /* ② i 从左往右找「比基准大」的 */
        while (i < j && a[i] <= pivot) { g_cmp++; i++; }
        if (i < j) {
            a[j] = a[i];                /* 填到右边的坑 */
            g_swap++;
            printf("      第 %d 步：a[%d]=%d 填到 j=%d\n", ++step, i, a[i], j);
        }
    }

    a[i] = pivot;                       /* 基准放到最终位置 */
    g_swap++;
    printf("      基准 %d 归位到下标 %d\n", pivot, i);

    return i;
}

/* ==================== 快速排序 ==================== */
void quickSort(int a[], int lo, int hi, int depth)
{
    if (depth > g_depth_max) g_depth_max = depth;

    if (lo >= hi) return;               /* 0 或 1 个元素，不用排 */

    printf("  区间 [%d, %d]", lo, hi);
    show("当前", a, lo, hi);

    int pivotPos = partition(a, lo, hi);

    show("分区后", a, lo, hi);
    printf("\n");

    quickSort(a, lo, pivotPos - 1, depth + 1);      /* 左半 */
    quickSort(a, pivotPos + 1, hi, depth + 1);      /* 右半 */
}

/* ---------- 辅助 ---------- */
static void copyArr(int dst[], const int src[], int n)
{
    for (int i = 0; i < n; i++) dst[i] = src[i];
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

/* ==================== 静默版（只为统计，不打印）==================== */
static int g_depth;

static void qsSilent(int a[], int lo, int hi)
{
    if (lo >= hi) return;

    g_depth++;
    int pivot = a[lo];
    int i = lo, j = hi;
    while (i < j) {
        while (i < j && a[j] >= pivot) { g_cmp++; j--; }
        if (i < j) { a[i] = a[j]; g_swap++; }
        while (i < j && a[i] <= pivot) { g_cmp++; i++; }
        if (i < j) { a[j] = a[i]; g_swap++; }
    }
    a[i] = pivot;
    g_swap++;

    qsSilent(a, lo, i - 1);
    qsSilent(a, i + 1, hi);
}

/* 跑一次统计，返回比较次数，深度写入 *depth */
static long long measure(int a[], int n, int *depth)
{
    int work[N];
    copyArr(work, a, n);
    g_cmp = g_swap = 0;
    g_depth = 0;

    qsSilent(work, 0, n - 1);

    *depth = g_depth;
    return g_cmp;
}

int main(void)
{
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49};

    /* ---------- 完整过程 ---------- */
    printf("=== ① 快速排序的完整过程 ===\n");
    printArr("原始", src, N);
    printf("\n");

    int a[N];
    copyArr(a, src, N);
    g_cmp = g_swap = 0;
    g_depth_max = 0;

    quickSort(a, 0, N - 1, 1);

    printf("=== ② 结果 ===\n");
    printArr("排序后", a, N);
    printf("  递归版比较 %lld 次，赋值 %lld 次，递归最大深度 %d\n",
           g_cmp, g_swap, g_depth_max);

    /* ---------- 最坏情况：随机 vs 已有序 ---------- */
    printf("\n=== ③ 最坏情况：数据已有序 + 取首元素为基准 ===\n");
    int sorted[N] = {13, 27, 38, 49, 49, 65, 76, 97};
    int reversed[N] = {97, 76, 65, 49, 49, 38, 27, 13};
    printArr("随机数据", src, N);
    printArr("已有序", sorted, N);
    printArr("完全逆序", reversed, N);

    int d1, d2, d3;
    long long c1 = measure(src, N, &d1);
    long long c2 = measure(sorted, N, &d2);
    long long c3 = measure(reversed, N, &d3);

    printf("\n  %-14s %-16s %s\n", "数据形态", "比较次数", "递归深度");
    printf("  ------------------------------------------------\n");
    printf("  %-14s %-16lld %d\n", "随机", c1, d1);
    printf("  %-14s %-16lld %d\n", "已有序", c2, d2);
    printf("  %-14s %-16lld %d\n", "完全逆序", c3, d3);

    printf("\n  ⭐ 已有序时比较 %lld 次 = n(n-1)/2 = %d —— 退化成了 O(n^2)！\n",
           c2, N * (N - 1) / 2);
    printf("     递归深度 %d，接近 n（随机数据只有 %d）—— 空间也退化了。\n", d2, d1);
    printf("     原因：每次选的基准都是最小值，分区后一边空、一边 n-1 个。\n");
    printf("\n  📌 这就是「快排最坏 O(n^2)」的具体场景，软考必考。\n");
    printf("     对比：随机数据只比较 %lld 次、深度 %d。\n", c1, d1);

    /* ---------- 怎么避免最坏 ---------- */
    printf("\n=== ④ 三种避免最坏情况的方法 ===\n");
    printf("  1. 随机选基准（随机化快排）\n");
    printf("  2. 三数取中（取首、中、尾的中位数作基准）\n");
    printf("  3. 数据量小时改用插入排序（小于 10 个元素时）\n");
    printf("\n  实测：本程序用「取首元素」是最简单的写法，但最怕有序数据。\n");

    /* ---------- 关键性质 ---------- */
    printf("\n=== ⑤ 快速排序的关键性质 ===\n");
    printf("  %-16s %s\n", "项", "值");
    printf("  ----------------------------------------\n");
    printf("  %-16s %s\n", "平均时间", "O(n log n)");
    printf("  %-16s %s\n", "最坏时间", "O(n^2)（已有序 + 取首元素）");
    printf("  %-16s %s\n", "空间", "O(log n)（递归栈）");
    printf("  %-16s %s\n", "稳定性", "不稳定");
    printf("  %-16s %s\n", "一趟效果", "基准元素归位（位置最终确定）");

    printf("\n  ⭐ 快排为什么平均快？\n");
    printf("     每次分区大致二分，递归 log n 层，每层扫一遍 n 个元素\n");
    printf("     → n × log n。而且常数因子小（原地交换，缓存友好）。\n");

    printf("\n=== ⑥ 为什么不稳定 ===\n");
    printf("  分区时是「远距离交换」：a[i] = a[j] 可能跨过相等元素。\n");
    printf("  例：[2a, 2b, 1]，基准 2a：j 找到 1，a[0]=1 → [1, 2b, 2a]\n");
    printf("  2a 和 2b 的相对顺序变了。\n");

    return 0;
}
