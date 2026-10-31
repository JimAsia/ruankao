/* ex174_slist_merge.c —— 参考答案 */

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

Node *mergeSorted(Node *a, Node *b)
{
    Node dummy;                     /* 栈上的哨兵，不需要 free */
    dummy.next = NULL;
    Node *tail = &dummy;

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    /* 剩下的整段接上（不用再循环） */
    tail->next = (a != NULL) ? a : b;

    return dummy.next;
}

int main(void)
{
    printf("=== 主测试 ===\n");
    Node *a = NULL, *b = NULL;
    int va[] = {1, 4, 7, 10};
    int vb[] = {2, 3, 8, 11, 15};
    for (int i = 0; i < 4; i++) a = pushBack(a, va[i]);
    for (int i = 0; i < 5; i++) b = pushBack(b, vb[i]);

    print("A", a);
    print("B", b);
    Node *m = mergeSorted(a, b);
    print("合并后", m);

    printf("\n=== 边界测试 ===\n");

    /* A 空 */
    Node *b1 = NULL;
    for (int i = 0; i < 3; i++) b1 = pushBack(b1, (i + 1) * 5);
    print("A = NULL", NULL);
    print("B", b1);
    Node *m1 = mergeSorted(NULL, b1);
    print("结果", m1);
    printf("  → 直接返回 B ✓\n");

    /* 都空 */
    Node *m2 = mergeSorted(NULL, NULL);
    print("\n两个都空", m2);
    printf("  → 返回 NULL，不崩 ✓\n");

    printf("\n=== 为什么不需要「循环接剩余」===\n");
    printf("  常见的写法是：\n");
    printf("     while (a) { tail->next = a; ... }\n");
    printf("     while (b) { tail->next = b; ... }\n");
    printf("  但剩余部分本来就是一条完整的链，\n");
    printf("  直接 tail->next = (a ? a : b) 一句就够，不用逐个搬。\n");
    printf("  ⭐ 这是链表合并比数组归并简洁的地方。\n");

    printf("\n=== 哨兵节点（dummy）的作用 ===\n");
    printf("  没有 dummy 时，第一个节点要特判：\n");
    printf("     if (head == NULL) head = 新节点; else tail->next = 新节点;\n");
    printf("  有了 dummy，第一个节点和其他节点完全一样处理，\n");
    printf("  最后 return dummy.next 就行。\n");
    printf("  📌 这个技巧在「合并、拆分、删除头节点」类题目里通用。\n");

    printf("\n=== 复杂度 ===\n");
    printf("  时间 O(n+m)：两个指针各走一遍\n");
    printf("  空间 O(1)：只用了 dummy 和 tail 几个局部变量\n");
    printf("  ⚠️ 合并后不能再单独使用 a、b —— 节点已经被重新串接了。\n");

    destroy(m);
    destroy(m1);
    return 0;
}
