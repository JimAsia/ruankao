/* ex172_slist_insert_delete.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int   length;
} LinkedList;

LinkedList *create(void)
{
    LinkedList *L = (LinkedList *)malloc(sizeof(LinkedList));
    if (!L) return NULL;
    L->head = (Node *)malloc(sizeof(Node));
    if (!L->head) { free(L); return NULL; }
    L->head->next = NULL;
    L->length = 0;
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
    L->length++;
}

void print(const LinkedList *L)
{
    printf("  ");
    for (Node *p = L->head->next; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf(" -> NULL   (length=%d)\n", L->length);
}

void destroy(LinkedList *L)
{
    if (!L) return;
    Node *p = L->head;
    while (p) { Node *nx = p->next; free(p); p = nx; }
    free(L);
}

/* 取第 pos 个节点的前驱（pos=0 时返回头结点） */
static Node *getPrev(const LinkedList *L, int pos)
{
    Node *p = L->head;
    for (int i = 0; i < pos && p != NULL; i++) {
        p = p->next;
    }
    return p;
}

int insertAt(LinkedList *L, int pos, int v)
{
    if (pos < 0 || pos > L->length) {
        printf("  插入失败：pos=%d 越界（合法 0..%d）\n", pos, L->length);
        return 0;
    }

    Node *prev = getPrev(L, pos);
    if (prev == NULL) return 0;

    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return 0;

    n->data = v;
    n->next = prev->next;           /* ① 先接后半段 */
    prev->next = n;                 /* ② 再断前半段 */

    L->length++;
    return 1;
}

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
    free(victim);                   /* ⚠️ 必须 free */

    L->length--;
    return 1;
}

int main(void)
{
    LinkedList *L = create();
    for (int i = 1; i <= 5; i++) pushBack(L, i * 10);

    printf("初始：\n"); print(L);

    printf("\n=== 在下标 2 插入 99 ===\n");
    insertAt(L, 2, 99);
    print(L);

    printf("\n=== 表头插入 5 ===\n");
    insertAt(L, 0, 5);
    print(L);
    printf("  ⭐ 表头插入时前驱就是头结点，一步找到 → O(1)\n");

    printf("\n=== 末尾插入 60 ===\n");
    insertAt(L, L->length, 60);
    print(L);
    printf("  ⚠️ 末尾插入要找前驱（走完整个链表）→ O(n)\n");

    printf("\n=== 删除下标 3 ===\n");
    int out = 0;
    if (deleteAt(L, 3, &out)) {
        printf("  被删的是 %d\n", out);
        print(L);
    }

    printf("\n=== 越界测试 ===\n");
    deleteAt(L, 99, &out);
    insertAt(L, -1, 1);
    insertAt(L, L->length + 1, 1);

    printf("\n=== 关键点 ===\n");
    printf("  1. 插入时 n->next 和 prev->next 的顺序不能反\n");
    printf("     （反了会丢后半段，后面的节点全部内存泄漏）\n");
    printf("  2. 删除时必须 free(victim)\n");
    printf("  3. 插入的 pos 可以等于 length（插在末尾）\n");
    printf("     删除的 pos 最大是 length-1\n");
    printf("  4. 链表插表头 O(1)、插表尾 O(n)，和顺序表正好相反\n");

    destroy(L);
    return 0;
}
