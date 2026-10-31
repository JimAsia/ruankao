/* ex125_condcompile.c —— 参考答案 */

#include <stdio.h>

/* ---------- 语言选择 ---------- */
#ifdef LANG_CN
    #define MSG_START  "程序开始运行"
    #define MSG_DETAIL "正在计算 1 + 2"
    #define MSG_RESULT "结果"
    #define MSG_END    "程序结束"
#else
    #define MSG_START  "program start"
    #define MSG_DETAIL "computing 1 + 2"
    #define MSG_RESULT "result"
    #define MSG_END    "program end"
#endif

/* ---------- 调试开关 ---------- */
#ifdef DEBUG
    #define DBG(...)   printf("[调试] " __VA_ARGS__)
#else
    #define DBG(...)   ((void)0)
#endif

/* ---------- 详细输出开关 ---------- */
#ifdef VERBOSE
    #define VERBOSE_LOG(...)  printf("[详细] " __VA_ARGS__)
#else
    #define VERBOSE_LOG(...)  ((void)0)
#endif

int main(void)
{
    DBG("%s\n", MSG_START);

    VERBOSE_LOG("%s\n", MSG_DETAIL);

    int a = 1, b = 2;
    printf("%s = %d\n", MSG_RESULT, a + b);

    DBG("%s\n", MSG_END);

    printf("\n本次编译的开关状态：\n");
#ifdef DEBUG
    printf("  DEBUG    = 开\n");
#else
    printf("  DEBUG    = 关\n");
#endif
#ifdef VERBOSE
    printf("  VERBOSE  = 开\n");
#else
    printf("  VERBOSE  = 关\n");
#endif
#ifdef LANG_CN
    printf("  LANG_CN  = 开（中文）\n");
#else
    printf("  LANG_CN  = 关（英文）\n");
#endif

    printf("\n⭐ 关键理解：宏没定义时，那一段代码【根本不参与编译】。\n");
    printf("   不是 if (0) 那种「编译了但不执行」，而是从源文本里被删掉。\n");
    printf("   所以 #if 里的代码即使有语法错，只要不开这个宏就不会报错。\n");

    return 0;
}
