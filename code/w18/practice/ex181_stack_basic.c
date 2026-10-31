/* ex181_stack_basic.c —— 顺序栈的完整实现
 *
 * 要求：实现顺序栈的六个基本操作
 *   1. initStack(S)   初始化，top = -1
 *   2. isEmpty(S)     判空
 *   3. isFull(S)      判满
 *   4. push(S, v)     入栈，成功返回 1
 *   5. pop(S, &out)   出栈，用 out 带回值
 *   6. getTop(S, &out) 取栈顶，不删除
 *
 * 测试序列：
 *   依次入栈 1 2 3 → 输出栈内容，top 应为 2
 *   取栈顶 → 3，栈不变
 *   依次出栈 → 3 2 1
 *   空栈出栈 → 失败但不崩
 *   入栈到满（MAXSIZE 次）→ 第 MAXSIZE+1 次失败
 *
 * 提示：
 *   判空：top == -1
 *   判满：top == MAXSIZE - 1      ← 不是 MAXSIZE
 *   入栈：先 ++top 再赋值
 *   出栈：先取值再 --top
 */

#include <stdio.h>

#define MAXSIZE 5

typedef struct {
    int data[MAXSIZE];
    int top;
} SqStack;

/* TODO 1：初始化 */
void initStack(SqStack *S)
{
    (void)S;
}

/* TODO 2：判空 */
int isEmpty(const SqStack *S)
{
    (void)S;
    return 1;
}

/* TODO 3：判满 */
int isFull(const SqStack *S)
{
    (void)S;
    return 0;
}

/* TODO 4：入栈 */
int push(SqStack *S, int v)
{
    (void)S; (void)v;
    return 0;
}

/* TODO 5：出栈 */
int pop(SqStack *S, int *out)
{
    (void)S; (void)out;
    return 0;
}

/* TODO 6：取栈顶 */
int getTop(const SqStack *S, int *out)
{
    (void)S; (void)out;
    return 0;
}

/* 辅助：打印栈（已给出） */
void show(const char *label, const SqStack *S)
{
    printf("  %-12s 栈底[", label);
    for (int i = 0; i <= S->top; i++) {
        printf("%d", S->data[i]);
        if (i != S->top) printf(" ");
    }
    printf("]栈顶   top=%d\n", S->top);
}

int main(void)
{
    SqStack S;
    /* TODO 7：初始化后按测试序列跑一遍 */

    return 0;
}
