/* ex07 参考答案 —— 秒数转换 */
#include <stdio.h>

int main(void)
{
    int total = 0, hour = 0, rest = 0, min = 0, sec = 0;

    printf("请输入总秒数: ");
    if (scanf("%d", &total) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    hour = total / 3600;      /* 有几个整小时 */
    rest = total % 3600;      /* 剩下多少秒 */
    min  = rest / 60;         /* 剩下的里面有几个整分钟 */
    sec  = rest % 60;         /* 最后剩下几秒 */

    printf("%d 时 %d 分 %d 秒\n", hour, min, sec);
    return 0;
}
