/* ex195_tree_full.c —— 判断完全二叉树
 *
 * 要求：
 *   1. isComplete(root)：判断是否是完全二叉树
 *   2. 用层序遍历的思路：一旦遇到一个「缺孩子」的节点，
 *      后面的所有节点都必须是叶子，否则不是完全二叉树
 *
 * 测试：
 *   完全二叉树（1..6 层序编号）→ 是
 *   缺右孩子但后面还有节点 → 不是
 *
 * 提示：
 *   层序遍历，用一个「是否已经遇到空位」的标志。
 *   完全二叉树的层序序列中，一旦出现 NULL，后面就不能再有非 NULL。
 *
 * 例：完全二叉树层序（含空位）：1 2 3 4 5 NULL NULL
 *     一旦遇到第一个 NULL（2 的右孩子），后面全是 NULL，是合法的。
 *     如果 NULL 之后又出现非 NULL，就不是完全二叉树。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    int           data;
    struct TNode *left;
    struct TNode *right;
} TNode;

static TNode *make(int v, TNode *l, TNode *r)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    if (!n) return NULL;
    n->data = v; n->left = l; n->right = r;
    return n;
}

/* TODO 1：判断完全二叉树 */
int isComplete(TNode *root)
{
    (void)root;
    return 1;
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
    /* TODO 2：构造一个完全二叉树，判断（应输出「是」） */

    /* TODO 3：构造一个非完全二叉树（缺右孩子但后面有节点），判断（应输出「否」） */

    return 0;
}
