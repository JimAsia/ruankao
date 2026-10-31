/* ex95 参考答案 —— 用二级指针修改指针的指向 */
#include <stdio.h>

void retarget(int **pp, int *target)
{
    *pp = target;           /* 修改 pp 指向的那个指针 */
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

/* ⭐ 为什么必须是二级指针？
 *
 * 假设参数写成 int *pp：
 *   void retarget(int *pp, int *target) { pp = target; }
 *   retarget(p, &b);
 *
 *   pp 是 p 的【副本】，pp = target 只改了副本，
 *   main 里的 p 完全没动。 ← 又回到 W7 的 swap 问题！
 *
 * 所以想改 p 本身，必须传 p 的地址，也就是 &p，类型是 int**。
 *
 * 类型链：
 *   p       int*    指向 int
 *   &p      int**   指向「int*」
 *   *pp     int*    就是 p 本身
 *   **pp    int     就是 p 指向的值
 *
 * 于是 *pp = target 等价于 p = target ✓
 *
 * ------ 这个模式在现实中的用途 ------
 * ① 链表操作：删除节点时可能要改 head 指针本身
 *    void removeHead(Node **head) { *head = (*head)->next; }
 * ② 函数返回指针，同时用返回值表示错误码
 *    int createList(Node **out);   // 返回 0 成功，-1 失败
 * ③ 动态内存分配（S2 会讲）
 *
 * 软考应用技术的链表题里，Node ** 这种写法出现过。 */
