/* 74_classic_rec.c —— 四个经典递归题
 */

#include <stdio.h>

/* ---------- ① 最大公约数：辗转相除（递归版） ---------- */
int gcd(int a, int b)
{
    if (b == 0) return a;               /* 出口 */
    return gcd(b, a % b);               /* 递推 */
}

/* ---------- ② 十进制转二进制（递归输出，顺序天然正确） ---------- */
void toBinary(int n)
{
    if (n == 0) return;                 /* 出口：没有更多位了 */

    toBinary(n / 2);                    /* 先递归处理高位 */
    printf("%d", n % 2);                /* 再输出这一位 */
}

/* ---------- ③ 递归求数组和 ---------- */
int sumRec(int a[], int n)
{
    if (n == 0) return 0;               /* 出口：没有元素了 */
    return a[n - 1] + sumRec(a, n - 1); /* 最后一个 + 前面所有 */
}

/* ---------- ④ 递归判断回文字符串 ---------- */
int isPalRec(const char *s, int left, int right)
{
    if (left >= right) return 1;        /* 出口：相遇了，是回文 */
    if (s[left] != s[right]) return 0;  /* 发现不同，不是回文 */
    return isPalRec(s, left + 1, right - 1);
}

int main(void)
{
    /* ---------- ① gcd ---------- */
    printf("=== ① 最大公约数 ===\n");
    printf("  gcd(12, 18) = %d\n", gcd(12, 18));
    printf("  gcd(100, 75) = %d\n", gcd(100, 75));
    printf("  gcd(17, 5) = %d\n", gcd(17, 5));
    printf("  推导 gcd(12,18)：\n");
    printf("    gcd(12,18) → gcd(18,12%%18=12) → gcd(12,18%%12=6) → gcd(6,12%%6=0) → 6\n");
    printf("  这是递归最优雅的例子：三行代码，没有循环\n");

    /* ---------- ② 十进制转二进制 ---------- */
    printf("\n=== ② 十进制转二进制 ===\n");
    int nums[] = {10, 255, 1024};
    for (int i = 0; i < 3; i++) {
        printf("  %d → ", nums[i]);
        if (nums[i] == 0) printf("0");
        else toBinary(nums[i]);
        printf("\n");
    }
    printf("  注意：必须先递归再输出，顺序才是正的高位在左\n");
    printf("  如果先输出再递归，会得到倒序的二进制\n");

    /* ---------- ③ 递归求数组和 ---------- */
    printf("\n=== ③ 递归求数组和 ===\n");
    int a[6] = {3, 7, 1, 9, 4, 6};
    printf("  数组：3 7 1 9 4 6\n");
    printf("  sumRec(a, 6) = %d\n", sumRec(a, 6));
    printf("  思路：和 = 最后一个元素 + 前面所有元素的和\n");
    printf("  ⚠️ 递归版比循环版慢（每次调用都有函数开销），这题用循环更好\n");
    printf("  但作为理解递归的练习很有价值\n");

    /* ---------- ④ 递归判断回文 ---------- */
    printf("\n=== ④ 递归判断回文 ===\n");
    char words[4][10] = {"level", "hello", "abcba", "ab"};
    for (int i = 0; i < 4; i++) {
        int len = 0;
        while (words[i][len] != '\0') len++;

        int r = isPalRec(words[i], 0, len - 1);
        printf("  %-8s → %s\n", words[i], r ? "是回文" : "不是回文");
    }
    printf("  思路：比较首尾，然后让指针向中间收缩 —— 递归地做同一件事\n");

    /* ---------- ⑤ 五个递归题的对照 ---------- */
    printf("\n=== ⑤ 出口与递推一览 ===\n");
    printf("  %-12s %-20s %s\n", "函数", "出口", "递推");
    printf("  %-12s %-20s %s\n", "gcd", "b == 0", "gcd(b, a%b)");
    printf("  %-12s %-20s %s\n", "toBinary", "n == 0", "toBinary(n/2)");
    printf("  %-12s %-20s %s\n", "sumRec", "n == 0", "a[n-1] + sumRec(a,n-1)");
    printf("  %-12s %-20s %s\n", "isPalRec", "left >= right", "(l+1, r-1)");

    return 0;
}
