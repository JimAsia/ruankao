/* 204_balanced_tree.c —— 平衡二叉树（AVL）与树的存储、线索
 *
 * 三个软考选择题高频内容：
 *   ① 平衡二叉树 AVL：高度差 <= 1，保证 O(log n)
 *   ② 二叉树的顺序存储：完全二叉树能高效存，一般树会浪费空间
 *   ③ 线索二叉树：利用空指针，加快遍历
 *
 * 本文件用「高度差」判断一棵树是否平衡，并演示顺序存储的空间浪费。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    int          data;
    struct TNode *left;
    struct TNode *right;
} TNode;

static TNode *make(int v, TNode *l, TNode *r)
{
    TNode *n = (TNode *)malloc(sizeof(TNode));
    if (!n) return NULL;
    n->data = v;
    n->left = l;
    n->right = r;
    return n;
}

/* 求高度 */
static int height(TNode *root)
{
    if (root == NULL) return 0;
    int hl = height(root->left);
    int hr = height(root->right);
    return (hl > hr ? hl : hr) + 1;
}

/* 判断是否平衡：每个节点左右子树高度差 <= 1 */
static int isBalanced(TNode *root)
{
    if (root == NULL) return 1;
    int hl = height(root->left);
    int hr = height(root->right);
    if (hl - hr > 1 || hr - hl > 1) return 0;
    return isBalanced(root->left) && isBalanced(root->right);
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
    /* ---------- ① 平衡 vs 不平衡 ---------- */
    printf("=== ① 平衡二叉树（AVL）===\n");
    printf("  定义：任意节点左右子树的高度差 <= 1。\n\n");

    /* 平衡树 */
    TNode *a = make(50,
                    make(30, make(20, NULL, NULL), make(40, NULL, NULL)),
                    make(70, make(60, NULL, NULL), make(80, NULL, NULL)));
    printf("  平衡树：高度差 <= 1，高度 = %d，是否平衡？%s\n",
           height(a), isBalanced(a) ? "是 ✓" : "否 ✗");

    /* 不平衡树（右斜） */
    TNode *b = make(10, NULL, make(20, NULL, make(30, NULL,
                       make(40, NULL, NULL))));
    printf("  斜树：高度差 = 3，是否平衡？%s\n", isBalanced(b) ? "是" : "否 ✗");

    freeTree(a);
    freeTree(b);

    printf("\n  ⭐ 为什么要平衡？\n");
    printf("     平衡树的查找是 O(log n)，不平衡的斜树退化到 O(n)。\n");
    printf("     AVL 树通过「旋转」保持平衡，保证查找稳定 O(log n)。\n");

    printf("\n  AVL 的四种旋转（软考常考，要会画）：\n");
    printf("    LL 型：右旋一次\n");
    printf("    RR 型：左旋一次\n");
    printf("    LR 型：先左旋后右旋（两步）\n");
    printf("    RL 型：先右旋后左旋（两步）\n");
    printf("  📌 判断是哪种：看「失衡节点」往「插入方向」走两步。\n");

    /* ---------- ② 顺序存储 ---------- */
    printf("\n=== ② 二叉树的顺序存储 ===\n");
    printf("  完全二叉树用数组存，下标规律：左孩子 2i，右孩子 2i+1。\n");
    printf("\n  完全二叉树：\n");
    printf("        A\n");
    printf("       / \\\n");
    printf("      B   C\n");
    printf("     / \\\n");
    printf("    D   E\n");
    printf("  数组：[A, B, C, D, E]  5 个位置全用上，无浪费。\n");

    printf("\n  一般的树（非完全）：\n");
    printf("        A\n");
    printf("       /\n");
    printf("      B\n");
    printf("     /\n");
    printf("    C\n");
    printf("  数组：[A, B, 空, C, 空, 空, 空]  ← 3 个节点用了 7 个位置！\n");
    printf("\n  ⭐ 最坏情况（斜树），n 个节点要 2^n - 1 个位置。\n");
    printf("     所以顺序存储【只适合完全二叉树】。\n");
    printf("     📌 这就是为什么「堆」必须是完全二叉树 —— 为了能用数组存。\n");

    /* ---------- ③ 线索二叉树 ---------- */
    printf("\n=== ③ 线索二叉树 ===\n");
    printf("  二叉树的 n 个节点有 2n 个指针，其中 n+1 个是空的。\n");
    printf("  线索二叉树：利用这些空指针，指向「前驱/后继」，加快遍历。\n");
    printf("\n  空指针数量 = n + 1（软考必记）\n");
    printf("  推导：n 个节点有 2n 个指针域，n-1 条边用了 n-1 个指针，\n");
    printf("        剩余 2n - (n-1) = n+1 个空指针。\n");

    printf("\n  线索的类型：\n");
    printf("    前驱线索：左空指针 → 指向中序前驱\n");
    printf("    后继线索：右空指针 → 指向中序后继\n");
    printf("\n  ⭐ 线索化的好处：中序遍历不用栈/递归，直接沿线索走。\n");

    /* ---------- ④ 树、森林、二叉树 ---------- */
    printf("\n=== ④ 树、森林、二叉树的转换（软考常考）===\n");
    printf("  任何树都能转成二叉树（左孩子右兄弟表示法）：\n");
    printf("    节点的第一个孩子 → 左孩子\n");
    printf("    节点的下一个兄弟 → 右孩子\n");
    printf("\n  森林 = 多棵树的集合，转成二叉树同理。\n");
    printf("  📌 这是「树/森林」和「二叉树」互转的桥梁，\n");
    printf("     也是很多树算法的实现基础。\n");

    /* ---------- ⑤ 汇总表 ---------- */
    printf("\n=== ⑤ 二叉树家族总结 ===\n");
    printf("  %-18s %-20s %s\n", "类型", "特点", "查找复杂度");
    printf("  ----------------------------------------------------------------------\n");
    printf("  %-18s %-20s %s\n", "普通二叉树", "无约束", "O(n) 最坏");
    printf("  %-18s %-20s %s\n", "二叉排序树 BST", "左<根<右", "O(log n)~O(n)");
    printf("  %-18s %-20s %s\n", "平衡二叉树 AVL", "高度差<=1", "O(log n) 稳定");
    printf("  %-18s %-20s %s\n", "哈夫曼树", "WPL 最小", "—");
    printf("  %-18s %-20s %s\n", "堆", "完全二叉树+堆序", "取最大 O(1)");

    return 0;
}
