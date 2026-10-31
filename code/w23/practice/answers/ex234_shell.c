/* ex234_shell.c —— 参考答案 */

#include <stdio.h>

#define N 10

static long long g_cmp = 0;

void shellSort(int a[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = a[i];
            int j = i - gap;
            while (j >= 0) {
                g_cmp++;
                if (a[j] > key) { a[j + gap] = a[j]; j -= gap; }
                else break;
            }
            a[j + gap] = key;
        }

        printf("  gap=%-3d 后：", gap);
        for (int k = 0; k < n; k++) printf("%d ", a[k]);
        printf("\n");
    }
}

static void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            g_cmp++;
            if (a[j] > key) { a[j + 1] = a[j]; j--; }
            else break;
        }
        a[j + 1] = key;
    }
}

int main(void)
{
    int src[N] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
    int work[N];

    printf("=== 希尔排序过程 ===\n  原始：");
    for (int i = 0; i < N; i++) printf("%d ", src[i]);
    printf("\n\n");

    for (int i = 0; i < N; i++) work[i] = src[i];
    g_cmp = 0;
    shellSort(work, N);
    long long c1 = g_cmp;

    printf("\n  比较 %lld 次\n", c1);

    printf("\n=== 直接插入排序对照 ===\n");
    for (int i = 0; i < N; i++) work[i] = src[i];
    g_cmp = 0;
    insertionSort(work, N);
    printf("  比较 %lld 次\n", g_cmp);

    printf("\n  ⭐ 希尔 %lld 次 < 插入 %lld 次\n", c1, g_cmp);
    printf("     差距在 n 更大时更明显（n=10000 时可能差一倍以上）。\n");

    printf("\n=== 观察每趟 ===\n");
    printf("  gap=5 时：把数组分成 5 组（下标 0-5、1-6、...），组内插入排序\n");
    printf("  gap=2 时：分成 2 组，组内插入排序\n");
    printf("  gap=1 时：就是普通插入排序，但此时已接近有序，几乎不用挪\n");
    printf("  ⭐ 这就是「先粗调再细调」的思想。\n");

    printf("\n=== 结论 ===\n");
    printf("  1. 复杂度约 O(n^1.3)，不是 O(n log n)\n");
    printf("  2. 空间 O(1)\n");
    printf("  3. 不稳定\n");
    printf("  ⚠️ 增量最后必须是 1，否则不保证有序\n");
    printf("  📌 软考问「希尔排序的复杂度」→ 答 O(n^1.3)（不要说 O(n log n)）。\n");

    return 0;
}
