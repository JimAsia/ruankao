/* ex176_slist_pointer_tricks.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

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

/* 找中间（偶数个取偏后） */
Node *findMiddle(Node *head)
{
    if (head == NULL) return NULL;

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/* 判环 */
int hasCycle(Node *head)
{
    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

/* 删除倒数第 k 个 */
Node *removeNthFromEnd(Node *head, int k)
{
    Node dummy;
    dummy.next = head;
    Node *fast = &dummy;
    Node *slow = &dummy;

    /* fast 先走 k+1 步 */
    for (int i = 0; i <= k; i++) {
        if (fast == NULL) {
            printf("  k=%d 超过链表长度，不做修改\n", k);
            return head;
        }
        fast = fast->next;
    }

    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    Node *victim = slow->next;
    if (victim != NULL) {
        slow->next = victim->next;
        free(victim);
    }
    return dummy.next;
}

int main(void)
{
    /* ---------- 找中间 ---------- */
    printf("=== 找中间节点 ===\n");
    Node *t = NULL;
    for (int i = 1; i <= 7; i++) t = pushBack(t, i);
    print("奇数个(7)", t);
    printf("  中间是 %d\n", findMiddle(t)->data);
    destroy(t);

    t = NULL;
    for (int i = 1; i <= 6; i++) t = pushBack(t, i);
    print("偶数个(6)", t);
    printf("  中间是 %d（偏后）\n", findMiddle(t)->data);
    destroy(t);

    /* ---------- 判环 ---------- */
    printf("\n=== 判断有环 ===\n");
    t = NULL;
    for (int i = 1; i <= 5; i++) t = pushBack(t, i);
    print("正常", t);
    printf("  有环？%s\n", hasCycle(t) ? "是" : "否");

    Node *tail = t;
    while (tail->next) tail = tail->next;
    tail->next = t->next->next;         /* 尾指回第 2 个，造环 */
    printf("  造环后 → 有环？%s\n", hasCycle(t) ? "是" : "否");

    tail->next = NULL;                  /* 拆环，否则 destroy 死循环 */
    destroy(t);

    /* ---------- 删除倒数第 k 个 ---------- */
    printf("\n=== 删除倒数第 1 个 ===\n");
    Node *r = NULL;
    for (int i = 1; i <= 5; i++) r = pushBack(r, i);
    print("原链表", r);
    r = removeNthFromEnd(r, 1);
    print("删除后", r);

    printf("\n=== 删除倒数第 4 个（当前的第一个）===\n");
    print("原链表", r);
    r = removeNthFromEnd(r, 4);
    print("删除后", r);
    printf("  ⭐ 删掉了头节点，所以必须用 dummy 才不用特判\n");

    printf("\n=== k 超长 ===\n");
    r = removeNthFromEnd(r, 99);
    print("结果", r);
    printf("  → 不变，不崩 ✓\n");

    destroy(r);

    printf("\n=== 快慢指针的四种题型 ===\n");
    printf("  %-22s %-22s %s\n", "问题", "快指针怎么走", "结束条件");
    printf("  ----------------------------------------------------------------------\n");
    printf("  %-22s %-22s %s\n", "找中间", "每次 2 步", "fast 到尾");
    printf("  %-22s %-22s %s\n", "判环", "每次 2 步", "slow == fast");
    printf("  %-22s %-22s %s\n", "找环入口", "相遇后从头再来一个慢指针", "再次相遇");
    printf("  %-22s %-22s %s\n", "删倒数第 k", "先走 k+1 步再同步", "fast 到尾");

    printf("\n=== 找环入口的补充（常考）===\n");
    printf("  相遇后，把其中一个指针放回头节点，两个都改成每次走 1 步，\n");
    printf("  再次相遇的位置就是环的入口。\n");
    printf("  证明用到「慢指针走了 x+y，快指针走了 2(x+y)」，这里不展开。\n");

    printf("\n=== while 条件的细节 ===\n");
    printf("  ✅ while (fast != NULL && fast->next != NULL)\n");
    printf("  ❌ while (fast->next != NULL && fast->next->next != NULL)\n");
    printf("     第一个条件缺了 fast != NULL 时，空表会直接崩（访问 NULL->next）。\n");
    printf("     ⭐ 两个条件顺序也不能反：先判 fast 非空，才能访问 fast->next。\n");

    return 0;
}
