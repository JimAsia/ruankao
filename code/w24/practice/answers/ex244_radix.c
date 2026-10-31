/* ex244_radix.c —— 参考答案 */

#include <stdio.h>

#define N 10

void radixSort(int a[], int n)
{
    int maxVal = a[0];
    for (int i = 1; i < n; i++) if (a[i] > maxVal) maxVal = a[i];

    int tmp[N];

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        int bucket[10] = {0};

        /* ① 统计各桶个数 */
        for (int i = 0; i < n; i++) bucket[(a[i] / exp) % 10]++;

        printf("  exp=%-4d 桶个数：", exp);
        for (int b = 0; b < 10; b++) printf("%d ", bucket[b]);
        printf("\n");

        /* ② 累加，得到每个桶的结束位置 */
        for (int b = 1; b < 10; b++) bucket[b] += bucket[b - 1];

        /* ③ 从后往前放（保证稳定） */
        for (int i = n - 1; i >= 0; i--) {
            int d = (a[i] / exp) % 10;
            tmp[--bucket[d]] = a[i];
        }

        /* ④ 拷回 */
        for (int i = 0; i < n; i++) a[i] = tmp[i];

        printf("          本趟：");
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }
}

int main(void)
{
    int a[N] = {329, 457, 657, 839, 436, 720, 355, 123, 90, 5};

    printf("=== 原始 ===\n  ");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("\n\n");

    radixSort(a, N);

    printf("\n=== 结果 ===\n  ");
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    printf("\n  期望：5 90 123 329 355 436 457 657 720 839\n");

    printf("\n=== 三趟的意义 ===\n");
    printf("  exp=1  （个位）：按个位排\n");
    printf("  exp=10 （十位）：按十位排，个位的顺序作为「次要关键字」保留\n");
    printf("  exp=100（百位）：按百位排，十位和个位的顺序作为次要关键字保留\n");
    printf("  ⭐ 从低位到高位，每一趟都把上一趟的结果当成「稳定」的基础。\n");

    printf("\n=== 为什么必须稳定 ===\n");
    printf("  假设十位相同时，个位的顺序被打乱了，\n");
    printf("  那百位排完后，同百位同十位的元素个位就乱了 → 结果错。\n");
    printf("  ⭐ 所以基数排序【必须是稳定排序】，这不是可选项。\n");

    printf("\n=== 复杂度 ===\n");
    printf("  时间 O(d(n+r))，d = 位数（本例 3），r = 基数（10）\n");
    printf("  空间 O(n+r)\n");
    printf("  ⭐ d 是常数时是【线性】O(n)。\n");
    printf("     比较排序的下界 O(n log n)，基数排序能突破是因为它不比较。\n");

    printf("\n=== 适用条件 ===\n");
    printf("  ✅ 整数、位数不多\n");
    printf("  ❌ 浮点数（要特殊处理）\n");
    printf("  ❌ 有负数（要分离正负）\n");
    printf("  ❌ 位数差异极大\n");

    return 0;
}
