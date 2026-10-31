/* ex201_bst_ops.c —— 参考答案 */

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

BSTNode *bstInsert(BSTNode *root, int v)
{
    if (root == NULL) return make(v);       /* 空位插入 */
    if (v < root->data) root->left = bstInsert(root->left, v);
    else if (v > root->data) root->right = bstInsert(root->right, v);
    /* 相等：忽略（BST 不存重复） */
    return root;
}

BSTNode *bstSearch(BSTNode *root, int v)
{
    while (root != NULL && root->data != v) {
        if (v < root->data) root = root->left;
        else                root = root->right;
    }
    return root;
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
    for (int i = 0; i < 7; i++) root = bstInsert(root, vals[i]);

    printf("=== 中序遍历 ===\n");
    inorder(root);
    printf("\n期望：20 30 40 50 60 70 80（升序）\n");

    printf("\n=== 查找 ===\n");
    printf("  找 40：%s\n", bstSearch(root, 40) ? "找到 ✓" : "没找到");
    printf("  找 99：%s\n", bstSearch(root, 99) ? "找到" : "没找到 ✓");

    printf("\n=== BST 的三大性质 ===\n");
    printf("  1. 左子树所有值 < 根 < 右子树所有值\n");
    printf("  2. 中序遍历 = 升序序列（这是验证 BST 正确性的标志）\n");
    printf("  3. 查找 = 每步比大小往下走，复杂度 O(高度)\n");

    printf("\n=== 插入为什么不会破坏 BST 性质 ===\n");
    printf("  新节点永远插在「叶子」位置：\n");
    printf("  一路比大小走到空位，那里本来就满足大小关系。\n");
    printf("  ⭐ 所以插入不需要调整整棵树，O(log n)。\n");

    freeTree(root);
    return 0;
}
