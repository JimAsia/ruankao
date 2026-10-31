/* ex202_bst_delete.c —— 参考答案 */

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

static BSTNode *findMin(BSTNode *root)
{
    while (root && root->left) root = root->left;
    return root;
}

BSTNode *bstDelete(BSTNode *root, int v)
{
    if (root == NULL) return NULL;

    if (v < root->data) {
        root->left = bstDelete(root->left, v);
    } else if (v > root->data) {
        root->right = bstDelete(root->right, v);
    } else {
        /* 找到了 */
        if (root->left == NULL) {           /* 情况1：无左孩子（含叶子） */
            BSTNode *tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) {   /* 情况2：只有左孩子 */
            BSTNode *tmp = root->left;
            free(root);
            return tmp;
        } else {                            /* 情况3：两个孩子 */
            BSTNode *min = findMin(root->right);    /* 右子树最小 = 后继 */
            root->data = min->data;                 /* 值复制 */
            root->right = bstDelete(root->right, min->data);  /* 删后继 */
        }
    }
    return root;
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

    printf("初始："); inorder(root); printf("\n");

    printf("\n=== 情况 1：删叶子 20 ===\n");
    root = bstDelete(root, 20);
    printf("  "); inorder(root); printf("\n");

    printf("\n=== 情况 2：删只有一个孩子的（先造一个）===\n");
    root = bstInsert(root, 45);             /* 45 是 40 的右孩子 */
    printf("  插入 45 后："); inorder(root); printf("\n");
    root = bstDelete(root, 40);             /* 40 现在有右孩子 45 */
    printf("  删 40 后："); inorder(root); printf("\n");

    printf("\n=== 情况 3：删两孩子的 70 ===\n");
    root = bstDelete(root, 70);
    printf("  "); inorder(root); printf("\n");
    printf("  ⭐ 70 有两个孩子，用右子树最小值 80 替代，仍升序 ✓\n");

    printf("\n=== 删根 50 ===\n");
    root = bstDelete(root, 50);
    printf("  "); inorder(root); printf("\n");

    printf("\n=== 三种情况总结 ===\n");
    printf("  情况 1（叶子）：直接删，返回 NULL\n");
    printf("  情况 2（一个孩子）：返回那个孩子（孩子顶上来）\n");
    printf("  情况 3（两个孩子）：用右子树最小值替代，再递归删它\n");
    printf("  ⭐ 情况 3 选「右子树最小值」而不是随便选，\n");
    printf("     是为了保证中序仍升序（它正好是「后继」）。\n");

    printf("\n=== 删除的复杂度 ===\n");
    printf("  找节点 O(log n) + 找后继 O(log n) + 调整 O(1)\n");
    printf("  平衡时总复杂度 O(log n)。\n");

    freeTree(root);
    return 0;
}
