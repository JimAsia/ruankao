/* ex185_queue_app.c —— 队列应用：滑动窗口最大值
 *
 * 问题：给定数组和窗口大小 k，求每个窗口的最大值。
 *   输入：[1 3 -1 -3 5 3 6 7]，k = 3
 *   输出：[3 3 5 5 6 7]
 *
 * 要求：
 *   1. 先用【暴力法】求一遍（每个窗口扫一遍，O(n*k)），作为正确答案参照
 *   2. 再用【单调队列】求一遍（每个元素最多进出队一次，O(n)）
 *   3. 对比两种方法的结果是否一致
 *
 * 单调队列思路：
 *   队列里存【下标】，对应元素从队头到队尾是【递减】的。
 *   处理每个新元素 a[i]：
 *     ① 队尾元素 <= a[i] 的全部出队（它们不可能再成为最大值）
 *     ② a[i] 的下标入队
 *     ③ 如果队头下标已经滑出窗口（< i-k+1），队头出队
 *     ④ 窗口形成后（i >= k-1），队头对应的元素就是当前窗口最大值
 *
 * 提示：
 *   用数组模拟双端队列：int dq[MAXSIZE]; int head = 0, tail = 0;
 *   队尾出队用 tail--，队头出队用 head++
 *
 * 预期输出：
 *   暴力法：3 3 5 5 6 7
 *   单调队列：3 3 5 5 6 7
 *   两者一致 ✓
 */

#include <stdio.h>

#define MAXN 64

/* TODO 1：暴力法 */
void maxSlidingWindowBrute(const int a[], int n, int k, int out[], int *outCnt)
{
    (void)a; (void)n; (void)k; (void)out; (void)outCnt;
}

/* TODO 2：单调队列 */
void maxSlidingWindowDeque(const int a[], int n, int k, int out[], int *outCnt)
{
    (void)a; (void)n; (void)k; (void)out; (void)outCnt;
}

int main(void)
{
    int a[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = 8, k = 3;

    /* TODO 3：两种方法各求一遍，输出结果并比较 */

    printf("\n=== 复杂度对比 ===\n");
    printf("  暴力法  ：O(n*k)，k 大时退化到 O(n^2)\n");
    printf("  单调队列：O(n)，每个元素最多进出队一次\n");
    printf("  ⭐ 单调队列的本质还是队列的「先进先出」，只是加了「维持单调」的规则。\n");

    return 0;
}
