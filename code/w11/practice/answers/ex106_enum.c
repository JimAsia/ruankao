/* ex106_enum.c —— 参考答案 */

#include <stdio.h>

enum Weekday {
    MON = 1, TUE, WED, THU, FRI, SAT, SUN
};

int main(void)
{
    int n;
    printf("请输入 1-7：");
    if (scanf("%d", &n) != 1) {
        printf("输入错误\n");
        return 1;
    }

    if (n < MON || n > SUN) {
        printf("输入错误（应为 1-7）\n");
        return 1;
    }

    enum Weekday w = (enum Weekday)n;       /* 整数转枚举 */

    /* 多个 case 共用一个分支：故意不写 break，让它穿透 */
    switch (w) {
        case MON:
        case TUE:
        case WED:
        case THU:
        case FRI:
            printf("%-4s 工作日\n", w == MON ? "MON" :
                                   w == TUE ? "TUE" :
                                   w == WED ? "WED" :
                                   w == THU ? "THU" : "FRI");
            break;
        case SAT:
            printf("SAT  休息日\n");
            break;
        case SUN:
            printf("SUN  休息日\n");
            break;
        default:
            printf("输入错误\n");
            break;
    }

    printf("\n数字对应：MON=1 TUE=2 WED=3 THU=4 FRI=5 SAT=6 SUN=7\n");
    printf("枚举值就是 %d 个整数，所以能直接和 n 比较\n", SUN);

    return 0;
}
