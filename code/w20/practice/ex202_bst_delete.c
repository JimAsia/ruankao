/* ex202_bst_delete.c —— 二叉排序树删除（三种情况都要处理）
 *
 * 要求：实现 bstDelete，正确处理三种情况
 *   1. 删叶子节点：直接删
 *   2. 删只有一个孩子的节点：孩子顶上
 *   3. 删有两个孩子的节点：用右子树最小值替代
 *
 * 测试（初始 50 30 70 20 40 60 80）：
 *   删 20（叶子）→ 中序 30 40 50 60 70 80
 *   删 70（两孩子）→ 中序仍升序
 *   删 50（根，两孩子）→ 中序仍升序
 *
 * 每次删除后都要验证中序仍升序（这是 BST 正确性的标志）。
 *
 * 提示：
 *   情况 1/2：返回「被删节点剩下的那个孩子」
 *   情况 3：找右子树最小节点，值复制，再递归删那个最小节点
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int            data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

static BSTNode *make(int v)
{
    BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
    if (!n) return NULL;
    n->data = v; n->left = n->right = NULL;
    return n;
}

static BSTNode *bstInsert(BSTNode *root, int v)
{
    if (!root) return make(v);
    if (v < root->data) root->left = bstInsert(root->left, v);
    else if (v > root->data) root->right = bstInsert(root->right, v);
    return root;
}

static void inorder(BSTNode *root)
{
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* 找最小节点 */
static BSTNode *findMin(BSTNode *root)
{
    while (root && root->left) root = root->left;
    return root;
}

/* TODO 1：删除 */
BSTNode *bstDelete(BSTNode *root, int v)
{
    (void)root; (void)v;
    return NULL;
}

static void freeTree(BSTNode *root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    BSTNode *root = NULL;
    for (int i = 0; i < 7; i++) root = bstInsert(root, vals[i]);

    printf("初始："); inorder(root); printf("\n\n");

    /* TODO 2：删叶子 20 */

    /* TODO 3：删两孩子的 70 */

    /* TODO 4：删根 50 */

    return 0;
}
