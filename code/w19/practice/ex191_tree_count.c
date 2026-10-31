/* ex191_tree_count.c —— 树的性质：节点数、叶子数、深度
 *
 * 要求：实现三个递归函数
 *   1. countNodes(root)：节点总数
 *   2. countLeaves(root)：叶子数
 *   3. treeDepth(root)：深度
 *
 * 测试树：
 *        A
 *       / \
 *      B   C
 *     / \
 *    D   E
 *       /
 *      F
 *
 * 期望：
 *   节点总数 = 6
 *   叶子数   = 3（D、F、C）
 *   深度     = 4
 *
 * 提示：
 *   节点数 = 左 + 右 + 1
 *   叶子 = 左右都空算 1 个
 *   深度 = max(左深, 右深) + 1
 *   空树（root == NULL）：节点 0，叶子 0，深度 0
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    char          data;
    struct TNode *left;
    struct TNode *right;
} TNode;

static TNode *make(char c, TNode *l, TNode *r)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    if (!n) return NULL;
    n->data = c; n->left = l; n->right = r;
    return n;
}

/* TODO 1：节点总数 */
int countNodes(TNode *root)
{
    (void)root;
    return 0;
}

/* TODO 2：叶子数 */
int countLeaves(TNode *root)
{
    (void)root;
    return 0;
}

/* TODO 3：深度 */
int treeDepth(TNode *root)
{
    (void)root;
    return 0;
}

static void freeTree(TNode *root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    /* TODO 4：构造测试树，输出三个统计结果 */

    /* TODO 5：边界 —— 空树 */

    return 0;
}
