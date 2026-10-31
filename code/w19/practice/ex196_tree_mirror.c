/* ex196_tree_mirror.c —— 求镜像树（翻转二叉树）
 *
 * 要求：
 *   1. mirror(root)：原地翻转一棵二叉树（左右子树互换）
 *   2. 翻转前后分别输出中序遍历
 *
 * 测试树：
 *        4
 *       / \
 *      2   7
 *     / \ / \
 *    1  3 6  9
 *
 * 翻转前中序：1 2 3 4 6 7 9
 * 翻转后中序：9 7 6 4 3 2 1
 *
 * 提示：
 *   递归：交换左右孩子，再分别递归左右子树
 *   三步：临时变量交换 → mirror(left) → mirror(right)
 *
 * ⭐ 这也是面试高频题（LeetCode 226）。
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

static void inorder(TNode *root)
{
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* TODO 1：翻转（镜像） */
void mirror(TNode *root)
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
    /* TODO 2：构造树，输出翻转前后中序 */

    printf("\n=== 关键点 ===\n");
    printf("  翻转只需交换左右孩子，三个递归调用就够：\n");
    printf("    swap(left, right);\n");
    printf("    mirror(left);\n");
    printf("    mirror(right);\n");
    printf("  先交换再递归，或先递归再交换，结果一样。\n");

    return 0;
}
