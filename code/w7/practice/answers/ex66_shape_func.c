/* ex66 参考答案 —— 用函数打印图形 */
#include <stdio.h>

void printTriangle(int n)
{
    for (int i = 1; i <= n; i++) {          /* 第 i 行 */
        for (int j = 1; j <= i; j++) {      /* 打 i 个星 */
            printf("*");
        }
        printf("\n");                       /* ⚠️ 每行必须换行 */
    }
}

void printDiamond(int n)
{
    /* 上半部分：等腰三角形，i 从 1 到 n */
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n - i; k++) printf(" ");     /* 空格 */
        for (int j = 1; j <= 2 * i - 1; j++) printf("*"); /* 星号 */
        printf("\n");
    }

    /* 下半部分：倒过来的等腰三角形，i 从 n-1 递减到 1 */
    for (int i = n - 1; i >= 1; i--) {
        for (int k = 1; k <= n - i; k++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }

    /* ⚠️ 下半部分从 n-1 开始，不是 n
     *    从 n 开始的话，中间那一行会被打印两次，菱形就变成"双腰"了。 */
}

int main(void)
{
    int n = 0;

    printf("请输入行数: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入格式不对\n");
        return 1;
    }

    printf("\n直角三角形：\n");
    printTriangle(n);

    printf("\n菱形：\n");
    printDiamond(n);

    /* 两个函数都不需要返回值（void），因为它们的作用就是"打印"，
     * 不需要把结果交给调用者。
     *
     * 判断该不该有返回值：
     *   需要把结果交回去 → 有返回值（如 sumArray）
     *   只是做事/输出   → void（如 printTriangle） */

    return 0;
}
