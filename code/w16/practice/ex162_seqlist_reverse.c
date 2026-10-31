/* ex162_seqlist_reverse.c —— 逆置与删除指定值
 *
 * 要求：
 *   1. reverseList(L)：原地逆置，空间 O(1)
 *   2. removeAll(L, v)：删除所有值为 v 的元素，用覆盖法，时间 O(n)
 *   3. 两个操作都要返回/输出「做了什么」，便于验证
 *
 * 测试 1（逆置）：
 *   输入 1 2 3 4 5 6 7  →  7 6 5 4 3 2 1
 *   输入 1 2 3 4        →  4 3 2 1（偶数个）
 *   输入 42             →  42（单个）
 *
 * 测试 2（删除）：
 *   3 5 3 7 3 9 1 3，删除 3  →  5 7 9 1，删掉 4 个
 *   1 2 3，删除 9            →  1 2 3，删掉 0 个
 *
 * 提示：
 *   逆置：i 从前往后、j 从后往前，条件是 i < j
 *   删除：k 记录写入位置，data[k] = data[i] 覆盖
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
    printf("  %-12s [", label);
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->data[i]);
        if (i != L->length - 1) printf(" ");
    }
    printf("]\n");
}

/* TODO 1：原地逆置 */
void reverseList(SqList *L)
{
    (void)L;
}

/* TODO 2：删除所有值为 value 的元素，返回删掉的个数 */
int removeAll(SqList *L, int value)
{
    (void)L; (void)value;
    return 0;
}

int main(void)
{
    /* TODO 3：测试逆置（三组：奇数个、偶数个、单个） */

    /* TODO 4：测试删除（两组：有命中、无命中） */

    return 0;
}
