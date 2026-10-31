/* ex182_bracket.c —— 括号匹配（扩展版）
 *
 * 要求：
 *   1. bracketMatch(s)：支持 () [] {} 三种括号，返回 1 匹配 / 0 不匹配
 *   2. 用栈实现：左括号入栈，右括号出栈配对
 *   3. 用 reason 字符串带回失败原因
 *
 * 测试数据（必须全部正确）：
 *   "{[()()]}"      → 匹配
 *   "(a+b)*[c-d]"   → 匹配
 *   "((()))"        → 匹配
 *   "{[(])}"        → 不匹配（第 4 个字符 ']' 与栈顶 '(' 不配对）
 *   "(()"           → 不匹配（左括号多余）
 *   "())"           → 不匹配（右括号多余）
 *   ""              → 匹配（空串算匹配）
 *
 * 提示：
 *   三种失败情况分别对应：
 *     1. 出栈时栈已空       → 右括号多了
 *     2. 栈顶和右括号不配对 → 类型错
 *     3. 扫完栈非空         → 左括号多了
 */

#include <stdio.h>
#include <string.h>

#define MAXSIZE 128

typedef struct {
    char data[MAXSIZE];
    int  top;
} CharStack;

/* ===== 栈操作已给出 ===== */
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
/* ===== 栈操作结束 ===== */

/* TODO 1：实现括号匹配 */
int bracketMatch(const char *s, char *reason)
{
    (void)s;
    if (reason) reason[0] = '\0';
    return 0;
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

    /* TODO 2：遍历测试数据，输出匹配结果和失败原因 */

    return 0;
}
