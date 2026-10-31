/* ex54 参考答案 —— 字符串反转（不用库函数） */
#include <stdio.h>

int main(void)
{
    char s[100];

    printf("请输入一个字符串: ");
    if (scanf("%99s", s) != 1) return 1;

    /* ① 先找末尾 */
    int right = 0;
    while (s[right] != '\0') right++;
    /* 此时 right 指向 '\0' 的位置 */

    /* ② 退到最后一个真实字符 */
    right--;

    /* ③ 首尾交换 */
    int left = 0;
    while (left < right) {
        char t = s[left];
        s[left] = s[right];
        s[right] = t;
        left++;
        right--;
    }

    printf("%s\n", s);

    /* ⚠️ 两个必须注意的点：
     *   ① right 一定要先 --，否则会把 '\0' 和首字符交换，
     *      结果字符串被截断成空串。
     *   ② 条件是 left < right，不是 left <= right（虽然单字符时也没事，
     *      但 <= 会让中间字符和自己交换一次，多做无用功）。 */

    return 0;
}
