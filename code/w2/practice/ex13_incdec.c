/* ex13 —— 自增自减的值
 *
 * 每组开始都把 i 重置为 5，然后把结果填进输出。
 *
 *  ① i = 5;  a = i++;      →  a = 5 , i = ___6
 *  ② i = 5;  b = ++i;      →  b = ___6 , i = ___6
 *  ③ i = 5;  c = i--;      →  c = ___5 , i = ___4
 *  ④ i = 5;  d = --i;      →  d = ___4 , i = ___4
 *  ⑤ i = 5;  e = i++ * 2;  →  e = ___10 , i = ___6
 *  ⑥ i = 5;  f = ++i * 2;  →  f = ___12 , i = ___6
 *
 * 先填预测，再补代码运行验证。
 */
#include <stdio.h>

int main(void)
{
    int i, a, b, c, d, e, f;

    i = 5; a = i++;
    printf("① a = %d, i = %d\n", a, i);

    i = 5; b = ++i;
    printf("② b = %d, i = %d\n", b, i);

    i = 5; c = i--;
    printf("③ c = %d, i = %d\n", c, i);

    i = 5; d = --i;
    printf("④ d = %d, i = %d\n", d, i);

    i = 5; e = i++ * 2;
    printf("⑤ e = %d, i = %d\n", e, i);

    i = 5; f = ++i * 2;
    printf("⑥ f = %d, i = %d\n", f, i);

    return 0;
}
