/* 22_switch.c —— switch 的基本用法
 */
#include <stdio.h>

int main(void)
{
    /* ---------- ① 基本形态 ---------- */
    int cmd = 2;
    printf("cmd = %d\n", cmd);
    switch (cmd) {
        case 1:
            printf("执行：新建\n");
            break;
        case 2:
            printf("执行：打开\n");
            break;
        case 3:
            printf("执行：保存\n");
            break;
        default:
            printf("执行：未知命令\n");
    }

    /* ---------- ② default 位置任意，但只在没匹配时执行 ---------- */
    printf("\n=== default 放最前面也行 ===\n");
    cmd = 1;
    switch (cmd) {
        default:
            printf("未知\n");
            break;
        case 1:
            printf("匹配 case 1，default 不执行\n");
            break;
    }

    /* ---------- ③ switch 的表达式只能是整型 ---------- */
    printf("\n=== switch 能接什么 ===\n");
    char ch = 'B';
    switch (ch) {                  /* char 本质是整数，可以 */
        case 'A': printf("等级 A\n"); break;
        case 'B': printf("等级 B\n"); break;
        default:  printf("其他等级\n");
    }
    printf("（float 不能作为 switch 表达式，编译会报错；字符串也不行）\n");

    /* ---------- ④ case 必须是常量 ---------- */
    printf("\n=== case 后面必须是常量表达式 ===\n");
    printf("case 1:、case 'A':、case 2+3: 都行；case n:（变量）不行\n");

    return 0;
}
