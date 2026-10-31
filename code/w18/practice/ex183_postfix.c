/* ex183_postfix.c —— 后缀表达式：求值 + 中缀转后缀
 *
 * 要求：
 *   1. evalPostfix(expr, &ok)：后缀表达式求值（支持 + - * / 和个位数字）
 *   2. infixToPostfix(infix, postfix)：中缀转后缀
 *   3. 两者串起来：中缀 → 后缀 → 求值，验证结果
 *
 * 测试数据：
 *   后缀求值：
 *     "3 4 +"              → 7
 *     "5 1 2 + 4 * + 3 -"  → 14
 *   中缀转后缀：
 *     "1+2*3"              → "1 2 3 * +"
 *     "(1+2)*3"            → "1 2 + 3 *"
 *   完整流程：
 *     "1+2*3"  → 后缀 "1 2 3 * +" → 值 7
 *     "(1+2)*3" → 后缀 "1 2 + 3 *" → 值 9
 *
 * 提示：
 *   后缀求值：数字入栈；运算符弹出两个（先弹的是右操作数！），算完入栈
 *
 *   中缀转后缀（调度场算法的简化版）：
 *     遇到数字   → 直接输出
 *     遇到 '('   → 入栈
 *     遇到 ')'   → 弹栈并输出，直到弹出 '('（'(' 不输出）
 *     遇到运算符 → 弹出所有【优先级 >= 自己】的运算符并输出，然后自己入栈
 *     扫完       → 把栈里剩下的全部弹出输出
 *
 *   优先级：* / 是 2，+ - 是 1
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 128

typedef struct {
    char data[MAXSIZE];
    int  top;
} CharStack;

void cinit(CharStack *S) { S->top = -1; }
int  cempty(const CharStack *S) { return S->top == -1; }
int  cpush(CharStack *S, char v)
{
    if (S->top >= MAXSIZE - 1) return 0;
    S->data[++S->top] = v;
    return 1;
}
int  cpop(CharStack *S, char *out)
{
    if (cempty(S)) return 0;
    *out = S->data[S->top--];
    return 1;
}
char ctop(const CharStack *S) { return cempty(S) ? '\0' : S->data[S->top]; }

/* TODO 1：后缀表达式求值 */
int evalPostfix(const char *expr, int *ok)
{
    (void)expr;
    *ok = 0;
    return 0;
}

/* TODO 2：运算符优先级 */
static int prec(char op)
{
    (void)op;
    return 0;
}

/* TODO 3：中缀转后缀（输出用空格隔开） */
void infixToPostfix(const char *infix, char *postfix)
{
    (void)infix;
    postfix[0] = '\0';
}

int main(void)
{
    /* TODO 4：测试后缀求值 */

    /* TODO 5：测试中缀转后缀 */

    /* TODO 6：串起来（中缀 → 后缀 → 求值） */

    return 0;
}
