/* ex13 参考答案 —— 自增自减的值
 *
 * 答案：
 *   ① a = 5, i = 6     先取 5 再变 6
 *   ② b = 6, i = 6     先变 6 再取 6
 *   ③ c = 5, i = 4     先取 5 再变 4
 *   ④ d = 4, i = 4     先变 4 再取 4
 *   ⑤ e = 10, i = 6    i++ 先给 5，5*2=10，然后 i 变 6
 *   ⑥ f = 12, i = 6    ++i 先把 i 变 6，6*2=12
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
