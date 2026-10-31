/* 243_radix_sort.c —— 基数排序 + 全套排序对比
 *
 * 基数排序（LSD，最低位优先）：
 *   不是比较排序！按「个位 → 十位 → 百位」依次分配到 10 个桶，再收集回来。
 *   每趟分配 + 收集是 O(n)，做 d 趟（d = 最大位数）→ O(d·n)
 *
 * 关键结论：
 *   时间 O(d(n+r))，d 是位数，r 是基数（十进制 r=10）
 *   空间 O(n+r)
 *   【稳定】（收集时必须按原顺序，这是它能工作的前提）
 *
 * 本文件最后给出一张「所有排序的实测对比表」。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10

static long long g_ops = 0;

/* ==================== 基数排序 ==================== */
void radixSort(int a[], int n)
{
    int maxVal = a[0];
    for (int i = 1; i < n; i++) if (a[i] > maxVal) maxVal = a[i];

    int tmp[N];

    /* 从个位开始，逐位分配 + 收集 */
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int bucket[10] = {0};           /* 每个桶装几个 */

        /* ① 统计每个桶的元素个数 */
        for (int i = 0; i < n; i++) {
            bucket[(a[i] / exp) % 10]++;
            g_ops++;
        }

        printf("    exp=%-4d 各桶个数：", exp);
        for (int b = 0; b < 10; b++) printf("%d ", bucket[b]);
        printf("\n");

        /* ② 累加，算出每个桶的「结束位置」 */
        for (int b = 1; b < 10; b++) bucket[b] += bucket[b - 1];

        /* ③ 从后往前放（⭐ 保证稳定） */
        for (int i = n - 1; i >= 0; i--) {
            int d = (a[i] / exp) % 10;
            tmp[--bucket[d]] = a[i];
            g_ops++;
        }

        /* ④ 拷回 */
        for (int i = 0; i < n; i++) a[i] = tmp[i];
        g_ops++;

        printf("    本趟结果：");
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }
}

/* ==================== 其他排序（用于对比）==================== */
static long long g_cmp;

static void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && (g_cmp++, a[j] > key)) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}

static void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int sw = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            g_cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; sw = 1;
            }
        }
        if (!sw) break;
    }
}

static void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int mi = i;
        for (int j = i + 1; j < n; j++) {
            g_cmp++;
            if (a[j] < a[mi]) mi = j;
        }
        if (mi != i) { int t = a[i]; a[i] = a[mi]; a[mi] = t; }
    }
}

static void shellSort(int a[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int key = a[i], j = i - gap;
            while (j >= 0 && (g_cmp++, a[j] > key)) { a[j + gap] = a[j]; j -= gap; }
            a[j + gap] = key;
        }
}

static void quickSortRec(int a[], int lo, int hi)
{
    if (lo >= hi) return;
    int p = a[lo], i = lo, j = hi;
    while (i < j) {
        while (i < j && (g_cmp++, a[j] >= p)) j--;
        if (i < j) a[i] = a[j];
        while (i < j && (g_cmp++, a[i] <= p)) i++;
        if (i < j) a[j] = a[i];
    }
    a[i] = p;
    quickSortRec(a, lo, i - 1);
    quickSortRec(a, i + 1, hi);
}

static void mergeSortRec(int a[], int lo, int hi, int tmp[])
{
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    mergeSortRec(a, lo, mid, tmp);
    mergeSortRec(a, mid + 1, hi, tmp);

    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        g_cmp++;
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= hi)  tmp[k++] = a[j++];
    for (int t = lo; t <= hi; t++) a[t] = tmp[t];
}

/* ==================== 稳定性验证 ==================== */
/* 用「值 + 原始下标」的双关键字来测稳定性
 * 排序后检查：相同的值，原始下标是否仍然递增 */
typedef struct {
    int val;
    int idx;
} Item;

static int stableInsertion(Item a[], int n)
{
    for (int i = 1; i < n; i++) {
        Item key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j].val > key.val) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
    return 1;
}

static int stableSelection(Item a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int mi = i;
        for (int j = i + 1; j < n; j++) if (a[j].val < a[mi].val) mi = j;
        if (mi != i) { Item t = a[i]; a[i] = a[mi]; a[mi] = t; }
    }
    return 0;       /* 声明不稳定 */
}

static int checkStable(Item a[], int n)
{
    for (int i = 1; i < n; i++) {
        if (a[i].val == a[i - 1].val && a[i].idx < a[i - 1].idx) return 0;
    }
    return 1;
}

int main(void)
{
    /* ---------- ① 基数排序过程 ---------- */
    printf("=== ① 基数排序过程 ===\n");
    int a[N] = {329, 457, 657, 839, 436, 720, 355, 123, 90, 5};
    printf("  原始：");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("\n\n");

    g_ops = 0;
    radixSort(a, N);

    printf("\n  结果：");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("\n  操作次数 %lld\n", g_ops);

    printf("\n  ⭐ 为什么从最低位开始？\n");
    printf("     低位先排，高位后排。高位排在后面，优先级更高，\n");
    printf("     会把低位已经排好的顺序「覆盖」掉，所以最终是正确的。\n");
    printf("     ⚠️ 反过来（从高位开始）就不对，那是 MSD 基数排序，要递归分桶。\n");

    printf("\n  ⭐ 为什么每趟必须「从后往前」放？\n");
    printf("     为了保证【稳定】：相同的当前位，原来在前面的仍在前面。\n");
    printf("     如果从前往后放，相同位的相对顺序会反转 → 不稳定 → 结果可能错。\n");

    /* ---------- ② 全套排序实测对比 ---------- */
    printf("\n=== ② 两种数据下各排序的比较次数 ===\n");
    srand(42);
    int n = 2000;
    int *big = (int *)malloc(sizeof(int) * (size_t)n);
    int *sortedBig = (int *)malloc(sizeof(int) * (size_t)n);
    int *work = (int *)malloc(sizeof(int) * (size_t)n);
    int *msTmp = (int *)malloc(sizeof(int) * (size_t)n);

    for (int i = 0; i < n; i++) big[i] = rand() % 10000;
    memcpy(sortedBig, big, sizeof(int) * (size_t)n);

    /* 先把 sortedBig 排好作为「已有序」数据 */
    g_cmp = 0;
    quickSortRec(sortedBig, 0, n - 1);

    printf("  n = %d\n\n", n);
    printf("  %-12s %-18s %-18s %s\n", "排序", "随机数据", "已有序数据", "是否受数据影响");
    printf("  --------------------------------------------------------------------\n");

    struct {
        const char *name;
        void (*fn)(int[], int);
        int isQuick;                /* 快排签名不同，特殊处理 */
        int isMerge;
    } sorts[] = {
        {"插入", insertionSort, 0, 0},
        {"冒泡", bubbleSort, 0, 0},
        {"选择", selectionSort, 0, 0},
        {"希尔", shellSort, 0, 0},
        {"快速", NULL, 1, 0},
        {"归并", NULL, 0, 1}
    };

    for (int s = 0; s < 6; s++) {
        long long c1, c2;

        memcpy(work, big, sizeof(int) * (size_t)n);
        g_cmp = 0;
        if (sorts[s].isQuick)      quickSortRec(work, 0, n - 1);
        else if (sorts[s].isMerge) mergeSortRec(work, 0, n - 1, msTmp);
        else                       sorts[s].fn(work, n);
        c1 = g_cmp;

        memcpy(work, sortedBig, sizeof(int) * (size_t)n);
        g_cmp = 0;
        if (sorts[s].isQuick)      quickSortRec(work, 0, n - 1);
        else if (sorts[s].isMerge) mergeSortRec(work, 0, n - 1, msTmp);
        else                       sorts[s].fn(work, n);
        c2 = g_cmp;

        printf("  %-12s %-18lld %-18lld %s\n", sorts[s].name, c1, c2,
               (c2 < c1 / 4) ? "差很多（有序时变快）" :
               (c2 > c1 * 4) ? "差很多（有序时变慢）" : "差不多");
    }

    printf("\n  ⭐ 三个值得注意的现象：\n");
    printf("     1. 插入/冒泡在「已有序」时比较次数暴跌 → 能提前结束\n");
    printf("     2. 选择排序两次完全一样 → 与数据无关\n");
    printf("     3. 快速排序在「已有序」时反而暴增 → 这就是最坏情况！\n");

    /* ---------- ③ 稳定性实测 ---------- */
    printf("\n=== ③ 稳定性实测 ===\n");
    printf("  数据：[2a, 2b, 1, 3]，下标区分相同值\n");
    printf("     选这个数据是因为：第一轮把最小的 1 换到最前，\n");
    printf("     正好会把 2a 换到 2b 后面 —— 能暴露选择排序的不稳定。\n");

    Item base[] = {{2, 0}, {2, 1}, {1, 2}, {3, 3}};
    Item t1[4], t2[4];
    memcpy(t1, base, sizeof(base));
    memcpy(t2, base, sizeof(base));

    stableInsertion(t1, 4);
    printf("\n  插入排序后：");
    for (int i = 0; i < 4; i++) printf("%d#%d ", t1[i].val, t1[i].idx);
    printf("\n  → %s\n", checkStable(t1, 4) ? "2#0 仍在 2#1 前，稳定 ✓" : "不稳定");

    stableSelection(t2, 4);
    printf("\n  选择排序后：");
    for (int i = 0; i < 4; i++) printf("%d#%d ", t2[i].val, t2[i].idx);
    printf("\n  → %s\n", checkStable(t2, 4) ? "稳定" : "2#1 跑到了 2#0 前面，不稳定 ✓");

    printf("\n  ⭐ 选择排序为什么不稳定：\n");
    printf("     [2a 2b 1 3] → 第一轮找最小是 1（下标 2），\n");
    printf("     把 a[0] 和 a[2] 交换 → [1 2b 2a 3]\n");
    printf("     ⚠️ 这个交换「跨越」了 2b，导致相对顺序反转。\n");
    printf("     根源：选择排序的交换是【远距离】的。\n");

    /* ---------- ④ 总表 ---------- */
    printf("\n=== ④ 所有排序的总表（这张表要背）===\n");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "排序", "最好", "最坏", "空间", "稳定性", "一趟后");
    printf("  ----------------------------------------------------------------------------------\n");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "直接插入", "O(n)", "O(n^2)", "O(1)", "稳定", "前 i 个局部有序");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "冒泡", "O(n)", "O(n^2)", "O(1)", "稳定", "最大到最后");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "选择", "O(n^2)", "O(n^2)", "O(1)", "不稳定", "最小到最前");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "希尔", "O(n^1.3)", "O(n^1.3)", "O(1)", "不稳定", "更接近有序");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "快速", "O(nlogn)", "O(n^2)", "O(logn)", "不稳定", "基准归位");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "归并", "O(nlogn)", "O(nlogn)", "O(n)", "稳定", "局部有序");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "堆", "O(nlogn)", "O(nlogn)", "O(1)", "不稳定", "堆顶归位");
    printf("  %-10s %-12s %-12s %-12s %-10s %s\n",
           "基数", "O(d(n+r))", "O(d(n+r))", "O(n+r)", "稳定", "按位有序");

    printf("\n=== ⑤ 怎么记稳定性 ===\n");
    printf("  稳定的：插入、冒泡、归并、基数    → 「插冒归基」\n");
    printf("  不稳定的：选择、希尔、快速、堆    → 「选希快堆」\n");
    printf("  ⭐ 口诀：插冒归基稳，选希快堆晃。\n");

    printf("\n=== ⑥ 什么时候用哪个 ===\n");
    printf("  n 很小（< 50）      → 插入排序（简单，常数小）\n");
    printf("  数据基本有序         → 插入排序（O(n)）\n");
    printf("  要求稳定            → 归并排序 / 插入\n");
    printf("  空间紧张            → 堆排序（O(1)）\n");
    printf("  一般情况最快         → 快速排序\n");
    printf("  链表排序            → 归并排序\n");
    printf("  整数且范围不大       → 基数排序（O(dn) 线性）\n");

    free(big); free(sortedBig); free(work); free(msTmp);
    return 0;
}
