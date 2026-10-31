/* ex235_stability.c —— 稳定性验证（用双关键字实测）
 *
 * 要求：
 *   1. 对「插入、冒泡、选择」三种排序，用「值 + 原始下标」实测稳定性
 *   2. 找出一个能让选择排序暴露不稳定的数据
 *
 * 判据：排序后，所有相同值的元素，原始下标必须仍然递增。
 *
 * 测试数据（关键）：
 *   [2a, 2b, 1, 3]  ← 第一轮把 1 换到最前时，会跨越 2b
 *
 * 期望：
 *   插入：[1, 2a, 2b, 3] → 稳定
 *   冒泡：[1, 2a, 2b, 3] → 稳定
 *   选择：[1, 2b, 2a, 3] → 不稳定（2b 跑到 2a 前面）
 *
 * 提示：
 *   定义一个带 idx 的结构体，排序时只比较 val
 *   排完检查：相邻且 val 相同的，idx 是否递增
 */

#include <stdio.h>

#define N 4

typedef struct {
    int val;
    int idx;        /* 原始下标，用来判断稳定性 */
} Item;

/* TODO 1：插入排序（按 val 比较） */
void insertionSort(Item a[], int n)
{
    (void)a; (void)n;
}

/* TODO 2：冒泡排序 */
void bubbleSort(Item a[], int n)
{
    (void)a; (void)n;
}

/* TODO 3：选择排序 */
void selectionSort(Item a[], int n)
{
    (void)a; (void)n;
}

/* TODO 4：检查稳定性，返回 1 稳定 / 0 不稳定 */
int checkStable(const Item a[], int n)
{
    (void)a; (void)n;
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

    /* TODO 5：三种排序各跑一次，输出并判断稳定性 */

    printf("\n=== 结论 ===\n");
    printf("  稳定：插入、冒泡（只和相邻比，相等时不交换）\n");
    printf("  不稳定：选择（远距离交换，会跨越相等元素）\n");
    printf("  ⭐ 记忆口诀：插冒归基稳，选希快堆晃。\n");

    return 0;
}
