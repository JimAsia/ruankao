/* ex173_slist_reverse.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

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

/* 三指针法 */
void reverseThreePointer(LinkedList *L)
{
    Node *prev = NULL;
    Node *cur  = L->head->next;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;           /* ① 存后继 */
        cur->next = prev;           /* ② 反向 */
        prev = cur;                 /* ③ prev 前进 */
        cur  = next;                /* ④ cur 前进 */
    }
    L->head->next = prev;           /* 头结点指向新的第一个 */
}

/* 头插法 */
void reverseReinsert(LinkedList *L)
{
    Node *cur = L->head->next;
    L->head->next = NULL;           /* 先摘空 */

    while (cur != NULL) {
        Node *next = cur->next;     /* 存后继 */
        cur->next = L->head->next;  /* 头插 */
        L->head->next = cur;
        cur = next;
    }
}

int main(void)
{
    printf("=== 三指针法 ===\n");
    LinkedList *L = create();
    for (int i = 1; i <= 5; i++) pushBack(L, i);
    print(L);
    reverseThreePointer(L);
    print(L);

    printf("\n=== 再跑一次头插法（应回到原顺序）===\n");
    reverseReinsert(L);
    print(L);

    printf("\n=== 为什么三指针把空表和单节点也处理对了 ===\n");
    printf("  空表：cur = head->next = NULL，while 一次都不进，\n");
    printf("        head->next = prev = NULL，还是空表 ✓\n");
    printf("  单节点：cur 走一轮，prev = 该节点，cur = NULL，\n");
    printf("        head->next = prev，还是它自己 ✓\n");
    printf("  ⭐ 不需要任何 if 特判 —— 这是三指针法的优雅之处。\n");

    /* 边界测试 */
    printf("\n=== 边界测试 ===\n");
    LinkedList *E = create();
    printf("空表：");  print(E);
    reverseThreePointer(E);
    printf("逆置后："); print(E);
    printf("空表不崩 ✓\n");

    LinkedList *S = create();
    pushBack(S, 42);
    printf("\n单节点："); print(S);
    reverseThreePointer(S);
    printf("逆置后："); print(S);
    printf("单节点不崩 ✓\n");

    destroy(L);
    destroy(E);
    destroy(S);

    printf("\n=== 三指针四步，顺序绝对不能错 ===\n");
    printf("  ✅ next = cur->next;  cur->next = prev;  prev = cur;  cur = next;\n");
    printf("  ❌ 如果先写 cur->next = prev：\n");
    printf("     那 cur 原来的后继指针被覆盖，后面的节点再也找不到了，\n");
    printf("     链表只剩前半截，后半截全部内存泄漏。\n");
    printf("  ⭐ 这是链表题第一大 bug，考试改错题常考。\n");

    return 0;
}
