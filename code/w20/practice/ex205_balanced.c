/* ex205_balanced.c —— 判断是否平衡二叉树
 *
 * 要求：
 *   1. height(root)：求高度
 *   2. isBalanced(root)：判断是否平衡（任意节点左右高度差 <= 1）
 *
 * 测试：
 *   平衡树（3 层满树）→ 是
 *   斜树 → 否
 *
 * 提示：
 *   平衡 = 每个节点都满足 |左高 - 右高| <= 1
 *   递归判断：自己平衡 && 左子树平衡 && 右子树平衡
 *
 * ⚠️ 注意：如果每次递归都重新算高度，是 O(n^2)。
 * 更好的做法是「自底向上返回高度，同时判断」—— 可以想想怎么优化到 O(n)。
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

/* TODO 1：求高度 */
int height(TNode *root)
{
    (void)root;
    return 0;
}

/* TODO 2：判断平衡 */
int isBalanced(TNode *root)
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
    /* TODO 3：构造平衡树和不平衡树，分别判断 */

    return 0;
}
