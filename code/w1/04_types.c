/* 04_types.c —— 基本数据类型与 sizeof
 * 软考《基础知识》几乎每年都考"某类型占几个字节""取值范围"。
 * 记住结论前，先让机器自己告诉你。
 */
#include <stdio.h>
#include <limits.h>     /* INT_MAX、CHAR_MIN 这些宏都在这里面 */
#include <float.h>      /* FLT_MAX、DBL_MAX */

int main(void)
{
    printf("%-14s %-6s %-24s %s\n", "type", "bytes", "min", "max");
    printf("%-14s %-6zu %-24lld %lld\n", "char",          sizeof(char),          (long long)CHAR_MIN,  (long long)CHAR_MAX);
    printf("%-14s %-6zu %-24d %d\n",     "short",         sizeof(short),         SHRT_MIN,             SHRT_MAX);
    printf("%-14s %-6zu %-24d %d\n",     "int",           sizeof(int),           INT_MIN,              INT_MAX);
    printf("%-14s %-6zu %-24u %u\n",     "unsigned int",  sizeof(unsigned int),  0,                    UINT_MAX);
    printf("%-14s %-6zu %-24lld %lld\n", "long long",     sizeof(long long),     (long long)LLONG_MIN, (long long)LLONG_MAX);
    printf("%-14s %-6zu %-24.3e %.3e\n", "float",         sizeof(float),         (double)FLT_MIN,      (double)FLT_MAX);
    printf("%-14s %-6zu %-24.3e %.3e\n", "double",        sizeof(double),        DBL_MIN,              DBL_MAX);
    printf("%-14s %-6zu %s\n", "long double", sizeof(long double), "(Windows 下 printf 对 long double 支持不全，软考基本不考)");

    printf("\n--- 三个必须记住的 ---\n");
    printf("char 占 %zu 字节，恰好存一个 ASCII 字符（'A' = %d）\n", sizeof(char), 'A');
    printf("int  占 %zu 字节，能存到 21 亿多，够用到几乎所有算法题\n", sizeof(int));
    printf("double 占 %zu 字节，浮点默认就用它，float 精度不够别用\n", sizeof(double));

    return 0;
}
