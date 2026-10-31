/* ex81 —— 用指针交换两个数（修复 W7 的 swap）
 * 要求：写 void swap(int *a, int *b)，真正交换调用者的两个变量。
 *       ⭐ 这正是 W7 里「swap 交换不了」的解决方案。
 *
 * 测试：输入 3 8
 *   输出：交换前 a = 3, b = 8
 *         交换后 a = 8, b = 3
 *
 * 提示：
 *   ① 参数类型是 int *（指针）
 *   ② 函数内用 *a、*b 操作它们指向的值
 *   ③ 调用时要传地址：swap(&a, &b)
 *   ④ 交换时用 (*a) 这种带括号的写法，或者先存到临时变量
 */
#include <stdio.h>

void swap(int *a, int *b)
{
    /* TODO */
}

int main(void)
{
    int a = 0, b = 0;

    printf("请输入两个整数: ");
    if (scanf("%d %d", &a, &b) != 2) return 1;

    printf("交换前 a = %d, b = %d\n", a, b);
    swap(&a, &b);                    /* ⚠️ 传的是地址 */
    printf("交换后 a = %d, b = %d\n", a, b);

    return 0;
}
