/* ex181_stack_basic.c —— 参考答案 */

#include <stdio.h>

#define MAXSIZE 5

typedef struct {
    int data[MAXSIZE];
    int top;
} SqStack;

void initStack(SqStack *S)
{
    S->top = -1;                    /* -1 表示空栈 */
}

int isEmpty(const SqStack *S)
{
    return S->top == -1;
}

int isFull(const SqStack *S)
{
    return S->top == MAXSIZE - 1;   /* ⚠️ 不是 MAXSIZE */
}

int push(SqStack *S, int v)
{
    if (isFull(S)) {
        printf("  入栈失败：栈满\n");
        return 0;
    }
    S->top++;                       /* ① top 先上移 */
    S->data[S->top] = v;            /* ② 再放元素 */
    return 1;
}

int pop(SqStack *S, int *out)
{
    if (isEmpty(S)) {
        printf("  出栈失败：栈空\n");
        return 0;
    }
    if (out) *out = S->data[S->top];
    S->top--;                       /* 取完再下移 */
    return 1;
}

int getTop(const SqStack *S, int *out)
{
    if (isEmpty(S)) return 0;
    *out = S->data[S->top];
    return 1;
}

void show(const char *label, const SqStack *S)
{
    printf("  %-12s 栈底[", label);
    for (int i = 0; i <= S->top; i++) {
        printf("%d", S->data[i]);
        if (i != S->top) printf(" ");
    }
    printf("]栈顶   top=%d  size=%d\n", S->top, S->top + 1);
}

int main(void)
{
    SqStack S;
    initStack(&S);

    printf("=== 入栈 1 2 3 ===\n");
    show("初始", &S);
    for (int v = 1; v <= 3; v++) {
        push(&S, v);
        show("入栈后", &S);
    }

    printf("\n=== 取栈顶（不删除）===\n");
    int v;
    if (getTop(&S, &v)) printf("  栈顶 = %d\n", v);
    show("栈未变", &S);

    printf("\n=== 依次出栈 ===\n");
    while (!isEmpty(&S)) {
        pop(&S, &v);
        printf("  弹出 %d → ", v);
        show("剩余", &S);
    }

    printf("\n=== 边界测试 ===\n");
    printf("  空栈出栈：");
    pop(&S, &v);

    printf("\n  入栈到满（MAXSIZE=%d）：\n", MAXSIZE);
    for (int i = 1; i <= MAXSIZE; i++) push(&S, i * 10);
    show("栈满", &S);
    printf("  再入栈一个：");
    push(&S, 999);

    printf("\n=== 两个必须记准的数字 ===\n");
    printf("  判空：top == -1\n");
    printf("  判满：top == MAXSIZE - 1 = %d\n", MAXSIZE - 1);
    printf("  元素个数 = top + 1\n");
    printf("\n  ⚠️ 判满写成 top == MAXSIZE 的话，\n");
    printf("     那一刻 top 已经指向数组外面了，data[top] 就是越界写。\n");

    printf("\n=== 入栈出栈的两行代码（背下来）===\n");
    printf("  入栈：S->data[++S->top] = v;     ← 先加后赋值\n");
    printf("  出栈：v = S->data[S->top--];     ← 先取值后减\n");
    printf("  ⭐ ++ 在前还是后，决定了「先动指针还是先动数据」。\n");

    return 0;
}
