/* 231_basic_sorts.c —— 三种 O(n^2) 排序：插入、冒泡、选择
 *
 * 三者都是「每次把一个元素放到它该在的位置」，但方式不同：
 *   直接插入：把当前元素插入到前面【已排好序】的部分里（像整理扑克牌）
 *   冒泡    ：相邻两两比较，大的往后浮（像气泡上浮）
 *   选择    ：每轮从后面选出最小的，放到前面
 *
 * 三者复杂度都是 O(n^2)，但：
 *   - 插入、冒泡可以「提前结束」（数据有序时变 O(n)）
 *   - 选择【不能】提前结束（必须扫完才知道最小值）
 *   - 插入、冒泡【稳定】；选择【不稳定】
 */

#include <stdio.h>

#define N 8

static long long g_cmp  = 0;    /* 比较次数 */
static long long g_move = 0;    /* 移动次数 */

/* ==================== ① 直接插入排序 ==================== */
void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        /* 从后往前找位置，比 key 大的都后移一格 */
        while (j >= 0) {
            g_cmp++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                g_move++;
                j--;
            } else {
                break;                  /* 找到位置了，提前停 */
            }
        }
        a[j + 1] = key;                 /* 插入 */
        g_move++;
    }
}

/* ==================== ② 冒泡排序（带提前退出）==================== */
void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            g_cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                g_move += 3;
                swapped = 1;
            }
        }
        if (!swapped) break;            /* 本趟无交换 → 已有序 */
    }
}

/* ==================== ③ 选择排序 ==================== */
void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            g_cmp++;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int t = a[i];
            a[i] = a[minIdx];
            a[minIdx] = t;
            g_move += 3;
        }
    }
}

/* ---------- 辅助 ---------- */
static void show(const char *label, const int a[], int n)
{
    printf("  %-16s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

/* 跑一种排序并输出统计 */
static void runOne(const char *name, void (*fn)(int[], int),
                   const int src[], int n)
{
    int work[N];
    for (int i = 0; i < n; i++) work[i] = src[i];

    g_cmp = g_move = 0;
    fn(work, n);

    printf("  %-8s 比较 %-4lld 移动 %-4lld 结果：", name, g_cmp, g_move);
    for (int i = 0; i < n; i++) printf("%d ", work[i]);
    printf("\n");
}

int main(void)
{
    /* 三种数据形态 */
    int random[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int sorted[] = {13, 27, 38, 49, 49, 65, 76, 97};
    int reversed[] = {97, 76, 65, 49, 49, 38, 27, 13};

    printf("=== ① 乱序数据 ===\n");
    show("原始", random, N);
    runOne("插入", insertionSort, random, N);
    runOne("冒泡", bubbleSort, random, N);
    runOne("选择", selectionSort, random, N);

    printf("\n=== ② 已排好序 ===\n");
    show("原始", sorted, N);
    runOne("插入", insertionSort, sorted, N);
    runOne("冒泡", bubbleSort, sorted, N);
    runOne("选择", selectionSort, sorted, N);

    printf("\n=== ③ 完全逆序 ===\n");
    show("原始", reversed, N);
    runOne("插入", insertionSort, reversed, N);
    runOne("冒泡", bubbleSort, reversed, N);
    runOne("选择", selectionSort, reversed, N);

    printf("\n=== 三个关键结论 ===\n");
    printf("  1. 数据已有序时：\n");
    printf("     插入：比较 %d 次（= n-1）。本程序统计「赋值」算移动，得 %d 次，\n",
           N - 1, N - 1);
    printf("           但这 %d 次都是 key 写回原位、没搬动别的元素；\n", N - 1);
    printf("           教材按「记录移动」算，记为移动 0 次。两种口径都对，\n");
    printf("           关键是：退化成 O(n)。\n");
    printf("     冒泡加提前退出只跑 1 趟 → 比较 7 次、移动 0 次 → O(n)\n");
    printf("     选择仍然要比较 n(n-1)/2 次 → 与数据无关！\n");

    printf("\n  2. 选择排序的比较次数恒为 n(n-1)/2 = %d\n", N * (N - 1) / 2);
    printf("     因为无论数据怎样，都要扫完才知道最小值在哪。\n");

    printf("\n  3. 移动次数：\n");
    printf("     插入：逆序时最多，约 n(n-1)/2 次移动\n");
    printf("     冒泡：每次交换算 3 次移动（临时变量），逆序时最多\n");
    printf("     选择：最多 n-1 次交换，是三者的最小值 —— 交换代价高时选它\n");

    printf("\n=== 稳定性 ===\n");
    printf("  本例数据里有两个 49（第 1 个和第 8 个）。\n");
    printf("  稳定 = 排序后这两个 49 的相对顺序不变。\n");
    printf("    ✅ 插入、冒泡 —— 稳定（只和相邻/相邻区间比，不会跨过相等元素）\n");
    printf("    ❌ 选择     —— 不稳定（交换是「远距离」的，可能跨过相等元素）\n");
    printf("\n  📌 选择排序不稳定的例子：\n");
    printf("     [2a, 2b, 1] → 第一轮选最小 1，和 2a 交换 → [1, 2b, 2a]\n");
    printf("     2a 和 2b 的相对顺序变了！\n");

    printf("\n=== 复杂度总表 ===\n");
    printf("  %-8s %-14s %-14s %-12s %-8s\n", "排序", "最好", "最坏", "空间", "稳定");
    printf("  ------------------------------------------------------------------\n");
    printf("  %-8s %-14s %-14s %-12s %-8s\n", "插入", "O(n)", "O(n^2)", "O(1)", "稳定");
    printf("  %-8s %-14s %-14s %-12s %-8s\n", "冒泡", "O(n)", "O(n^2)", "O(1)", "稳定");
    printf("  %-8s %-14s %-14s %-12s %-8s\n", "选择", "O(n^2)", "O(n^2)", "O(1)", "不稳定");
    printf("\n  ⚠️ 选择排序的「最好」也是 O(n^2)，这是它和另外两个的最大区别。\n");

    printf("\n=== 一趟排序后的效果（软考常考）===\n");
    printf("  插入排序：前 i+1 个元素局部有序（但不一定是最终位置）\n");
    printf("  冒泡排序：最大的元素到了最后（或最小的到了最前）\n");
    printf("  选择排序：最小的元素到了最前\n");
    printf("  ⭐ 题目给「第一趟后的结果」，要用这个判断是哪种排序。\n");

    return 0;
}
