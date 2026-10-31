/* ex32 参考答案 —— 阶乘表 */
#include <stdio.h>

int main(void)
{
    /* 累乘范式：fac 里始终存着"到上一轮为止的乘积"，
     * 每轮乘上当前的 i，就得到新一阶的阶乘。
     * 这样是 O(n)，不用每轮从头再乘一遍。 */
    long long fac = 1;

    for (int i = 1; i <= 10; i++) {
        fac *= i;
        printf("%d! = %lld\n", i, fac);
    }

    /* 为什么用 long long：
     *   10! = 3628800，int 装得下；
     *   但 13! = 6227020800 已经超出 int 的 21 亿上限，
     *   所以从 13! 起必须用 long long。这里用到 10! 其实 int 也够，
     *   但养成用 long long 的习惯能少踩坑。 */

    return 0;
}
