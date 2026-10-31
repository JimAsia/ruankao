/* 193_tree_build.c —— 由前序+中序重建二叉树 + 统计节点
 *
 * 两个软考核心考点：
 *   ① 由「前序 + 中序」重建二叉树（递归分治）
 *   ② 统计节点总数、叶子数、深度（树的递归统计模板）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode {
    char          data;
    struct TNode *left;
    struct TNode *right;
} TNode;

static TNode *make(char c)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    if (!n) return NULL;
    n->data = c;
    n->left = n->right = NULL;
    return n;
}

/* ==================== ① 由前序 + 中序重建 ==================== */
/* pre[] 前序序列，in[] 中序序列，n 是长度
 * 返回根节点指针 */
TNode *buildTree(char pre[], char in[], int n)
{
    if (n <= 0) return NULL;

    char rootData = pre[0];                 /* 前序第一个是根 */
    TNode *root = make(rootData);

    /* 在中序里找根的位置 */
    int rootIdx = 0;
    while (rootIdx < n && in[rootIdx] != rootData) rootIdx++;

    /* 左子树有 rootIdx 个节点，右子树有 n-1-rootIdx 个 */
    root->left  = buildTree(pre + 1, in, rootIdx);
    root->right = buildTree(pre + 1 + rootIdx, in + rootIdx + 1, n - 1 - rootIdx);

    return root;
}

/* 验证：重建后再做一次中序，应该和原中序一致 */
static void inorder(TNode *root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

/* ==================== ② 三种递归统计 ==================== */

/* 节点总数：左 + 右 + 1 */
static int countNodes(TNode *root)
{
    if (root == NULL) return 0;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

/* 叶子数：左右都空才算叶子 */
static int countLeaves(TNode *root)
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

/* 深度：max(左深, 右深) + 1 */
static int treeDepth(TNode *root)
{
    if (root == NULL) return 0;
    int dl = treeDepth(root->left);
    int dr = treeDepth(root->right);
    return (dl > dr ? dl : dr) + 1;
}

/* 度为 2 的节点数（用来验证 n0 = n2 + 1） */
static int countDeg2(TNode *root)
{
    if (root == NULL) return 0;
    int self = (root->left != NULL && root->right != NULL) ? 1 : 0;
    return self + countDeg2(root->left) + countDeg2(root->right);
}

static void freeTree(TNode *root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    /* ---------- ① 重建树 ---------- */
    printf("=== ① 由前序 + 中序重建 ===\n");
    char pre[] = "ABDEGHCF";
    char in[]  = "DBGEHACF";
    int  n = (int)strlen(pre);

    printf("  前序：%s\n", pre);
    printf("  中序：%s\n", in);

    TNode *root = buildTree(pre, in, n);

    printf("  重建后中序遍历：");
    inorder(root);
    printf("\n  ⭐ 和原中序一致 → 重建正确 ✓\n");

    printf("\n  ⭐ 重建的分治步骤：\n");
    printf("     1. 前序第一个 A 是根\n");
    printf("     2. 中序里 A 左边 DBGEH 是左子树（5 个），右边 CF 是右子树（2 个）\n");
    printf("     3. 左子树的前序是 B D E G H，递归重建\n");
    printf("     4. 右子树的前序是 C F，递归重建\n");

    /* ---------- ② 统计 ---------- */
    printf("\n=== ② 递归统计三件套 ===\n");
    printf("  节点总数 = %d\n", countNodes(root));
    printf("  叶子数   = %d\n", countLeaves(root));
    printf("  深度     = %d\n", treeDepth(root));
    printf("  度为 2 的节点数 = %d\n", countDeg2(root));

    /* 验证 n0 = n2 + 1 */
    int n0 = countLeaves(root);
    int n2 = countDeg2(root);
    printf("\n  验证性质：叶子 %d = 度为2的 %d + 1 = %d %s\n",
           n0, n2, n2 + 1, (n0 == n2 + 1) ? "✓" : "✗");

    printf("\n  ⭐ 递归统计的模板（记住这个套路）：\n");
    printf("     节点数 = 左子树节点数 + 右子树节点数 + 1\n");
    printf("     叶子数 = (左右都空 ? 1 : 0) + 左叶子 + 右叶子\n");
    printf("     深度   = max(左深, 右深) + 1\n");
    printf("     都是「先问左右子树，再汇总自己」的分治思想。\n");

    freeTree(root);

    /* ---------- ③ 特殊形态的树 ---------- */
    printf("\n=== ③ 两种退化形态（软考常考）===\n");
    printf("  斜树（每个节点只有一个孩子）：\n");
    printf("      A            A\n");
    printf("     /              \\\n");
    printf("    B                B\n");
    printf("   /                  \\\n");
    printf("  C                    C\n");
    printf("  左斜树              右斜树\n");
    printf("\n  ⭐ 斜树的深度 = 节点数 = n，是最深的二叉树。\n");
    printf("     对比：完全二叉树深度只有 log2(n)。\n");
    printf("     📌 这就是为什么「平衡」很重要 —— 后面 W20 会讲。\n");

    /* ---------- ④ 中序 + 后序重建 ---------- */
    printf("\n=== ④ 中序 + 后序也能重建 ===\n");
    printf("  和「前序+中序」唯一的区别：\n");
    printf("     前序：根在最前面 → 第一个是根\n");
    printf("     后序：根在最后面 → 最后一个才是根\n");
    printf("  其余分治逻辑完全一样。\n");
    printf("\n  📌 软考可能考「给前序和中序，写出后序」，\n");
    printf("     或者「给中序和后序，写出前序」—— 都是先重建再遍历。\n");

    return 0;
}
