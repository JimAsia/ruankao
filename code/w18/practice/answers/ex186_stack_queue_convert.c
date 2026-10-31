/* ex186_stack_queue_convert.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 32

/* ==================== 用两个栈实现队列 ==================== */
typedef struct {
    int inData[MAXSIZE];
    int inTop;
    int outData[MAXSIZE];
    int outTop;
} QueueByStack;

static void qbsInit(QueueByStack *Q)
{
    Q->inTop = -1;
    Q->outTop = -1;
}

void qbsPush(QueueByStack *Q, int v)
{
    if (Q->inTop >= MAXSIZE - 1) { printf("  队列满\n"); return; }
    Q->inData[++Q->inTop] = v;          /* 入队只进 inStack */
}

/* outStack 空了才倒，倒一次管很久 */
static void qbsTransfer(QueueByStack *Q)
{
    if (Q->outTop != -1) return;        /* 还有货，不用倒 */
    while (Q->inTop >= 0) {
        Q->outData[++Q->outTop] = Q->inData[Q->inTop--];
    }
}

int qbsPop(QueueByStack *Q, int *out)
{
    qbsTransfer(Q);
    if (Q->outTop < 0) return 0;
    *out = Q->outData[Q->outTop--];
    return 1;
}

/* ==================== 用两个队列实现栈 ==================== */
typedef struct {
    int data[MAXSIZE];
    int front, rear;
} SimpleQueue;

static void sqInit(SimpleQueue *Q) { Q->front = Q->rear = 0; }
static int  sqEmpty(const SimpleQueue *Q) { return Q->front == Q->rear; }
static void sqPush(SimpleQueue *Q, int v) { Q->data[Q->rear++] = v; }
static int  sqPop(SimpleQueue *Q, int *out)
{
    if (sqEmpty(Q)) return 0;
    *out = Q->data[Q->front++];
    return 1;
}

typedef struct {
    SimpleQueue q1, q2;
} StackByQueue;

void sbqInit(StackByQueue *S)
{
    sqInit(&S->q1);
    sqInit(&S->q2);
}

void sbqPush(StackByQueue *S, int v)
{
    sqPush(&S->q1, v);                  /* 入栈总进 q1 */
}

int sbqPop(StackByQueue *S, int *out)
{
    if (sqEmpty(&S->q1)) return 0;

    int v;
    while (S->q1.rear - S->q1.front > 1) {   /* 留下最后一个 */
        sqPop(&S->q1, &v);
        sqPush(&S->q2, v);
    }
    sqPop(&S->q1, out);                      /* 最后那个就是栈顶 */

    /* 把 q2 搬回 q1，保证下次入栈还是进 q1 */
    while (!sqEmpty(&S->q2)) {
        sqPop(&S->q2, &v);
        sqPush(&S->q1, v);
    }
    return 1;
}

int main(void)
{
    /* ---------- 两个栈实现队列 ---------- */
    printf("=== ① 两个栈实现队列（FIFO）===\n");
    QueueByStack Q;
    qbsInit(&Q);

    printf("  入队 1 2 3：\n");
    for (int v = 1; v <= 3; v++) {
        qbsPush(&Q, v);
        printf("    入队 %d  → inStack 栈顶=%d，outStack 栈顶=%d\n",
               v, Q.inTop >= 0 ? Q.inData[Q.inTop] : -1,
               Q.outTop >= 0 ? Q.outData[Q.outTop] : -1);
    }

    printf("\n  出队三个：\n");
    int v;
    for (int i = 0; i < 3; i++) {
        if (qbsPop(&Q, &v)) printf("    出队 %d\n", v);
    }
    printf("  出队顺序 1 2 3 —— 先进先出 ✓\n");

    printf("\n  ⭐ 为什么对：\n");
    printf("     inStack 里压入 1 2 3（栈顶 3），倒进 outStack 后栈顶变 1，\n");
    printf("     再依次弹出就是 1 2 3 —— 倒了两次，负负得正。\n");

    /* 混合操作，验证仍正确 */
    printf("\n  混合操作：入队 4 5，出队一个，入队 6，再全出队：\n");
    qbsPush(&Q, 4);
    qbsPush(&Q, 5);
    qbsPop(&Q, &v); printf("    出队 %d\n", v);
    qbsPush(&Q, 6);
    while (qbsPop(&Q, &v)) printf("    出队 %d\n", v);
    printf("  顺序 4 5 6 ✓（混着来也不会乱，因为 transfer 只在 outStack 空时做）\n");

    /* ---------- 两个队列实现栈 ---------- */
    printf("\n=== ② 两个队列实现栈（LIFO）===\n");
    StackByQueue S;
    sbqInit(&S);

    printf("  入栈 1 2 3：\n");
    for (int x = 1; x <= 3; x++) {
        sbqPush(&S, x);
        printf("    入栈 %d\n", x);
    }

    printf("\n  出栈三个：\n");
    for (int i = 0; i < 3; i++) {
        if (sbqPop(&S, &v)) printf("    出栈 %d\n", v);
    }
    printf("  出栈顺序 3 2 1 —— 后进先出 ✓\n");

    printf("\n=== ③ 复杂度对比（重要）===\n");
    printf("  %-28s %-16s %s\n", "实现", "时间复杂度", "说明");
    printf("  --------------------------------------------------------------------\n");
    printf("  %-28s %-16s %s\n", "两个栈 → 队列：入队", "O(1)", "只压 inStack");
    printf("  %-28s %-16s %s\n", "两个栈 → 队列：出队", "均摊 O(1)", "每个元素最多倒一次");
    printf("  %-28s %-16s %s\n", "两个队列 → 栈：入栈", "O(1)", "只进 q1");
    printf("  %-28s %-16s %s\n", "两个队列 → 栈：出栈", "O(n)", "每次都要搬 n-1 个");

    printf("\n  ⭐ 为什么栈能均摊 O(1) 模拟队列，反过来不行？\n");
    printf("     栈→队列：倒一次之后，outStack 能连续出队很多次，成本被摊掉了。\n");
    printf("     队列→栈：每次出栈都必须把 n-1 个搬走，每次都 O(n)，摊不掉。\n");
    printf("     📌 本质原因：栈只有一端能用，队列两端都能用，\n");
    printf("        信息量大的（队列）能模拟信息量小的（栈）才高效。\n");

    return 0;
}
