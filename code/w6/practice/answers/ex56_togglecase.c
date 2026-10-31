/* ex56 参考答案 —— 大小写互换 */
#include <stdio.h>

int main(void)
{
    char s[200];

    printf("请输入一行字符串: ");
    /* fgets 读整行（含空格），最多读 sizeof(s)-1 个字符 */
    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("读取失败\n");
        return 1;
    }

    /* ⚠️ fgets 会把末尾的换行符也读进来，先去掉
     * 不去掉的话，输出时末尾会多一个空行 */
    int len = 0;
    while (s[len] != '\0') len++;
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
        len--;
    }

    /* 逐字符转换 */
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 32;           /* 小写 → 大写 */
        else if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;           /* 大写 → 小写 */
        /* 其他字符不动 */
    }

    printf("%s\n", s);

    /* 三个要点：
     *   ① 这题必须用 fgets 不能用 scanf("%s")，因为要保留空格
     *   ② fgets 会带进来 '\n'，必须手动去掉，否则输出格式不对
     *   ③ 'a' - 'A' = 32，所以小写减 32 变大写，大写加 32 变小写
     *
     * 如果允许用库函数，可以写：
     *   #include <ctype.h>
     *   s[i] = isupper(s[i]) ? tolower(s[i]) : toupper(s[i]);
     * 但考试时手写更稳妥，也更能看出你懂原理。 */

    return 0;
}
