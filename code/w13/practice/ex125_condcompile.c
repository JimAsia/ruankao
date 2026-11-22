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

// 如果编译时定义了宏 LANG_CN（如 -DLANG_CN），则编译下面的中文分支；否则跳到 #else。
#ifdef LANG_CN
	#define MSG_HELLO "[调试] 程序开始运行"  // 定义MSG_HELLO内容为字符串"[调试] 程序开始运行"
	#define MSG_DETAIL "[详细] 正在计算 %d + %d"
	#define MSG_RESULT "结果 = %d"
	#define MSG_BYE "[调试] 程序结束"
#else
    #define MSG_HELLO   "[DEBUG] Program started"
    #define MSG_DETAIL  "[VERBOSE] Computing %d + %d"
    #define MSG_RESULT  "Result = %d"
    #define MSG_BYE     "[DEBUG] Program ended"
#endif

/* TODO 2：用 #ifdef DEBUG 定义 DBG 宏，否则定义成空 */

// 如果定义了 DEBUG（如 -DDEBUG），DBG 展开为真正的 printf
#ifdef DEBUG
	#define DBG(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)
#else
	#define DBG(fmt, ...) ((void)0)
#endif

#ifdef VERBOSE
    #define VERB(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)
#else
    #define VERB(fmt, ...) ((void)0)
#endif

int main(void)
{
    /* TODO 3：按开关输出对应内容 */
	DBG(MSG_HELLO); // DEBUG 控制
	int a = 1, b = 2;
	VERB(MSG_DETAIL, a, b); // VERBOSE 控制（不是 DBG）
	int result = a + b;
	printf(MSG_RESULT "\n", result);  // 结果始终输出
	
	DBG(MSG_BYE);  // DEBUG 控制
    return 0;
}