/* 33_while_dowhile.c —— while 与 do-while
 *
 * while：先判断，可能一次都不执行
 * do-while：先执行，至少执行一次
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① while 基本 ---------- */
    printf("=== ① while ===\n");
    int i = 1;
    while (i <= 5) {
        printf("i = %d  ", i);
        i++;                    /* ⚠️ 忘了这句就是死循环 */
    }
    printf("\n");

    /* ---------- ② 条件一开始就为假：while 一次都不执行 ---------- */
    printf("\n=== ② 条件一开始为假 ===\n");
    i = 100;
    printf("while：  ");
    while (i <= 5) {
        printf("这句不会执行 ");
        i++;
    }
    printf("（循环体执行了 0 次）\n");

    /* ---------- ③ 同样的条件，do-while 会执行一次 ---------- */
    printf("\ndo-while：");
    i = 100;
    do {
        printf("执行了一次 ");
        i++;
    } while (i <= 5);
    printf("（循环体执行了 1 次）\n");

    printf("\n  这就是两者的本质区别：\n");
    printf("    while    先判断，条件假 → 0 次\n");
    printf("    do-while 先执行，条件假 → 1 次\n");

    /* ---------- ④ do-while 的典型场景：菜单 ---------- */
    printf("\n=== ④ do-while 最适合的场景：菜单至少显示一次 ===\n");
    int choice;
    int round = 0;
    do {
        round++;
        printf("  [第 %d 次显示菜单]  1.开始  2.退出  → ", round);
        /* 这里为了演示不真的读输入，用固定值模拟 */
        choice = (round == 1) ? 1 : 2;
        printf("用户选了 %d\n", choice);
    } while (choice != 2);
    printf("  退出菜单。do-while 保证菜单至少出现一次，即使一进来就想退出\n");

    /* ---------- ⑤ while 与 for 的互换 ---------- */
    printf("\n=== ⑤ for 和 while 可以互相转换 ===\n");
    printf("for 写法：");
    for (int k = 0; k < 3; k++) printf("%d ", k);
    printf("\n");

    printf("while 等价写法：");
    int k = 0;                  /* 初始化提到外面 */
    while (k < 3) {             /* 条件 */
        printf("%d ", k);
        k++;                    /* 更新放循环体末尾 */
    }
    printf("\n");
    printf("  规律：for 的三段，分别对应 while 的「前面」「条件」「末尾」\n");

    /* ---------- ⑥ 死循环的两种写法 ---------- */
    printf("\n=== ⑥ 死循环（本文件不会真的执行，只展示写法）===\n");
    printf("  for (;;) { ... }\n");
    printf("  while (1) { ... }\n");
    printf("  通常配合 break 使用：满足条件就跳出\n");

    /* ---------- ⑦ do-while 末尾的分号 ---------- */
    printf("\n=== ⑦ 最容易漏的细节 ===\n");
    printf("  do { ... } while (条件);    ← 末尾的分号不能丢\n");
    printf("  这是 C 里少数几个必须带分号的复合语句结构\n");

    return 0;
}
