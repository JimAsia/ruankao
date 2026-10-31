/* 05_printf.c —— printf 格式化输出全解
 * 这是应用技术大题里"输出格式不对"的万恶之源，一次搞清。
 */
#include <stdio.h>

int main(void)
{
    int    n    = 42;
    double pi   = 3.14159265;
    char   ch   = 'A';
    char   name[] = "Programmer";

    /* ---------- 基本转换符 ---------- */
    printf("十进制 %%d      : %d\n", n);
    printf("八进制 %%o      : %o\n", n);
    printf("十六进制 %%x    : %x\n", n);
    printf("十六进制(大写)  : %X\n", n);
    printf("无符号 %%u      : %u\n", n);
    printf("字符 %%c        : %c\n", ch);
    printf("字符串 %%s      : %s\n", name);

    /* ---------- 浮点 ---------- */
    printf("\n默认 6 位小数  : %f\n", pi);
    printf("保留 2 位      : %.2f\n", pi);
    printf("科学计数法     : %e\n", pi);
    printf("自动选 %%g      : %g\n", pi);

    /* ---------- 宽度与对齐（考试爱考） ---------- */
    printf("\n宽度 8 右对齐  : [%8d]\n", n);
    printf("宽度 8 左对齐  : [%-8d]\n", n);
    printf("宽度 8 补零    : [%08d]\n", n);
    printf("宽度 8 保留2位 : [%8.2f]\n", pi);

    /* ---------- 两个转义坑 ---------- */
    printf("\n百分号本身要写两个: 100%%\n");
    printf("反斜杠本身要写两个: C:\\msys64\\ucrt64\\bin\n");
    printf("换行\\n 制表\\t 回车\\r 都是转义字符\n");

    /* ---------- 一次打印多个值 ---------- */
    printf("\n%d + %d = %d\n", 3, 4, 3 + 4);

    /* ---------- 经典坑：转换符和参数类型不匹配 ---------- */
    /* printf("%d\n", pi);   错！double 用 %d 打印是未定义行为 */
    /* printf("%f\n", n);    错！int 用 %f 打印是未定义行为 */

    return 0;
}
