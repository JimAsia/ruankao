/* 171_slist_basic.c —— 单链表：用指针串起来的线性表
 *
 * 顺序表的痛点：插入删除要挪元素（O(n)）。
 * 链表用指针把节点串起来，插入删除只改指针，O(1)。
 * 代价：不能随机访问，找第 i 个要一个个走（O(n)）。
 *
 * 本文件讲三件事：建表（头插/尾插）、遍历、销毁。
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- 节点结构 ---------- */
typedef struct Node {
    int          data;      /* 数据域 */
    struct Node *next;      /* 指针域：指向下一个节点 */
} Node;

/* ---------- 带头结点的链表 ---------- */
/* 头结点（dummy head）不存数据，只是为了让「第一个节点」和
 * 「其他节点」的处理方式一样，省掉一堆 if (p == head) 的特判。 */
typedef struct {
    Node *head;             /* 永远指向头结点 */
    int   length;           /* 元素个数（不含头结点） */
} LinkedList;

/* 创建头结点，得到空链表 */
LinkedList *listCreate(void)
{
    LinkedList *L = (LinkedList *)malloc(sizeof(LinkedList));
    if (L == NULL) return NULL;

    L->head = (Node *)malloc(sizeof(Node));
    if (L->head == NULL) {
        free(L);
        return NULL;
    }
    L->head->next = NULL;
    L->head->data = 0;              /* 头结点的数据域不用 */
    L->length = 0;
    return L;
}

/* ---------- ① 头插法：每次插在头结点之后 ---------- */
/* 结果：输入顺序与链表顺序【相反】 */
int insertHead(LinkedList *L, int value)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) return 0;

    n->data = value;
    n->next = L->head->next;        /* ① 新节点先接上原来的第一个 */
    L->head->next = n;              /* ② 头结点再指向新节点 */
    L->length++;
    return 1;
}

/* ---------- ② 尾插法：每次插在链表末尾 ---------- */
/* 结果：输入顺序与链表顺序【相同】。这是最常用的建表方式 */
int insertTail(LinkedList *L, int value)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) return 0;

    /* 找尾节点：从头走到 next == NULL 的那个 */
    Node *p = L->head;
    while (p->next != NULL) p = p->next;

    n->data = value;
    n->next = NULL;
    p->next = n;                    /* 尾节点指向新节点 */
    L->length++;
    return 1;
}

/* ---------- ③ 遍历 ---------- */
void listPrint(const LinkedList *L)
{
    printf("  ");
    Node *p = L->head->next;        /* 从第一个真节点开始（跳过 dummy） */
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) printf(" -> ");
        p = p->next;
    }
    printf(" -> NULL   (length=%d)\n", L->length);
}

/* ---------- ④ 求长度（两种方式）---------- */
int lengthByField(const LinkedList *L)
{
    return L->length;               /* O(1)：维护了一个计数字段 */
}

int lengthByWalk(const LinkedList *L)
{
    int n = 0;
    Node *p = L->head->next;
    while (p != NULL) {             /* O(n)：走一遍数 */
        n++;
        p = p->next;
    }
    return n;
}

/* ---------- ⑤ 按值查找，返回节点指针 ---------- */
Node *findValue(const LinkedList *L, int value)
{
    Node *p = L->head->next;
    while (p != NULL) {
        if (p->data == value) return p;
        p = p->next;
    }
    return NULL;
}

/* ---------- ⑥ 销毁：每个 malloc 都要 free ---------- */
void listDestroy(LinkedList *L)
{
    if (L == NULL) return;

    Node *p = L->head;
    while (p != NULL) {
        Node *next = p->next;       /* 先存下一个，否则 free 后拿不到 */
        free(p);
        p = next;
    }
    free(L);                        /* 最后释放链表结构本身 */
}

int main(void)
{
    /* ---------- ① 尾插法建表 ---------- */
    printf("=== ① 尾插法：顺序与输入一致 ===\n");
    LinkedList *L1 = listCreate();
    for (int i = 1; i <= 5; i++) insertTail(L1, i * 10);
    listPrint(L1);
    printf("  输入 10 20 30 40 50，链表也是 10 20 30 40 50\n");

    /* ---------- ② 头插法建表 ---------- */
    printf("\n=== ② 头插法：顺序与输入相反 ===\n");
    LinkedList *L2 = listCreate();
    for (int i = 1; i <= 5; i++) insertHead(L2, i * 10);
    listPrint(L2);
    printf("  输入 10 20 30 40 50，链表变成 50 40 30 20 10\n");
    printf("\n  ⭐ 为什么？每次新节点都插在最前面，最后一次插的排最前。\n");
    printf("     这个特性可以用来「逆序建表」，也可以用来自动逆置。\n");

    /* ---------- ③ 头结点到底有什么用 ---------- */
    printf("\n=== ③ 头结点的作用 ===\n");
    printf("  带头结点：头结点的 next 指向第一个真元素\n");
    printf("  不带头结点：head 直接指向第一个元素\n");
    printf("\n  ⭐ 差别在「空表」和「插第一个元素」时：\n");
    printf("     不带头结点要在删除/插入时特判「操作的是不是第一个节点」，\n");
    printf("     代码里到处是 if (p == head) 或 if (prev == NULL)。\n");
    printf("     带头结点后，所有节点的操作方式都统一了，\n");
    printf("     第一个元素的前驱就是头结点，不用特判。\n");
    printf("\n  📌 软考题里如果给了带头结点的图，插入删除都按「有前驱」处理。\n");

    /* ---------- ④ 两种求长度 ---------- */
    printf("\n=== ④ 求长度的两种方式 ===\n");
    printf("  维护计数字段：%d（O(1)）\n", lengthByField(L1));
    printf("  走一遍数    ：%d（O(n)）\n", lengthByWalk(L1));
    printf("  ⭐ 顺序表求长度是 O(1)（length 字段），链表如果维护了计数也是 O(1)。\n");
    printf("     不维护的话就是 O(n)，所以工程上都维护。\n");

    /* ---------- ⑤ 查找：链表最慢的地方 ---------- */
    printf("\n=== ⑤ 按值查找 ===\n");
    Node *p = findValue(L1, 30);
    printf("  找 30：%s", p ? "找到了" : "没找到");
    if (p) printf("，节点地址 %p，data=%d\n", (void *)p, p->data);

    p = findValue(L1, 99);
    printf("  找 99：%s\n", p ? "找到了" : "没找到（返回 NULL）");

    printf("\n  ⭐ 链表不能随机访问：\n");
    printf("     顺序表 L[i] 一步到位（地址算出来），O(1)；\n");
    printf("     链表找第 i 个必须从头走 i 步，O(n)。\n");
    printf("     这是链表最大的缺点，也是它和顺序表互补的地方。\n");

    /* ---------- ⑥ 内存：每个 malloc 都要有 free ---------- */
    printf("\n=== ⑥ 内存管理 ===\n");
    printf("  5 个节点 + 1 个头结点 + 1 个链表结构 = 7 次 malloc\n");
    printf("  销毁时必须全部 free，否则内存泄漏。\n");
    printf("  ⚠️ 释放时要先保存 next 再 free，否则 free 之后就取不到 next 了。\n");

    listDestroy(L1);
    listDestroy(L2);
    printf("  已全部释放。\n");

    printf("\n=== ⑦ 顺序表 vs 链表（背诵这张表）===\n");
    printf("  %-20s %-16s %s\n", "对比项", "顺序表", "链表");
    printf("  ------------------------------------------------------------\n");
    printf("  %-20s %-16s %s\n", "存储方式", "连续内存", "分散 + 指针");
    printf("  %-20s %-16s %s\n", "按位置访问", "O(1) 随机访问", "O(n) 要走");
    printf("  %-20s %-16s %s\n", "按值查找", "O(n)", "O(n)");
    printf("  %-20s %-16s %s\n", "插入删除", "O(n) 要挪元素", "O(1) 只改指针*");
    printf("  %-20s %-16s %s\n", "额外空间", "无", "每节点 1 个指针");
    printf("  %-20s %-16s %s\n", "长度", "固定（或要扩容）", "动态，想加就加");
    printf("\n  * 链表插入删除 O(1) 的前提是「已经拿到那个位置的指针」；\n");
    printf("    如果只知道值、要先查找，那整体还是 O(n)。\n");
    printf("    📌 这个前提软考常考，别漏。\n");

    return 0;
}
