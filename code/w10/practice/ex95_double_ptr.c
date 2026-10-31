/* ex95 —— 用二级指针修改指针的指向
 * 要求：写 void retarget(int **pp, int *target)，让 pp 指向的那个指针
 *       改为指向 target。
 *
 * 测试：p 原本指向 a（值 10），调用 retarget(&p, &b) 之后，
 *       *p 应该变成 b 的值 20。
 *
 * 提示：
 *   ① 参数是 int **（二级指针）
 *   ② 函数内写 *pp = target;     ← 修改「指针的指向」
 *   ③ 调用时传 &p
 *
 * 理解要点：
 *   p   是 int*，指向 int
 *   &p  是 int**，指向「int*」
 *   *pp 就是 p 本身，所以 *pp = target 等价于 p = target
 */
#include <stdio.h>

void retarget(int **pp, int *target)
{
    /* TODO */
}

int main(void)
{
    int a = 10, b = 20;
    int *p = &a;

    printf("初始：*p = %d（指向 a）\n", *p);

    retarget(&p, &b);

    printf("retarget 之后：*p = %d（应该指向 b）\n", *p);
    return 0;
}
