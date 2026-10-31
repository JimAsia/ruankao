/* ex184_circular_queue.c —— 循环队列的完整实现
 *
 * 要求：用「少用一个存储单元」的方案实现循环队列
 *   1. cqInit(Q)       front = rear = 0
 *   2. cqEmpty(Q)      front == rear
 *   3. cqFull(Q)       (rear + 1) % MAXSIZE == front
 *   4. cqSize(Q)       (rear - front + MAXSIZE) % MAXSIZE
 *   5. cqEnqueue(Q,v)  入队
 *   6. cqDequeue(Q,&v) 出队
 *
 * MAXSIZE = 5，所以最多存 4 个元素。
 *
 * 测试序列（重点看 rear 绕回 0）：
 *   入队 1 2 3 4  → 满，第 5 个失败
 *   出队 2 个     → front 前移
 *   入队 5 6      → rear 从 4 绕回 0、1
 *   输出每一步的 front / rear / size
 *
 * 提示：
 *   入队：data[rear] = v;  rear = (rear + 1) % MAXSIZE;
 *   出队：v = data[front]; front = (front + 1) % MAXSIZE;
 *   ⚠️ 取模不能漏，否则又回到假溢出
 */

#include <stdio.h>

#define MAXSIZE 5

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} CircQueue;

/* TODO 1：初始化 */
void cqInit(CircQueue *Q)
{
    (void)Q;
}

/* TODO 2：判空 */
int cqEmpty(const CircQueue *Q)
{
    (void)Q;
    return 1;
}

/* TODO 3：判满 */
int cqFull(const CircQueue *Q)
{
    (void)Q;
    return 0;
}

/* TODO 4：元素个数 */
int cqSize(const CircQueue *Q)
{
    (void)Q;
    return 0;
}

/* TODO 5：入队 */
int cqEnqueue(CircQueue *Q, int v)
{
    (void)Q; (void)v;
    return 0;
}

/* TODO 6：出队 */
int cqDequeue(CircQueue *Q, int *out)
{
    (void)Q; (void)out;
    return 0;
}

/* 辅助：打印队列（已给出，注意要按 size 循环读，不能直接 for i=front..rear） */
void cqShow(const char *label, const CircQueue *Q)
{
    printf("  %-10s front=%d rear=%d size=%d [", label,
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
    /* TODO 7：按测试序列跑一遍 */

    return 0;
}
