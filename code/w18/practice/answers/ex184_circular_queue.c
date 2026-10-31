/* ex184_circular_queue.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 5

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} CircQueue;

void cqInit(CircQueue *Q)
{
    Q->front = Q->rear = 0;
}

int cqEmpty(const CircQueue *Q)
{
    return Q->front == Q->rear;
}

int cqFull(const CircQueue *Q)
{
    return (Q->rear + 1) % MAXSIZE == Q->front;     /* 牺牲一个单元 */
}

int cqSize(const CircQueue *Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

int cqEnqueue(CircQueue *Q, int v)
{
    if (cqFull(Q)) {
        printf("  入队失败：队列满\n");
        return 0;
    }
    Q->data[Q->rear] = v;
    Q->rear = (Q->rear + 1) % MAXSIZE;              /* ⭐ 取模 */
    return 1;
}

int cqDequeue(CircQueue *Q, int *out)
{
    if (cqEmpty(Q)) {
        printf("  出队失败：队列空\n");
        return 0;
    }
    if (out) *out = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;            /* ⭐ 取模 */
    return 1;
}

void cqShow(const char *label, const CircQueue *Q)
{
    printf("  %-12s front=%d rear=%d size=%d [", label,
           Q->front, Q->rear, cqSize(Q));
    int n = cqSize(Q);
    for (int i = 0; i < n; i++) {
        printf("%d", Q->data[(Q->front + i) % MAXSIZE]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    CircQueue Q;
    cqInit(&Q);

    printf("=== MAXSIZE=%d，最多存 %d 个 ===\n\n", MAXSIZE, MAXSIZE - 1);
    cqShow("初始", &Q);

    printf("\n=== 入队 1 2 3 4 ===\n");
    for (int v = 1; v <= 4; v++) {
        cqEnqueue(&Q, v);
        cqShow("入队后", &Q);
    }

    printf("\n=== 第 5 个失败 ===\n");
    cqEnqueue(&Q, 5);

    printf("\n=== 出队 2 个 ===\n");
    int v;
    for (int i = 0; i < 2; i++) {
        cqDequeue(&Q, &v);
        printf("  出队 %d\n", v);
        cqShow("出队后", &Q);
    }

    printf("\n=== 再入队 5 6 —— 看 rear 绕回 0 ===\n");
    for (int i = 5; i <= 6; i++) {
        cqEnqueue(&Q, i);
        cqShow("入队后", &Q);
    }

    printf("\n  ⭐ 第 4 次入队时 rear 从 4 变成 0：\n");
    printf("     (4 + 1) %% %d = 0，绕回数组开头，前面的空位重新可用。\n", MAXSIZE);
    printf("     这就是循环队列解决假溢出的方式。\n");

    printf("\n=== 关键公式（必须能默写）===\n");
    printf("  判空：front == rear\n");
    printf("  判满：(rear + 1) %% MAXSIZE == front\n");
    printf("  个数：(rear - front + MAXSIZE) %% MAXSIZE\n");

    printf("\n=== 为什么三个公式都要取模 ===\n");
    printf("  rear 和 front 都在 0..MAXSIZE-1 之间循环走，\n");
    printf("  rear+1 可能等于 MAXSIZE，必须 %% 回来变成 0。\n");
    printf("  个数公式里的 +MAXSIZE 是为了处理「rear 比 front 小」的情况，\n");
    printf("  否则 rear-front 是负数，%% 之后还是负数。\n");

    printf("\n=== 验证：此时 front=%d rear=%d ===\n", Q.front, Q.rear);
    printf("  size = (%d - %d + %d) %% %d = %d\n",
           Q.rear, Q.front, MAXSIZE, MAXSIZE, cqSize(&Q));
    printf("  逐个读一遍：[");
    int n = cqSize(&Q);
    for (int i = 0; i < n; i++) {
        printf("%d", Q.data[(Q.front + i) % MAXSIZE]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
    printf("  ⚠️ 遍历时不能写 for (i = front; i < rear; i++)，\n");
    printf("     因为 rear 可能比 front 小（绕过了），这样会一个都读不到。\n");
    printf("     正确写法：for (i = 0; i < size; i++) 读 data[(front+i)%%MAXSIZE]。\n");

    return 0;
}
