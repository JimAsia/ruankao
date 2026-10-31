/* 36_classic.c —— 五个循环经典题
 *
 * 这五个是软考应用题和所有编程入门题的原型，必须能手写。
 */
#include <stdio.h>

int main(void)
{
    /* ========== ① 数字拆位：各位数字之和 ========== */
    printf("=== ① 各位数字之和 ===\n");
    int n = 3725;
    int sum = 0, tmp = n;
    while (tmp > 0) {
        sum += tmp % 10;        /* 取出个位 */
        tmp /= 10;              /* 去掉个位 */
    }
    printf("  %d 的各位数字之和 = %d\n", n, sum);
    printf("  过程：5 → 2 → 7 → 3，合计 3+7+2+5 = 17\n");

    /* ========== ② 数字反转 ========== */
    printf("\n=== ② 数字反转 ===\n");
    tmp = n;
    int rev = 0;
    while (tmp > 0) {
        rev = rev * 10 + tmp % 10;      /* 把个位接到反转数末尾 */
        tmp /= 10;
    }
    printf("  %d 反转后 = %d\n", n, rev);
    printf("  关键：rev * 10 是「腾位子」，+ tmp %% 10 是「填个位」\n");

    /* ========== ③ 判断回文数 ========== */
    printf("\n=== ③ 回文数判断 ===\n");

    int a = 12321, b = 12345;
    int ra = 0, rb = 0;

    tmp = a;
    while (tmp > 0) { ra = ra * 10 + tmp % 10; tmp /= 10; }
    tmp = b;
    while (tmp > 0) { rb = rb * 10 + tmp % 10; tmp /= 10; }

    printf("  %d 反转得 %d → %s\n", a, ra, (ra == a) ? "是回文数" : "不是回文数");
    printf("  %d 反转得 %d → %s\n", b, rb, (rb == b) ? "是回文数" : "不是回文数");
    printf("  思路：反转后和原数比。负数不参与（-121 反转是 121-，无意义）\n");

    /* ========== ④ 判断素数 ========== */
    printf("\n=== ④ 素数判断 ===\n");

    /* 逐个判断几个数 */
    int check = 97;
    int isPrime = 1;                    /* 先假设是素数 */
    if (check < 2) {
        isPrime = 0;
    } else {
        for (int i = 2; i * i <= check; i++) {   /* ⚠️ 只需试到 √n */
            if (check % i == 0) {
                isPrime = 0;
                break;                  /* 找到一个因子就够了 */
            }
        }
    }
    printf("  %d %s素数\n", check, isPrime ? "是" : "不是");

    check = 91;                         /* 91 = 7 × 13 */
    isPrime = 1;
    for (int i = 2; i * i <= check; i++) {
        if (check % i == 0) { isPrime = 0; break; }
    }
    printf("  %d %s素数\n", check, isPrime ? "是" : "不是");
    printf("  优化点：只需试除到 √n，因为因子成对出现（7×13 = 13×7）\n");

    /* 打印 1~50 内所有素数，顺便用上"计数"范式 */
    printf("  1~50 的素数：");
    int primeCnt = 0;
    for (int k = 2; k <= 50; k++) {
        int ok = 1;
        for (int i = 2; i * i <= k; i++) {
            if (k % i == 0) { ok = 0; break; }
        }
        if (ok) {
            printf("%d ", k);
            primeCnt++;
        }
    }
    printf("\n  共 %d 个\n", primeCnt);

    /* ========== ⑤ 斐波那契数列 ========== */
    printf("\n=== ⑤ 斐波那契数列 ===\n");
    printf("  前 15 项：");
    long long f1 = 1, f2 = 1, f3;
    printf("%lld %lld ", f1, f2);
    for (int i = 3; i <= 15; i++) {
        f3 = f1 + f2;
        printf("%lld ", f3);
        f1 = f2;                        /* 往前挪 */
        f2 = f3;
    }
    printf("\n  递推式：f(n) = f(n-1) + f(n-2)，这里用迭代实现，O(n)\n");
    printf("  用递归实现会是指数级，W8 讲递归时会对比\n");

    return 0;
}
