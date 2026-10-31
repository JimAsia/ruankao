/* ex235_stability.c —— 参考答案 */

#include <stdio.h>

#define N 4

typedef struct {
    int val;
    int idx;
} Item;

void insertionSort(Item a[], int n)
{
    for (int i = 1; i < n; i++) {
        Item key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j].val > key.val) {   /* 严格大于才交换 → 稳定 */
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void bubbleSort(Item a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int sw = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j].val > a[j + 1].val) {       /* 严格大于 → 稳定 */
                Item t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                sw = 1;
            }
        }
        if (!sw) break;
    }
}

void selectionSort(Item a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int mi = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j].val < a[mi].val) mi = j;    /* 严格小于 → 不越过相等元素 */
        }
        if (mi != i) {
            /* ⚠️ 这个交换是「远距离」的，会跨越中间所有元素 */
            Item t = a[i];
            a[i] = a[mi];
            a[mi] = t;
        }
    }
}

int checkStable(const Item a[], int n)
{
    for (int i = 1; i < n; i++) {
        if (a[i].val == a[i - 1].val && a[i].idx < a[i - 1].idx) return 0;
    }
    return 1;
}

static void printItems(const char *label, const Item a[], int n)
{
    printf("  %-14s ", label);
    for (int i = 0; i < n; i++) printf("%d#%d ", a[i].val, a[i].idx);
    printf("\n");
}

static void copyItems(Item dst[], const Item src[], int n)
{
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

int main(void)
{
    Item base[N] = {{2, 0}, {2, 1}, {1, 2}, {3, 3}};
    Item work[N];

    printf("=== 数据：[2#0, 2#1, 1#2, 3#3] ===\n");
    printItems("原始", base, N);
    printf("  ⭐ #0 #1 是原始下标，稳定 = 排完后 2#0 仍在 2#1 前面\n\n");

    struct {
        const char *name;
        void (*fn)(Item[], int);
    } sorts[] = {
        {"插入", insertionSort},
        {"冒泡", bubbleSort},
        {"选择", selectionSort}
    };

    for (int s = 0; s < 3; s++) {
        copyItems(work, base, N);
        sorts[s].fn(work, N);
        printf("  %-6s 排序后：", sorts[s].name);
        for (int i = 0; i < N; i++) printf("%d#%d ", work[i].val, work[i].idx);
        printf("→ %s\n", checkStable(work, N) ? "稳定 ✓" : "不稳定 ✗");
    }

    printf("\n=== 选择排序为什么不稳定 ===\n");
    printf("  第 1 轮：找最小值 1（下标 2），和 a[0] 交换\n");
    printf("     [2#0, 2#1, 1#2, 3#3]\n");
    printf("       ↑___________↑  这两个交换\n");
    printf("     → [1#2, 2#1, 2#0, 3#3]\n");
    printf("  ⚠️ 2#0 被丢到了 2#1 后面 → 相对顺序反转。\n");
    printf("  ⭐ 根源：这个交换跨越了 2#1，是「远距离」操作。\n");
    printf("     而插入/冒泡只和相邻元素打交道，不会跨过相等元素。\n");

    printf("\n=== 结论 ===\n");
    printf("  稳定：插入、冒泡\n");
    printf("  不稳定：选择\n");
    printf("  ⭐ 口诀：插冒归基稳，选希快堆晃。\n");

    printf("\n=== 一个细节 ===\n");
    printf("  插入和冒泡用的是「严格大于」（>），不是「大于等于」（>=）。\n");
    printf("  如果用 >=，相等时也会交换 → 稳定性就丢了。\n");
    printf("  📌 这个符号是软考改错题的高频点。\n");

    return 0;
}
