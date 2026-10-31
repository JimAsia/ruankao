/* ex231_insertion.c —— 参考答案 */

#include <stdio.h>

#define N 8

static long long g_cmp = 0;

void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0) {
            g_cmp++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;

        printf("  第 %d 趟后：", i);
        for (int k = 0; k < n; k++) printf("%d ", a[k]);
        printf("\n");
    }
}

int main(void)
{
    int a[N] = {49, 38, 65, 97, 76, 13, 27, 49};

    printf("=== 直接插入排序 ===\n  原始：");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("\n\n");

    insertionSort(a, N);

    printf("\n  比较 %lld 次\n", g_cmp);

    printf("\n=== 观察每趟结果 ===\n");
    printf("  ⭐ 每趟结束后，【前 i+1 个元素】是局部有序的：\n");
    printf("     第 1 趟后：前 2 个有序\n");
    printf("     第 2 趟后：前 3 个有序\n");
    printf("     ...\n");
    printf("  ⚠️ 但「局部有序」不等于「在最终位置」——\n");
    printf("     后面的元素插进来时，它们还会被挤动。\n");

    printf("\n=== 关键点 ===\n");
    printf("  1. 数据已有序时只比较 n-1 次 → O(n)\n");
    printf("  2. 稳定：只和相邻元素比，相等时不交换（用 > 而不是 >=）\n");
    printf("  3. 空间 O(1)\n");
    printf("  4. 适合：n 小、或数据基本有序\n");

    return 0;
}
