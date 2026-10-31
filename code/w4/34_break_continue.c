/* 34_break_continue.c —— break 与 continue
 *
 * break    ：立刻跳出【本层】循环，后面的循环不再执行
 * continue ：跳过本次剩余部分，直接进入下一次判断
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① break：找到就停 ---------- */
    printf("=== ① break：i 到 4 就跳出 ===\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 4) break;
        printf("%d ", i);
    }
    printf("\n  → 只打印了 1 2 3，4 及以后都没执行\n");

    /* ---------- ② continue：跳过 4，继续后面的 ---------- */
    printf("\n=== ② continue：跳过 4 ===\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 4) continue;
        printf("%d ", i);
    }
    printf("\n  → 打印 1 2 3 5 6 7 8 9 10，只是没有 4\n");

    /* ---------- ③ 对比表 ---------- */
    printf("\n=== ③ 两者的差别 ===\n");
    printf("  break    ：整个循环结束，不再进行后续任何轮\n");
    printf("  continue ：只结束【这一轮】，下一轮照常\n");

    /* ---------- ④ 只打印奇数：continue 的典型用法 ---------- */
    printf("\n=== ④ 跳过偶数 ===\n");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) continue;       /* 是偶数就跳过 */
        printf("%d ", i);
    }
    printf("\n  → 1 3 5 7 9\n");

    /* ---------- ⑤ 嵌套循环里，break 只管自己那一层 ---------- */
    printf("\n=== ⑤ 嵌套循环：break 只管本层 ===\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (j == 2) break;          /* 只跳出内层，外层继续 */
            printf("(%d,%d) ", i, j);
        }
    }
    printf("\n  → 外层照常跑 3 轮，每轮内层只打了 j=1\n");

    /* ---------- ⑥ 想跳出两层：用标志变量 ---------- */
    printf("\n=== ⑥ 跳出多层：标志变量法 ===\n");
    int found = 0;
    for (int i = 1; i <= 3 && !found; i++) {
        for (int j = 1; j <= 3; j++) {
            if (i * j == 6) {
                printf("  找到 i=%d, j=%d，两层一起停\n", i, j);
                found = 1;
                break;                  /* 先跳出内层 */
            }
        }
    }
    printf("  原理：内层 break 后，外层的条件 !found 也变假，于是外层也停\n");

    /* ---------- ⑦ continue 在 while 里的死循环陷阱 ---------- */
    printf("\n=== ⑦ ⚠️ continue 在 while 里可能造成死循环 ===\n");
    printf("  错误写法：\n");
    printf("    int i = 0;\n");
    printf("    while (i < 10) {\n");
    printf("        if (i == 5) continue;   ← i 永远停在 5\n");
    printf("        i++;\n");
    printf("    }\n");
    printf("  原因：continue 跳过了 i++，i 卡在 5，条件永远成立 → 死循环\n");
    printf("  正确做法：把 i++ 提到 continue 之前，或者改用 for\n");

    /* 演示正确的做法 */
    printf("\n  正确的 while 写法：");
    int i = 0;
    while (i < 10) {
        i++;                            /* 先更新 */
        if (i == 5) continue;
        printf("%d ", i);
    }
    printf("\n  → 同样跳过 5，但不会死循环\n");

    return 0;
}
