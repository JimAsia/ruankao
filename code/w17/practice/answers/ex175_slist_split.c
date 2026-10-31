/* ex175_slist_split.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int   length;
} LinkedList;

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

void splitOddEven(LinkedList *src, LinkedList *odd, LinkedList *even)
{
    Node *cur = src->head->next;

    while (cur != NULL) {
        Node *next = cur->next;     /* ⚠️ 先存后继，下面要改 cur->next */

        if (cur->data % 2 != 0) {
            /* 接到 odd 末尾 */
            cur->next = NULL;
            odd->tail->next = cur;
            odd->tail = cur;
            odd->length++;
        } else {
            cur->next = NULL;
            even->tail->next = cur;
            even->tail = cur;
            even->length++;
        }

        cur = next;
    }

    /* 源链表变空 */
    src->head->next = NULL;
    src->tail = src->head;
    src->length = 0;
}

int main(void)
{
    /* ---------- 主测试 ---------- */
    printf("=== 主测试：1..8 ===\n");
    LinkedList *src  = create();
    LinkedList *odd  = create();
    LinkedList *even = create();

    for (int i = 1; i <= 8; i++) pushBack(src, i);
    print("源", src);

    splitOddEven(src, odd, even);
    print("奇数链", odd);
    print("偶数链", even);
    print("源（已空）", src);

    /* ---------- 全是奇数 ---------- */
    printf("\n=== 边界：全是奇数 ===\n");
    LinkedList *s2 = create(), *o2 = create(), *e2 = create();
    for (int i = 1; i <= 5; i += 2) pushBack(s2, i);
    print("源", s2);
    splitOddEven(s2, o2, e2);
    print("奇数链", o2);
    print("偶数链", e2);
    printf("  → 偶数链为空，不崩 ✓\n");

    /* ---------- 空表 ---------- */
    printf("\n=== 边界：空表 ===\n");
    LinkedList *s3 = create(), *o3 = create(), *e3 = create();
    splitOddEven(s3, o3, e3);
    print("奇数链", o3);
    print("偶数链", e3);
    printf("  → 两条都空，不崩 ✓\n");

    printf("\n=== 两个致命细节 ===\n");
    printf("  ① 摘节点前必须存 next\n");
    printf("     Node *next = cur->next;\n");
    printf("     ... cur->next = NULL;（接到新链）...\n");
    printf("     cur = next;\n");
    printf("     少了这句，cur->next 一改，后面的节点全丢。\n");
    printf("\n  ② 必须维护 tail 指针\n");
    printf("     没有 tail，每次尾插都要从头找尾 → 整体 O(n^2)。\n");
    printf("     有了 tail，每次插入 O(1) → 整体 O(n)。\n");
    printf("     实测：n=8 时差别看不出，n=100000 时差几个小时。\n");

    printf("\n=== 复杂度 ===\n");
    printf("  时间 O(n)：每个节点只被访问常数次\n");
    printf("  空间 O(1)：只重排指针，不新建节点\n");
    printf("  ⭐ 这就是「原地拆分」，链表最擅长的操作。\n");

    destroy(src); destroy(odd); destroy(even);
    destroy(s2);  destroy(o2);  destroy(e2);
    destroy(s3);  destroy(o3);  destroy(e3);
    return 0;
}
