/* ex201_bst_ops.c —— 二叉排序树的查找、插入、验证
 *
 * 要求：
 *   1. bstInsert(root, v)：插入
 *   2. bstSearch(root, v)：查找，返回节点或 NULL
 *   3. 验证中序遍历是否升序
 *
 * 测试：
 *   依次插入 50 30 70 20 40 60 80
 *   中序遍历应输出升序 20 30 40 50 60 70 80
 *   查找 40 → 找到；查找 99 → 没找到
 *
 * 提示：
 *   插入：比根小往左，比根大往右，空位插入
 *   查找：同样比大小往下走
 *   中序遍历 BST = 升序
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

/* TODO 1：插入 */
BSTNode *bstInsert(BSTNode *root, int v)
{
    (void)root; (void)v;
    return NULL;
}

/* TODO 2：查找 */
BSTNode *bstSearch(BSTNode *root, int v)
{
    (void)root; (void)v;
    return NULL;
}

static void inorder(BSTNode *root)
{
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
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

    /* TODO 3：依次插入，输出中序 */

    /* TODO 4：查找 40 和 99 */

    return 0;
}
