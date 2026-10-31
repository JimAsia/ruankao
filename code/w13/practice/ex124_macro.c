/* ex124_macro.c —— 写三个「正确的」宏
 *
 * 要求：
 *   1. MAX(a, b)   取较大值
 *   2. MIN(a, b)   取较小值
 *   3. CLAMP(x, lo, hi)  把 x 限制在 [lo, hi] 范围内
 *   4. SQUARE(x)   平方
 *
 * 而且必须写成「防得住」的版本：下面这些调用都要得到正确结果
 *   2 * MAX(3, 4)          → 8（不是 3*2=6 之类）
 *   MAX(a + 1, b)          → 正确
 *   SQUARE(1 + 2)          → 9（不是 5）
 *   CLAMP(15, 0, 10)       → 10
 *   CLAMP(-5, 0, 10)       → 0
 *   CLAMP(5, 0, 10)        → 5
 *
 * 输出示例：
 *   2 * MAX(3, 4) = 8
 *   SQUARE(1 + 2) = 9
 *   CLAMP(15, 0, 10) = 10
 *
 * 要点：每个参数加括号，整体再加一层括号
 */

#include <stdio.h>

/* TODO 1：MAX */
/* TODO 2：MIN */
/* TODO 3：CLAMP（可以复用 MAX/MIN） */
/* TODO 4：SQUARE */

int main(void)
{
    /* TODO 5：按上面的要求逐个输出验证 */

    return 0;
}
