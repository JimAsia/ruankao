/* ex195_tree_full.c —— 参考答案 */

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

int isComplete(TNode *root)
{
    if (root == NULL) return 1;     /* 空树算完全二叉树 */

    TNode *q[64];
    int front = 0, rear = 0;
    int seenNull = 0;               /* 是否已经遇到过空位 */

    q[rear++] = root;

    while (front < rear) {
        TNode *cur = q[front++];

        if (cur == NULL) {
            seenNull = 1;           /* 遇到空位，做标记 */
            continue;
        }

        if (seenNull) {
            return 0;               /* 空位之后又出现非空节点 → 不是完全二叉树 */
        }

        q[rear++] = cur->left;      /* 左孩子（可能是 NULL）入队 */
        q[rear++] = cur->right;     /* 右孩子（可能是 NULL）入队 */
    }

    return 1;
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
    /* 完全二叉树：1 2 3 4 5 6 */
    TNode *n4 = make(4, NULL, NULL);
    TNode *n5 = make(5, NULL, NULL);
    TNode *n6 = make(6, NULL, NULL);
    TNode *n2 = make(2, n4, n5);
    TNode *n3 = make(3, n6, NULL);      /* 3 的左孩子 6，右孩子空 */
    TNode *n1 = make(1, n2, n3);

    printf("=== 测试 1：完全二叉树 ===\n");
    printf("  1 2 3 4 5 6（层序），是否完全？%s\n",
           isComplete(n1) ? "是 ✓" : "否 ✗");

    printf("\n  层序序列（含空位）：1 2 3 4 5 6 NULL\n");
    printf("  ⭐ 空位出现在最后，前面连续 → 完全二叉树\n");
    freeTree(n1);

    /* 非完全：3 只有右孩子 6，没有左孩子（空洞） */
    TNode *m6 = make(6, NULL, NULL);
    TNode *m4 = make(4, NULL, NULL);
    TNode *m5 = make(5, NULL, NULL);
    TNode *m2 = make(2, m4, m5);
    TNode *m3 = make(3, NULL, m6);      /* 3 左孩子空，右孩子 6 */
    TNode *m1 = make(1, m2, m3);

    printf("\n=== 测试 2：非完全二叉树 ===\n");
    printf("  3 缺左孩子但右孩子有 6，是否完全？%s\n",
           isComplete(m1) ? "是" : "否 ✗");

    printf("\n  层序序列（含空位）：1 2 3 4 5 NULL 6\n");
    printf("  ⭐ NULL 之后又出现了 6 → 不是完全二叉树\n");
    freeTree(m1);

    printf("\n=== 判断完全二叉树的标准 ===\n");
    printf("  把树按层序排开（空位也占位置），\n");
    printf("  完全二叉树 = 空位只能出现在【最后】，且中间不能断。\n");
    printf("  📌 等价说法：最后一层从左到右连续填，前面层全满。\n");

    printf("\n=== 为什么要判断完全二叉树 ===\n");
    printf("  因为只有完全二叉树才能用数组高效存储（下标 2i / 2i+1），\n");
    printf("  堆就必须是完全二叉树。\n");

    return 0;
}
