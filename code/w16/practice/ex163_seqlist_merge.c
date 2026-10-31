/* ex163_seqlist_merge.c —— 合并两个有序表并去重
 *
 * 要求：
 *   1. mergeUnique(A, B, C)：把两个【升序】表合并到 C，结果仍升序，且【去掉重复】
 *   2. 输出 C 的长度，并和 n+m 对比，说明去掉了几个
 *
 * 测试数据：
 *   A = 1 3 5 7 9 11
 *   B = 2 3 5 8 11 13
 *   期望 C = 1 2 3 5 7 8 9 11 13（9 个）
 *
 * 提示：
 *   双指针 i、j 分别扫 A、B
 *     A[i] < B[j] → 收 A[i]，i++
 *     A[i] > B[j] → 收 B[j]，j++
 *     A[i] == B[j] → 收一个，i++、j++ 都前进（这就是去重）
 *   某一方走完后，另一方剩余直接接上
 */

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
    printf("}\n");
}

/* TODO 1：合并并去重 */
void mergeUnique(const SqList *A, const SqList *B, SqList *C)
{
    (void)A; (void)B; (void)C;
}

int main(void)
{
    int a[] = {1, 3, 5, 7, 9, 11};
    int b[] = {2, 3, 5, 8, 11, 13};

    SqList A, B, C;
    build(&A, a, 6);
    build(&B, b, 6);

    /* TODO 2：调用 mergeUnique 并输出 */

    /* TODO 3：输出「6 + 6 = 12，去重后 X 个」 */

    return 0;
}
