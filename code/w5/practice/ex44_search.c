/* ex44 —— 顺序查找
 * 要求：读入 n 个整数，再读入一个待查找的数 key，输出：
 *   找到了 → 输出它在数组中的下标（第一次出现的位置）
 *   没找到 → 输出 -1
 *
 * 测试：输入 6
 *            15 28 37 42 58 63
 *            42
 *   输出：下标 = 3
 *
 *       输入 6
 *            15 28 37 42 58 63
 *            100
 *   输出：-1
 *
 * 提示：用 pos = -1 表示"没找到"，找到就改 pos 并 break。
 */
#include <stdio.h>

int main(void)
{
    int a[20];
    int n = 0, key = 0;

    /* TODO */
	printf("输入 ");
	scanf("%d", &n);
    /* TODO: 循环读入 n 个元素 */
	printf("输入 ");
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	printf("输入key: ");
	scanf("%d",&key);
	// 
	int index = -1;
	for (int i = 0; i < n; ++i) {
		if (a[i] == key) {
			index = i;
		}
	}
	if (index < 0)
		printf("输出： %d", index);
	else
		printf("输出：下标 = %d", index);
    return 0;
}
