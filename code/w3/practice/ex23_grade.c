/* ex23 —— 成绩分级（两种写法）
 * 要求：读入一个 0~100 的整数成绩，分别用两种方式输出等级：
 *   第一行用 if - else if 链
 *   第二行用 switch
 *
 *   90~100 优秀 ｜ 80~89 良好 ｜ 70~79 中等 ｜ 60~69 及格 ｜ 0~59 不及格
 *
 * 测试：输入 85   输出：if-else：良好
 *                        switch ：良好
 *
 * 注意 if-else 链的判断顺序：必须从大到小写，否则 85 会先命中 score >= 60。
 */
#include <stdio.h>

int main(void)
{
    int score = 0;

    /* TODO: 读入成绩 */

    /* TODO: 写法一 if - else if 链 */

    /* TODO: 写法二 switch（用 score / 10） */

    return 0;
}
