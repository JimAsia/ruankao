/* ex164_seqlist_partition.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 20

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

static void build(SqList *L, const int a[], int n)
{
    for (int i = 0; i < n; i++) L->data[i] = a[i];
    L->length = n;
}

void show(const char *label, const SqList *L)
{
    printf("  %-10s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]\n");
}

/* 双指针分割 */
void partition(SqList *L, int x)
{
    int i = 0, j = L->length - 1;

    while (i < j) {
        /* i 往后找第一个 >= x 的 */
        while (i < j && L->data[i] < x) i++;
        /* j 往前找第一个 < x 的 */
        while (i < j && L->data[j] >= x) j--;

        if (i < j) {
            int t = L->data[i];
            L->data[i] = L->data[j];
            L->data[j] = t;
            i++;
            j--;
        }
    }
}

static int checkPartition(const SqList *L, int x)
{
    int i = 0;
    while (i < L->length && L->data[i] < x) i++;
    while (i < L->length && L->data[i] >= x) i++;
    return i == L->length;
}

int main(void)
{
    /* ---------- 主测试 ---------- */
    printf("=== 主测试：x = 5 ===\n");
    int a[] = {8, 3, 9, 1, 5, 7, 2, 6};
    SqList L; build(&L, a, 8);
    show("原表", &L);
    partition(&L, 5);
    show("分割后", &L);
    printf("  分割%s\n", checkPartition(&L, 5) ? "正确 ✓" : "错误 ✗");

    printf("\n  ⭐ 前 3 个都 < 5（2 3 1），后面 5 个都 >= 5（9 5 7 8 6）。\n");
    printf("     注意内部顺序被打乱了 —— 这是「不稳定」的分割。\n");

    /* ---------- 边界：全是小值 ---------- */
    printf("\n=== 边界 1：全是小值 ===\n");
    int b[] = {1, 2, 3, 4};
    SqList L2; build(&L2, b, 4);
    show("原表", &L2);
    partition(&L2, 10);
    show("分割后", &L2);
    printf("  分割%s（一个都不该动）\n", checkPartition(&L2, 10) ? "正确 ✓" : "错误 ✗");

    /* ---------- 边界：全是大值 ---------- */
    printf("\n=== 边界 2：全是大值 ===\n");
    int c[] = {10, 20, 30};
    SqList L3; build(&L3, c, 3);
    show("原表", &L3);
    partition(&L3, 5);
    show("分割后", &L3);
    printf("  分割%s（一个都不该动）\n", checkPartition(&L3, 5) ? "正确 ✓" : "错误 ✗");

    /* ---------- 边界：空表 ---------- */
    printf("\n=== 边界 3：空表 ===\n");
    SqList L4; L4.length = 0;
    partition(&L4, 5);              /* 不能崩 */
    show("分割后", &L4);
    printf("  空表不崩 ✓\n");

    printf("\n=== 为什么内层循环也要写 i < j ===\n");
    printf("  如果只写 while (L->data[i] < x) i++，\n");
    printf("  遇到「全是小值」的情况 i 会一路冲出数组，越界崩溃。\n");
    printf("  ⭐ 双指针的每个内层循环都必须带 i < j 保护。\n");

    printf("\n=== 稳定分割的代价 ===\n");
    printf("  本题的算法【不稳定】：相等元素的相对顺序会变。\n");
    printf("  要做到稳定且 O(n) 时间，必须用 O(n) 辅助空间（两边各存一份再拼）。\n");
    printf("  原地 + 稳定 + O(n) 时间 —— 三者不可兼得。\n");
    printf("  📌 这就是快速排序「不稳定」的根本原因：它用的就是这个分割。\n");

    return 0;
}
