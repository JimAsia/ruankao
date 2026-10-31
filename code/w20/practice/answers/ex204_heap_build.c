/* ex204_heap_build.c —— 参考答案 */

#include <stdio.h>

#define MAXN 100

void siftDown(int a[], int i, int n)
{
    while (1) {
        int largest = i;
        int left  = 2 * i;
        int right = 2 * i + 1;

        if (left  <= n && a[left]  > a[largest]) largest = left;
        if (right <= n && a[right] > a[largest]) largest = right;

        if (largest == i) break;            /* 比两个孩子都大，停 */

        int t = a[i];
        a[i] = a[largest];
        a[largest] = t;

        i = largest;                        /* 继续下沉 */
    }
}

void buildHeap(int a[], int n)
{
    for (int i = n / 2; i >= 1; i--) {      /* 从最后一个非叶子开始 */
        siftDown(a, i, n);
    }
}

void heapSort(int a[], int n)
{
    buildHeap(a, n);

    for (int i = n; i > 1; i--) {
        int t = a[1];                       /* 堆顶（最大）换到末尾 */
        a[1] = a[i];
        a[i] = t;

        siftDown(a, 1, i - 1);              /* 恢复堆 */
    }
}

void show(const char *label, const int a[], int n)
{
    printf("  %-14s [", label);
    for (int i = 1; i <= n; i++) {
        printf("%d", a[i]);
        if (i != n) printf(" ");
    }
    printf("]\n");
}

int main(void)
{
    int a[MAXN];
    int raw[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
    int n = 8;

    /* 建堆 */
    for (int i = 1; i <= n; i++) a[i] = raw[i];
    show("原始数组", a, n);
    buildHeap(a, n);
    show("建堆后", a, n);
    printf("  堆顶 = %d（应该是最大值 97）\n", a[1]);

    /* 排序 */
    for (int i = 1; i <= n; i++) a[i] = raw[i];
    heapSort(a, n);
    show("排序后(升序)", a, n);
    printf("  期望：13 27 38 49 49 65 76 97\n");

    printf("\n=== 建堆为什么从 n/2 开始 ===\n");
    printf("  下标 > n/2 的节点都是叶子，没有孩子，不用调整。\n");
    printf("  n=8 时，n/2=4，从下标 4 往前到 1 逐个向下调整。\n");

    printf("\n=== 堆排序三步 ===\n");
    printf("  ① 建堆 O(n)\n");
    printf("  ② 堆顶和末尾交换（最大到末尾）\n");
    printf("  ③ 向下调整恢复堆\n");
    printf("  重复 ②③ n-1 次，每次 O(log n)\n");
    printf("  ⭐ 总复杂度 O(n log n)\n");

    printf("\n=== 堆排序 vs 其他 ===\n");
    printf("  优势：空间 O(1)，最坏也是 O(n log n)\n");
    printf("  劣势：不稳定，常数大\n");
    printf("  📌 软考常问：堆排序的空间复杂度是 O(1)。\n");

    return 0;
}
