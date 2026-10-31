/* ex194_tree_level.c —— 层序遍历（用队列）
 *
 * 要求：
 *   1. levelOrder(root)：按层从上到下、从左到右输出
 *   2. 用【队列】实现（不能用递归）
 *
 * 测试树：
 *        1
 *       / \
 *      2   3
 *     / \   \
 *    4   5   6
 *
 * 期望输出：1 2 3 4 5 6
 *
 * 提示：
 *   根入队
 *   循环：出队一个 → 访问 → 它的左右孩子入队
 *   直到队列空
 *
 * 关键：层序遍历必须用队列（BFS），递归做不了。
 * 队列可以用数组模拟：TNode* q[64]; int front=0, rear=0;
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

/* TODO 1：层序遍历 */
void levelOrder(TNode *root)
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
    /* TODO 2：构造树，层序遍历 */

    printf("\n=== 四种遍历总结 ===\n");
    printf("  前序/中序/后序：深度优先 DFS（用递归/栈）\n");
    printf("  层序：           广度优先 BFS（用队列）\n");
    printf("  ⭐ 这是「DFS vs BFS」在树上的体现，图（W21）也会用到。\n");

    return 0;
}
