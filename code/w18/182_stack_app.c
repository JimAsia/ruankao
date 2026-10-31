/* 182_stack_app.c —— 栈的三个经典应用（软考必考）
 *
 * ① 括号匹配：左括号入栈，右括号出栈配对
 * ② 进制转换：除基取余，余数入栈，最后倒序弹出
 * ③ 后缀表达式求值：遇到数字入栈，遇到运算符弹出两个算完再入栈
 *
 * 三个都用同一个栈，只是「什么时候入、什么时候出」不同。
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 64

/* ---------- 通用字符栈 ---------- */
typedef struct {
    char data[MAXSIZE];
    int  top;
} CharStack;

static void cinit(CharStack *S) { S->top = -1; }
static int  cempty(const CharStack *S) { return S->top == -1; }
static int  cfull(const CharStack *S) { return S->top == MAXSIZE - 1; }

static int cpush(CharStack *S, char v)
{
    if (cfull(S)) return 0;
    S->data[++S->top] = v;
    return 1;
}

static int cpop(CharStack *S, char *out)
{
    if (cempty(S)) return 0;
    *out = S->data[S->top--];
    return 1;
}

/* ==================== ① 括号匹配 ==================== */
/* 支持三种括号：() [] {}。返回 1 匹配，0 不匹配，原因写入 reason */
int bracketMatch(const char *s, char *reason)
{
    CharStack S;
    cinit(&S);

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            cpush(&S, c);                       /* 左括号入栈 */
        } else if (c == ')' || c == ']' || c == '}') {
            char left;
            if (!cpop(&S, &left)) {
                sprintf(reason, "第 %d 个字符 '%c' 多余（栈已空）", i + 1, c);
                return 0;                       /* 右括号多了 */
            }
            /* 检查配对 */
            int ok = (left == '(' && c == ')') ||
                     (left == '[' && c == ']') ||
                     (left == '{' && c == '}');
            if (!ok) {
                sprintf(reason, "第 %d 个字符 '%c' 与栈顶 '%c' 不配对",
                        i + 1, c, left);
                return 0;
            }
        }
        /* 其他字符（字母、数字、运算符）直接忽略 */
    }

    if (!cempty(&S)) {
        sprintf(reason, "扫描完还有 %d 个左括号没闭合", S.top + 1);
        return 0;                               /* 左括号多了 */
    }
    reason[0] = '\0';
    return 1;
}

/* ==================== ② 进制转换 ==================== */
/* 十进制 n 转 base 进制（2 ≤ base ≤ 16），结果写入 out */
void convertBase(int n, int base, char *out)
{
    const char digits[] = "0123456789ABCDEF";
    CharStack S;
    cinit(&S);

    if (n == 0) { strcpy(out, "0"); return; }

    int neg = 0;
    if (n < 0) { neg = 1; n = -n; }

    /* 除基取余，余数依次入栈 */
    while (n > 0) {
        cpush(&S, digits[n % base]);
        n /= base;
    }

    /* 弹出就是倒序 —— 这正是栈的用处 */
    int k = 0;
    if (neg) out[k++] = '-';
    char c;
    while (cpop(&S, &c)) out[k++] = c;
    out[k] = '\0';
}

/* ==================== ③ 后缀表达式求值 ==================== */
/* 只支持个位数字和 + - * /，用空格分隔 */
int evalPostfix(const char *expr, int *ok)
{
    CharStack S;
    cinit(&S);
    *ok = 1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == ' ') continue;

        if (isdigit((unsigned char)c)) {
            cpush(&S, (char)(c - '0'));         /* 数字入栈（这里只用 0-9 和 结果） */
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            char b, a;
            if (!cpop(&S, &b) || !cpop(&S, &a)) {
                printf("    运算符 '%c' 缺操作数\n", c);
                *ok = 0;
                return 0;
            }
            int r = 0;
            switch (c) {
                case '+': r = a + b;  break;
                case '-': r = a - b;  break;    /* ⚠️ 是 a-b，不是 b-a */
                case '*': r = a * b;  break;
                case '/':
                    if (b == 0) { printf("    除数为 0\n"); *ok = 0; return 0; }
                    r = a / b;                     /* ⚠️ 是 a/b，不是 b/a */
                    break;
            }
            cpush(&S, (char)r);                 /* 结果再入栈 */
        } else {
            printf("    非法字符 '%c'\n", c);
            *ok = 0;
            return 0;
        }
    }

    char r;
    if (!cpop(&S, &r)) { *ok = 0; return 0; }
    if (!cempty(&S)) { printf("    栈里还有多余操作数\n"); *ok = 0; return 0; }
    return r;
}

int main(void)
{
    /* ---------- ① 括号匹配 ---------- */
    printf("=== ① 括号匹配 ===\n");
    const char *tests[] = {
        "{[()()]}",
        "(a+b)*[c-d]",
        "{[(])}",
        "((()))",
        "(()",
        "())",
        "no brackets here"
    };
    for (int i = 0; i < 7; i++) {
        char reason[128];
        int ok = bracketMatch(tests[i], reason);
        printf("  %-22s → %s\n", tests[i], ok ? "匹配 ✓" : "不匹配 ✗");
        if (!ok) printf("  %-22s   %s\n", "", reason);
    }

    printf("\n  ⭐ 三种不匹配的情况：\n");
    printf("     1. 右括号多余 → 出栈时栈已空\n");
    printf("     2. 左右类型不配对 → 栈顶和当前右括号不匹配\n");
    printf("     3. 左括号多余 → 扫描完栈非空\n");

    /* ---------- ② 进制转换 ---------- */
    printf("\n=== ② 进制转换 ===\n");
    char buf[64];
    int nums[] = {10, 255, 100, 0, 12345};
    int bases[] = {2, 8, 16};

    for (int i = 0; i < 5; i++) {
        printf("  %-6d → ", nums[i]);
        for (int j = 0; j < 3; j++) {
            convertBase(nums[i], bases[j], buf);
            printf("%d进制 %-16s ", bases[j], buf);
        }
        printf("\n");
    }

    printf("\n  ⭐ 为什么用栈？\n");
    printf("     除基取余得到的余数是【从低位到高位】的，\n");
    printf("     而输出要【从高位到低位】，正好倒过来 —— 栈就是干这个的。\n");
    printf("     10 → 2 进制：余数 0,1,0,1，倒过来是 1010\n");

    /* ---------- ③ 后缀表达式求值 ---------- */
    printf("\n=== ③ 后缀表达式求值 ===\n");
    const char *exprs[] = {
        "3 4 +",            /* 7 */
        "5 1 2 + 4 * + 3 -",/* 14  ← 软考经典题 */
        "2 3 *",            /* 6 */
        "8 2 /",            /* 4 */
        "1 2 + 3 *",        /* 9 */
        "6 2 - 3 +"         /* 7 */
    };
    for (int i = 0; i < 6; i++) {
        int ok = 1;
        int r = evalPostfix(exprs[i], &ok);
        printf("  %-22s = %s%d\n", exprs[i], ok ? "" : "（出错）", ok ? r : 0);
    }

    printf("\n  ⭐ 后缀表达式求值三步：\n");
    printf("     1. 遇到数字 → 入栈\n");
    printf("     2. 遇到运算符 → 弹出两个（先弹的是右操作数！），算完再入栈\n");
    printf("     3. 扫完栈里只剩一个数，就是结果\n");
    printf("\n  ⚠️ 顺序陷阱：先弹出的是【右】操作数，后弹出的是【左】操作数。\n");
    printf("     减法除法写反了结果就错（3 4 - 是 3-4=-1，不是 1）。\n");

    /* ---------- ④ 栈与递归的关系 ---------- */
    printf("\n=== ④ 栈和递归是同一件事 ===\n");
    printf("  递归函数调用时，系统用一个「函数调用栈」保存：\n");
    printf("    返回地址、参数、局部变量\n");
    printf("  每次递归就是入栈，每次返回就是出栈。\n");
    printf("  ⭐ 所以「递归深度过大导致栈溢出」，说的就是这个栈。\n");
    printf("     任何递归都能用「显式栈 + 循环」改写（S1-W8 讲过）。\n");

    return 0;
}
