/* ============================================================================
 * 271_verify_part1.c  —— W27 大题专项（一）答案验证
 *
 * 本文件不教新东西，只做一件事：把讲义里让你「手算」的三道大题
 * 用代码算一遍，确认给的标准答案是对的。
 *
 *   题 1：读程序写结果（二叉树后序 / 先序 / 节点数）
 *   题 2：手算执行过程（快排一趟分区、建大根堆、取堆顶后调整）
 *   题 3：补全算法（单链表逆置、循环队列、折半查找递归版）
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 271.exe 271_verify_part1.c
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

/* ==========================================================================
 * 题 1：读程序写结果
 *
 * 树：
 *           8
 *         /   \
 *        3     10
 *       / \      \
 *      1   6      14
 *         / \    /
 *        4   7  13
 * ========================================================================*/

typedef struct Node { int key; struct Node *left, *right; } Node;

static Node *newNode(int k)
{
    Node *p = malloc(sizeof(Node));
    p->key = k; p->left = p->right = NULL;
    return p;
}

/* 题目给的函数：先递归左右，再打印自己 */
static int f(Node *t)
{
    if (!t) return 0;
    int l = f(t->left);
    int r = f(t->right);
    printf("%d ", t->key);
    return l + r + 1;
}

/* 对照：把打印放到最前面（先序） */
static int g(Node *t)
{
    if (!t) return 0;
    printf("%d ", t->key);
    return g(t->left) + g(t->right) + 1;
}

static void freeTree(Node *t)
{
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

/* ==========================================================================
 * 题 2：手算执行过程
 * ========================================================================*/

static void printArr(const char *tag, const int *a, int n)
{
    printf("  %-14s", tag);
    for (int i = 0; i < n; i++) printf("%3d", a[i]);
    printf("\n");
}

/* ---------- 2(a) 快排一趟分区（挖坑法，取首元素为基准）---------- */
static int partitionTrace(int *a, int lo, int hi)
{
    int pivot = a[lo];
    int i = lo, j = hi;
    printf("  基准 = %d（挖走 a[%d]，留一个坑）\n", pivot, lo);

    while (i < j) {
        while (i < j && a[j] >= pivot) j--;
        if (i < j) {
            a[i] = a[j];
            printf("    a[%d]=%d 填到左边的坑 → ", j, a[j]);
            printArr("当前:", a, hi + 1);
            i++;
        }
        while (i < j && a[i] <= pivot) i++;
        if (i < j) {
            a[j] = a[i];
            printf("    a[%d]=%d 填到右边的坑 → ", i, a[i]);
            printArr("当前:", a, hi + 1);
            j--;
        }
    }
    a[i] = pivot;
    printf("  基准归位到下标 %d\n", i);
    return i;
}

/* ---------- 2(b) 建大根堆 ---------- */
static void siftDown(int *a, int i, int n, int verbose)
{
    int tmp = a[i];
    int child = 2 * i + 1;
    while (child < n) {
        if (child + 1 < n && a[child + 1] > a[child]) child++;   /* 选较大的孩子 */
        if (tmp >= a[child]) break;
        a[i] = a[child];
        i = child;
        child = 2 * i + 1;
    }
    a[i] = tmp;
    if (verbose) printArr("  调整后:", a, n);
}

static void buildHeap(int *a, int n, int verbose)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        if (verbose) printf("  从 i=%d（值 %d）开始下沉：\n", i, a[i]);
        siftDown(a, i, n, verbose);
    }
}

/* ==========================================================================
 * 题 3：补全算法
 * ========================================================================*/

typedef struct LNode { int data; struct LNode *next; } LNode;

static LNode *buildList(const int *arr, int n)
{
    LNode *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        LNode *p = malloc(sizeof(LNode));
        p->data = arr[i]; p->next = NULL;
        if (!head) head = p; else tail->next = p;
        tail = p;
    }
    return head;
}

static void showList(const char *tag, LNode *h)
{
    printf("  %-14s", tag);
    for (; h; h = h->next) printf("%d ", h->data);
    printf("\n");
}

/* 3(a) 就地逆置：三指针 */
static LNode *reverseList(LNode *head)
{
    LNode *prev = NULL, *cur = head, *next;
    while (cur) {
        next = cur->next;       /* ① 先记住后面 */
        cur->next = prev;       /* ② 掉头 */
        prev = cur;             /* ③ prev 前进 */
        cur = next;             /* ④ cur 前进 */
    }
    return prev;
}

/* 3(b) 循环队列：少用一个元素区分队空队满 */
#define QMAX 6
typedef struct { int data[QMAX]; int front, rear; } CQueue;

static void qInit(CQueue *q) { q->front = q->rear = 0; }
static int qEmpty(CQueue *q) { return q->front == q->rear; }
static int qFull(CQueue *q)  { return (q->rear + 1) % QMAX == q->front; }
static int qPush(CQueue *q, int x)
{
    if (qFull(q)) return 0;
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % QMAX;
    return 1;
}
static int qPop(CQueue *q, int *x)
{
    if (qEmpty(q)) return 0;
    *x = q->data[q->front];
    q->front = (q->front + 1) % QMAX;
    return 1;
}

/* 3(c) 折半查找递归版 */
static int binRec(const int *a, int lo, int hi, int key)
{
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == key) return mid;
    if (a[mid] < key) return binRec(a, mid + 1, hi, key);
    return binRec(a, lo, mid - 1, key);
}

int main(void)
{
    /* ---------------- 题 1 ---------------- */
    printf("=== 题 1：读程序写结果 ===\n");
    Node *root = newNode(8);
    root->left = newNode(3);
    root->right = newNode(10);
    root->left->left = newNode(1);
    root->left->right = newNode(6);
    root->left->right->left = newNode(4);
    root->left->right->right = newNode(7);
    root->right->right = newNode(14);
    root->right->right->left = newNode(13);

    printf("  f() 的输出（后序）：");
    int cnt = f(root);
    printf("\n  返回值 = %d\n", cnt);
    printf("  g() 的输出（先序）：");
    g(root);
    printf("\n");
    freeTree(root);

    /* ---------------- 题 2(a) ---------------- */
    printf("\n=== 题 2(a)：快排第一趟分区 ===\n");
    int a[] = {49, 38, 65, 97, 76, 13, 27, 52};
    int n = 8;
    printArr("初始:", a, n);
    int p = partitionTrace(a, 0, n - 1);
    printArr("一趟后:", a, n);
    printf("  基准 49 的最终位置 = %d\n", p);

    /* ---------------- 题 2(b) ---------------- */
    printf("\n=== 题 2(b)：建大根堆 ===\n");
    int b[] = {49, 38, 65, 97, 76, 13, 27, 52};
    printArr("初始:", b, n);
    buildHeap(b, n, 1);
    printArr("建堆后:", b, n);

    printf("\n  取出堆顶 %d，把末尾元素 %d 放到堆顶后重新下沉：\n", b[0], b[n - 1]);
    int top = b[0];
    b[0] = b[n - 1];
    n--;
    siftDown(b, 0, n, 0);
    printArr("调整后:", b, n);
    printf("  新的堆顶 = %d（原第二大）\n", b[0]);
    (void)top;

    /* ---------------- 题 3(a) ---------------- */
    printf("\n=== 题 3(a)：单链表就地逆置 ===\n");
    int arr[] = {1, 2, 3, 4, 5};
    LNode *head = buildList(arr, 5);
    showList("原链表:", head);
    head = reverseList(head);
    showList("逆置后:", head);
    while (head) { LNode *t = head; head = head->next; free(t); }

    /* ---------------- 题 3(b) ---------------- */
    printf("\n=== 题 3(b)：循环队列（长度 6，最多存 5 个）===\n");
    CQueue q; qInit(&q);
    printf("  QMAX=%d，判满条件 (rear+1)%%QMAX == front\n", QMAX);
    for (int i = 1; i <= 5; i++) {
        int ok = qPush(&q, i);          /* 先调用，再读 front/rear，避免求值顺序问题 */
        printf("    入队 %d → %s（front=%d, rear=%d）\n", i,
               ok ? "成功" : "队满失败", q.front, q.rear);
    }
    int ok6 = qPush(&q, 6);
    printf("    第 6 次入队 6 → %s（front=%d, rear=%d，说明少用一个元素）\n",
           ok6 ? "成功" : "队满失败", q.front, q.rear);
    int x = 0;
    int p1 = qPop(&q, &x);
    printf("    出队 → %d（front=%d）\n", p1 ? x : -1, q.front);
    p1 = qPop(&q, &x);
    printf("    出队 → %d（front=%d）\n", p1 ? x : -1, q.front);
    int ok7 = qPush(&q, 7);
    printf("    再入队 7 → %s（front=%d, rear=%d）\n",
           ok7 ? "成功" : "失败", q.front, q.rear);

    /* ---------------- 题 3(c) ---------------- */
    printf("\n=== 题 3(c)：折半查找递归版 ===\n");
    int s[] = {8, 15, 22, 27, 33, 41, 55, 60, 73, 84, 96};
    int sn = 11;
    int keys[] = {33, 8, 96, 50};
    for (int i = 0; i < 4; i++)
        printf("    查 %-4d → 下标 %d\n", keys[i], binRec(s, 0, sn - 1, keys[i]));
    return 0;
}
