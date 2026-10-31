/* 203_heap.c —— 堆与堆排序
 *
 * 堆是完全二叉树，用数组存储（利用完全二叉树的下标规律）。
 *   大顶堆：每个节点 >= 它的孩子（根是最大值）
 *   小顶堆：每个节点 <= 它的孩子（根是最小值）
 *
 * 数组下标（从 1 开始，0 号位不用，方便算孩子）：
 *   节点 i 的左孩子 = 2i，右孩子 = 2i+1，父节点 = i/2
 *
 * 堆排序三步：
 *   ① 建堆（从最后一个非叶子节点开始，向下调整）
 *   ② 堆顶（最大值）和末尾交换，堆大小减 1
 *   ③ 对新堆顶向下调整，恢复堆序
 *   重复 ②③ 直到堆空
 *
 * 复杂度：建堆 O(n)，排序 O(n log n)，空间 O(1)，不稳定。
 */

#include <stdio.h>

#define MAXN 100

/* 向下调整：把 a[i] 下沉到合适位置，使以 i 为根的子树成为大顶堆
 * a 数组下标从 1 开始，n 是堆的大小 */
static void siftDown(int a[], int i, int n)
{
    while (1) {
        int largest = i;
        int left  = 2 * i;
        int right = 2 * i + 1;

        if (left  <= n && a[left]  > a[largest]) largest = left;
        if (right <= n && a[right] > a[largest]) largest = right;

        if (largest == i) break;        /* 已经比两个孩子都大，停止 */

        /* 和较大的孩子交换，继续下沉 */
        int t = a[i];
        a[i] = a[largest];
        a[largest] = t;

        i = largest;
    }
}

/* 建堆：从最后一个非叶子节点 n/2 开始，往前逐个向下调整 */
static void buildHeap(int a[], int n)
{
    for (int i = n / 2; i >= 1; i--) {
        siftDown(a, i, n);
    }
}

/* 堆排序 */
static void heapSort(int a[], int n)
{
    buildHeap(a, n);                    /* ① 建堆 */

    for (int i = n; i > 1; i--) {
        /* ② 堆顶（最大）和末尾交换 */
        int t = a[1];
        a[1] = a[i];
        a[i] = t;

        /* ③ 恢复堆（大小减到 i-1） */
        siftDown(a, 1, i - 1);
    }
}

/* 打印数组（下标 1..n） */
static void show(const char *label, const int a[], int n)
{
    printf("  %-14s [", label);
    for (int i = 1; i <= n; i++) {
        printf("%d", a[i]);
        if (i != n) printf(" ");
    }
    printf("]\n");
}

/* 验证是否是大顶堆 */
static int isMaxHeap(const int a[], int n)
{
    for (int i = 1; i <= n / 2; i++) {
        if (2 * i <= n && a[i] < a[2 * i]) return 0;           /* 左孩子更大 */
        if (2 * i + 1 <= n && a[i] < a[2 * i + 1]) return 0;   /* 右孩子更大 */
    }
    return 1;
}

int main(void)
{
    /* ---------- ① 建堆过程 ---------- */
    printf("=== ① 建堆（大顶堆）===\n");
    int a[MAXN];
    int raw[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};  /* 0 号位占位 */
    int n = 8;
    for (int i = 1; i <= n; i++) a[i] = raw[i];

    show("原始数组", a, n);
    buildHeap(a, n);
    show("建堆后", a, n);
    printf("  是大顶堆？%s\n", isMaxHeap(a, n) ? "是 ✓" : "否 ✗");
    printf("  ⭐ 堆顶 a[1] = %d 是最大值\n", a[1]);

    printf("\n  建堆后的树（按数组顺序）：\n");
    printf("             %d\n", a[1]);
    printf("           /    \\\n");
    printf("         %d        %d\n", a[2], a[3]);
    printf("        /  \\     /  \\\n");
    printf("      %d    %d   %d    %d\n", a[4], a[5], a[6], a[7]);
    printf("     /\n");
    printf("   %d\n", a[8]);
    printf("  ⭐ 每个父节点都 >= 孩子，这就是大顶堆。\n");

    /* ---------- ② 堆排序 ---------- */
    printf("\n=== ② 堆排序 ===\n");
    for (int i = 1; i <= n; i++) a[i] = raw[i];
    show("原始数组", a, n);
    heapSort(a, n);
    show("排序后(升序)", a, n);

    printf("\n  ⭐ 堆排序为什么能得到升序？\n");
    printf("     每次把堆顶（当前最大值）换到末尾，\n");
    printf("     换到末尾的就不再参与堆调整，相当于「固定」了。\n");
    printf("     所以从后往前，依次是最大、次大、...、最小。\n");

    /* ---------- ③ 堆排序 vs 其他排序 ---------- */
    printf("\n=== ③ 堆排序 vs 其他 O(n log n) 排序 ===\n");
    printf("  %-12s %-12s %-10s %-8s\n", "排序", "时间", "空间", "稳定");
    printf("  ------------------------------------------------------\n");
    printf("  %-12s %-12s %-10s %-8s\n", "堆排序", "O(n log n)", "O(1)", "不稳定");
    printf("  %-12s %-12s %-10s %-8s\n", "归并排序", "O(n log n)", "O(n)", "稳定");
    printf("  %-12s %-12s %-10s %-8s\n", "快速排序", "O(n log n)平均", "O(log n)", "不稳定");
    printf("\n  ⭐ 堆排序的独特优势：\n");
    printf("     1. 空间 O(1) —— 原地排序，不需要额外数组\n");
    printf("     2. 最坏也是 O(n log n) —— 不会像快排那样退化到 O(n^2)\n");
    printf("     代价：不稳定，且常数比快排大（实际更慢）。\n");

    /* ---------- ④ 堆的应用：优先级队列 ---------- */
    printf("\n=== ④ 堆的用途：优先级队列 ===\n");
    printf("  堆最常见的用途不是排序，而是「优先级队列」。\n");
    printf("  场景：随时插入元素，随时取「最大/最小」的元素。\n");
    printf("\n  %-16s %-14s %-14s %s\n", "操作", "普通数组", "有序数组", "堆");
    printf("  ------------------------------------------------------\n");
    printf("  %-16s %-14s %-14s %s\n", "取最大", "O(n)", "O(1)", "O(1)");
    printf("  %-16s %-14s %-14s %s\n", "插入", "O(1)", "O(n)", "O(log n)");
    printf("  %-16s %-14s %-14s %s\n", "删除最大", "O(n)", "O(1)", "O(log n)");
    printf("\n  ⭐ 堆的「插入 + 删除」都是 O(log n)，综合最优。\n");

    /* ---------- ⑤ 建堆的复杂度为什么是 O(n) ---------- */
    printf("\n=== ⑤ 建堆复杂度为什么是 O(n) 而不是 O(n log n) ===\n");
    printf("  直觉上：n/2 个节点，每个向下调整 O(log n) → 看着像 O(n log n)。\n");
    printf("  但实际上：\n");
    printf("    最底层（约 n/2 个节点）根本不用调整\n");
    printf("    倒数第二层（约 n/4 个）最多下沉 1 层\n");
    printf("    倒数第三层（约 n/8 个）最多下沉 2 层\n");
    printf("    ...\n");
    printf("  总下沉次数 = 0*(n/2) + 1*(n/4) + 2*(n/8) + ... < n\n");
    printf("  ⭐ 这个级数收敛到 O(n)，所以建堆是线性的。\n");
    printf("     📌 软考选择题考过「建堆复杂度」，答案是 O(n)。\n");

    /* ---------- ⑥ 大顶堆 vs 小顶堆 ---------- */
    printf("\n=== ⑥ 大顶堆 vs 小顶堆 ===\n");
    printf("  大顶堆：a[i] >= a[2i] 且 a[i] >= a[2i+1]（根最大）\n");
    printf("  小顶堆：a[i] <= a[2i] 且 a[i] <= a[2i+1]（根最小）\n");
    printf("  ⭐ 堆排序升序用大顶堆（每次取最大放末尾），\n");
    printf("     降序用小顶堆。\n");
    printf("  📌 判断「这是不是堆」：只需检查每个父节点和孩子的关系。\n");

    return 0;
}
