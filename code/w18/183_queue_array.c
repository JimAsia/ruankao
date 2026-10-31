/* 183_queue_array.c —— 顺序队列的假溢出与循环队列
 *
 * 队列是**受限的线性表**：只允许在一端（队尾 rear）插入，另一端（队头 front）删除。
 * 特性：先进先出 FIFO（First In First Out）。
 *
 * 顺序队列有个致命问题叫【假溢出】：
 *   出队后 front 往后走，前面的空间就再也用不到了；
 *   rear 走到数组末尾时，明明前面还有空位，却报「满」。
 *
 * 解决办法：让 rear 和 front 绕回来 —— 循环队列（取模）。
 */

#include <stdio.h>

#define MAXSIZE 5

/* ==================== ① 普通顺序队列（有假溢出问题） ==================== */
typedef struct {
    int data[MAXSIZE];
    int front;              /* 队头下标，指向第一个元素 */
    int rear;               /* 队尾下标，指向【下一个空位】 */
} Queue;

void qinit(Queue *Q) { Q->front = Q->rear = 0; }

int qempty(const Queue *Q) { return Q->front == Q->rear; }
int qfull(const Queue *Q)  { return Q->rear == MAXSIZE; }   /* 直接看 rear */

int enqueue(Queue *Q, int v)
{
    if (qfull(Q)) {
        printf("    入队失败：rear 已到 %d\n", Q->rear);
        return 0;
    }
    Q->data[Q->rear++] = v;         /* 放进去，rear 后移 */
    return 1;
}

int dequeue(Queue *Q, int *out)
{
    if (qempty(Q)) return 0;
    *out = Q->data[Q->front++];     /* 取出，front 后移 */
    return 1;
}

void qshow(const char *label, const Queue *Q)
{
    printf("  %-12s front=%d rear=%d 队列[", label, Q->front, Q->rear);
    for (int i = Q->front; i < Q->rear; i++) {
        printf("%d", Q->data[i]);
        if (i != Q->rear - 1) printf(" ");
    }
    printf("]\n");
}

/* ==================== ② 循环队列（解决假溢出） ==================== */
/* 方案一：少用一个存储单元（最常考）
 *   判空：front == rear
 *   判满：(rear + 1) % MAXSIZE == front
 *   这样 MAXSIZE=5 的数组最多存 4 个元素。 */
typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} CircQueue;

void cqinit(CircQueue *Q) { Q->front = Q->rear = 0; }

int cqempty(const CircQueue *Q) { return Q->front == Q->rear; }
int cqfull(const CircQueue *Q)  { return (Q->rear + 1) % MAXSIZE == Q->front; }

/* 队列元素个数 —— 软考常考这个公式 */
int cqsize(const CircQueue *Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

int cqenqueue(CircQueue *Q, int v)
{
    if (cqfull(Q)) {
        printf("    入队失败：队列满（front=%d rear=%d）\n", Q->front, Q->rear);
        return 0;
    }
    Q->data[Q->rear] = v;
    Q->rear = (Q->rear + 1) % MAXSIZE;      /* ⭐ 取模，绕回来 */
    return 1;
}

int cqdequeue(CircQueue *Q, int *out)
{
    if (cqempty(Q)) {
        printf("    出队失败：队列空\n");
        return 0;
    }
    *out = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;    /* ⭐ 取模，绕回来 */
    return 1;
}

void cqshow(const char *label, const CircQueue *Q)
{
    printf("  %-12s front=%d rear=%d size=%d 队列[", label,
           Q->front, Q->rear, cqsize(Q));
    int n = cqsize(Q);
    for (int i = 0; i < n; i++) {
        printf("%d", Q->data[(Q->front + i) % MAXSIZE]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    /* ---------- ① 演示假溢出 ---------- */
    printf("=== ① 普通顺序队列：演示假溢出 ===\n");
    printf("  数组容量 MAXSIZE = %d\n\n", MAXSIZE);

    Queue Q;
    qinit(&Q);

    printf("  入队 1 2 3 4 5：\n");
    for (int i = 1; i <= 5; i++) enqueue(&Q, i);
    qshow("队满", &Q);

    printf("\n  出队 3 个（1 2 3）：\n");
    int v;
    for (int i = 0; i < 3; i++) { dequeue(&Q, &v); printf("    出队 %d\n", v); }
    qshow("出队后", &Q);

    printf("\n  ⭐ 现在队列里只有 2 个元素（4 5），\n");
    printf("     但 data[0] data[1] data[2] 三个位置**空着用不了**。\n");
    printf("     rear 已经等于 MAXSIZE，再入队就报「满」：\n");
    enqueue(&Q, 6);

    printf("\n  ⚠️ 这就是【假溢出】：真的有空间，但下标走不回去了。\n");
    printf("     明明只存了 2 个，容量 5，却不能再入队。\n");
    printf("     📌 这个现象是软考选择题的经典考点。\n");

    /* ---------- ② 循环队列 ---------- */
    printf("\n=== ② 循环队列：用取模让下标绕回来 ===\n");
    CircQueue C;
    cqinit(&C);

    printf("  入队 1 2 3 4（MAXSIZE=5，最多存 4 个）：\n");
    for (int i = 1; i <= 4; i++) {
        cqenqueue(&C, i);
        cqshow("入队后", &C);
    }

    printf("\n  第 5 个会失败（少用一个单元）：\n");
    cqenqueue(&C, 5);

    printf("\n  出队 2 个：\n");
    for (int i = 0; i < 2; i++) {
        cqdequeue(&C, &v);
        printf("    出队 %d → ", v);
        cqshow("", &C);
    }

    printf("\n  再入队 5 6 —— 注意 rear 怎么绕回 0：\n");
    for (int i = 5; i <= 6; i++) {
        cqenqueue(&C, i);
        cqshow("入队后", &C);
    }

    printf("\n  ⭐ 关键看 rear 的变化：4 → 0（绕回来了）\n");
    printf("     这就是取模的作用：(4+1) %% 5 = 0\n");
    printf("     前面的空位重新被利用了 —— 假溢出被解决。\n");

    /* ---------- ③ 三种判满方案 ---------- */
    printf("\n=== ③ 循环队列判满的三种方案（软考必考）===\n");
    printf("\n  方案一：少用一个存储单元（最常见）\n");
    printf("     判空：front == rear\n");
    printf("     判满：(rear + 1) %% MAXSIZE == front\n");
    printf("     元素个数：(rear - front + MAXSIZE) %% MAXSIZE\n");
    printf("     代价：MAXSIZE 个位置只能用 MAXSIZE-1 个\n");

    printf("\n  方案二：增加一个计数器 size\n");
    printf("     入队 size++，出队 size--\n");
    printf("     判空：size == 0\n");
    printf("     判满：size == MAXSIZE\n");
    printf("     优点：空间全用上；缺点：多维护一个变量\n");

    printf("\n  方案三：增加一个标志 tag\n");
    printf("     入队成功 tag = 1，出队成功 tag = 0\n");
    printf("     判空：front == rear && tag == 0\n");
    printf("     判满：front == rear && tag == 1\n");
    printf("     原理：front==rear 有两种可能（空或满），用 tag 区分\n");

    printf("\n  ⭐ 为什么 front == rear 不能同时用来判空判满？\n");
    printf("     空队列：front == rear（都指向同一个位置）\n");
    printf("     满队列：front == rear（转了一圈又追上）\n");
    printf("     两种情况下标完全一样，所以必须靠「牺牲一个单元」或「加变量」来区分。\n");
    printf("     📌 这是循环队列最核心的一个理解点。\n");

    /* ---------- ④ 元素个数公式 ---------- */
    printf("\n=== ④ 元素个数公式 ===\n");
    printf("  size = (rear - front + MAXSIZE) %% MAXSIZE\n");
    printf("\n  ⭐ 为什么要 + MAXSIZE？\n");
    printf("     因为 rear 可能比 front 小（绕回去了），直接相减是负数。\n");
    printf("     加一个 MAXSIZE 保证非负，再取模就是正确个数。\n");
    printf("\n  验证：当前 front=%d rear=%d\n", C.front, C.rear);
    printf("     (%d - %d + %d) %% %d = %d\n",
           C.rear, C.front, MAXSIZE, MAXSIZE, cqsize(&C));
    printf("     实际元素个数 = %d ✓\n", cqsize(&C));

    /* ---------- ⑤ 复杂度 ---------- */
    printf("\n=== ⑤ 队列的复杂度 ===\n");
    printf("  %-16s %-10s %s\n", "操作", "复杂度", "原因");
    printf("  --------------------------------------------------\n");
    printf("  %-16s %-10s %s\n", "入队 enqueue", "O(1)", "只改 rear");
    printf("  %-16s %-10s %s\n", "出队 dequeue", "O(1)", "只改 front");
    printf("  %-16s %-10s %s\n", "取队头", "O(1)", "直接读 data[front]");
    printf("  %-16s %-10s %s\n", "判空/判满", "O(1)", "看 front/rear");
    printf("\n  ⭐ 和栈一样，全部 O(1)。区别只在「从哪进、从哪出」。\n");
    printf("     栈：同一端进出（LIFO）\n");
    printf("     队列：一端进另一端出（FIFO）\n");

    return 0;
}
