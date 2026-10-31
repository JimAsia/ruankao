/* 202_huffman.c —— 哈夫曼树与哈夫曼编码（软考必考）
 *
 * 哈夫曼树：带权路径长度 WPL 最小的二叉树，用于数据压缩。
 *
 * 核心概念：
 *   WPL = 所有叶子节点的「权值 × 到根的路径长度」之和
 *
 * 构造算法（贪心）：
 *   每次取两个【权值最小】的节点，合并成一个新节点（权 = 两者之和），
 *   重复直到只剩一个根。
 *
 * 哈夫曼编码：
 *   左分支记 0，右分支记 1，从根到叶子的路径就是该字符的编码。
 *   频率高的字符编码短，频率低的编码长 → 平均编码最短。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct HTNode {
    int           weight;     /* 权值（出现频率） */
    struct HTNode *left;
    struct HTNode *right;
} HTNode;

/* 求 WPL：每个叶子的 权值 × 深度 */
static int wpl(HTNode *root, int depth)
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) {
        return root->weight * depth;        /* 叶子：权 × 深 */
    }
    return wpl(root->left, depth + 1) + wpl(root->right, depth + 1);
}

/* 打印哈夫曼编码：从根走，0 走左 1 走右 */
static void printCodes(HTNode *root, char *code, int depth)
{
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        printf("    权值 %-4d → %s\n", root->weight, code);
        return;
    }

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

/* 用数组做「每次取最小两个」—— 简化版哈夫曼构造 */
/* weights 数组，n 个权值。返回根。 */
static HTNode *buildHuffman(int weights[], int n)
{
    /* 把所有权值做成单节点，放进一个数组 */
    HTNode **nodes = (HTNode **)malloc(sizeof(HTNode *) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = (HTNode *)malloc(sizeof(HTNode));
        nodes[i]->weight = weights[i];
        nodes[i]->left = nodes[i]->right = NULL;
    }

    int count = n;
    while (count > 1) {
        /* 找两个最小的 */
        int min1 = 0, min2 = 1;
        if (nodes[min1]->weight > nodes[min2]->weight) {
            int t = min1; min1 = min2; min2 = t;
        }
        for (int i = 2; i < count; i++) {
            if (nodes[i]->weight < nodes[min1]->weight) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->weight < nodes[min2]->weight) {
                min2 = i;
            }
        }

        /* 合并成一个新节点 */
        HTNode *merged = (HTNode *)malloc(sizeof(HTNode));
        merged->weight = nodes[min1]->weight + nodes[min2]->weight;
        merged->left = nodes[min1];
        merged->right = nodes[min2];

        /* 用 min1 位置放新节点，min2 位置用最后一个顶替 */
        nodes[min1] = merged;
        nodes[min2] = nodes[count - 1];
        count--;
    }

    HTNode *root = nodes[0];
    free(nodes);
    return root;
}

static void freeTree(HTNode *root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    /* ---------- ① 经典例子：五个字符 ---------- */
    printf("=== ① 哈夫曼树构造 ===\n");
    int weights[] = {5, 32, 18, 7, 25};     /* 经典教材例子 */
    int n = 5;

    HTNode *root = buildHuffman(weights, n);

    printf("  权值：5, 32, 18, 7, 25\n");
    printf("  构造出的 WPL = %d\n", wpl(root, 0));

    printf("\n  哈夫曼编码（左 0 右 1）：\n");
    char code[64];
    printCodes(root, code, 0);

    printf("\n  ⭐ 观察：权值越大的字符，编码越短。\n");
    printf("     权值 32 的编码最短（出现最多，用最短码），\n");
    printf("     权值 5、7 的编码最长（出现少，用长码）。\n");

    /* ---------- ② WPL 的计算 ---------- */
    printf("\n=== ② WPL（带权路径长度）===\n");
    printf("  编码结果对应的深度：\n");
    printf("    权值 32 → 深度 1（编码 0）\n");
    printf("    权值 25 → 深度 2（编码 10）\n");
    printf("    权值 18 → 深度 3（编码 111）\n");
    printf("    权值 5  → 深度 4（编码 1100）\n");
    printf("    权值 7  → 深度 4（编码 1101）\n");
    printf("  WPL = 32*1 + 25*2 + 18*3 + 5*4 + 7*4\n");
    printf("      = 32 + 50 + 54 + 20 + 28 = 184\n");
    printf("  程序 = %d %s\n", wpl(root, 0),
           wpl(root, 0) == 184 ? "✓" : "✗");
    freeTree(root);

    printf("\n  ⭐ 另一个著名例子（教材常用）：\n");
    int w2[] = {2, 4, 5, 7};
    HTNode *r2 = buildHuffman(w2, 4);
    printf("  权值 2,4,5,7 的 WPL = %d\n", wpl(r2, 0));
    printf("  （答案是 35）\n");
    freeTree(r2);

    /* ---------- ③ 为什么哈夫曼编码能省空间 ---------- */
    printf("\n=== ③ 为什么哈夫曼编码能压缩 ===\n");
    printf("  假设 4 个字符出现频率：A 50%%, B 25%%, C 12.5%%, D 12.5%%\n");
    printf("  定长编码：每个字符 2 位\n");
    printf("    平均长度 = 2 位/字符\n");
    printf("  哈夫曼编码：\n");
    printf("    A(50%%)   → 0      （1 位）\n");
    printf("    B(25%%)   → 10     （2 位）\n");
    printf("    C(12.5%%) → 110    （3 位）\n");
    printf("    D(12.5%%) → 111    （3 位）\n");
    printf("    平均长度 = 0.5*1 + 0.25*2 + 0.125*3 + 0.125*3 = 1.75 位\n");
    printf("  ⭐ 2 位 → 1.75 位，节省了 12.5%%。\n");

    /* ---------- ④ 前缀码 ---------- */
    printf("\n=== ④ 哈夫曼编码是前缀码 ===\n");
    printf("  前缀码：任何一个编码都不是另一个编码的前缀。\n");
    printf("  例如上面：0 不是 10/110/111 的前缀，\n");
    printf("            10 不是 110/111 的前缀。\n");
    printf("\n  ⭐ 为什么必须是前缀码？\n");
    printf("     否则解码时无法判断边界。\n");
    printf("     例：0 和 01 就不是前缀码，\n");
    printf("     收到 01 不知道是一个 01，还是 0 后面跟 1。\n");
    printf("  📌 哈夫曼编码天然是前缀码（因为字符都在叶子上）。\n");

    /* ---------- ⑤ 软考考点 ---------- */
    printf("\n=== ⑤ 哈夫曼树的软考考点 ===\n");
    printf("  1. 给定权值，求 WPL（必须会手算）\n");
    printf("  2. 给定权值，写出哈夫曼编码\n");
    printf("  3. 哈夫曼树中「没有度为 1 的节点」（因为每次合并两个）\n");
    printf("  4. n 个叶子节点的哈夫曼树，总节点数 = 2n - 1\n");
    printf("  5. 哈夫曼编码是前缀码\n");
    printf("\n  ⭐ 第 3、4 条最容易考：\n");
    printf("     因为每次取两个合并成一个，净减少一个节点，\n");
    printf("     从 n 个叶子到 1 个根，共合并 n-1 次，\n");
    printf("     产生 n-1 个「度为 2 的内部节点」。\n");
    printf("     总节点 = n + (n-1) = 2n - 1。\n");

    return 0;
}
