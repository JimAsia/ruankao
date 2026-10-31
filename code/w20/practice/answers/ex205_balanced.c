/* ex205_balanced.c —— 参考答案 */

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

int height(TNode *root)
{
    if (root == NULL) return 0;
    int hl = height(root->left);
    int hr = height(root->right);
    return (hl > hr ? hl : hr) + 1;
}

int isBalanced(TNode *root)
{
    if (root == NULL) return 1;

    int hl = height(root->left);
    int hr = height(root->right);
    if (hl - hr > 1 || hr - hl > 1) return 0;   /* 自己不平衡 */

    return isBalanced(root->left) && isBalanced(root->right);
}

/* 优化版：自底向上，一次遍历 O(n)
 * 返回 -1 表示不平衡，否则返回高度 */
static int checkAndHeight(TNode *root)
{
    if (root == NULL) return 0;

    int hl = checkAndHeight(root->left);
    if (hl == -1) return -1;

    int hr = checkAndHeight(root->right);
    if (hr == -1) return -1;

    if (hl - hr > 1 || hr - hl > 1) return -1;

    return (hl > hr ? hl : hr) + 1;
}

int isBalancedFast(TNode *root)
{
    return checkAndHeight(root) != -1;
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
    /* 平衡树 */
    TNode *a = make(4,
                    make(2, make(1, NULL, NULL), make(3, NULL, NULL)),
                    make(6, make(5, NULL, NULL), make(7, NULL, NULL)));
    printf("平衡树：%s\n", isBalanced(a) ? "是 ✓" : "否");
    freeTree(a);

    /* 不平衡树（右斜） */
    TNode *b = make(1, NULL, make(2, NULL, make(3, NULL, make(4, NULL, NULL))));
    printf("斜树：%s\n", isBalanced(b) ? "是" : "否 ✓");
    freeTree(b);

    printf("\n=== 平衡二叉树定义 ===\n");
    printf("  任意节点的左右子树高度差 <= 1。\n");
    printf("  ⭐ 平衡保证查找 O(log n)，不平衡退化到 O(n)。\n");

    printf("\n=== 复杂度对比 ===\n");
    printf("  朴素版：每个节点都算一次高度，O(n^2)\n");
    printf("  优化版：自底向上返回高度，一次遍历 O(n)\n");
    printf("  ⭐ 优化版的关键：递归函数「返回高度」的同时「传递不平衡信号（-1）」。\n");

    printf("\n=== AVL 树 ===\n");
    printf("  AVL 是最早的平衡二叉树，靠「旋转」维持平衡。\n");
    printf("  四种失衡：LL / RR / LR / RL，对应右旋/左旋/先左后右/先右后左。\n");
    printf("  📌 软考主要考「判断是否平衡」和「四种旋转」，不要求写旋转代码。\n");

    return 0;
}
