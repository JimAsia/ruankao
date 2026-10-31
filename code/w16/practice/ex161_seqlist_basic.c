/* ex161_seqlist_basic.c —— 顺序表的基本操作
 *
 * 要求：补全 insertAt / deleteAt / locate 三个函数
 *
 *   1. insertAt(L, pos, v)：在下标 pos 处插入 v，成功返回 1
 *      合法性：0 <= pos <= length，且表未满
 *   2. deleteAt(L, pos, out)：删除下标 pos，用 out 带回被删的值
 *      合法性：0 <= pos < length
 *   3. locate(L, v)：按值查找，返回下标，找不到返回 -1
 *
 * 测试序列：
 *   依次在末尾插入 10 20 30 40 50
 *   在下标 2 插入 99        → [10 20 99 30 40 50]
 *   删除下标 0              → [20 99 30 40 50]，被删的是 10
 *   查找 30                 → 下标 2
 *   查找 999                → -1
 *
 * 提示：
 *   插入要【从后往前】挪，删除要【从前往后】挪
 *   全局 g_moves 统计移动次数，每次赋值算一次
 */

#include <stdio.h>

#define MAXSIZE 20

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

static long long g_moves = 0;

void initList(SqList *L)
{
    L->length = 0;
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

/* TODO 1：按位置插入 */
int insertAt(SqList *L, int pos, int value)
{
    (void)L; (void)pos; (void)value;
    return 0;
}

/* TODO 2：按位置删除 */
int deleteAt(SqList *L, int pos, int *out)
{
    (void)L; (void)pos; (void)out;
    return 0;
}

/* TODO 3：按值查找 */
int locate(const SqList *L, int value)
{
    (void)L; (void)value;
    return -1;
}

int main(void)
{
    SqList L;
    initList(&L);

    /* TODO 4：依次在末尾插入 10 20 30 40 50 */
    show("初始", &L);

    /* TODO 5：在下标 2 插入 99，输出结果和移动次数 */

    /* TODO 6：删除下标 0，输出被删的值和结果 */

    /* TODO 7：查找 30 和 999，输出下标 */

    return 0;
}
