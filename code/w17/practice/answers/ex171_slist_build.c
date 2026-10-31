/* ex171_slist_build.c —— 参考答案 */

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
    L->head->data = 0;
    return L;
}

void insertHead(LinkedList *L, int v)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return;

    n->data = v;
    n->next = L->head->next;        /* ① 新节点接上原来的第一个 */
    L->head->next = n;              /* ② 头结点改指新节点 */
}

void insertTail(LinkedList *L, int v)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return;

    n->data = v;
    n->next = NULL;

    Node *p = L->head;
    while (p->next != NULL) p = p->next;    /* 走到尾节点 */
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

int length(const LinkedList *L)
{
    int n = 0;
    for (Node *p = L->head->next; p; p = p->next) n++;
    return n;
}

void destroy(LinkedList *L)
{
    if (!L) return;
    Node *p = L->head;
    while (p) {
        Node *nx = p->next;         /* ⚠️ 先存，否则 free 后取不到 */
        free(p);
        p = nx;
    }
    free(L);
}

int main(void)
{
    printf("=== 尾插法 ===\n");
    LinkedList *L1 = create();
    for (int i = 1; i <= 5; i++) insertTail(L1, i * 10);
    print(L1);
    printf("  输入 10 20 30 40 50 → 顺序一致\n");

    printf("\n=== 头插法 ===\n");
    LinkedList *L2 = create();
    for (int i = 1; i <= 5; i++) insertHead(L2, i * 10);
    print(L2);
    printf("  输入 10 20 30 40 50 → 顺序相反\n");

    printf("\n=== 遍历求长度 ===\n");
    printf("  尾插链表长度：%d\n", length(L1));
    printf("  头插链表长度：%d\n", length(L2));

    printf("\n=== 头插法的两个易错点 ===\n");
    printf("  1. 两句顺序不能反：\n");
    printf("     ✅ n->next = head->next;  head->next = n;\n");
    printf("     ❌ head->next = n;  n->next = head->next;\n");
    printf("        反了之后 n->next 指向自己，链表变成自环，遍历死循环。\n");
    printf("  2. 头插法建表得到的是逆序 —— 这既是「缺点」也是「特性」：\n");
    printf("     想逆序一个链表，不用逆置算法，头插法重建一遍就行。\n");

    destroy(L1);
    destroy(L2);
    printf("\n已释放两条链表。\n");

    return 0;
}
