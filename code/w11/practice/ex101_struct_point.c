/* ex101_struct_point.c —— 结构体基础：两点距离
 *
 * 要求：
 *   1. 定义 struct Point { double x; double y; };
 *   2. 输入两个点的坐标，输出它们之间的距离，保留 2 位小数
 *   3. 距离公式：sqrt((x1-x2)^2 + (y1-y2)^2)
 *
 * 输入示例：
 *   0 0
 *   3 4
 * 输出示例：
 *   距离 = 5.00
 *
 * 提示：需要 #include <math.h>，编译时加 -lm
 */

#include <stdio.h>
#include <math.h>

/* TODO 1：定义 struct Point */
struct Point {
	double x;
	double y;
};

int main(void)
{
    /* TODO 2：声明两个 struct Point 变量 */
	struct Point p1;
	struct Point p2;
    /* TODO 3：读入 4 个数（%lf） */
	printf("输入示例：\n");
	scanf("%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y);
    /* TODO 4：算距离并输出 */
	printf("输出示例：\n");
	printf("距离 = %.2lf", sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) ));
    return 0;
}
