/* 173_slist_advanced.c —— 单链表四个进阶题（软考与面试高频）
 *
 * ① 合并两个有序链表
 * ② 找中间节点 —— 快慢指针
 * ③ 判断有没有环 —— 快慢指针相遇
 * ④ 删除倒数第 k 个节点 —— 双指针间隔 k
 *
 * 后三个都是「快慢指针」的变形，一个套路打三个题。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

static Node *newNode(int v)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = v;
    n->next = NULL;
    return n;
}

static Node *pushBack(Node *head, int v)
{
    Node *n = newNode(v);
    if (!n) return head;
    if (head == NULL) return n;
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

/* ---------- ① 合并两个有序链表（升序）---------- */
/* 用「哨兵节点」简化：不用特判空表 */
Node *mergeTwoSorted(Node *a, Node *b)
{
    Node dummy;                     /* 栈上的哨兵，不 malloc，省得 free */
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
    /* 谁还有剩就接上 */
    tail->next = (a != NULL) ? a : b;

    return dummy.next;
}

/* ---------- ② 找中间节点：快慢指针 ---------- */
/* 慢指针走 1 步，快指针走 2 步。快指针到尾时，慢指针正好在中间。
 * 偶数个节点时返回「偏后」的那个。 */
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

/* ---------- ③ 判断有没有环 ---------- */
/* 快慢指针，若有环必相遇（快指针每步追上 1 个） */
int hasCycle(Node *head)
{
    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;     /* 相遇即有环 */
    }
    return 0;
}

/* ---------- ④ 删除倒数第 k 个节点 ---------- */
/* 思路：先让快指针走 k 步，然后快慢一起走；
 *       快指针到尾时，慢指针正好停在「倒数第 k 个」的前一个。
 * 返回新的头节点（可能删掉原头节点）。 */
Node *removeNthFromEnd(Node *head, int k)
{
    Node dummy;
    dummy.next = head;
    Node *fast = &dummy;
    Node *slow = &dummy;

    /* ① 快指针先走 k+1 步（因为要停在被删节点的前驱） */
    for (int i = 0; i <= k; i++) {
        if (fast == NULL) return head;      /* k 超过链表长度 */
        fast = fast->next;
    }
    /* ② 快慢一起走 */
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    /* ③ 删掉 slow 的后继 */
    Node *victim = slow->next;
    if (victim != NULL) {
        slow->next = victim->next;
        free(victim);
    }
    return dummy.next;
}

int main(void)
{
    /* ---------- ① 合并有序链表 ---------- */
    printf("=== ① 合并两个有序链表 ===\n");
    Node *a = NULL, *b = NULL;
    int va[] = {1, 4, 7, 10};
    int vb[] = {2, 3, 8, 11, 15};
    for (int i = 0; i < 4; i++) a = pushBack(a, va[i]);
    for (int i = 0; i < 5; i++) b = pushBack(b, vb[i]);

    print("A", a);
    print("B", b);
    Node *m = mergeTwoSorted(a, b);
    print("合并结果", m);

    printf("\n  ⭐ 时间 O(n+m)，空间 O(1) —— 只是把节点重新串起来，\n");
    printf("     没有新建节点，这是它比「复制到新表」好的地方。\n");
    printf("  📌 注意合并后 a、b 两条原链已经被「拆散重组」，不能再单独用。\n");

    /* ---------- ② 找中间节点 ---------- */
    printf("\n=== ② 找中间节点（快慢指针）===\n");
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    Node *t = NULL;
    for (int i = 0; i < 7; i++) t = pushBack(t, data[i]);
    print("奇数个(7)", t);
    printf("  中间是 %d\n", findMiddle(t)->data);
    destroy(t);

    t = NULL;
    int data2[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) t = pushBack(t, data2[i]);
    print("偶数个(6)", t);
    printf("  中间是 %d（偶数个时取偏后的那个）\n", findMiddle(t)->data);
    destroy(t);

    printf("\n  ⭐ 为什么快慢指针能找到中点？\n");
    printf("     快指针速度是慢指针的 2 倍，走同样时间，路程也是 2 倍。\n");
    printf("     快指针走完整条，慢指针正好走一半。\n");
    printf("  ⭐ 如果想让偶数个时取「偏前」的，循环条件改成\n");
    printf("     while (fast->next != NULL && fast->next->next != NULL)\n");

    /* ---------- ③ 判断有环 ---------- */
    printf("\n=== ③ 判断链表有没有环 ===\n");
    int d3[] = {1, 2, 3, 4, 5};
    Node *c = NULL;
    for (int i = 0; i < 5; i++) c = pushBack(c, d3[i]);
    print("正常链表", c);
    printf("  有环？%s\n", hasCycle(c) ? "是" : "否");

    /* 手动造一个环：尾节点指回第 2 个节点 */
    Node *tail = c;
    while (tail->next) tail = tail->next;
    Node *second = c->next;
    tail->next = second;            /* 造环 */
    printf("  把尾节点指回第 2 个节点后 → 有环？%s\n",
           hasCycle(c) ? "是" : "否");

    /* 注意：有环的链表不能直接 destroy（会死循环） */
    tail->next = NULL;              /* 先拆环再释放 */
    destroy(c);

    printf("\n  ⭐ 为什么有环一定会相遇？\n");
    printf("     进环后，快指针每轮比慢指针多走 1 步，\n");
    printf("     相当于「快指针在环内以 1 步/轮 的速度追慢指针」，\n");
    printf("     环是有限的，所以一定会追上，不会错过。\n");
    printf("  ⚠️ 如果快指针一次走 3 步，就可能「跳过」慢指针，不一定相遇。\n");

    /* ---------- ④ 删除倒数第 k 个 ---------- */
    printf("\n=== ④ 删除倒数第 1 个（尾节点）===\n");
    Node *r = NULL;
    for (int i = 1; i <= 5; i++) r = pushBack(r, i);
    print("原链表", r);
    r = removeNthFromEnd(r, 1);
    print("删除倒数第1", r);

    printf("\n=== 删除倒数第 3 个 ===\n");
    print("原链表", r);
    r = removeNthFromEnd(r, 3);
    print("删除倒数第3", r);

    printf("\n  ⭐ 双指针间隔 k 的原理：\n");
    printf("     快指针先走 k+1 步，两者相距 k+1 个节点。\n");
    printf("     快指针到尾时，慢指针距尾正好 k 个 → 停在倒数第 k 个的前驱。\n");
    printf("     一趟扫描完成，O(n) 时间、O(1) 空间。\n");
    printf("  📌 如果先求长度再删，要扫描两趟 —— 面试常问「怎么只扫一趟」。\n");

    destroy(m);
    destroy(r);

    /* ---------- ⑤ 快慢指针家族 ---------- */
    printf("\n=== ⑤ 快慢指针的四种用法 ===\n");
    printf("  %-26s %-20s %s\n", "问题", "指针设置", "结束条件");
    printf("  --------------------------------------------------------------------\n");
    printf("  %-26s %-20s %s\n", "找中间节点", "慢1步 快2步", "快到尾");
    printf("  %-26s %-20s %s\n", "判断有环", "慢1步 快2步", "相遇");
    printf("  %-26s %-20s %s\n", "找环的入口", "先相遇再从头走", "再次相遇");
    printf("  %-26s %-20s %s\n", "删除倒数第k个", "快先行k+1步", "快到尾");

    printf("\n  ⭐ 这四个题骨架一样，只是「快指针先走多少」和「怎么判断结束」不同。\n");

    return 0;
}
