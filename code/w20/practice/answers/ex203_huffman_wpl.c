/* ex203_huffman_wpl.c —— 参考答案 */

#include <stdio.h>
#include <stdlib.h>

typedef struct HTNode {
    int           weight;
    struct HTNode *left;
    struct HTNode *right;
} HTNode;

HTNode *buildHuffman(int weights[], int n)
{
    /* 把每个权值做成单节点 */
    HTNode **nodes = (HTNode **)malloc(sizeof(HTNode *) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = (HTNode *)malloc(sizeof(HTNode));
        nodes[i]->weight = weights[i];
        nodes[i]->left = nodes[i]->right = NULL;
    }

    int count = n;
    while (count > 1) {
        /* 找两个最小的 */
        int m1 = 0, m2 = 1;
        if (nodes[m1]->weight > nodes[m2]->weight) { int t = m1; m1 = m2; m2 = t; }
        for (int i = 2; i < count; i++) {
            if (nodes[i]->weight < nodes[m1]->weight) { m2 = m1; m1 = i; }
            else if (nodes[i]->weight < nodes[m2]->weight) { m2 = i; }
        }

        /* 合并 */
        HTNode *merged = (HTNode *)malloc(sizeof(HTNode));
        merged->weight = nodes[m1]->weight + nodes[m2]->weight;
        merged->left = nodes[m1];
        merged->right = nodes[m2];

        /* m1 放新节点，m2 用末尾顶替 */
        nodes[m1] = merged;
        nodes[m2] = nodes[count - 1];
        count--;
    }

    HTNode *root = nodes[0];
    free(nodes);
    return root;
}

int wpl(HTNode *root, int depth)
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) {
        return root->weight * depth;        /* 叶子：权 × 深度 */
    }
    return wpl(root->left, depth + 1) + wpl(root->right, depth + 1);
}

static void freeTree(HTNode *root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    printf("=== 测试 1：{2, 4, 5, 7} ===\n");
    int w1[] = {2, 4, 5, 7};
    HTNode *r1 = buildHuffman(w1, 4);
    printf("  WPL = %d（期望 35）\n", wpl(r1, 0));
    freeTree(r1);

    printf("\n=== 测试 2：{5, 32, 18, 7, 25} ===\n");
    int w2[] = {5, 32, 18, 7, 25};
    HTNode *r2 = buildHuffman(w2, 5);
    printf("  WPL = %d（期望 184）\n", wpl(r2, 0));
    freeTree(r2);

    printf("\n=== WPL 的手算方法 ===\n");
    printf("  ① 每次取两个最小的合并，画出哈夫曼树\n");
    printf("  ② 每个叶子：权值 × 到根的边数\n");
    printf("  ③ 全部加起来\n");
    printf("  ⭐ WPL 越小，平均编码越短，压缩效果越好。\n");

    printf("\n=== 为什么哈夫曼树 WPL 最小 ===\n");
    printf("  贪心策略：频率高的（权值大）放在离根近的地方（深度小），\n");
    printf("  频率低的放在离根远的地方。\n");
    printf("  这样「权值 × 深度」的总和最小。\n");
    printf("  📌 这是「贪心算法」的经典例子，W26 会正式讲贪心。\n");

    printf("\n=== 构造细节 ===\n");
    printf("  找两个最小：可以用最小堆 O(n log n)，\n");
    printf("  本实现用线性扫描 O(n^2)（n 小，够用）。\n");
    printf("  软考只考「手算 WPL」和「画出树」，不考代码细节。\n");

    return 0;
}
