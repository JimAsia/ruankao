/* ex12 参考答案 —— 短路求值
 *
 * 答案：
 *   ① 0 && ++i   →  r = 0, i = 0     左边为假，右边不执行
 *   ② 1 || ++i   →  r = 1, i = 0     左边为真，右边不执行
 *   ③ 1 && ++i   →  r = 1, i = 1     左边为真，右边必须执行
 *   ④ 0 || ++i   →  r = 1, i = 1     左边为假，右边必须执行
 */
#include <stdio.h>

int main(void)
{
    int i;
    int r;

    i = 0;
    r = 0 && ++i;
    printf("① r = %d, i = %d\n", r, i);

    i = 0;
    r = 1 || ++i;
    printf("② r = %d, i = %d\n", r, i);

    i = 0;
    r = 1 && ++i;
    printf("③ r = %d, i = %d\n", r, i);

    i = 0;
    r = 0 || ++i;
    printf("④ r = %d, i = %d\n", r, i);

    return 0;
}
