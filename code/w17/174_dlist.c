/* 174_dlist.c —— 双向链表与循环链表
 *
 * 单链表的痛点：知道一个节点，删不掉自己（要找前驱，O(n)）。
 * 双向链表每个节点多存一个 prev，就能直接删自己，O(1)。
 *
 * 代价：每个节点多 8 字节，插入删除要改 4 个指针而不是 2 个。
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- 双向链表节点 ---------- */
typedef struct DNode {
    int           data;
    struct DNode *prev;         /* 指向前一个 */
    struct DNode *next;         /* 指向后一个 */
} DNode;

typedef struct {
    DNode *head;                /* 头结点（dummy） */
    DNode *tail;                /* 尾节点（真节点，空表时等于 head） */
    int    length;
} DList;

static DList *dcreate(void)
{
    DList *L = (DList *)malloc(sizeof(DList));
    if (!L) return NULL;
    L->head = (DNode *)malloc(sizeof(DNode));
    if (!L->head) { free(L); return NULL; }

    L->head->prev = NULL;       /* 头结点的 prev 永远是 NULL */
    L->head->next = NULL;
    L->head->data = 0;
    L->tail = L->head;          /* 空表时 tail 指向 head */
    L->length = 0;
    return L;
}

/* 尾插：双链表有 tail 指针，O(1) */
static void dpushBack(DList *L, int v)
{
    DNode *n = (DNode *)malloc(sizeof(DNode));
    if (!n) return;
    n->data = v;

    /* 四步：新节点的 next、新节点的 prev、旧尾的 next、tail 前移 */
    n->next = NULL;
    n->prev = L->tail;
    L->tail->next = n;
    L->tail = n;
    L->length++;
}

static void dprint(const DList *L)
{
    printf("  正向：");
    for (DNode *p = L->head->next; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" <-> ");
    }
    printf("\n");

    printf("  反向：");
    for (DNode *p = L->tail; p != L->head; p = p->prev) {
        printf("%d", p->data);
        if (p->prev != L->head) printf(" <-> ");
    }
    printf("\n");
}

/* ---------- ① 在已知节点 p 之后插入 ---------- */
/* 这是双链表的杀手锏：只改 4 个指针，不需要找前驱 */
static void dinsertAfter(DList *L, DNode *p, int v)
{
    DNode *n = (DNode *)malloc(sizeof(DNode));
    if (!n) return;
    n->data = v;

    n->next = p->next;          /* ① 新节点接后 */
    n->prev = p;                /* ② 新节点接前 */
    if (p->next != NULL) {
        p->next->prev = n;      /* ③ 后节点的 prev 改指新节点 */
    } else {
        L->tail = n;            /* p 原来是尾节点 → 更新 tail */
    }
    p->next = n;                /* ④ 前节点的 next 改指新节点 */
    L->length++;
}

/* ---------- ② 删除已知节点 p ---------- */
/* 单链表要 O(n) 找前驱，双链表 O(1) 直接删 */
static void ddeleteNode(DList *L, DNode *p)
{
    if (p == NULL || p == L->head) return;

    p->prev->next = p->next;    /* ① 前驱跳过自己 */
    if (p->next != NULL) {
        p->next->prev = p->prev;/* ② 后继的 prev 改指自己的前驱 */
    } else {
        L->tail = p->prev;      /* 自己是尾节点 → 更新 tail */
    }
    free(p);
    L->length--;
}

static void ddestroy(DList *L)
{
    if (!L) return;
    DNode *p = L->head;
    while (p) { DNode *nx = p->next; free(p); p = nx; }
    free(L);
}

int main(void)
{
    DList *L = dcreate();
    for (int i = 1; i <= 4; i++) dpushBack(L, i * 10);

    printf("=== ① 双向链表结构 ===\n");
    dprint(L);
    printf("  length=%d\n", L->length);
    printf("\n  ⭐ 每个节点有两个指针：prev 指向前、next 指向后。\n");
    printf("     所以既能正向遍历，也能反向遍历 —— 单链表做不到。\n");

    /* ---------- ② 已知节点后插入 ---------- */
    printf("\n=== ② 在 2 号节点（值是 20）之后插入 25 ===\n");
    DNode *p20 = L->head->next->next;       /* 第二个节点 */
    dinsertAfter(L, p20, 25);
    dprint(L);

    printf("\n  ⭐ 只改 4 个指针，全程 O(1)，不需要从头找。\n");
    printf("     对比单链表：要在 p 之后插入其实也是 O(1)，\n");
    printf("     但要在 p 【之前】插入，单链表必须找前驱 O(n)，双链表 O(1)。\n");

    /* ---------- ③ 删除已知节点 ---------- */
    printf("\n=== ③ 删除节点 25（已拿到它的指针）===\n");
    DNode *p25 = p20->next;
    ddeleteNode(L, p25);
    dprint(L);

    printf("\n  ⭐ 这是双链表最大的价值：\n");
    printf("     单链表要删某个节点，必须知道它的【前驱】，否则得从头找 O(n)。\n");
    printf("     双链表有 prev，直接就能删，O(1)。\n");
    printf("  📌 LRU 缓存、链表节点删除类题目都用双链表，就是为了这个 O(1)。\n");

    /* ---------- ④ 双链表的代价 ---------- */
    printf("\n=== ④ 代价：多改指针、多占内存 ===\n");
    printf("  %-18s %-14s %s\n", "项目", "单链表", "双链表");
    printf("  --------------------------------------------------\n");
    printf("  %-18s %-14s %s\n", "每节点指针数", "1 个 next", "2 个 prev+next");
    printf("  %-18s %-14s %s\n", "32 位机每节点", "8 字节", "12 字节");
    printf("  %-18s %-14s %s\n", "64 位机每节点", "16 字节", "24 字节");
    printf("  %-18s %-14s %s\n", "插入要改指针", "2 个", "4 个");
    printf("  %-18s %-14s %s\n", "删除已知节点", "O(n) 找前驱", "O(1)");
    printf("  %-18s %-14s %s\n", "反向遍历", "不支持", "支持");

    printf("\n  ⭐ 用空间换时间：每节点多 8 字节，换来「删除 O(1)」和「反向遍历」。\n");

    ddestroy(L);

    /* ---------- ⑤ 循环链表 ---------- */
    printf("\n=== ⑤ 循环链表：尾节点指回头结点 ===\n");
    printf("  单链表：  1 -> 2 -> 3 -> NULL\n");
    printf("  循环链表：1 -> 2 -> 3 -> （回到 1）\n");
    printf("\n  ⭐ 三个要点：\n");
    printf("     1. 判遍历结束不能用 p != NULL，要用 p != head\n");
    printf("        （否则死循环，这是循环链表最常见的 bug）\n");
    printf("     2. 从任意节点出发都能遍历整条链 —— 这是它的优势\n");
    printf("        约瑟夫环、轮转调度都用它\n");
    printf("     3. 只有一个节点的循环链表：next 指向自己\n");
    printf("\n  📌 软考里常画「循环单链表」和「循环双链表」的结构图，\n");
    printf("     记特征：尾巴不指向 NULL，而是绕回去。\n");

    /* ---------- ⑥ 四种链表一览 ---------- */
    printf("\n=== ⑥ 四种链表 ===\n");
    printf("  %-18s %-24s %s\n", "类型", "指针情况", "典型用途");
    printf("  ----------------------------------------------------------------------------\n");
    printf("  %-18s %-24s %s\n", "单链表", "1 个 next，尾指 NULL", "普通链式存储");
    printf("  %-18s %-24s %s\n", "双链表", "prev + next，尾指 NULL", "需要反向/删除 O(1)");
    printf("  %-18s %-24s %s\n", "循环单链表", "1 个 next，尾指回头结点", "约瑟夫环、轮转");
    printf("  %-18s %-24s %s\n", "循环双链表", "prev + next，头尾互指", "双向轮转");

    printf("\n  ⭐ 软考最常考的是**单链表**和**双链表**，\n");
    printf("     循环链表主要考「判空条件」和「结构图识别」。\n");

    return 0;
}
