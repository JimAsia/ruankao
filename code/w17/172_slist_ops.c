/* 172_slist_ops.c —— 单链表的插入、删除、逆置
 *
 * 链表的核心只有一句话：**先接后断**。
 * 顺序错了，后面的节点就找不回来了（内存泄漏 + 链表断裂）。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;         /* 头结点，dummy */
    int   length;
} LinkedList;

/* ---------- 基础工具 ---------- */
static LinkedList *create(void)
{
    LinkedList *L = (LinkedList *)malloc(sizeof(LinkedList));
    if (!L) return NULL;
    L->head = (Node *)malloc(sizeof(Node));
    if (!L->head) { free(L); return NULL; }
    L->head->next = NULL;
    L->length = 0;
    return L;
}

static void pushBack(LinkedList *L, int v)
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

static void print(const LinkedList *L)
{
    printf("  ");
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

/* ---------- ① 取第 pos 个节点的前驱 ---------- */
/* pos 从 0 起。返回第 pos 个节点的前一个节点（pos=0 时返回头结点） */
static Node *getPrev(const LinkedList *L, int pos)
{
    Node *p = L->head;              /* 头结点是第 0 个节点的前驱 */
    for (int i = 0; i < pos && p != NULL; i++) {
        p = p->next;
    }
    return p;
}

/* ---------- ② 按位置插入 ---------- */
int insertAt(LinkedList *L, int pos, int value)
{
    if (pos < 0 || pos > L->length) {
        printf("  插入失败：pos=%d 越界（合法 0..%d）\n", pos, L->length);
        return 0;
    }

    Node *prev = getPrev(L, pos);   /* 找到前驱，O(n) */
    if (prev == NULL) return 0;

    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return 0;

    /* ⭐ 先接后断：新节点的 next 先指向后继，再让前驱指向新节点 */
    n->data = value;
    n->next = prev->next;           /* ① 接上后半段 */
    prev->next = n;                 /* ② 断开，改指新节点 */

    L->length++;
    return 1;
}

/* ---------- ③ 按位置删除 ---------- */
int deleteAt(LinkedList *L, int pos, int *out)
{
    if (pos < 0 || pos >= L->length) {
        printf("  删除失败：pos=%d 越界（合法 0..%d）\n", pos, L->length - 1);
        return 0;
    }

    Node *prev = getPrev(L, pos);
    Node *victim = prev->next;

    prev->next = victim->next;      /* 前驱跳过被删节点 */
    if (out) *out = victim->data;
    free(victim);                   /* ⚠️ 必须 free，否则内存泄漏 */
    L->length--;
    return 1;
}

/* ---------- ④ 逆置：三指针法 ---------- */
void reverseList(LinkedList *L)
{
    Node *prev = NULL;
    Node *cur  = L->head->next;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;           /* ① 先存后继，否则断链后找不到 */
        cur->next = prev;           /* ② 反转指向 */
        prev = cur;                 /* ③ prev 前进 */
        cur  = next;                /* ④ cur 前进 */
    }
    L->head->next = prev;           /* 头结点指向新表头（原尾节点） */
}

/* ---------- ⑤ 逆置的另一种写法：重新头插 ---------- */
void reverseByReinsert(LinkedList *L)
{
    Node *oldFirst = L->head->next;
    L->head->next = NULL;           /* 摘掉整条链，只剩头结点 */

    Node *cur = oldFirst;
    while (cur != NULL) {
        Node *next = cur->next;
        cur->next = L->head->next;  /* 头插 */
        L->head->next = cur;
        cur = next;
    }
}

int main(void)
{
    LinkedList *L = create();
    for (int i = 1; i <= 5; i++) pushBack(L, i * 10);

    printf("=== 初始链表 ===\n");
    print(L);

    /* ---------- ① 插入 ---------- */
    printf("\n=== ① 在下标 2 插入 99 ===\n");
    insertAt(L, 2, 99);
    print(L);
    printf("  10 -> 20 -> [99] -> 30 -> 40 -> 50\n");
    printf("  ⭐ 只需要改两个指针，不用挪任何元素 → O(1)（找到前驱后）\n");
    printf("     但找前驱花了 O(n)，所以按位置插入整体是 O(n)。\n");

    /* ---------- ② 表头插入的对比 ---------- */
    printf("\n=== ② 表头插入 vs 表尾插入 ===\n");
    insertAt(L, 0, 5);
    print(L);
    printf("  表头插入：前驱就是头结点，一步找到 → O(1)\n");

    insertAt(L, L->length, 60);
    print(L);
    printf("  表尾插入：要找前驱（走完整个链表）→ O(n)\n");
    printf("\n  ⭐ 这是链表和顺序表【相反】的地方：\n");
    printf("     顺序表：表尾插 O(1)，表头插 O(n)\n");
    printf("     链表  ：表头插 O(1)，表尾插 O(n)（除非维护尾指针）\n");

    /* ---------- ③ 删除 ---------- */
    printf("\n=== ③ 删除下标 3 的元素 ===\n");
    int out = 0;
    if (deleteAt(L, 3, &out)) {
        printf("  删除的是 %d\n", out);
        print(L);
    }
    printf("  ⚠️ 别忘了 free(victim)，否则每次删除都泄漏一个节点\n");

    /* ---------- ④ 逆置（三指针） ---------- */
    printf("\n=== ④ 逆置 —— 三指针法 ===\n");
    print(L);
    reverseList(L);
    print(L);

    printf("\n  ⭐ 三指针法的四步（背下来）：\n");
    printf("     next = cur->next;     ① 先存后继\n");
    printf("     cur->next = prev;     ② 反转指向\n");
    printf("     prev = cur;           ③ prev 前进\n");
    printf("     cur = next;           ④ cur 前进\n");
    printf("\n  ⚠️ 第 ① 步绝对不能颠倒顺序。\n");
    printf("     如果先写 cur->next = prev，那 cur 原来的后继就永久丢失了，\n");
    printf("     后面的节点全部泄漏，链表只剩前半截。\n");

    /* ---------- ⑤ 逆置（头插法）---------- */
    printf("\n=== ⑤ 逆置 —— 头插法（另一种思路）===\n");
    printf("  当前是 60..5，再逆置一次应回到 5..60：\n");
    reverseByReinsert(L);
    print(L);
    printf("  思路：把整条链摘下来，再逐个头插回原表头。\n");
    printf("  ⭐ 两种方法都是 O(n) 时间、O(1) 空间，用哪个都行。\n");
    printf("     头插法更容易理解，三指针法更常见于教材。\n");

    /* ---------- ⑥ 复杂度总结 ---------- */
    printf("\n=== ⑥ 单链表操作复杂度 ===\n");
    printf("  %-24s %-12s %s\n", "操作", "复杂度", "原因");
    printf("  ------------------------------------------------------------------\n");
    printf("  %-24s %-12s %s\n", "按值查找", "O(n)", "必须从头走");
    printf("  %-24s %-12s %s\n", "按位置取第 i 个", "O(n)", "不能随机访问");
    printf("  %-24s %-12s %s\n", "在已知前驱后插入", "O(1)", "只改两个指针");
    printf("  %-24s %-12s %s\n", "删除已知节点的后继", "O(1)", "只改一个指针");
    printf("  %-24s %-12s %s\n", "按位置插入/删除", "O(n)", "找前驱要 O(n)");
    printf("  %-24s %-12s %s\n", "头插", "O(1)", "前驱是头结点");
    printf("  %-24s %-12s %s\n", "尾插（无尾指针）", "O(n)", "要找尾节点");
    printf("  %-24s %-12s %s\n", "逆置", "O(n)", "走一遍");

    printf("\n  ⭐ 记住一句话：链表的 O(1) 插入删除，前提是「已经拿到前驱」。\n");
    printf("     这个前提在软考里是高频陷阱。\n");

    destroy(L);
    return 0;
}
