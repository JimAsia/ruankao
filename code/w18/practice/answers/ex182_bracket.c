/* ex182_bracket.c —— 参考答案 */

#include <stdio.h>
#include <string.h>

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

int bracketMatch(const char *s, char *reason)
{
    CharStack S;
    cinit(&S);

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            cpush(&S, c);                   /* 左括号入栈 */
        } else if (c == ')' || c == ']' || c == '}') {
            char left;
            if (!cpop(&S, &left)) {
                if (reason) sprintf(reason, "第 %d 个字符 '%c' 多余（栈已空）", i + 1, c);
                return 0;                   /* 情况 1：右括号多了 */
            }
            int ok = (left == '(' && c == ')') ||
                     (left == '[' && c == ']') ||
                     (left == '{' && c == '}');
            if (!ok) {
                if (reason) sprintf(reason, "第 %d 个字符 '%c' 与栈顶 '%c' 不配对",
                                    i + 1, c, left);
                return 0;                   /* 情况 2：类型错 */
            }
        }
    }

    if (!cempty(&S)) {
        if (reason) sprintf(reason, "扫描完还有 %d 个左括号没闭合", S.top + 1);
        return 0;                           /* 情况 3：左括号多了 */
    }

    if (reason) reason[0] = '\0';
    return 1;
}

int main(void)
{
    const char *tests[] = {
        "{[()()]}",
        "(a+b)*[c-d]",
        "((()))",
        "{[(])}",
        "(()",
        "())",
        ""
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));

    printf("=== 括号匹配测试 ===\n");
    for (int i = 0; i < n; i++) {
        char reason[128];
        int ok = bracketMatch(tests[i], reason);
        printf("  %-16s → %s\n", tests[i][0] ? tests[i] : "(空串)",
               ok ? "匹配 ✓" : "不匹配 ✗");
        if (!ok) printf("  %-16s   %s\n", "", reason);
    }

    printf("\n=== 三种失败情况 ===\n");
    printf("  1. 右括号多余：出栈时栈已空\n");
    printf("     例 \"())\" —— 第 3 个 ')' 时栈空\n");
    printf("  2. 类型不配对：栈顶和当前右括号不是一对\n");
    printf("     例 \"{[(])}\" —— ']' 遇到栈顶 '('\n");
    printf("  3. 左括号多余：扫完栈非空\n");
    printf("     例 \"(()\" —— 还剩 1 个没闭合\n");

    printf("\n=== 为什么用栈 ===\n");
    printf("  括号匹配的本质是「最近打开的，最先关闭」—— 这正是后进先出。\n");
    printf("  ⭐ 所以「嵌套结构」都可以用栈检查：\n");
    printf("     HTML 标签配对、函数调用嵌套、JSON 的 {} 配对。\n");

    printf("\n=== 复杂度 ===\n");
    printf("  时间 O(n)：每个字符进出栈各一次\n");
    printf("  空间 O(n)：最坏情况全是左括号，栈深度 n\n");

    return 0;
}
