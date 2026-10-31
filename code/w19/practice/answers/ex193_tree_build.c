/* ex193_tree_build.c —— 参考答案 */

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
    n->data = c; n->left = n->right = NULL;
    return n;
}

TNode *buildTree(char pre[], char in[], int n)
{
    if (n <= 0) return NULL;

    char rootData = pre[0];             /* 前序第一个是根 */
    TNode *root = make(rootData);

    /* 在中序里找根的位置 */
    int rootIdx = 0;
    while (rootIdx < n && in[rootIdx] != rootData) rootIdx++;

    /* 左子树 rootIdx 个，右子树 n-1-rootIdx 个 */
    root->left  = buildTree(pre + 1, in, rootIdx);
    root->right = buildTree(pre + 1 + rootIdx, in + rootIdx + 1, n - 1 - rootIdx);

    return root;
}

void postorder(TNode *root)
{
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
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
    char pre[] = "ABDECFG";
    char in[]  = "DBEAFCG";
    int  n = (int)strlen(pre);

    printf("前序：%s\n", pre);
    printf("中序：%s\n", in);

    TNode *root = buildTree(pre, in, n);
    printf("重建后，后序：");
    postorder(root);
    printf("\n\n期望：DEBFGCA\n");
    printf("\n=== 手算过程 ===\n");
    printf("  1. 前序第一个 A 是根\n");
    printf("  2. 中序里 A 左边 DBE 是左子树，右边 FCG 是右子树\n");
    printf("  3. 左子树：前序 BDE，中序 DBE\n");
    printf("       B 是根，左 D，右 E\n");
    printf("  4. 右子树：前序 CFG，中序 FCG\n");
    printf("       C 是根，左 F，右 G\n");
    printf("  5. 后序：左子树 DEB + 右子树 FGC + 根 A = DEBFGCA ✓\n");

    printf("\n=== 关键：根的下标怎么切分 ===\n");
    printf("  前序 pre 里根在 pre[0]\n");
    printf("  中序 in 里找到根的下标 rootIdx\n");
    printf("    左子树：pre+1, in, 长度 rootIdx\n");
    printf("    右子树：pre+1+rootIdx, in+rootIdx+1, 长度 n-1-rootIdx\n");
    printf("  ⭐ 两个数组的「左右子树」必须用【同一套下标】切，不能各切各的。\n");

    freeTree(root);
    return 0;
}
