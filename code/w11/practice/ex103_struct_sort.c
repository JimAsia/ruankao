/* ex103_struct_sort.c —— 结构体数组排序：按姓名升序
 *
 * 要求：
 *   1. 读入 n 个学生的学号、姓名、成绩
 *   2. 按姓名升序排序（用 strcmp 比较，不要用 ==）
 *   3. 输出排序后的名单，每人一行
 *
 * 输入示例：
 *   3
 *   1 Zhang 85.0
 *   2 Li 92.0
 *   3 Wang 78.0
 * 输出示例：
 *   2 Li 92.0
 *   3 Wang 78.0
 *   1 Zhang 85.0
 *
 * 要点：交换时整个结构体一起换，用临时变量 struct Xxx t = a[j];
 *       不要逐个字段交换（容易漏字段）
 */

#include <stdio.h>
#include <string.h>

#define MAXN 100

/* TODO 1：定义结构体 */

int main(void)
{
    int n;
    /* TODO 2：读入数据 */

    /* TODO 3：冒泡排序，比较用 strcmp(a[j].name, a[j+1].name) > 0 */

    /* TODO 4：输出 */

    return 0;
}
