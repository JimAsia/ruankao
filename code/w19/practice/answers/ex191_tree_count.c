/* ex191_tree_count.c —— 参考答案 */

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

int countNodes(TNode *root)
{
    if (root == NULL) return 0;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

int countLeaves(TNode *root)
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;  /* 叶子 */
    return countLeaves(root->left) + countLeaves(root->right);
}

int treeDepth(TNode *root)
{
    if (root == NULL) return 0;
    int dl = treeDepth(root->left);
    int dr = treeDepth(root->right);
    return (dl > dr ? dl : dr) + 1;
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
    /*        A
     *       / \
     *      B   C
     *     / \
     *    D   E
     *       /
     *      F
     */
    TNode *F = make('F', NULL, NULL);
    TNode *D = make('D', NULL, NULL);
    TNode *E = make('E', F, NULL);
    TNode *C = make('C', NULL, NULL);
    TNode *B = make('B', D, E);
    TNode *A = make('A', B, C);

    printf("=== 统计 ===\n");
    printf("  节点总数 = %d（A B C D E F 共 6 个）\n", countNodes(A));
    printf("  叶子数   = %d（D F C）\n", countLeaves(A));
    printf("  深度     = %d（A-B-E-F 共 4 层）\n", treeDepth(A));

    /* 验证叶子：D(无孩子)、F(无孩子)、C(无孩子) = 3 */
    /* 验证深度：A(1) B(2) E(3) F(4) = 4 */

    printf("\n=== 边界：空树 ===\n");
    printf("  节点 %d，叶子 %d，深度 %d\n",
           countNodes(NULL), countLeaves(NULL), treeDepth(NULL));
    printf("  ⭐ 空树三项都是 0，递归基要写对。\n");

    printf("\n=== 递归统计的模板 ===\n");
    printf("  节点数 = 左 + 右 + 1\n");
    printf("  叶子   = (左右都空?1:0) + 左叶子 + 右叶子\n");
    printf("  深度   = max(左深, 右深) + 1\n");
    printf("  ⭐ 三者的共同点：先递归问左右子树，再汇总自己。\n");
    printf("     这是「树的递归」最核心的套路，\n");
    printf("     后面所有树的题都是这个骨架。\n");

    freeTree(A);
    return 0;
}
