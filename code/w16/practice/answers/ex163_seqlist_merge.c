/* ex163_seqlist_merge.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 40

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
    printf("  %-10s {", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(", ");
    }
    printf("}  (length=%d)\n", L->length);
}

void mergeUnique(const SqList *A, const SqList *B, SqList *C)
{
    int i = 0, j = 0, k = 0;

    while (i < A->length && j < B->length) {
        if (A->data[i] < B->data[j]) {
            C->data[k++] = A->data[i++];        /* A 小，收 A */
        } else if (A->data[i] > B->data[j]) {
            C->data[k++] = B->data[j++];        /* B 小，收 B */
        } else {
            C->data[k++] = A->data[i];          /* 相等，只收一个 */
            i++;
            j++;                                /* ⭐ 两个指针都前进 = 去重 */
        }
    }
    while (i < A->length) C->data[k++] = A->data[i++];
    while (j < B->length) C->data[k++] = B->data[j++];

    C->length = k;
}

int main(void)
{
    int a[] = {1, 3, 5, 7, 9, 11};
    int b[] = {2, 3, 5, 8, 11, 13};

    SqList A, B, C;
    build(&A, a, 6);
    build(&B, b, 6);

    printf("=== 输入 ===\n");
    show("A", &A);
    show("B", &B);

    printf("\n=== 合并去重 ===\n");
    mergeUnique(&A, &B, &C);
    show("C", &C);
    printf("  6 + 6 = 12，去重后 %d 个，重复 %d 个（3、5、11）\n",
           C.length, 12 - C.length);

    printf("\n=== 关键：去重只发生在「相等」这一支 ===\n");
    printf("  A[i] < B[j] → 收 A[i]，i++\n");
    printf("  A[i] > B[j] → 收 B[j]，j++\n");
    printf("  A[i] == B[j] → 收一个，i++ 且 j++   ← 两边同时跳过，才不重复\n");
    printf("  ⭐ 如果相等时只 i++，那 B 的这个元素下次还会被收，就重复了。\n");

    printf("\n=== 与「合并但不去重」的区别 ===\n");
    printf("  不去重：相等时随便收一个，然后只让一个指针前进\n");
    printf("  去重  ：相等时收一个，两个指针都前进\n");
    printf("  代码只差一行，结果完全不同 —— 这是软考改错题的高频点。\n");

    printf("\n=== 复杂度 ===\n");
    printf("  时间 O(n+m)：i、j 各走一遍，总共 n+m 步\n");
    printf("  空间 O(n+m)：C 要能装下最多 n+m 个元素\n");
    printf("  ⚠️ 前提：A、B 必须已经有序，否则结果不有序也不正确\n");

    return 0;
}
