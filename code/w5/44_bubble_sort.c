/* 44_bubble_sort.c —— 冒泡排序
 *
 * 思路：相邻两两比较，大的往后冒。
 * 每一轮结束，当前未排序部分的最大值就被送到了末尾。
 */
#include <stdio.h>

int main(void)
{
    int a[8] = {72, 45, 91, 38, 66, 88, 55, 79};
    int n = 8;

    printf("排序前：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n\n");

    /* ---------- 标准冒泡 ---------- */
    /* 外层 i：第几轮，最多 n-1 轮（最后一个元素自然就位） */
    /* 内层 j：每轮比较到哪里，末尾 i 个已经有序，不用再比 */
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {              /* 前一个比后一个大，交换 */
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }

        printf("第 %d 轮后：", i + 1);
        for (int k = 0; k < n; k++) printf("%d ", a[k]);
        printf("\n");
    }

    printf("\n排序结果：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* ---------- 两个边界为什么这样写 ---------- */
    printf("\n=== 两个边界的原因 ===\n");
    printf("  外层 i < n-1：\n");
    printf("    n 个元素最多比较 n-1 轮，最后一轮剩下一个元素自然就位\n");
    printf("  内层 j < n-1-i：\n");
    printf("    末尾已经有 i 个元素排好且是最大的，不用再碰\n");
    printf("    第 0 轮比 n-1 次，第 1 轮比 n-2 次……总数 = n(n-1)/2，即 O(n²)\n");

    /* ---------- 优化：某轮没交换就说明已经有序 ---------- */
    printf("\n=== 优化版：提前结束 ===\n");
    int b[6] = {12, 25, 33, 47, 58, 69};    /* 已经有序的数组 */
    int m = 6, rounds = 0, swapped;

    for (int i = 0; i < m - 1; i++) {
        swapped = 0;                         /* 本轮是否发生过交换 */
        rounds++;

        for (int j = 0; j < m - 1 - i; j++) {
            if (b[j] > b[j + 1]) {
                int t = b[j];
                b[j] = b[j + 1];
                b[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break;                 /* 一次都没换，说明已经有序 */
    }
    printf("  已有序的数组，加优化后只跑了 %d 轮（没有优化要跑 5 轮）\n", rounds);
    printf("  这就是冒泡排序最好情况是 O(n) 的原因\n");

    return 0;
}
