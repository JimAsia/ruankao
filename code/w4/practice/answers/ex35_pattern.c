/* ex35 参考答案 —— 打印图案 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    printf("请输入行数: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入格式不对\n");
        return 1;
    }

    /* ---------- 正三角形（左对齐） ---------- */
    printf("\n正三角：\n");
    for (int i = 1; i <= n; i++) {      /* 外层：第几行 */
        for (int j = 1; j <= i; j++) {  /* 内层：这行打几个 */
            printf("*");
        }
        printf("\n");                   /* ⚠️ 每行结束必须换行 */
    }

    /* ---------- 倒三角形 ---------- */
    printf("\n倒三角：\n");
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    /* ---------- 等腰三角形（前面补空格） ---------- */
    printf("\n等腰三角：\n");
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n - i; k++) {      /* 先打空格 */
            printf(" ");
        }
        for (int j = 1; j <= 2 * i - 1; j++) {  /* 再打星号 */
            printf("*");
        }
        printf("\n");
    }
    /* 规律：第 i 行前面有 n-i 个空格，有 2i-1 个星号 */

    /* ---------- 菱形（上半 + 下半） ---------- */
    printf("\n菱形：\n");
    for (int i = 1; i <= n; i++) {              /* 上半部分 */
        for (int k = 1; k <= n - i; k++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }
    for (int i = n - 1; i >= 1; i--) {          /* 下半部分（倒着来） */
        for (int k = 1; k <= n - i; k++) printf(" ");
        for (int j = 1; j <= 2 * i - 1; j++) printf("*");
        printf("\n");
    }

    return 0;
}
