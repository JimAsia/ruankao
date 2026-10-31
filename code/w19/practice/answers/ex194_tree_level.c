/* ex194_tree_level.c —— 参考答案 */

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

void levelOrder(TNode *root)
{
    if (root == NULL) return;

    TNode *q[64];               /* 用数组模拟队列 */
    int front = 0, rear = 0;

    q[rear++] = root;           /* 根入队 */

    while (front < rear) {
        TNode *cur = q[front++];        /* 出队 */
        printf("%d ", cur->data);       /* 访问 */

        if (cur->left != NULL)  q[rear++] = cur->left;   /* 左孩子入队 */
        if (cur->right != NULL) q[rear++] = cur->right;  /* 右孩子入队 */
    }
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
    /*        1
     *       / \
     *      2   3
     *     / \   \
     *    4   5   6
     */
    TNode *n4 = make(4, NULL, NULL);
    TNode *n5 = make(5, NULL, NULL);
    TNode *n6 = make(6, NULL, NULL);
    TNode *n2 = make(2, n4, n5);
    TNode *n3 = make(3, NULL, n6);
    TNode *n1 = make(1, n2, n3);

    printf("层序遍历：");
    levelOrder(n1);
    printf("\n期望：1 2 3 4 5 6\n");

    printf("\n=== 层序遍历为什么必须用队列 ===\n");
    printf("  层序要求「先遇到先访问」—— 正是先进先出。\n");
    printf("  递归（栈）做的是「先遇到后访问」，所以做不了层序。\n");
    printf("\n  ⭐ 四种遍历的本质：\n");
    printf("     前/中/后序 = DFS（深度优先，用栈/递归）\n");
    printf("     层序      = BFS（广度优先，用队列）\n");
    printf("  📌 DFS 和 BFS 是图遍历的两大算法，W21 会正式讲。\n");

    printf("\n=== 队列在这里的角色 ===\n");
    printf("  入队顺序：1 → 2 3 → 4 5 6\n");
    printf("  出队顺序：1 → 2 → 3 → 4 → 5 → 6\n");
    printf("  每一层入队后，下一层在队尾排队，保证按层顺序出。\n");

    freeTree(n1);
    return 0;
}
