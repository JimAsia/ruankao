/* ex165_seqlist_rotate.c —— 参考答案 */

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
    printf("  %-14s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]\n");
}

static void reverseRange(SqList *L, int lo, int hi)
{
    while (lo < hi) {
        int t = L->data[lo];
        L->data[lo] = L->data[hi];
        L->data[hi] = t;
        lo++;
        hi--;
    }
}

/* 三次逆置法 */
void rotateLeft(SqList *L, int m)
{
    if (L->length <= 1) return;

    /* ⚠️ m 可能大于 n，必须取模，否则越界 */
    m = m % L->length;
    if (m == 0) return;

    reverseRange(L, 0, m - 1);              /* ① 逆置前 m 个 */
    reverseRange(L, m, L->length - 1);      /* ② 逆置后 n-m 个 */
    reverseRange(L, 0, L->length - 1);      /* ③ 整体逆置 */
}

/* 对照：辅助数组法（简单但费空间） */
void rotateByTemp(SqList *L, int m)
{
    int tmp[MAXSIZE];
    if (L->length <= 1) return;
    m = m % L->length;
    if (m == 0) return;

    int k = 0;
    for (int i = m; i < L->length; i++) tmp[k++] = L->data[i];
    for (int i = 0; i < m; i++)         tmp[k++] = L->data[i];
    for (int i = 0; i < L->length; i++) L->data[i] = tmp[i];
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};

    printf("=== 三次逆置法 ===\n");
    int ms[] = {3, 0, 7, 9};
    for (int t = 0; t < 4; t++) {
        SqList L; build(&L, a, 7);
        printf("  m = %d\n", ms[t]);
        show("  原表", &L);
        rotateLeft(&L, ms[t]);
        show("  左移后", &L);
    }

    printf("\n=== 关键：m 必须取模 ===\n");
    printf("  n=7，m=9 时 9 %% 7 = 2，等价于左移 2 位。\n");
    printf("  不取模的话 sub 区间会算出 [0, 8]，直接越界。\n");
    printf("  📌 m=7 时 m%%n=0，直接返回（不用动）—— 这个判断必须有，\n");
    printf("     否则 reverseRange(0,-1) 会出问题。\n");

    printf("\n=== 三种解法对比 ===\n");
    printf("  %-16s %-12s %-12s %s\n", "方法", "时间", "空间", "说明");
    printf("  --------------------------------------------------------------\n");
    printf("  %-16s %-12s %-12s %s\n", "三次逆置", "O(n)", "O(1)", "推荐");
    printf("  %-16s %-12s %-12s %s\n", "辅助数组", "O(n)", "O(n)", "最简单");
    printf("  %-16s %-12s %-12s %s\n", "逐次左移一位", "O(n*m)", "O(1)", "最慢");

    printf("\n=== 验证三次逆置的正确性 ===\n");
    SqList L; build(&L, a, 7);
    printf("  原表：    [1 2 3 4 5 6 7]   m=3\n");
    reverseRange(&L, 0, 2);
    show("  逆置前半", &L);
    reverseRange(&L, 3, 6);
    show("  逆置后半", &L);
    reverseRange(&L, 0, 6);
    show("  整体逆置", &L);

    printf("\n  ⭐ 为什么对：设 A = 前 m 个，B = 后 n-m 个，原表是 AB。\n");
    printf("     逆置 A → A^R，得 A^R B\n");
    printf("     逆置 B → B^R，得 A^R B^R\n");
    printf("     整体逆置 → (A^R B^R)^R = B A   ← 正好是左移 m 位\n");

    printf("\n=== 对照：辅助数组法结果相同 ===\n");
    SqList L2; build(&L2, a, 7);
    rotateByTemp(&L2, 3);
    show("  结果", &L2);

    return 0;
}
