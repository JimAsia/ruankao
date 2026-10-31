/* ex164_seqlist_partition.c —— 按值分割：小于 x 的放前面
 *
 * 要求：
 *   1. partition(L, x)：把表中「小于 x」的元素全部移到前面，
 *      「大于等于 x」的移到后面，不要求保持原来的相对顺序
 *   2. 时间 O(n)，空间 O(1)（不能用辅助数组）
 *
 * 测试：
 *   输入 8 3 9 1 5 7 2 6，x = 5
 *   可能输出：3 1 2 5 7 8 9 6  或  1 3 2 6 5 7 9 8（相对顺序可变）
 *   但必须满足：前 3 个都 < 5，后面都 >= 5
 *
 * 提示：
 *   双指针：i 从前往后找「>= x」的，
 *          j 从后往前找「< x」的，找到就交换
 *   注意循环条件是 i < j，否则会重复交换
 *
 * 思考：如果要「保持相对顺序」，还能 O(n) 且 O(1) 空间吗？
 *       （不能，要么 O(n) 空间，要么 O(n^2) 时间 —— 这是「稳定分割」的代价）
 */

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

/* TODO 1：分割 */
void partition(SqList *L, int x)
{
    (void)L; (void)x;
}

/* 辅助：检查分割是否正确（返回 1 正确，0 错误） */
static int checkPartition(const SqList *L, int x)
{
    int i = 0;
    while (i < L->length && L->data[i] < x) i++;   /* 跳过 < x 的 */
    while (i < L->length && L->data[i] >= x) i++;  /* 跳过 >= x 的 */
    return i == L->length;                         /* 全过完说明分对了 */
}

int main(void)
{
    int a[] = {8, 3, 9, 1, 5, 7, 2, 6};
    SqList L;
    build(&L, a, 8);

    /* TODO 2：调用 partition，输出结果 */

    /* TODO 3：用 checkPartition 验证，输出「分割正确 / 错误」 */

    /* TODO 4：再测一组全是小值、一组全是大值的边界情况 */

    return 0;
}
