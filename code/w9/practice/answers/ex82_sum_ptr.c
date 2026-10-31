/* ex82 参考答案 —— 用指针遍历数组求和 */
#include <stdio.h>

int sumByPtr(int *a, int n)
{
    int sum = 0;
    for (int *p = a; p < a + n; p++) {
        sum += *p;
    }
    return sum;
}

int main(void)
{
    int a[20], n = 0;

    printf("请输入元素个数: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20) return 1;

    printf("请输入 %d 个整数: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    printf("和 = %d\n", sumByPtr(a, n));
    return 0;
}

/* 三种等价的遍历写法：
 *
 *   ① 下标法（最易读）
 *      for (int i = 0; i < n; i++) sum += a[i];
 *
 *   ② 指针 + 下标（本答案本来可以这么写，但要求不用下标）
 *      for (int i = 0; i < n; i++) sum += p[i];
 *
 *   ③ 指针移动（本答案用的）
 *      for (int *p = a; p < a + n; p++) sum += *p;
 *
 * ⚠️ 循环条件必须是 p < a + n，不能写 p <= a + n。
 *    a + n 是「最后一个元素的后面那个位置」，解引用它就是越界。
 *
 * 💡 为什么 a + n 合法？C 标准允许数组指针指向「末尾的下一个位置」，
 *    但不允许解引用它。所以 (p < a + n) 是安全的，(p <= a + n) 不安全。 */
