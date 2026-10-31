/* ex02 —— 两个整数的四则运算
 * 要求：用 scanf 读入两个整数 a、b（假设 b 不为 0），输出：
 *   a + b = ?
 *   a - b = ?
 *   a * b = ?
 *   a / b = ?      （整数除法，只要商）
 *   a %% b = ?      （取余数）
 *
 * 注意：输出里的百分号要写成两个 %%
 * 测试数据：输入 17 5
 *   期望输出：
 *     17 + 5 = 22
 *     17 - 5 = 12
 *     17 * 5 = 85
 *     17 / 5 = 3
 *     17 %% 5 = 2
 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    /* TODO: 读入 a 和 b */
    scanf("%d%d", &a, &b);

    /* TODO: 五行 printf */
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n", a % b);
    
    return 0;
}
