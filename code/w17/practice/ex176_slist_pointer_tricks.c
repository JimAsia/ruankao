/* ex176_slist_pointer_tricks.c —— 快慢指针三连
 *
 * 要求：
 *   1. findMiddle(head)：找中间节点，偶数个时取【偏后】的那个
 *   2. hasCycle(head)：判断有没有环
 *   3. removeNthFromEnd(head, k)：删除倒数第 k 个，返回新头节点
 *
 * 测试：
 *   [1..7] 中间是 4
 *   [1..6] 中间是 4（偏后）
 *   正常链表 hasCycle = 0，造环后 = 1
 *   [1..5] 删除倒数第 1 → [1 2 3 4]
 *   [1..5] 删除倒数第 5 → [2 3 4 5]（删掉的是头节点）
 *   [1..5] 删除倒数第 6 → 不变（k 超长）
 *
 * 提示：
 *   找中间：slow 走 1 步，fast 走 2 步，while (fast && fast->next)
 *   判环  ：同上，若 slow == fast 则有环
 *   删倒数：fast 先走 k+1 步，再和 slow 同步走；fast 到尾时删 slow->next
 *          （要用 dummy 哨兵，因为可能删掉头节点）
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

/* ===== 工具函数 ===== */
static Node *pushBack(Node *head, int v)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return head;
    n->data = v;
    n->next = NULL;
    if (!head) return n;
    Node *p = head;
    while (p->next) p = p->next;
    p->next = n;
    return head;
}

static void print(const char *label, const Node *head)
{
    printf("  %-14s ", label);
    for (const Node *p = head; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf(" -> NULL\n");
}

static void destroy(Node *head)
{
    while (head) { Node *nx = head->next; free(head); head = nx; }
}
/* ===== 工具函数结束 ===== */

/* TODO 1：找中间节点 */
Node *findMiddle(Node *head)
{
    (void)head;
    return NULL;
}

/* TODO 2：判断有环 */
int hasCycle(Node *head)
{
    (void)head;
    return 0;
}

/* TODO 3：删除倒数第 k 个 */
Node *removeNthFromEnd(Node *head, int k)
{
    (void)head; (void)k;
    return NULL;
}

int main(void)
{
    /* TODO 4：找中间（奇数个 7、偶数个 6） */

    /* TODO 5：判环（正常 / 造环 / 拆环后再释放） */

    /* TODO 6：删除倒数第 1、第 5、第 6（超长） */

    return 0;
}
