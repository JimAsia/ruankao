/* ex196_tree_mirror.c —— 参考答案 */

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

void mirror(TNode *root)
{
    if (root == NULL) return;

    /* 交换左右孩子 */
    TNode *t = root->left;
    root->left = root->right;
    root->right = t;

    /* 递归翻转左右子树 */
    mirror(root->left);
    mirror(root->right);
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
    /*        4
     *       / \
     *      2   7
     *     / \ / \
     *    1  3 6  9
     */
    TNode *n1 = make(1, NULL, NULL);
    TNode *n3 = make(3, NULL, NULL);
    TNode *n6 = make(6, NULL, NULL);
    TNode *n9 = make(9, NULL, NULL);
    TNode *n2 = make(2, n1, n3);
    TNode *n7 = make(7, n6, n9);
    TNode *root = make(4, n2, n7);

    printf("翻转前中序：");
    inorder(root);
    printf("\n");

    mirror(root);

    printf("翻转后中序：");
    inorder(root);
    printf("\n");

    printf("\n期望：\n");
    printf("  翻转前：1 2 3 4 6 7 9\n");
    printf("  翻转后：9 7 6 4 3 2 1\n");

    printf("\n=== 为什么中序会反转 ===\n");
    printf("  镜像后，原来的「左中右」变成「右中左」，\n");
    printf("  所以中序序列正好是原来的倒序。\n");

    printf("\n=== 镜像的本质 ===\n");
    printf("  每个节点的左右孩子互换，整棵树就像照了镜子。\n");
    printf("  ⭐ 三步：\n");
    printf("    t = left;\n");
    printf("    left = right;\n");
    printf("    right = t;\n");
    printf("  然后对左右子树递归做同样的事。\n");

    printf("\n=== 复杂度 ===\n");
    printf("  时间 O(n)：每个节点访问一次\n");
    printf("  空间 O(h)：递归栈深度 = 树高\n");

    freeTree(root);
    return 0;
}
