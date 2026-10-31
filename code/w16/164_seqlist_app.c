/* 164_seqlist_app.c —— 顺序表应用：有序表的集合运算（并、交、差）
 *
 * 软考「线性表」大题最爱的题型：
 *   给定两个递增有序的顺序表 A、B，求 A∪B、A∩B、A-B。
 *
 * 三个算法都用**双指针**，时间 O(n+m)：
 *   A[i] < B[j]  →  A 的元素小
 *   A[i] > B[j]  →  B 的元素小
 *   A[i] == B[j] →  相等
 *
 * 三个运算的差别只在「什么时候把元素放进结果」。
 */

#include <stdio.h>

#define MAXSIZE 40

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

static void show(const char *label, const SqList *L)
{
    printf("  %-14s {", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(", ");
    }
    printf("}\n");
}

static void build(SqList *L, const int a[], int n)
{
    for (int i = 0; i < n; i++) L->data[i] = a[i];
    L->length = n;
}

/* ---------- ① 并集 A ∪ B ---------- */
/* 相等时只放一个；不等时把小的那个放进去 */
void unionSet(const SqList *A, const SqList *B, SqList *C)
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
            j++;
        }
    }
    /* 剩余部分直接接上 */
    while (i < A->length) C->data[k++] = A->data[i++];
    while (j < B->length) C->data[k++] = B->data[j++];

    C->length = k;
}

/* ---------- ② 交集 A ∩ B ---------- */
/* 只有相等时才放进结果 */
void intersectSet(const SqList *A, const SqList *B, SqList *C)
{
    int i = 0, j = 0, k = 0;

    while (i < A->length && j < B->length) {
        if (A->data[i] < B->data[j]) {
            i++;                                /* A 小，A 往前走，丢弃 */
        } else if (A->data[i] > B->data[j]) {
            j++;                                /* B 小，B 往前走，丢弃 */
        } else {
            C->data[k++] = A->data[i];          /* 相等，收下 */
            i++;
            j++;
        }
    }
    C->length = k;                              /* 剩下的都不要 */
}

/* ---------- ③ 差集 A - B（属于 A 但不属于 B）---------- */
void differenceSet(const SqList *A, const SqList *B, SqList *C)
{
    int i = 0, j = 0, k = 0;

    while (i < A->length && j < B->length) {
        if (A->data[i] < B->data[j]) {
            C->data[k++] = A->data[i++];        /* B 里没有这个，收 */
        } else if (A->data[i] > B->data[j]) {
            j++;                                /* B 小，B 往后找 */
        } else {
            i++;                                /* 相等，A 的这个不要 */
            j++;
        }
    }
    /* A 剩下的都是 B 里没有的 */
    while (i < A->length) C->data[k++] = A->data[i++];

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

    printf("\n=== ① 并集 A ∪ B ===\n");
    unionSet(&A, &B, &C);
    show("结果", &C);
    printf("  长度 6 + 6 = 12，去重后 %d 个\n", C.length);
    printf("  ⭐ 相等时只收一个，这是「去重」的关键\n");

    printf("\n=== ② 交集 A ∩ B ===\n");
    intersectSet(&A, &B, &C);
    show("结果", &C);
    printf("  只有 3、5、11 三个同时在两边\n");
    printf("  ⭐ 不等时直接跳过，什么都不收\n");

    printf("\n=== ③ 差集 A - B ===\n");
    differenceSet(&A, &B, &C);
    show("结果", &C);
    printf("  1、7、9 属于 A 但不属于 B\n");
    printf("  ⭐ A 小就收，相等就跳过，B 小就只让 B 前进\n");

    printf("\n=== ④ 三个算法的差别只有一处 ===\n");
    printf("  %-12s %-18s %-18s %s\n", "运算", "A[i] < B[j] 时", "A[i] == B[j] 时", "剩余部分");
    printf("  ----------------------------------------------------------------------\n");
    printf("  %-12s %-18s %-18s %s\n", "并集", "收 A[i]", "收一个", "两边都要接");
    printf("  %-12s %-18s %-18s %s\n", "交集", "跳过 A[i]", "收 A[i]", "都不要");
    printf("  %-12s %-18s %-18s %s\n", "差集", "收 A[i]", "跳过", "只接 A 的");

    printf("\n  ⭐ 记住这张表，三个算法就都记住了 —— 骨架完全一样。\n");

    printf("\n=== ⑤ 复杂度 ===\n");
    printf("  时间 O(n+m)：两个指针都只往前走，总共走 n+m 步\n");
    printf("  空间 O(n+m)：结果表要能装下所有元素\n");
    printf("\n  ⚠️ 前提：A、B 必须**已经有序**。\n");
    printf("     无序的话只能双重循环 O(n×m)，或者先排序 O((n+m)log(n+m))。\n");

    printf("\n=== ⑥ 软考常见变体 ===\n");
    printf("  1. 两个有序表归并成一个（不去重）→ 就是 162 里的 mergeSorted\n");
    printf("  2. 求交集后**保持原顺序**→ 上面就是\n");
    printf("  3. 求 A-B 后统计个数 → 只要 C.length\n");
    printf("  4. 三个表两两运算 → 先算两个，结果再和第三个算\n");

    return 0;
}
