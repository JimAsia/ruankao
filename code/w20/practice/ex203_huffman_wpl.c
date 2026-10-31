/* ex203_huffman_wpl.c —— 计算哈夫曼树的 WPL
 *
 * 要求：
 *   1. buildHuffman(weights, n)：构造哈夫曼树
 *   2. wpl(root, depth)：计算带权路径长度
 *
 * 测试（经典例题）：
 *   权值 {2, 4, 5, 7} 的 WPL = 35
 *   权值 {5, 32, 18, 7, 25} 的 WPL = 184
 *
 * 提示：
 *   构造：每次取两个最小的合并，直到剩一个
 *   WPL：每个叶子的 权值 × 深度 之和
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct HTNode {
    int           weight;
    struct HTNode *left;
    struct HTNode *right;
} HTNode;

/* TODO 1：构造哈夫曼树 */
HTNode *buildHuffman(int weights[], int n)
{
    (void)weights; (void)n;
    return NULL;
}

/* TODO 2：计算 WPL */
int wpl(HTNode *root, int depth)
{
    (void)root; (void)depth;
    return 0;
}

static void freeTree(HTNode *root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    /* TODO 3：测试 {2,4,5,7} 和 {5,32,18,7,25} */

    return 0;
}
