/* ex174_slist_merge.c —— 合并两个有序链表（原地，不新建节点）
 *
 * 要求：
 *   1. mergeSorted(a, b)：把两个升序链表合并成一个升序链表
 *   2. 必须「重新串接已有节点」，不能 malloc 新节点，空间 O(1)
 *   3. 用哨兵节点（dummy）简化代码，避免特判空表
 *   4. 返回合并后的第一个真节点
 *
 * 测试：
 *   A = 1 4 7 10
 *   B = 2 3 8 11 15
 *   结果 = 1 2 3 4 7 8 10 11 15
 *
 * 边界：
 *   A 空 → 返回 B
 *   B 空 → 返回 A
 *   两个都空 → 返回 NULL
 *
 * 提示：
 *   Node dummy; dummy.next = NULL;  Node *tail = &dummy;
 *   while (a && b) { 把小的接到 tail 后面; tail 前进; }
 *   tail->next = (a ? a : b);
 *   return dummy.next;
 *
 * ⚠️ dummy 在栈上（不是 malloc），所以不需要 free。
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
    printf("  %-10s ", label);
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

/* TODO 1：合并两个有序链表 */
Node *mergeSorted(Node *a, Node *b)
{
    (void)a; (void)b;
    return NULL;
}

int main(void)
{
    /* TODO 2：建两条链表并合并 */

    /* TODO 3：边界测试（A 空、B 空、都空） */

    printf("\n=== 为什么空间是 O(1) ===\n");
    printf("  全程只操作 next 指针，没有 malloc。\n");
    printf("  合并后的链表复用了原来的节点 —— 这叫「原地合并」。\n");
    printf("  📌 如果是数组实现，合并必须开一个新数组 O(n+m) 空间。\n");
    printf("     这是链表比数组强的地方之一。\n");

    return 0;
}
