/* 42_array_ops.c —— 数组的五个基本操作
 *
 * 这些操作就是 W4 的四大范式换了个数据来源：
 * 以前是"边算边用"，现在是从数组里取。
 */
#include <stdio.h>

int main(void)
{
    int a[8] = {72, 45, 91, 38, 66, 88, 55, 79};
    int n = sizeof(a) / sizeof(a[0]);

    printf("数组：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n长度：%d\n", n);

    /* ---------- ① 求和与平均 ---------- */
    printf("\n=== ① 求和与平均 ===\n");
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    printf("  总和 = %d\n", sum);
    printf("  平均 = %.2f\n", (double)sum / n);

    /* ---------- ② 求最大值及其下标 ---------- */
    printf("\n=== ② 最值（打擂台）===\n");
    int max = a[0];             /* ✅ 用第一个元素初始化，最稳妥 */
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {       /* 从 1 开始，a[0] 已经当过擂主了 */
        if (a[i] > max) {
            max = a[i];
            maxIdx = i;         /* 顺便记住位置 */
        }
    }
    printf("  最大值 = %d，在下标 %d\n", max, maxIdx);

    int min = a[0];
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
            minIdx = i;
        }
    }
    printf("  最小值 = %d，在下标 %d\n", min, minIdx);

    /* ---------- ③ 计数：统计及格的个数 ---------- */
    printf("\n=== ③ 计数 ===\n");
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= 60) cnt++;
    }
    printf("  及格的（>=60）有 %d 个\n", cnt);

    /* ---------- ④ 顺序查找 ---------- */
    printf("\n=== ④ 顺序查找 ===\n");
    int target = 66;
    int pos = -1;               /* ⚠️ 初值 -1 表示"没找到" */
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            pos = i;
            break;              /* 找到就停 */
        }
    }
    if (pos != -1)
        printf("  %d 在下标 %d\n", target, pos);
    else
        printf("  %d 不存在\n", target);

    target = 100;
    pos = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == target) { pos = i; break; }
    }
    if (pos != -1)
        printf("  %d 在下标 %d\n", target, pos);
    else
        printf("  %d 不存在（返回 -1 表示没找到）\n", target);

    /* ---------- ⑤ 逆序：首尾交换 ---------- */
    printf("\n=== ⑤ 逆序 ===\n");
    printf("  逆序前：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* 关键：i < n/2。如果写成 i < n，会交换两次，等于白干 */
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    printf("  逆序后：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    printf("  只走 n/2 轮就够了：每轮同时处理首尾两个元素\n");

    return 0;
}
