/* 201_bst.c —— 二叉排序树 BST（二叉查找树）
 *
 * 定义：对每个节点，左子树所有值 < 根 < 右子树所有值。
 * 中序遍历 BST 会得到一个【升序】序列 —— 这是它的核心性质。
 *
 * 三个操作：
 *   查找：从根开始，比根小走左，比根大走右，O(深度)
 *   插入：先查找，插在「找不到的位置」
 *   删除：三种情况（叶子 / 一个孩子 / 两个孩子）
 *
 * 关键结论：BST 的复杂度取决于【树的高度】，不是节点数。
 *   平衡时 O(log n)，退化成斜树时 O(n)。
 */

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
    n->data = v;
    n->left = n->right = NULL;
    return n;
}

/* ==================== ① 插入 ==================== */
/* 递归插入，返回新的根 */
BSTNode *bstInsert(BSTNode *root, int v)
{
    if (root == NULL) return make(v);       /* 找到空位，插这里 */

    if (v < root->data) {
        root->left = bstInsert(root->left, v);
    } else if (v > root->data) {
        root->right = bstInsert(root->right, v);
    }
    /* v == root->data：忽略重复（BST 通常不允许重复） */

    return root;
}

/* ==================== ② 查找 ==================== */
/* 返回找到的节点，找不到返回 NULL。返回【父节点】用于删除 */
BSTNode *bstSearch(BSTNode *root, int v, BSTNode **parent)
{
    BSTNode *cur = root;
    *parent = NULL;

    while (cur != NULL && cur->data != v) {
        *parent = cur;
        if (v < cur->data) cur = cur->left;
        else               cur = cur->right;
    }
    return cur;
}

/* 找以 root 为根的子树的最小值节点 */
static BSTNode *findMin(BSTNode *root)
{
    while (root != NULL && root->left != NULL) {
        root = root->left;                  /* 一路向左，最左的就是最小 */
    }
    return root;
}

/* ==================== ③ 删除 ==================== */
/* 返回新的根 */
BSTNode *bstDelete(BSTNode *root, int v)
{
    if (root == NULL) return NULL;

    if (v < root->data) {
        root->left = bstDelete(root->left, v);
    } else if (v > root->data) {
        root->right = bstDelete(root->right, v);
    } else {
        /* 找到了要删的节点，分三种情况 */
        if (root->left == NULL) {           /* 情况1：只有右孩子（或没有孩子） */
            BSTNode *tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) {   /* 情况2：只有左孩子 */
            BSTNode *tmp = root->left;
            free(root);
            return tmp;
        } else {                            /* 情况3：有两个孩子 */
            /* 用「右子树的最小值」替代自己（也叫后继），然后删掉那个后继 */
            BSTNode *minNode = findMin(root->right);
            root->data = minNode->data;     /* 值复制过来 */
            root->right = bstDelete(root->right, minNode->data); /* 删后继 */
        }
    }
    return root;
}

/* ==================== 中序遍历（验证升序） ==================== */
static void inorder(BSTNode *root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* 树的高度 */
static int height(BSTNode *root)
{
    if (root == NULL) return 0;
    int hl = height(root->left);
    int hr = height(root->right);
    return (hl > hr ? hl : hr) + 1;
}

static void freeTree(BSTNode *root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    /* ---------- ① 建树 + 中序升序 ---------- */
    printf("=== ① 插入并验证中序升序 ===\n");
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    BSTNode *root = NULL;
    for (int i = 0; i < 7; i++) root = bstInsert(root, vals[i]);

    printf("  插入：50 30 70 20 40 60 80\n");
    printf("  中序遍历：");
    inorder(root);
    printf("\n  ⭐ 中序遍历 BST 得到升序序列 —— 这是 BST 最重要的性质。\n");

    /* 画出树 */
    printf("\n  树的形状：\n");
    printf("          50\n");
    printf("         /  \\\n");
    printf("       30    70\n");
    printf("      /  \\  /  \\\n");
    printf("     20  40 60  80\n");
    printf("  树的高度 = %d（平衡，log2(7)≈3）\n", height(root));

    /* ---------- ② 查找 ---------- */
    printf("\n=== ② 查找 ===\n");
    BSTNode *parent;
    BSTNode *found = bstSearch(root, 60, &parent);
    printf("  找 60：%s\n", found ? "找到" : "没找到");
    if (found) printf("    父节点是 %d\n", parent ? parent->data : -1);

    found = bstSearch(root, 99, &parent);
    printf("  找 99：%s\n", found ? "找到" : "没找到");

    printf("\n  ⭐ 查找的路径：50 → 70 → 60（比根大走右，比 70 小走左）\n");
    printf("     每比较一次，搜索范围减半 → O(深度)。\n");

    /* ---------- ③ 删除的三种情况 ---------- */
    printf("\n=== ③ 删除的三种情况 ===\n");

    printf("  情况 1（删叶子 20）：\n");
    root = bstDelete(root, 20);
    printf("    中序："); inorder(root); printf("\n");

    printf("  情况 2（删只有一个孩子的节点）：\n");
    /* 先插入一个只有一个孩子的节点 45（在 40 的右边） */
    root = bstInsert(root, 45);
    printf("    插入 45 后："); inorder(root); printf("\n");
    root = bstDelete(root, 40);         /* 40 现在有右孩子 45 */
    printf("    删 40 后："); inorder(root); printf("\n");

    printf("  情况 3（删有两个孩子的节点 50 根）：\n");
    root = bstDelete(root, 50);
    printf("    删 50 后："); inorder(root); printf("\n");
    printf("    ⭐ 用「右子树最小值」替代被删节点，中序仍保持升序 ✓\n");

    freeTree(root);

    /* ---------- ④ 复杂度：取决于高度 ---------- */
    printf("\n=== ④ BST 的致命缺陷：可能退化成斜树 ===\n");
    printf("  如果按升序插入 10 20 30 40 50：\n");
    printf("        10\n");
    printf("          \\\n");
    printf("           20\n");
    printf("             \\\n");
    printf("              30\n");
    printf("                \\\n");
    printf("                 40\n");
    printf("                   \\\n");
    printf("                    50\n");

    BSTNode *skew = NULL;
    for (int i = 10; i <= 50; i += 10) skew = bstInsert(skew, i);
    printf("  高度 = %d（= 节点数 5），退化成斜树\n", height(skew));
    freeTree(skew);

    printf("\n  ⭐ BST 的复杂度 = O(高度)：\n");
    printf("     平衡时：高度 ≈ log2(n) → O(log n)\n");
    printf("     退化成斜树：高度 = n → O(n)\n");
    printf("\n  📌 这就是为什么要「平衡二叉树（AVL）」「红黑树」——\n");
    printf("     保证高度始终是 O(log n)，查找才快。\n");

    printf("\n=== ⑤ BST vs 顺序查找 vs 二分查找 ===\n");
    printf("  %-14s %-14s %-14s %s\n", "", "查找", "插入", "删除");
    printf("  ----------------------------------------------------------\n");
    printf("  %-14s %-14s %-14s %s\n", "无序数组", "O(n)", "O(1)", "O(n)");
    printf("  %-14s %-14s %-14s %s\n", "有序数组", "O(log n)", "O(n)", "O(n)");
    printf("  %-14s %-14s %-14s %s\n", "BST(平衡)", "O(log n)", "O(log n)", "O(log n)");
    printf("  %-14s %-14s %-14s %s\n", "BST(退化)", "O(n)", "O(n)", "O(n)");
    printf("\n  ⭐ BST 的价值：查找、插入、删除【都是 O(log n)】（平衡时）。\n");
    printf("     有序数组查找快但插入慢，BST 三者兼顾。\n");

    return 0;
}
