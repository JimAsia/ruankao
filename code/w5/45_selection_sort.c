/* 45_selection_sort.c —— 选择排序
 *
 * 思路：每轮从未排序部分选出最小的，与该轮的首位交换。
 * 和冒泡的区别：冒泡是"边比边换"，选择是"先找到最小的，最后换一次"。
 */
#include <stdio.h>

int main(void)
{
    int a[8] = {72, 45, 91, 38, 66, 88, 55, 79};
    int n = 8;
    int swaps = 0;                  /* 统计交换次数 */

    printf("排序前：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n\n");

    for (int i = 0; i < n - 1; i++) {
        /* ① 在 [i, n-1] 这一段里找最小值的下标 */
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIdx]) {
                minIdx = j;
            }
        }

        /* ② 如果最小值不在 i 位置，就交换 */
        if (minIdx != i) {
            int t = a[i];
            a[i] = a[minIdx];
            a[minIdx] = t;
            swaps++;
            printf("第 %d 轮：把 %d 换到下标 %d（交换 1 次）\n", i + 1, a[i], i);
        } else {
            printf("第 %d 轮：%d 已经是最小，不用换\n", i + 1, a[i]);
        }

        printf("         当前：");
        for (int k = 0; k < n; k++) printf("%d ", a[k]);
        printf("\n");
    }

    printf("\n排序结果：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* ---------- 冒泡 vs 选择 ---------- */
    printf("\n=== 冒泡 vs 选择 ===\n");
    printf("  选择排序总共只交换了 %d 次\n", swaps);
    printf("  冒泡排序同样 8 个数，交换次数通常要多得多\n");
    printf("  原因：冒泡每发现一次逆序就换一次；选择每轮最多只换一次\n");

    printf("\n  复杂度对比：\n");
    printf("    比较次数：两者都是 n(n-1)/2 ≈ O(n²)\n");
    printf("    交换次数：冒泡最坏 O(n²)，选择固定 O(n)\n");
    printf("    稳定性  ：冒泡【稳定】，选择【不稳定】\n");

    /* ---------- 为什么选择排序不稳定 ---------- */
    printf("\n=== 为什么选择排序不稳定 ===\n");
    printf("  假设原数组：5a 5b 3 8 1     （5a、5b 是两个相等的值）\n");
    printf("  第 1 轮：最小是 1（下标 4），和下标 0 的 5a 交换\n");
    printf("          变成：1 5b 3 8 5a\n");
    printf("  看到了吗：5a 跑到了 5b 后面 —— 相等元素的相对次序被改变了\n");
    printf("  这就是「不稳定」的含义\n");

    return 0;
}
