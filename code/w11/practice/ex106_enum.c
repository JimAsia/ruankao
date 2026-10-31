/* ex106_enum.c —— 枚举与 switch：星期判断
 *
 * 要求：
 *   1. 定义 enum Weekday { MON=1, TUE, WED, THU, FRI, SAT, SUN };
 *   2. 读入一个 1-7 的整数，转成枚举值
 *   3. 用 switch 输出：1-5 输出「工作日」，6-7 输出「休息日」
 *      并输出英文缩写（MON/TUE/...）
 *   4. 输入不在 1-7 范围时输出「输入错误」
 *
 * 输入示例：
 *   6
 * 输出示例：
 *   SAT 休息日
 *
 * 要点：可以多个 case 共用一个分支（case MON: case TUE: ... 不写 break）
 *       这就是 W3 讲的「穿透」的正确用法
 */

#include <stdio.h>

/* TODO 1：定义枚举 */

int main(void)
{
    int n;
    /* TODO 2：读入 n */

    /* TODO 3：判断范围，转枚举 */

    /* TODO 4：switch 输出英文缩写 + 工作日/休息日 */

    return 0;
}
