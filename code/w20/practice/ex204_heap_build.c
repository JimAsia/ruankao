/* ex204_heap_build.c —— 建堆 + 堆排序
 *
 * 要求：
 *   1. siftDown(a, i, n)：向下调整
 *   2. buildHeap(a, n)：建大顶堆
 *   3. heapSort(a, n)：堆排序（升序）
 *
 * 测试：
 *   数组 {49, 38, 65, 97, 76, 13, 27, 49}
 *   建堆后堆顶应是 97
 *   排序后应是升序 13 27 38 49 49 65 76 97
 *
 * 提示：
 *   向下调整：找左右孩子中较大的，比自己大就交换下沉
 *   建堆：从 n/2 到 1 逐个向下调整
 *   排序：堆顶换末尾，再向下调整
 *   ⚠️ 下标从 1 开始，0 号位不用
 */

#include <stdio.h>

#define MAXN 100

/* TODO 1：向下调整 */
void siftDown(int a[], int i, int n)
{
    (void)a; (void)i; (void)n;
}

/* TODO 2：建堆 */
void buildHeap(int a[], int n)
{
    (void)a; (void)n;
}

/* TODO 3：堆排序 */
void heapSort(int a[], int n)
{
    (void)a; (void)n;
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
    int raw[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};  /* 0 号占位 */
    int n = 8;

    /* TODO 4：建堆，输出，验证堆顶是 97 */

    /* TODO 5：排序，输出 */

    return 0;
}
