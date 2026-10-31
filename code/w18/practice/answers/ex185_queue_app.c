/* ex185_queue_app.c —— 参考答案
 *
 * 滑动窗口最大值：暴力法 O(n*k) vs 单调队列 O(n)
 */

#include <stdio.h>
#include <string.h>

#define MAXN 64

/* ---------- ① 暴力法 ---------- */
void maxSlidingWindowBrute(const int a[], int n, int k, int out[], int *outCnt)
{
    int cnt = 0;
    for (int i = 0; i + k - 1 < n; i++) {
        int mx = a[i];
        for (int j = i + 1; j < i + k; j++) {
            if (a[j] > mx) mx = a[j];
        }
        out[cnt++] = mx;
    }
    *outCnt = cnt;
}

/* ---------- ② 单调队列 ---------- */
void maxSlidingWindowDeque(const int a[], int n, int k, int out[], int *outCnt)
{
    int dq[MAXN];               /* 存下标，对应元素从队头到队尾递减 */
    int head = 0, tail = 0;     /* [head, tail) 区间 */
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        /* ① 队尾所有 <= a[i] 的都出队（它们永远不可能成为最大值） */
        while (tail > head && a[dq[tail - 1]] <= a[i]) {
            tail--;
        }
        /* ② 当前下标入队 */
        dq[tail++] = i;

        /* ③ 队头下标滑出窗口就出队 */
        if (dq[head] < i - k + 1) {
            head++;
        }

        /* ④ 窗口形成后，队头就是最大值 */
        if (i >= k - 1) {
            out[cnt++] = a[dq[head]];
        }
    }
    *outCnt = cnt;
}

static void showArr(const char *label, const int a[], int n)
{
    printf("  %-14s [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    int a[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = 8, k = 3;

    printf("=== 输入 ===\n");
    showArr("数组", a, n);
    printf("  %-14s %d\n", "窗口大小 k", k);

    int out1[MAXN], c1 = 0;
    int out2[MAXN], c2 = 0;

    maxSlidingWindowBrute(a, n, k, out1, &c1);
    maxSlidingWindowDeque(a, n, k, out2, &c2);

    printf("\n=== 结果 ===\n");
    showArr("暴力法", out1, c1);
    showArr("单调队列", out2, c2);

    int same = (c1 == c2);
    if (same) {
        for (int i = 0; i < c1; i++) if (out1[i] != out2[i]) { same = 0; break; }
    }
    printf("  %s\n", same ? "两者一致 ✓" : "两者不一致 ✗");

    printf("\n=== 手动验证 ===\n");
    printf("  窗口 [1 3 -1] → 3\n");
    printf("  窗口 [3 -1 -3] → 3\n");
    printf("  窗口 [-1 -3 5] → 5\n");
    printf("  窗口 [-3 5 3] → 5\n");
    printf("  窗口 [5 3 6] → 6\n");
    printf("  窗口 [3 6 7] → 7\n");

    printf("\n=== 单调队列关键步骤 ===\n");
    printf("  处理 a[4]=5 时（此时窗口应是 [-1,-3,5]）：\n");
    printf("    队里原有下标 1(值3)、2(值-1)、3(值-3)\n");
    printf("    值 3 <= 5 → 出队；-1 <= 5 → 出队；-3 <= 5 → 出队\n");
    printf("    5 入队，队头就是 5 ✓\n");
    printf("  ⭐ 被踢掉的元素永远不可能再当最大值，因为它们左边又小又旧。\n");

    printf("\n=== 复杂度对比 ===\n");
    printf("  %-14s %-14s %s\n", "方法", "时间", "说明");
    printf("  ----------------------------------------------------\n");
    printf("  %-14s %-14s %s\n", "暴力法", "O(n*k)", "k 大时退化到 O(n^2)");
    printf("  %-14s %-14s %s\n", "单调队列", "O(n)", "每个元素最多进出各一次");
    printf("\n  ⭐ 单调队列的本质仍是队列（FIFO），只是加了「维持递减」的规则。\n");
    printf("     它的两个操作端：队头出（滑出窗口）、队尾出（被更优的挤掉）。\n");
    printf("     所以严格说它是【双端队列 deque】。\n");

    return 0;
}
