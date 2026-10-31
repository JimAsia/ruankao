/* ex193_tree_build.c —— 由前序+中序重建，并求后序
 *
 * 要求：
 *   1. buildTree(pre, in, n)：由前序+中序重建
 *   2. 重建后输出后序遍历
 *
 * 测试：
 *   前序 = ABDECFG
 *   中序 = DBEAFCG
 *   后序应该是 DEBFGCA
 *
 * 提示：
 *   前序第一个是根
 *   中序里根左边是左子树，右边是右子树
 *   递归分治
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode {
    char          data;
    struct TNode *left;
    struct TNode *right;
} TNode;

static TNode *make(char c)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    if (!n) return NULL;
    n->data = c; n->left = n->right = NULL;
    return n;
}

/* TODO 1：由前序+中序重建 */
TNode *buildTree(char pre[], char in[], int n)
{
    (void)pre; (void)in; (void)n;
    return NULL;
}

/* 后序遍历（已给出） */
void postorder(TNode *root)
{
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
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
    char pre[] = "ABDECFG";
    char in[]  = "DBEAFCG";
    int  n = (int)strlen(pre);

    /* TODO 2：重建并输出后序 */

    return 0;
}
