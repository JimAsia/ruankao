/* ex245_sort_choice.c —— 排序算法的选择（场景题）
 *
 * 要求：下面 8 个场景，各选哪种排序最合适？把答案填进字符串，然后运行看解析。
 *
 * 场景 1：n=20 的小数组，要求简单不易错
 * 场景 2：数据基本有序，只有几个元素错位
 * 场景 3：要求稳定，且 n=100000
 * 场景 4：内存极度紧张，n=100000
 * 场景 5：一般情况，要求平均最快
 * 场景 6：对链表排序
 * 场景 7：全是 0~999 的整数，n=1000000
 * 场景 8：找 n 个数里的第 k 小，不要求整体有序
 *
 * 提示：
 *   考虑：n 大小、数据是否基本有序、是否要求稳定、空间限制、数据类型
 */

#include <stdio.h>

int main(void)
{
    /* TODO 1：填 8 个答案 */
    const char *a1 = "?";
    const char *a2 = "?";
    const char *a3 = "?";
    const char *a4 = "?";
    const char *a5 = "?";
    const char *a6 = "?";
    const char *a7 = "?";
    const char *a8 = "?";

    printf("=== 场景 → 算法 ===\n");
    printf("  1. n=20 小数组         → %s\n", a1);
    printf("  2. 基本有序            → %s\n", a2);
    printf("  3. 要求稳定 n=100000   → %s\n", a3);
    printf("  4. 内存紧张            → %s\n", a4);
    printf("  5. 一般情况最快        → %s\n", a5);
    printf("  6. 链表排序            → %s\n", a6);
    printf("  7. 0~999 的整数        → %s\n", a7);
    printf("  8. 第 k 小             → %s\n", a8);

    return 0;
}
