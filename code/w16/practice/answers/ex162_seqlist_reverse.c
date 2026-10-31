/* ex162_seqlist_reverse.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 30

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
    printf("  %-12s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]\n");
}

/* 原地逆置：首尾交换 */
void reverseList(SqList *L)
{
    int i = 0, j = L->length - 1;
    while (i < j) {                 /* ⚠️ i < j，不是 i < length */
        int t = L->data[i];
        L->data[i] = L->data[j];
        L->data[j] = t;
        i++;
        j--;
    }
}

/* 覆盖法删除所有 value */
int removeAll(SqList *L, int value)
{
    int k = 0, removed = 0;
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] != value) {
            L->data[k++] = L->data[i];
        } else {
            removed++;
        }
    }
    L->length = k;
    return removed;
}

int main(void)
{
    /* ---------- 逆置：三组 ---------- */
    printf("=== 逆置 ===\n");
    int a1[] = {1, 2, 3, 4, 5, 6, 7};
    SqList L1; build(&L1, a1, 7);
    show("原表(奇数个)", &L1);
    reverseList(&L1);
    show("逆置后", &L1);

    int a2[] = {1, 2, 3, 4};
    SqList L2; build(&L2, a2, 4);
    show("原表(偶数个)", &L2);
    reverseList(&L2);
    show("逆置后", &L2);

    int a3[] = {42};
    SqList L3; build(&L3, a3, 1);
    show("原表(单个)", &L3);
    reverseList(&L3);
    show("逆置后", &L3);

    printf("\n  ⭐ 偶数个时 i 和 j 会「错身而过」，所以条件是 i < j：\n");
    printf("     [1 2 3 4]：i=0,j=3 换 → i=1,j=2 换 → i=2,j=1 停\n");
    printf("     若写成 i < length，每个元素被换两次，结果不变（等于白做）。\n");

    /* ---------- 删除：两组 ---------- */
    printf("\n=== 删除所有 3 ===\n");
    int b1[] = {3, 5, 3, 7, 3, 9, 1, 3};
    SqList M1; build(&M1, b1, 8);
    show("原表", &M1);
    int r = removeAll(&M1, 3);
    show("删除后", &M1);
    printf("  删掉 %d 个\n", r);

    printf("\n=== 删除所有 9（无命中）===\n");
    int b2[] = {1, 2, 3};
    SqList M2; build(&M2, b2, 3);
    show("原表", &M2);
    r = removeAll(&M2, 9);
    show("删除后", &M2);
    printf("  删掉 %d 个（表不变）\n", r);

    printf("\n=== 覆盖法的正确性 ===\n");
    printf("  k 是「写入位置」，i 是「读取位置」。\n");
    printf("  因为 k <= i 恒成立（k 只在保留时 +1，i 每轮都 +1），\n");
    printf("  所以 data[k] = data[i] 永远写在已经读过的位置上，\n");
    printf("  绝不会覆盖还没读的数据。\n");
    printf("  ⭐ 这是「原地删除」的标准做法，O(n) 时间、O(1) 空间。\n");

    printf("\n=== 对比低效写法 ===\n");
    printf("  ❌ 找到一个就整体前移：\n");
    printf("     for (i = 0; i < n; i++)\n");
    printf("         if (a[i] == v) { 把 i 后面的全部前移; n--; }\n");
    printf("     有 m 个目标就要挪 m 次，每次 O(n) → O(n*m)，最坏 O(n^2)\n");
    printf("  ✅ 覆盖法：一趟扫完，O(n)\n");

    return 0;
}
