/* ex05 参考答案 —— 交换两个变量的值 */
#include <stdio.h>

int main(void)
{
    int a = 0, b = 0;

    printf("请输入两个整数(空格分隔): ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("输入格式不对\n");
        return 1;
    }
    printf("交换前 a = %d, b = %d\n", a, b);

    /* ---------- 第一问：借助第三个变量 ---------- */
    int temp = a;
    a = b;
    b = temp;
    printf("第一问交换后 a = %d, b = %d\n", a, b);

    /* ---------- 第二问：不用第三个变量（加减法） ---------- */
    /* 设原始值 a0、b0，推一遍：
     *   a = a + b   →  a 里存了 a0+b0
     *   b = a - b   →  (a0+b0) - b0 = a0   ← b 拿到原始 a
     *   a = a - b   →  (a0+b0) - a0 = b0   ← a 拿到原始 b
     */
    a = a + b;
    b = a - b;
    a = a - b;
    printf("第二问交换后 a = %d, b = %d（又换回来了）\n", a, b);

    /* 补充：还有异或版 a ^= b; b ^= a; a ^= b; 原理一样，但同样有溢出风险，
     * 实际工程里不推荐，考试知道思路即可。 */
    return 0;
}
