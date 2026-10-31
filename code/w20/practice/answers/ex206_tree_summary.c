/* ex206_tree_summary.c —— 参考答案 */

#include <stdio.h>

static long long pow2(int n)
{
    long long r = 1;
    for (int i = 0; i < n; i++) r *= 2;
    return r;
}

static int floorLog2(int n)
{
    int lg = 0;
    while (n > 1) { n /= 2; lg++; }
    return lg;
}

int main(void)
{
    printf("=== 五道选择题型，代码验证 ===\n\n");

    /* 题目 1 */
    printf("题目 1：深度为 5 的满二叉树有多少个节点？\n");
    printf("  答案：2^5 - 1 = %lld 个\n", pow2(5) - 1);

    /* 题目 2 */
    printf("\n题目 2：100 个节点的完全二叉树，深度是多少？\n");
    printf("  答案：⌊log2(100)⌋ + 1 = %d + 1 = %d\n",
           floorLog2(100), floorLog2(100) + 1);

    /* 题目 3 */
    printf("\n题目 3：n 个节点的二叉树，空指针有多少个？\n");
    printf("  答案：n + 1 个（n=7 时是 8 个）\n");
    printf("  推导：2n 个指针域 - (n-1) 条边 = n+1 个空指针\n");

    /* 题目 4 */
    printf("\n题目 4：叶子数 n0 和度为 2 的节点 n2 的关系？\n");
    printf("  答案：n0 = n2 + 1\n");
    printf("  推导：n = n0+n1+n2，且 n-1 = n1+2n2，联立得 n0=n2+1\n");

    /* 题目 5 */
    printf("\n题目 5：n 个叶子节点的哈夫曼树，总节点数？\n");
    printf("  答案：2n - 1 个\n");
    printf("  推导：n 个叶子 + (n-1) 个内部节点 = 2n-1\n");

    printf("\n=== 六条核心性质速记 ===\n");
    printf("  1. 第 i 层最多 2^(i-1) 个节点\n");
    printf("  2. 深度 k 最多 2^k - 1 个节点\n");
    printf("  3. 完全二叉树深度 = ⌊log2(n)⌋ + 1\n");
    printf("  4. n0 = n2 + 1\n");
    printf("  5. 空指针 = n + 1\n");
    printf("  6. 哈夫曼树总节点 = 2n - 1\n");
    printf("\n  ⭐ 这六条是 W19/W20 的选择题「必背清单」。\n");

    printf("\n=== 常见陷阱 ===\n");
    printf("  1. 「深度」和「层」的差一：深度从 1 数，高度从 0 数\n");
    printf("  2. 满二叉树节点数是 2^k-1，不是 2^k\n");
    printf("  3. 完全二叉树深度公式是「向下取整」log2\n");
    printf("  4. 哈夫曼树没有度为 1 的节点\n");
    printf("  5. BST 中序是升序，但「先序/后序」不保证有序\n");

    return 0;
}
