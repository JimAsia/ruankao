/* ex41 参考答案 —— 输入、输出、求和、平均 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) {
        printf("个数必须在 1~20 之间\n");
        return 1;
    }

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("输入格式不对\n");
            return 1;
        }
    }

    printf("数组：");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* 累加范式，换成从数组里取数 */
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    printf("总和 = %d\n", sum);
    printf("平均 = %.2f\n", (double)sum / n);

    return 0;
}
