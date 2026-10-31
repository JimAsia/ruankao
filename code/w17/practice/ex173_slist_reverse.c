/* ex173_slist_reverse.c —— 单链表逆置（两种方法都要会）
 *
 * 要求：
 *   1. reverseThreePointer(L)：三指针法，原地逆置，O(n) 时间 O(1) 空间
 *   2. reverseReinsert(L)：头插法，原地逆置
 *   3. 两个函数对同一条链表各跑一次，应该都能得到逆序结果
 *
 * 期望：
 *   原表 1 -> 2 -> 3 -> 4 -> 5
 *   三指针法后：5 -> 4 -> 3 -> 2 -> 1
 *   再跑头插法后：1 -> 2 -> 3 -> 4 -> 5（又逆回去了）
 *
 * 另测边界：空表、单节点，都不能崩。
 *
 * 提示：
 *   三指针四步（顺序不能错）：
 *     next = cur->next;   cur->next = prev;   prev = cur;   cur = next;
 *   最后 head->next = prev;
 *
 *   头插法：先把 head->next 置 NULL，再逐个取下节点头插回去
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

/* ===== 工具函数 ===== */
LinkedList *create(void)
{
    LinkedList *L = (LinkedList *)malloc(sizeof(LinkedList));
    if (!L) return NULL;
    L->head = (Node *)malloc(sizeof(Node));
    if (!L->head) { free(L); return NULL; }
    L->head->next = NULL;
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

/* TODO 1：三指针法逆置 */
void reverseThreePointer(LinkedList *L)
{
    (void)L;
}

/* TODO 2：头插法逆置 */
void reverseReinsert(LinkedList *L)
{
    (void)L;
}

int main(void)
{
    /* TODO 3：建表 1..5，用三指针法逆置，输出 */

    /* TODO 4：再用头插法逆置一次，输出（应回到原顺序） */

    /* TODO 5：边界测试 —— 空表 */

    /* TODO 6：边界测试 —— 单节点 */

    return 0;
}
