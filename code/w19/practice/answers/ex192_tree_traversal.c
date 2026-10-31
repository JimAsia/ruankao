/* ex192_tree_traversal.c —— 参考答案 */

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

static int g_visits = 0;

void preorder(TNode *root)
{
    if (root == NULL) return;
    g_visits++;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(TNode *root)
{
    if (root == NULL) return;
    inorder(root->left);
    g_visits++;
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(TNode *root)
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    g_visits++;
    printf("%d ", root->data);
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
     *     / \
     *    4   5
     */
    TNode *n4 = make(4, NULL, NULL);
    TNode *n5 = make(5, NULL, NULL);
    TNode *n3 = make(3, NULL, NULL);
    TNode *n2 = make(2, n4, n5);
    TNode *n1 = make(1, n2, n3);

    printf("=== 三种遍历 ===\n");

    g_visits = 0;
    printf("  先序："); preorder(n1); printf("（访问 %d 次）\n", g_visits);

    g_visits = 0;
    printf("  中序："); inorder(n1);  printf("（访问 %d 次）\n", g_visits);

    g_visits = 0;
    printf("  后序："); postorder(n1); printf("（访问 %d 次）\n", g_visits);

    printf("\n  ⭐ 三种遍历各访问 5 次 = 节点数，只是「顺序不同」。\n");

    printf("\n=== 三种遍历的差异，一句话 ===\n");
    printf("  先序：根 → 左 → 右    （根最先）\n");
    printf("  中序：左 → 根 → 右    （根居中）\n");
    printf("  后序：左 → 右 → 根    （根最后）\n");
    printf("  ⭐ 左孩子永远在右孩子之前。区别只在根的位置。\n");

    printf("\n=== 记忆技巧 ===\n");
    printf("  先序 = Pre-order，根「先」\n");
    printf("  中序 = In-order，根在「中间」\n");
    printf("  后序 = Post-order，根「后」\n");
    printf("  📌 英文名里的 Pre/In/Post 就是指根的位置。\n");

    freeTree(n1);
    return 0;
}
