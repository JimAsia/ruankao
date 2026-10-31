/* ex192_tree_traversal.c —— 三种遍历 + 统计遍历次数
 *
 * 要求：
 *   1. 实现先序、中序、后序遍历
 *   2. 用全局计数器统计「每个节点被访问几次」
 *   3. 输出三种遍历结果，以及访问次数（应该是节点数）
 *
 * 测试树：
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 *
 * 期望输出：
 *   先序：1 2 4 5 3
 *   中序：4 2 5 1 3
 *   后序：4 5 2 3 1
 *
 * 提示：
 *   先序：访问根 → 左 → 右
 *   中序：左 → 访问根 → 右
 *   后序：左 → 右 → 访问根
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

static int g_visits = 0;

/* TODO 1：先序 */
void preorder(TNode *root)
{
    (void)root;
}

/* TODO 2：中序 */
void inorder(TNode *root)
{
    (void)root;
}

/* TODO 3：后序 */
void postorder(TNode *root)
{
    (void)root;
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
    /* TODO 4：构造树，三种遍历各跑一次，输出结果和访问次数 */

    return 0;
}
