/* 23_switch_penetrate.c —— case 穿透：既是陷阱，也是武器
 *
 * ⚠️ 本文件故意保留 3 处 -Wimplicit-fallthrough 警告。
 *    第一段就是故意不写 break 来演示穿透，编译器逐条提醒「这里会掉下去」。
 *    真实代码里出现这个警告，八成是你漏了 break —— 别忽略它。
 *
 * 忘了 break 就会"穿透"到下一个 case 继续执行。
 * 大部分时候是 bug，但故意不写 break 是合法的写法，用来让多个 case 共享代码。
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① 反面：忘了 break ---------- */
    printf("=== 忘了 break 会怎样 ===\n");
    int n = 2;
    printf("n = %d，执行：\n", n);
    switch (n) {
        case 1: printf("  case 1\n");
        case 2: printf("  case 2\n");
        case 3: printf("  case 3\n");
        default: printf("  default\n");
    }
    printf("↑ 从 case 2 开始一路往下执行到底，因为没遇到 break\n");

    printf("\n对照：加了 break 之后\n");
    switch (n) {
        case 1: printf("  case 1\n"); break;
        case 2: printf("  case 2\n"); break;
        case 3: printf("  case 3\n"); break;
        default: printf("  default\n");
    }
    printf("↑ 只执行 case 2，然后跳出\n");

    /* ---------- ② 正面：故意利用穿透共享代码 ---------- */
    printf("\n=== 故意不写 break：多个 case 共享同一段逻辑 ===\n");
    int score = 85;
    printf("score = %d\n", score);
    switch (score / 10) {
        case 10:
        case 9:
            printf("等级：优秀\n");
            break;
        case 8:
        case 7:
            printf("等级：良好\n");
            break;
        case 6:
            printf("等级：及格\n");
            break;
        default:
            printf("等级：不及格\n");
    }
    printf("↑ 90~100 都走「优秀」，80~89 都走「良好」—— 这是标准用法\n");

    /* ---------- ③ switch 里能放什么 ---------- */
    printf("\n=== switch 的几条硬规则 ===\n");
    printf("① 表达式必须是整型（int / char / enum），float 和字符串不行\n");
    printf("② case 后面必须是常量，不能是变量\n");
    printf("③ case 的值不能重复\n");
    printf("④ default 可以省略，位置任意\n");
    printf("⑤ break 只跳出 switch，不是跳出函数\n");
    printf("⑥ switch 里可以嵌套 switch，但别这么写\n");

    /* ---------- ④ switch vs if-else 怎么选 ---------- */
    printf("\n=== 什么时候用 switch ===\n");
    printf("等值判断、分支多 → switch（编译器可做跳转表，比 if-else 链快）\n");
    printf("范围判断、条件复杂 → if-else（switch 没法判 a > 10 && a < 20）\n");

    return 0;
}
