/* 181_stack_array.c —— 顺序栈：只能在栈顶操作
 *
 * 栈是**受限的线性表**：只允许在一端（栈顶）插入和删除。
 * 特性：后进先出 LIFO（Last In First Out）。
 *
 * 三个核心操作：
 *   push  入栈：--top 位置放新元素
 *   pop   出栈：取 top 位置的值，top 下移
 *   top   取栈顶：只看不删
 *
 * 判空判满是软考重点：
 *   判空：top == -1
 *   判满：top == MAXSIZE - 1
 */

#include <stdio.h>

#define MAXSIZE 8

/* ---------- 顺序栈结构 ---------- */
typedef struct {
    int data[MAXSIZE];
    int top;                /* 栈顶下标，空栈时是 -1 */
} SqStack;

/* 初始化：top = -1 表示空栈 */
void initStack(SqStack *S)
{
    S->top = -1;
}

int isEmpty(const SqStack *S) { return S->top == -1; }
int isFull(const SqStack *S)  { return S->top == MAXSIZE - 1; }
int sizeOf(const SqStack *S)  { return S->top + 1; }     /* 元素个数 = top+1 */

/* 入栈 */
int push(SqStack *S, int v)
{
    if (isFull(S)) {
        printf("  入栈失败：栈满（top=%d）\n", S->top);
        return 0;
    }
    S->top++;                   /* ① top 先上移 */
    S->data[S->top] = v;        /* ② 再放元素 */
    return 1;
}

/* 出栈：用 out 带回值 */
int pop(SqStack *S, int *out)
{
    if (isEmpty(S)) {
        printf("  出栈失败：栈空（top=%d）\n", S->top);
        return 0;
    }
    if (out != NULL) *out = S->data[S->top];
    S->top--;                   /* 取完再下移 */
    return 1;
}

/* 取栈顶：不删除 */
int top(const SqStack *S, int *out)
{
    if (isEmpty(S)) return 0;
    *out = S->data[S->top];
    return 1;
}

/* 从栈底到栈顶打印 */
void show(const char *label, const SqStack *S)
{
    printf("  %-10s 栈底[", label);
    for (int i = 0; i <= S->top; i++) {
        printf("%d", S->data[i]);
        if (i != S->top) printf(" ");
    }
    printf("]栈顶   top=%d  size=%d\n", S->top, sizeOf(S));
}

int main(void)
{
    SqStack S;
    initStack(&S);

    /* ---------- ① 入栈 ---------- */
    printf("=== ① 依次入栈 10 20 30 ===\n");
    show("初始", &S);
    for (int v = 10; v <= 30; v += 10) {
        push(&S, v);
        show("入栈后", &S);
    }

    printf("\n  ⭐ 注意 top 的变化：-1 → 0 → 1 → 2\n");
    printf("     元素个数 = top + 1 = 3\n");

    /* ---------- ② 取栈顶（不删） ---------- */
    printf("\n=== ② 取栈顶 ===\n");
    int v;
    if (top(&S, &v)) printf("  栈顶是 %d，取完后栈不变\n", v);
    show("栈", &S);

    /* ---------- ③ 出栈 ---------- */
    printf("\n=== ③ 依次出栈 ===\n");
    while (!isEmpty(&S)) {      /* 先判空再弹，避免多余的失败提示 */
        pop(&S, &v);
        printf("  弹出 %d → ", v);
        show("剩余", &S);
    }

    printf("\n  ⭐ 入栈顺序 10 20 30，出栈顺序 30 20 10 —— 后进先出。\n");

    /* ---------- ④ 栈空时出栈 ---------- */
    printf("\n=== ④ 边界：栈空时出栈 ===\n");
    pop(&S, &v);                /* 应该失败但程序不崩 */

    /* ---------- ⑤ 栈满时入栈 ---------- */
    printf("\n=== ⑤ 边界：栈满时入栈 ===\n");
    for (int i = 1; i <= MAXSIZE; i++) push(&S, i);
    show("栈满", &S);
    push(&S, 99);               /* 第 9 个，应失败 */

    printf("\n  ⭐ 判满条件是 top == MAXSIZE - 1，不是 top == MAXSIZE。\n");
    printf("     因为下标从 0 开始，8 个元素的下标是 0..7。\n");
    printf("     写成 top == MAXSIZE 就已经越界了。\n");

    /* ---------- ⑥ 共享栈：两个栈共用一个数组 ---------- */
    printf("\n=== ⑥ 共享栈：两个栈从两端往中间长 ===\n");

    typedef struct {
        int data[MAXSIZE];
        int top1;               /* 栈 1 的栈顶，从左往右长 */
        int top2;               /* 栈 2 的栈顶，从右往左长 */
    } SharedStack;

    SharedStack SS;
    SS.top1 = -1;               /* 栈 1 空 */
    SS.top2 = MAXSIZE;          /* 栈 2 空（注意是 MAXSIZE 不是 MAXSIZE-1） */
    for (int i = 0; i < MAXSIZE; i++) SS.data[i] = 0;   /* 清零便于观察 */

    printf("  初始：top1=%d, top2=%d\n", SS.top1, SS.top2);

    /* 交替入栈，看两个 top 怎么靠拢 */
    SS.data[++SS.top1] = 1;     /* 栈 1 入栈 */
    SS.data[--SS.top2] = 100;   /* 栈 2 入栈 */
    SS.data[++SS.top1] = 2;
    SS.data[--SS.top2] = 200;
    SS.data[++SS.top1] = 3;
    SS.data[--SS.top2] = 300;

    printf("  入栈 3 个后：top1=%d, top2=%d\n", SS.top1, SS.top2);
    printf("  数组内容：");
    for (int i = 0; i < MAXSIZE; i++) printf("%d ", SS.data[i]);
    printf("\n");
    printf("  栈1（左→右）：");
    for (int i = 0; i <= SS.top1; i++) printf("%d ", SS.data[i]);
    printf("\n  栈2（右→左）：");
    for (int i = MAXSIZE - 1; i >= SS.top2; i--) printf("%d ", SS.data[i]);
    printf("\n");

    printf("\n  ⭐ 共享栈的判满条件：top1 + 1 == top2\n");
    printf("     现在 top1+1 = %d，top2 = %d，%s\n",
           SS.top1 + 1, SS.top2,
           (SS.top1 + 1 == SS.top2) ? "满了" : "还没满");

    printf("\n  📌 共享栈的意义：两个栈此消彼长，只有当总和超过 MAXSIZE 时才满，\n");
    printf("     比两个独立栈各分一半空间更省。这是软考常考的结构。\n");

    /* ---------- ⑦ 复杂度 ---------- */
    printf("\n=== ⑦ 顺序栈的复杂度 ===\n");
    printf("  %-14s %-10s %s\n", "操作", "复杂度", "原因");
    printf("  ------------------------------------------\n");
    printf("  %-14s %-10s %s\n", "入栈 push", "O(1)", "只改 top 和一个位置");
    printf("  %-14s %-10s %s\n", "出栈 pop", "O(1)", "只改 top");
    printf("  %-14s %-10s %s\n", "取栈顶 top", "O(1)", "直接读 data[top]");
    printf("  %-14s %-10s %s\n", "判空/判满", "O(1)", "看 top 的值");
    printf("\n  ⭐ 全部 O(1) —— 这是栈最漂亮的地方。\n");
    printf("     对比顺序表：插入删除要挪元素 O(n)，而栈只在栈顶动，不用挪。\n");

    return 0;
}
