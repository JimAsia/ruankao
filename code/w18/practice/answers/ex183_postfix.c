/* ex183_postfix.c —— 参考答案 */

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

/* ---------- 整数栈（求值用）---------- */
typedef struct {
    int data[MAXSIZE];
    int top;
} IntStack;

static void iinit(IntStack *S) { S->top = -1; }
static int  iempty(const IntStack *S) { return S->top == -1; }
static void ipush(IntStack *S, int v) { S->data[++S->top] = v; }
static int  ipop(IntStack *S, int *out)
{
    if (iempty(S)) return 0;
    *out = S->data[S->top--];
    return 1;
}

/* ---------- ① 后缀表达式求值 ---------- */
int evalPostfix(const char *expr, int *ok)
{
    IntStack S;
    iinit(&S);
    *ok = 1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == ' ') continue;

        if (isdigit((unsigned char)c)) {
            ipush(&S, c - '0');                 /* 数字入栈 */
        } else if (strchr("+-*/", c) != NULL) {
            int b, a;
            if (!ipop(&S, &b) || !ipop(&S, &a)) {
                printf("    运算符 '%c' 缺操作数\n", c);
                *ok = 0; return 0;
            }
            /* ⚠️ 先弹出的是右操作数 b，后弹出的是左操作数 a */
            switch (c) {
                case '+': ipush(&S, a + b); break;
                case '-': ipush(&S, a - b); break;
                case '*': ipush(&S, a * b); break;
                case '/':
                    if (b == 0) { printf("    除数为 0\n"); *ok = 0; return 0; }
                    ipush(&S, a / b);
                    break;
            }
        } else {
            printf("    非法字符 '%c'\n", c);
            *ok = 0; return 0;
        }
    }

    int r;
    if (!ipop(&S, &r)) { *ok = 0; return 0; }
    if (!iempty(&S)) {
        printf("    栈里还有多余操作数\n");
        *ok = 0; return 0;
    }
    return r;
}

/* ---------- ② 运算符优先级 ---------- */
static int prec(char op)
{
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

/* ---------- ③ 中缀转后缀 ---------- */
void infixToPostfix(const char *infix, char *postfix)
{
    CharStack S;
    cinit(&S);
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == ' ') continue;

        if (isdigit((unsigned char)c)) {
            postfix[k++] = c;                   /* 数字直接输出 */
            postfix[k++] = ' ';
        } else if (c == '(') {
            cpush(&S, c);                       /* 左括号入栈 */
        } else if (c == ')') {
            char t;
            while (cpop(&S, &t) && t != '(') {  /* 弹到左括号为止 */
                postfix[k++] = t;
                postfix[k++] = ' ';
            }
            /* 左括号本身不输出 */
        } else if (strchr("+-*/", c) != NULL) {
            /* 弹出所有优先级 >= 自己的运算符 */
            while (!cempty(&S) && ctop(&S) != '(' &&
                   prec(ctop(&S)) >= prec(c)) {
                char t;
                cpop(&S, &t);
                postfix[k++] = t;
                postfix[k++] = ' ';
            }
            cpush(&S, c);                       /* 自己入栈 */
        }
    }

    /* 扫完，把栈里剩下的全部弹出 */
    char t;
    while (cpop(&S, &t)) {
        if (t != '(') {
            postfix[k++] = t;
            postfix[k++] = ' ';
        }
    }

    if (k > 0) k--;                             /* 去掉末尾空格 */
    postfix[k] = '\0';
}

int main(void)
{
    /* ---------- 后缀求值 ---------- */
    printf("=== ① 后缀表达式求值 ===\n");
    const char *exprs[] = {
        "3 4 +",
        "5 1 2 + 4 * + 3 -",        /* 软考经典题 */
        "2 3 *",
        "8 2 /",
        "1 2 + 3 *",
        "6 2 - 3 +",
        "3 4 -"                     /* 负数：3-4 = -1 */
    };
    for (int i = 0; i < 7; i++) {
        int ok = 1;
        int r = evalPostfix(exprs[i], &ok);
        printf("  %-22s = %d\n", exprs[i], ok ? r : 0);
    }

    printf("\n=== ② 中缀转后缀 ===\n");
    const char *infixs[] = {
        "1+2*3",
        "(1+2)*3",
        "1+2+3",
        "2*(3+4)-5",
        "((1+2)*(3+4))"
    };
    char post[MAXSIZE];
    for (int i = 0; i < 5; i++) {
        infixToPostfix(infixs[i], post);
        printf("  %-16s → %s\n", infixs[i], post);
    }

    printf("\n=== ③ 串起来：中缀 → 后缀 → 求值 ===\n");
    for (int i = 0; i < 5; i++) {
        infixToPostfix(infixs[i], post);
        int ok = 1;
        int r = evalPostfix(post, &ok);
        printf("  %-16s → %-18s → %d\n", infixs[i], post, ok ? r : 0);
    }
    printf("\n  ⭐ 验证 2*(3+4)-5 = 14-5 = 9 ✓\n");

    printf("\n=== 转换规则（背这张表）===\n");
    printf("  %-14s %s\n", "遇到", "动作");
    printf("  ----------------------------------------------\n");
    printf("  %-14s %s\n", "数字", "直接输出");
    printf("  %-14s %s\n", "'('", "入栈");
    printf("  %-14s %s\n", "')'", "弹栈并输出，直到弹出 '('（它不输出）");
    printf("  %-14s %s\n", "运算符", "弹出所有【优先级 >= 自己】的并输出，然后自己入栈");
    printf("  %-14s %s\n", "扫描结束", "把栈里剩下的全部弹出输出");

    printf("\n=== 为什么「>=」而不是「>」 ===\n");
    printf("  ≥ 保证「左结合」：1+2+3 → 1 2 + 3 +\n");
    printf("  如果写 >，同优先级不弹出，1+2+3 会变成 1 2 3 + +\n");
    printf("  ⭐ 减法和除法必须左结合，所以必须用 >=。\n");

    printf("\n=== 局限 ===\n");
    printf("  本实现只支持【个位数字】。要支持多位数，\n");
    printf("  需要把连续数字拼成一个数再入栈/输出。\n");
    printf("  软考题目通常给个位数，或直接给好后缀式让你求值。\n");

    return 0;
}
