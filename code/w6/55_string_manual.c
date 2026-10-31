/* 55_string_manual.c —— 不用库函数，手动实现字符串操作
 *
 * 因为还没学函数（W7），这里全部写在 main 里。
 * 重点是理解 strlen / strcpy 这些函数内部到底在做什么。
 */
#include <stdio.h>

int main(void)
{
    char src[] = "Programming";

    /* ========== ① 手写 strlen ========== */
    printf("=== ① 手写 strlen ===\n");
    int len = 0;
    while (src[len] != '\0') {
        len++;
    }
    printf("  \"%s\" 的长度 = %d\n", src, len);
    printf("  原理：从头数到 '\\0' 为止，一个字符一个字符数\n");

    /* ========== ② 手写 strcpy ========== */
    printf("\n=== ② 手写 strcpy ===\n");
    char dst[50];
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';                      /* ⚠️ 必须补上结束符，否则 dst 不是合法字符串 */
    printf("  复制结果：\"%s\"\n", dst);
    printf("  原理：逐字符搬，最后补 '\\0'\n");
    printf("  忘了补 '\\0' 的话，dst 就没有结束标志，printf 会一直往后读\n");

    /* ========== ③ 手写字符串反转 ========== */
    printf("\n=== ③ 手写字符串反转 ===\n");
    char s[] = "Hello";

    printf("  反转前：\"%s\"\n", s);

    int left = 0;
    int right = 0;
    while (s[right] != '\0') right++;   /* 先找到末尾 */
    right--;                            /* 退回到最后一个字符（不是 '\0'） */

    printf("  长度 = %d，反转前 right 指向下标 %d 的 '%c'\n", right + 1, right, s[right]);

    while (left < right) {              /* 首尾交换 */
        char t = s[left];
        s[left] = s[right];
        s[right] = t;
        left++;
        right--;
    }
    printf("  反转后：\"%s\"\n", s);
    printf("  关键：right 最后要减 1，否则会把 '\\0' 也卷进来\n");

    /* ========== ④ 手写 strcmp ========== */
    printf("\n=== ④ 手写 strcmp ===\n");
    char a[] = "abc";
    char b1[] = "abd";
    char b2[] = "abc";
    char b3[] = "ab";

    /* 比较 a 和 b1 */
    int k = 0;
    while (a[k] != '\0' && b1[k] != '\0' && a[k] == b1[k]) {
        k++;
    }
    int diff1 = (unsigned char)a[k] - (unsigned char)b1[k];

    k = 0;
    while (a[k] != '\0' && b2[k] != '\0' && a[k] == b2[k]) {
        k++;
    }
    int diff2 = (unsigned char)a[k] - (unsigned char)b2[k];

    k = 0;
    while (a[k] != '\0' && b3[k] != '\0' && a[k] == b3[k]) {
        k++;
    }
    int diff3 = (unsigned char)a[k] - (unsigned char)b3[k];

    printf("  \"abc\" vs \"abd\" → 差值 %d（负数，前者小）\n", diff1);
    printf("  \"abc\" vs \"abc\" → 差值 %d（相等）\n", diff2);
    printf("  \"abc\" vs \"ab\"  → 差值 %d（正数，前者长所以大）\n", diff3);
    printf("  原理：逐字符比到不同为止，返回第一个不同字符的 ASCII 差值\n");

    /* ========== ⑤ 手写字符串连接 ========== */
    printf("\n=== ⑤ 手写 strcat ===\n");
    char base[50] = "Hello";
    char tail[] = ", World";
    int pos = 0;

    while (base[pos] != '\0') pos++;    /* 先走到 base 的末尾 */

    int j = 0;
    while (tail[j] != '\0') {
        base[pos] = tail[j];
        pos++;
        j++;
    }
    base[pos] = '\0';                   /* 补结束符 */

    printf("  拼接结果：\"%s\"\n", base);
    printf("  原理：先找到 dst 的末尾，再从那里开始把 src 一个个抄过去\n");
    printf("  ⚠️ 如果 dst 空间不够，就会越界写入 —— 库函数也不检查\n");

    return 0;
}
