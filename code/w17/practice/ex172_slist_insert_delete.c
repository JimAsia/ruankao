/* ex172_slist_insert_delete.c —— 单链表的按位置插入与删除
 *
 * 要求：
 *   1. insertAt(L, pos, v)：在下标 pos 处插入，pos 合法范围 0..length
 *   2. deleteAt(L, pos, out)：删除下标 pos，用 out 带回值，范围 0..length-1
 *   3. 两个函数内部都要「先找前驱，再改指针」
 *
 * 测试序列（初始 10 20 30 40 50）：
 *   在下标 2 插入 99   → 10 20 99 30 40 50
 *   在表头插入 5       → 5 10 20 99 30 40 50
 *   在末尾插入 60      → 5 10 20 99 30 40 50 60
 *   删除下标 3         → 5 10 20 30 40 50 60，被删的是 99
 *   删除下标 99        → 失败提示
 *
 * 提示：
 *   getPrev(L, pos)：返回第 pos 个节点的前驱；pos=0 时返回头结点
 *   插入四步：malloc → 赋值 → n->next = prev->next → prev->next = n
 *   删除：prev->next = victim->next; free(victim);
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int   length;
} LinkedList;

/* ===== 以下工具函数已给出，直接用 ===== */
LinkedList *create(void)
{
    LinkedList *L = (LinkedList *)malloc(sizeof(LinkedList));
    if (!L) return NULL;
    L->head = (Node *)malloc(sizeof(Node));
    if (!L->head) { free(L); return NULL; }
    L->head->next = NULL;
    L->length = 0;
    return L;
}

void pushBack(LinkedList *L, int v)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return;
    n->data = v;
    n->next = NULL;
    Node *p = L->head;
    while (p->next) p = p->next;
    p->next = n;
    L->length++;
}

void print(const LinkedList *L)
{
    printf("  ");
    for (Node *p = L->head->next; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf(" -> NULL\n");
}

void destroy(LinkedList *L)
{
    if (!L) return;
    Node *p = L->head;
    while (p) { Node *nx = p->next; free(p); p = nx; }
    free(L);
}
/* ===== 工具函数结束 ===== */

/* TODO 1：取第 pos 个节点的前驱 */
static Node *getPrev(const LinkedList *L, int pos)
{
    (void)L; (void)pos;
    return NULL;
}

/* TODO 2：按位置插入 */
int insertAt(LinkedList *L, int pos, int v)
{
    (void)L; (void)pos; (void)v;
    return 0;
}

/* TODO 3：按位置删除 */
int deleteAt(LinkedList *L, int pos, int *out)
{
    (void)L; (void)pos; (void)out;
    return 0;
}

int main(void)
{
    LinkedList *L = create();
    for (int i = 1; i <= 5; i++) pushBack(L, i * 10);

    printf("初始：\n"); print(L);

    /* TODO 4：按下标 2 插入 99 */

    /* TODO 5：表头插入 5 */

    /* TODO 6：末尾插入 60 */

    /* TODO 7：删除下标 3，输出被删的值 */

    /* TODO 8：越界测试（删除下标 99） */

    destroy(L);
    return 0;
}
