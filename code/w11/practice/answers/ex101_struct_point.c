/* ex101_struct_point.c —— 参考答案
 * 编译：gcc -std=c17 -Wall -Wextra -o ex101 ex101_struct_point.c -lm
 */

#include <stdio.h>
#include <math.h>

struct Point {
    double x;
    double y;
};

int main(void)
{
    struct Point a, b;

    printf("请输入第一个点（x y）：");
    scanf("%lf %lf", &a.x, &a.y);

    printf("请输入第二个点（x y）：");
    scanf("%lf %lf", &b.x, &b.y);

    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dist = sqrt(dx * dx + dy * dy);

    printf("\n点 A(%.1f, %.1f)\n", a.x, a.y);
    printf("点 B(%.1f, %.1f)\n", b.x, b.y);
    printf("距离 = %.2f\n", dist);

    /* 顺带验证一个结论：点本身占多少字节 */
    printf("\nstruct Point 占 %zu 字节（2 个 double，没填充）\n", sizeof(struct Point));

    return 0;
}
