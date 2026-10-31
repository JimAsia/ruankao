/* ex165_seqlist_rotate.c —— 循环左移：把前 m 个元素移到后面
 *
 * 要求：
 *   1. rotateLeft(L, m)：把表循环左移 m 位
 *      例：[1 2 3 4 5 6 7]，m=3  →  [4 5 6 7 1 2 3]
 *   2. 空间 O(1)，时间尽量 O(n)
 *   3. m 可能大于 n，要取模（m % n）
 *
 * 测试：
 *   [1 2 3 4 5 6 7]，m=3  →  [4 5 6 7 1 2 3]
 *   [1 2 3 4 5 6 7]，m=0  →  不变
 *   [1 2 3 4 5 6 7]，m=7  →  不变
 *   [1 2 3 4 5 6 7]，m=9  →  等同于 m=2  →  [3 4 5 6 7 1 2]
 *
 * 三种解法（都要会）：
 *   ① 三次逆置法（推荐，O(n) 时间、O(1) 空间）
 *        逆置前 m 个 → 逆置后 n-m 个 → 整体逆置
 *   ② 辅助数组法（最简单，但 O(n) 空间）
 *   ③ 逐次左移一位，做 m 次（O(n*m) 时间，最慢）
 *
 * 提示：本文件里已有 reverseRange 可复用
 */

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
    printf("  %-10s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]\n");
}

/* 逆置 [lo, hi] 区间（闭区间），已给出 */
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

/* TODO 1：用三次逆置实现循环左移 */
void rotateLeft(SqList *L, int m)
{
    (void)L; (void)m;
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};

    /* TODO 2：测试 m = 3 */
    /* TODO 3：测试 m = 0、m = 7、m = 9 */

    printf("\n=== 三次逆置为什么对 ===\n");
    printf("  原表：  [1 2 3 | 4 5 6 7]      m=3\n");
    printf("  逆置前半：[3 2 1 | 4 5 6 7]\n");
    printf("  逆置后半：[3 2 1 | 7 6 5 4]\n");
    printf("  整体逆置：[4 5 6 7 1 2 3]     ← 正好是左移 3 位\n");
    printf("  ⭐ 每一步都是 O(n)，做三次还是 O(n)。\n");

    return 0;
}
