/* ex126_bitfield.c —— 位域：压缩一个 RGB 颜色
 *
 * 要求：
 *   1. 定义 struct RGB { unsigned int r:8; g:8; b:8; };
 *   2. 定义 struct RGB16 { unsigned int r:5; g:6; b:5; };   ← RGB565
 *   3. 各定义一个变量，赋 r=200, g=150, b=100
 *   4. 输出两个结构体的 sizeof，以及各成员的值
 *
 * 预期输出（参考）：
 *   struct RGB 占 4 字节
 *   r=200 g=150 b=100
 *   struct RGB16 占 4 字节
 *   r=8 g=22 b=4        ← 5 位装不下 200，被截断
 *
 * 说明：
 *   200 的低 5 位 = 200 & 31 = 8
 *   150 的低 6 位 = 150 & 63 = 22
 *   100 的低 5 位 = 100 & 31 = 4
 *
 * 要点：
 *   - 位域成员赋值超范围会被截断（gcc 会给 -Woverflow 警告，正常）
 *   - sizeof 按声明类型（unsigned int）分配，不是按位精确计算
 */

#include <stdio.h>

/* TODO 1：定义 struct RGB */
/* TODO 2：定义 struct RGB16 */

int main(void)
{
    /* TODO 3：两个变量分别赋值并输出 */

    return 0;
}
