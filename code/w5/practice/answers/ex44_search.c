/* ex44 参考答案 —— 顺序查找 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0, key = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    printf("请输入要查找的数: ");
    if (scanf("%d", &key) != 1) return 1;

    /* -1 表示"没找到"，这是约定俗成的写法 */
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            pos = i;
            break;                  /* 找第一个就够了，找到就不用再扫 */
        }
    }

    if (pos != -1)
        printf("下标 = %d\n", pos);
    else
        printf("-1\n");

    /* 补充：如果要找"所有出现位置"，去掉 break 即可，但那样就不能用 pos 存了，
     * 得一边扫一边打印（见 43_array_search.c 的第 ② 段）。 */

    return 0;
}
