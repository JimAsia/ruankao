/* 43_array_search.c —— 查找、删除、插入
 *
 * 删除和插入的核心动作都是"移动元素"，这是软考应用技术的常见考点。
 */
#include <stdio.h>

int main(void)
{
    int a[10] = {15, 28, 37, 42, 58, 63, 71};
    int n = 7;                  /* 当前有效元素个数（数组容量是 10） */

    printf("初始数组（%d 个）：", n);
    for (int k = 0; k < n; k++) printf("%d ", a[k]);
    printf("\n");

    /* ---------- ① 顺序查找：找第一个匹配 ---------- */
    printf("\n=== ① 顺序查找 ===\n");
    int target = 42;
    int pos = -1;               /* ⚠️ -1 表示"没找到" */
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            pos = i;
            break;              /* 找到第一个就够了 */
        }
    }
    if (pos != -1)
        printf("  查找 %d → 找到，下标 %d\n", target, pos);
    else
        printf("  查找 %d → 未找到\n", target);

    /* ---------- ② 查找所有出现的位置 ---------- */
    printf("\n=== ② 查找全部匹配 ===\n");
    int b[8] = {5, 3, 5, 7, 5, 9, 1, 5};
    int m = 8;
    int key = 5;
    int count = 0;

    printf("  数组：");
    for (int i = 0; i < m; i++) printf("%d ", b[i]);
    printf("\n  查找 %d 出现的所有位置：", key);
    for (int i = 0; i < m; i++) {
        if (b[i] == key) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\n  共出现 %d 次\n", count);
    printf("  注意：这里不能 break，必须扫完整个数组\n");

    /* ---------- ③ 删除下标为 k 的元素 ---------- */
    printf("\n=== ③ 删除元素 ===\n");
    int k = 2;
    printf("  要把下标 %d 的元素 %d 删掉\n", k, a[k]);
    printf("  删除前：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* 把 k 之后的元素全部前移一位，覆盖掉要删的那个 */
    for (int i = k; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    n--;                        /* 有效元素个数减一 */

    printf("  删除后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    printf("  ⚠️ 原来最后一个位置还留着旧值，但它已经不算有效数据了\n");
    printf("  删除 = 后面所有元素前移 + 长度减 1\n");
    printf("  代价：最坏要移动 n 个元素，所以顺序表删除是 O(n)\n");

    /* ---------- ④ 在下标 k 处插入元素 ---------- */
    printf("\n=== ④ 插入元素 ===\n");
    int insertPos = 3;
    int newVal = 99;
    printf("  在下标 %d 处插入 %d\n", insertPos, newVal);
    printf("  插入前：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* ⚠️ 必须从后往前移！从前往后会覆盖掉还没搬走的数据 */
    for (int i = n; i > insertPos; i--) {
        a[i] = a[i - 1];
    }
    a[insertPos] = newVal;
    n++;

    printf("  插入后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    printf("  插入 = 从末尾往前依次后移 + 填空 + 长度加 1\n");
    printf("  ⚠️ 顺序不能反：从前往后移会把 a[3] 覆盖成 a[4]，数据就丢了\n");

    return 0;
}
