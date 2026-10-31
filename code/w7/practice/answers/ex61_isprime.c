/* ex61 参考答案 —— 用函数判断素数 */
#include <stdio.h>

int isPrime(int n)
{
    /* 小于 2 的都不是素数 */
    if (n < 2) return 0;

    /* 试除到 √n 就够了：因子成对出现 */
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;       /* 找到因子，立刻返回"不是" */
    }
    return 1;
}

int main(void)
{
    printf("1~50 之间的素数：\n  ");

    int count = 0;
    for (int k = 2; k <= 50; k++) {
        if (isPrime(k)) {               /* 函数返回 1 表示是素数，直接当条件用 */
            printf("%d ", k);
            count++;
        }
    }
    printf("\n共 %d 个\n", count);

    /* 封装成函数的好处：
     *   ① main 里只剩下"遍历"这一件事，可读性大幅提升
     *   ② 想改判断逻辑（比如改成"是不是完全数"），只改函数内部
     *   ③ 函数可以在别的地方复用
     *
     * 对比 W4 的写法：那时所有逻辑都堆在 main 里，两层循环嵌套，
     * 光看代码就要想半天哪层在干什么。 */

    return 0;
}
