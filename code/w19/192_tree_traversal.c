/* 192_tree_traversal.c —— 二叉树的三种遍历（软考必考）
 *
 * 三种遍历（对根而言）：
 *   先序（前序）：根 → 左 → 右    根在最前
 *   中序：        左 → 根 → 右    根在中间
 *   后序：        左 → 右 → 根    根在最后
 *
 * 用一棵固定的树，递归实现三种遍历，并和手算结果对照。
 * 还验证两个关键结论：
 *   ① 中序 + 先序（或后序）能唯一确定一棵树
 *   ② 只有先序 + 后序不能唯一确定
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    char          data;
    struct TNode *left;
    struct TNode *right;
} TNode;

/* 建一个节点 */
static TNode *make(char c, TNode *l, TNode *r)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    if (!n) return NULL;
    n->data = c;
    n->left = l;
    n->right = r;
    return n;
}

/* 先序：根 左 右 */
static void preorder(TNode *root)
{
    if (root == NULL) return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

/* 中序：左 根 右 */
static void inorder(TNode *root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

/* 后序：左 右 根 */
static void postorder(TNode *root)
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

/* 释放整棵树 */
static void freeTree(TNode *root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    /* 构造一棵树：
     *        A
     *       / \
     *      B   C
     *     / \   \
     *    D   E   F
     *       / \
     *      G   H
     */
    TNode *G = make('G', NULL, NULL);
    TNode *H = make('H', NULL, NULL);
    TNode *D = make('D', NULL, NULL);
    TNode *E = make('E', G, H);
    TNode *F = make('F', NULL, NULL);
    TNode *B = make('B', D, E);
    TNode *C = make('C', NULL, F);
    TNode *A = make('A', B, C);

    printf("=== 树的形状 ===\n");
    printf("          A\n");
    printf("         / \\\n");
    printf("        B   C\n");
    printf("       / \\   \\\n");
    printf("      D   E   F\n");
    printf("         / \\\n");
    printf("        G   H\n");

    printf("\n=== 三种遍历 ===\n");
    printf("  先序（根左右）：");
    preorder(A);
    printf("\n  中序（左根右）：");
    inorder(A);
    printf("\n  后序（左右根）：");
    postorder(A);
    printf("\n");

    printf("\n  ⭐ 手算核对：\n");
    printf("     先序：A B D E G H C F   （根最先）\n");
    printf("     中序：D B G E H A C F   （根在中间）\n");
    printf("     后序：D G H E B F C A   （根最后）\n");

    printf("\n  ⭐ 记忆口诀：三种遍历的唯一区别是「根什么时候访问」。\n");
    printf("     先序 = 根最先，中序 = 根居中，后序 = 根最后。\n");
    printf("     左孩子永远在右孩子之前。\n");

    /* ---------- 递归 vs 非递归 ---------- */
    printf("\n=== 递归写法为什么是三种 ----------\n");
    printf("  先序：\n");
    printf("    visit(root);          ← 根先访问\n");
    printf("    preorder(left);\n");
    printf("    preorder(right);\n");
    printf("\n  中序：\n");
    printf("    inorder(left);\n");
    printf("    visit(root);          ← 根在中间访问\n");
    printf("    inorder(right);\n");
    printf("\n  后序：\n");
    printf("    postorder(left);\n");
    printf("    postorder(right);\n");
    printf("    visit(root);          ← 根最后访问\n");
    printf("\n  ⭐ 三份代码只有 visit 的位置不同。\n");

    /* ---------- 递归本质 = 栈 ---------- */
    printf("\n=== 遍历的递归本质 = 栈 ===\n");
    printf("  递归遍历时，系统用「函数调用栈」保存：\n");
    printf("    先序：访问 A 后，先递归左子树，左子树全部处理完才回来处理右子树\n");
    printf("    这正是「栈」的深度优先搜索（DFS）\n");
    printf("\n  📌 中序的非递归写法需要显式栈（W18 学的），\n");
    printf("     因为要「先走到底，再回头访问」。\n");

    freeTree(A);

    /* ---------- 遍历序列反推树 ---------- */
    printf("\n=== ④ 由遍历序列重建树 ===\n");
    printf("  结论一：中序 + 先序（或中序 + 后序）能唯一确定一棵树。\n");
    printf("  结论二：只有先序 + 后序【不能】唯一确定。\n");

    printf("\n  例：中序 = D B G E H A C F，先序 = A B D E G H C F\n");
    printf("  步骤：\n");
    printf("    1. 先序第一个 A 是根\n");
    printf("    2. 在中序里找到 A，左边 D B G E H 是左子树，右边 C F 是右子树\n");
    printf("    3. 递归处理左右子树\n");

    printf("\n  ⭐ 为什么「先序+后序」不够？\n");
    printf("     先序 A B C，后序 C B A：\n");
    printf("        A            A\n");
    printf("       / \\   还是    /      ← 两种都可能！\n");
    printf("      B   C        B\n");
    printf("                    \\\n");
    printf("                     C\n");
    printf("     因为先序后序都只能确定「根是谁」，不能确定左右子树的分界。\n");
    printf("     📌 这是软考选择题的经典考点。\n");

    return 0;
}
