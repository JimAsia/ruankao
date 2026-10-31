/* ex125_condcompile.c —— 条件编译：一份代码，多种编译结果
 *
 * 要求：
 *   1. 定义三个开关宏：DEBUG、VERBOSE、LANG_CN
 *   2. 用 #ifdef / #ifndef 控制输出：
 *        DEBUG     打开时，打印「[调试] 程序开始运行」
 *        VERBOSE   打开时，打印每一步的详细信息
 *        LANG_CN   打开时用中文，否则用英文
 *   3. 用 -D 在命令行控制，不改源码
 *
 * 编译与运行：
 *   gcc -std=c17 -o ex125 ex125_condcompile.c && ./ex125
 *   gcc -std=c17 -DDEBUG -o ex125 ex125_condcompile.c && ./ex125
 *   gcc -std=c17 -DDEBUG -DVERBOSE -DLANG_CN -o ex125 ex125_condcompile.c && ./ex125
 *
 * 预期（全开）：
 *   [调试] 程序开始运行
 *   [详细] 正在计算 1 + 2
 *   结果 = 3
 *   [调试] 程序结束
 *
 * 要点：
 *   - 宏没定义时 #ifdef 整段不参与编译，不是「运行时不执行」
 *   - 记得 #endif
 */

#include <stdio.h>

/* TODO 1：用 #ifdef LANG_CN 定义 MSG_HELLO 和 MSG_RESULT 两个宏 */
/* TODO 2：用 #ifdef DEBUG 定义 DBG 宏，否则定义成空 */

int main(void)
{
    /* TODO 3：按开关输出对应内容 */

    return 0;
}
