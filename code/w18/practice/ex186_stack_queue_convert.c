/* ex186_stack_queue_convert.c —— 栈与队列的相互实现（面试高频）
 *
 * 要求：
 *   1. 用【两个栈】实现一个队列：
 *        inStack 负责入队，outStack 负责出队
 *        出队时如果 outStack 空了，就把 inStack 全部倒过去
 *   2. 用【两个队列】实现一个栈：
 *        入栈进 q1；出栈时把 q1 的前 n-1 个搬到 q2，
 *        剩下那个就是栈顶，弹出后交换 q1、q2
 *
 * 测试：
 *   两个栈实现的队列：入队 1 2 3 → 出队应得 1 2 3（FIFO）
 *   两个队列实现的栈：入栈 1 2 3 → 出栈应得 3 2 1（LIFO）
 *
 * 提示：
 *   两个栈：关键在于「倒一次就反了两次 = 顺序恢复」
 *           1 2 3 压进 inStack（栈顶是 3），倒进 outStack 后栈顶变 1，
 *           依次弹出就是 1 2 3 ✓
 */

#include <stdio.h>
#include <string.h>

#define MAXSIZE 32

/* ==================== 用两个栈实现队列 ==================== */
typedef struct {
    int inData[MAXSIZE];
    int inTop;
    int outData[MAXSIZE];
    int outTop;
} QueueByStack;

/* TODO 1：入队 */
void qbsPush(QueueByStack *Q, int v)
{
    (void)Q; (void)v;
}

/* TODO 2：出队 */
int qbsPop(QueueByStack *Q, int *out)
{
    (void)Q; (void)out;
    return 0;
}

/* ==================== 用两个队列实现栈 ==================== */
/* 这里用最简的数组队列（不用循环，够用就行） */
typedef struct {
    int data[MAXSIZE];
    int front, rear;
} SimpleQueue;

static void sqInit(SimpleQueue *Q) { Q->front = Q->rear = 0; }
static int  sqEmpty(const SimpleQueue *Q) { return Q->front == Q->rear; }
static int  sqSize(const SimpleQueue *Q) { return Q->rear - Q->front; }
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

/* TODO 3：初始化 */
void sbqInit(StackByQueue *S)
{
    (void)S;
}

/* TODO 4：入栈 */
void sbqPush(StackByQueue *S, int v)
{
    (void)S; (void)v;
}

/* TODO 5：出栈 */
int sbqPop(StackByQueue *S, int *out)
{
    (void)S; (void)out;
    return 0;
}

int main(void)
{
    /* TODO 6：测试「两个栈实现队列」 */

    /* TODO 7：测试「两个队列实现栈」 */

    printf("\n=== 复杂度 ===\n");
    printf("  两个栈实现队列：入队 O(1)，出队【均摊】O(1)\n");
    printf("     每个元素最多被倒一次，所以 n 次操作总共 O(n)。\n");
    printf("  两个队列实现栈：入栈 O(1)，出栈 O(n)（要搬 n-1 个）\n");
    printf("\n  ⭐ 结论：栈能高效模拟队列（均摊 O(1)），队列模拟栈要 O(n)。\n");
    printf("     因为队列两端都能操作，栈只有一端，方向受限。\n");

    return 0;
}
