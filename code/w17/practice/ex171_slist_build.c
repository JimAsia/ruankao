/* ex171_slist_build.c —— 单链表的建立与遍历
 *
 * 要求：
 *   1. 用【尾插法】建立链表 10 20 30 40 50，遍历输出，验证顺序一致
 *   2. 用【头插法】建立同样的数据，遍历输出，验证顺序相反
 *   3. 实现 length(L)：遍历求长度（不用计数字段）
 *   4. 实现 destroy(L)：释放所有节点
 *
 * 期望输出：
 *   尾插：10 -> 20 -> 30 -> 40 -> 50 -> NULL
 *   头插：50 -> 40 -> 30 -> 20 -> 10 -> NULL
 *   遍历求长度：5
 *
 * 提示：
 *   头插：n->next = head->next; head->next = n;   ← 顺序不能反
 *   尾插：先走到 p->next == NULL，再 p->next = n
 *   销毁：先存 next 再 free
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

/* 带头结点 */
typedef struct {
    Node *head;
} LinkedList;

/* TODO 1：创建空表（malloc 头结点，head->next = NULL） */
LinkedList *create(void)
{
    return NULL;
}

/* TODO 2：头插 */
void insertHead(LinkedList *L, int v)
{
    (void)L; (void)v;
}

/* TODO 3：尾插 */
void insertTail(LinkedList *L, int v)
{
    (void)L; (void)v;
}

/* TODO 4：遍历输出 */
void print(const LinkedList *L)
{
    (void)L;
}

/* TODO 5：遍历求长度 */
int length(const LinkedList *L)
{
    (void)L;
    return 0;
}

/* TODO 6：销毁 */
void destroy(LinkedList *L)
{
    (void)L;
}

int main(void)
{
    /* TODO 7：尾插建表 10..50，输出 */

    /* TODO 8：头插建表 10..50，输出 */

    /* TODO 9：输出遍历求得的长度 */

    /* TODO 10：销毁两条链表 */

    return 0;
}
