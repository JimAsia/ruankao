/* ex34 参考答案 —— 数字拆位综合 */
#include <stdio.h>

int main(void)
{
    int n = 0;

    printf("请输入一个正整数: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入格式不对\n");
        return 1;
    }

    int tmp  = n;       /* ⚠️ 复制一份，因为拆位会破坏原数 */
    int cnt  = 0;       /* 位数 */
    int sum  = 0;       /* 各位和 */
    int rev  = 0;       /* 反转后的数 */

    while (tmp > 0) {
        int digit = tmp % 10;       /* 取个位 */

        sum += digit;               /* 累加到各位和 */
        rev  = rev * 10 + digit;    /* 接到反转数的末尾 */
        cnt++;                      /* 位数加一 */

        tmp /= 10;                  /* 去掉个位 */
    }

    printf("位数 = %d\n", cnt);
    printf("各位和 = %d\n", sum);
    printf("反转 = %d\n", rev);

    /* 三个动作共用一个循环，这是拆位题的常见写法。
     * 拆开写三个循环也能对，但没必要。 */

    return 0;
}
