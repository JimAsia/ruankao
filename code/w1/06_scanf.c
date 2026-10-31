/* 06_scanf.c —— 用 scanf 从键盘读数据
 * 核心口诀：scanf 的参数前面几乎都要加 &（取地址符）
 */
#include <stdio.h>

int main(void)
{
    int    age    = 0;
    double height = 0.0;
    char   grade  = 0;

    /* ---------- 读整数 ---------- */
    printf("请输入年龄: ");
    if (scanf("%d", &age) != 1) {
        printf("输入格式不对，程序退出\n");
        return 1;
    }
    /* ↑ &age 表示"age 那块内存的地址"。scanf 要把值写进去，
     *   所以必须告诉它"写到哪儿"，而不是"age 现在是几"。
     *   忘写 & 是新手第一大崩溃原因 —— 程序可能直接崩，也可能悄悄写坏内存。 */

    /* ---------- 读浮点 ---------- */
    printf("请输入身高(米): ");
    if (scanf("%lf", &height) != 1) {      /* double 必须用 %lf，不是 %f */
        printf("输入格式不对\n");
        return 1;
    }

    /* ---------- 读单个字符（有坑） ---------- */
    printf("请输入等级(A/B/C): ");
    if (scanf(" %c", &grade) != 1) {       /* 注意 %c 前面那个空格 */
        printf("输入格式不对\n");
        return 1;
    }
    /* ↑ 为什么 "%c" 前面要加空格？
     *   上面 scanf("%lf") 读完后，缓冲区里还留着你敲的那个"回车"(\n)。
     *   如果不加空格，%c 会立刻把这个换行符读走，你根本没机会输入。
     *   加了空格，表示"先跳过所有空白字符（空格、制表、换行），再读一个字符"。
     *   这个坑软考笔试选择题考过不止一次。 */

    printf("\n--- 你输入的是 ---\n");
    printf("age    = %d\n", age);
    printf("height = %.2f 米\n", height);
    printf("grade  = %c\n", grade);

    return 0;
}
