/* ex175_slist_split.c —— 按奇偶拆成两个链表
 *
 * 要求：
 *   1. splitOddEven(src, odd, even)：
 *      把 src 中「值为奇数」的节点串到 odd，「值为偶数」的串到 even
 *   2. 复用原节点，不新建（除了两条新链表的头结点）
 *   3. src 拆完后应该变成空表
 *
 * 测试：
 *   源：1 2 3 4 5 6 7 8
 *   奇数链：1 3 5 7
 *   偶数链：2 4 6 8
 *
 * 边界：
 *   全是奇数 → 偶数链为空
 *   空表 → 两条都为空
 *
 * 提示：
 *   遍历 src，对每个节点判断奇偶，然后头插或尾插到对应链表。
 *   尾插要维护两个尾指针，否则每次都要重新找尾（O(n^2)）。
 *   ⚠️ 摘节点时要先把 cur->next 存下来，否则改完之后找不到下一个。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;         /* 带头结点 */
    Node *tail;         /* 尾指针，尾插 O(1) */
    int   length;
} LinkedList;

/* ===== 工具函数 ===== */
static LinkedList *create(void)
{
    LinkedList *L = (LinkedList *)malloc(sizeof(LinkedList));
    if (!L) return NULL;
    L->head = (Node *)malloc(sizeof(Node));
    if (!L->head) { free(L); return NULL; }
    L->head->next = NULL;
    L->head->data = 0;
    L->tail = L->head;
    L->length = 0;
    return L;
}

static void pushBack(LinkedList *L, int v)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return;
    n->data = v;
    n->next = NULL;
    L->tail->next = n;
    L->tail = n;
    L->length++;
}

static void print(const char *label, const LinkedList *L)
{
    printf("  %-10s ", label);
    for (Node *p = L->head->next; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf(" -> NULL   (length=%d)\n", L->length);
}

static void destroy(LinkedList *L)
{
    if (!L) return;
    Node *p = L->head;
    while (p) { Node *nx = p->next; free(p); p = nx; }
    free(L);
}
/* ===== 工具函数结束 ===== */

/* @brief 把 src 按奇偶拆到 odd 和 even（odd、even 必须是空表）
 * @note  src 拆完后变空
 */
void splitOddEven(LinkedList *src, LinkedList *odd, LinkedList *even)
{
    /* TODO 1：实现拆分 */
    (void)src; (void)odd; (void)even;
}

int main(void)
{
    /* TODO 2：建源链表 1..8，拆分，输出三条链 */

    /* TODO 3：边界测试 —— 全是奇数 */

    /* TODO 4：边界测试 —— 空表 */

    printf("\n=== 两个关键点 ===\n");
    printf("  1. 摘节点前必须先存 next：\n");
    printf("     Node *next = cur->next;   ← 少了这句，cur->next 一改就丢了后面\n");
    printf("  2. 尾插必须维护 tail 指针：\n");
    printf("     没有 tail 就要每次走一遍找尾，整体退化到 O(n^2)。\n");

    return 0;
}
