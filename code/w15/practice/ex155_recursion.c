/* ex155_recursion.c —— 三个递归，判断它们的复杂度
 *
 * 要求：
 *   1. 下面三个递归函数已给出，先自己想复杂度，填进字符串
 *   2. 运行程序，看 n 翻倍时调用次数怎么变，验证你的判断
 *
 * 三个函数：
 *   r1：每次 n/2，只递归一次     → ？
 *   r2：每次 n/2，递归两次，无合并 → ？
 *   r3：每次 n-1，递归一次       → ？
 *
 * 预期：
 *   r1：O(log n)     n=16 时 5 次，n=32 时 6 次
 *   r2：O(n)         n=16 时 31 次，n=32 时 63 次
 *   r3：O(n)         n=16 时 17 次，n=32 时 33 次
 *
 * 思考题：r2 每次分两支，为什么不是 O(2^n) 而是 O(n)？
 *        （提示：分支数多，但每支规模减半，总节点数是 2^log2(n) = n）
 */

#include <stdio.h>

static long long g_calls = 0;

/* r1：规模减半，只走一支 */
static int r1(int n)
{
    g_calls++;
    if (n <= 1) return 0;
    return 1 + r1(n / 2);
}

/* r2：规模减半，走两支 */
static int r2(int n)
{
    g_calls++;
    if (n <= 1) return 0;
    return 1 + r2(n / 2) + r2(n / 2);
}

/* r3：规模减 1，走一支 */
static int r3(int n)
{
    g_calls++;
    if (n <= 0) return 0;
    return 1 + r3(n - 1);
}

int main(void)
{
    /* TODO 1：填写你判断的复杂度 */
    const char *c1 = "O(?)";
    const char *c2 = "O(?)";
    const char *c3 = "O(?)";

    printf("%-6s %-14s %-14s %s\n", "n", "r1 调用次数", "r2 调用次数", "r3 调用次数");
    printf("------------------------------------------------------\n");

    int ns[] = {8, 16, 32, 64};
    for (int k = 0; k < 4; k++) {
        int n = ns[k];

        g_calls = 0; (void)r1(n); long long a = g_calls;
        g_calls = 0; (void)r2(n); long long b = g_calls;
        g_calls = 0; (void)r3(n); long long c = g_calls;

        printf("%-6d %-14lld %-14lld %lld\n", n, a, b, c);
    }

    printf("\n我的判断：\n");
    printf("  r1 = %s\n", c1);
    printf("  r2 = %s\n", c2);
    printf("  r3 = %s\n", c3);

    /* TODO 2：算一下 n 从 16 到 32（翻倍）时，三个函数各涨多少倍，
     *         用这个倍数验证你的判断：
     *         涨 1 倍多（只 +1）→ 对数
     *         涨 2 倍 → 线性
     *         涨 4 倍 → 平方
     */

    return 0;
}
