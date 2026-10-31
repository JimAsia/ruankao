/* 82_null_wild.c —— 空指针与野指针
 *
 * ⚠️ 本文件故意保留 1 处 -Wuninitialized 警告。
 *    第 ② 段声明了一个未初始化的 `int *wild` 并打印它的值，
 *    编译器提醒「你正在使用未初始化的变量」——
 *    这正是野指针的成因，警告本身就是最好的教材。
 *
 * 这两个是指针最危险的两个来源。
 * 本程序不真的制造崩溃（那会中断课程），只用打印和判断来展示。
 */

#include <stdio.h>
#include <stddef.h>         /* NULL 定义在这里 */

int main(void)
{
    /* ---------- ① NULL 是什么 ---------- */
    printf("=== ① 空指针 NULL ===\n");
    int *p = NULL;

    printf("  int *p = NULL;\n");
    printf("  p 的值 = %p\n", (void *)p);
    printf("  NULL 本质就是 (void*)0 —— 一个保证不指向任何有效数据的地址\n");

    /* 正确用法：用之前先判空 */
    if (p == NULL) {
        printf("  if (p == NULL) → 成立，说明 p 没指向任何东西\n");
        printf("  ⚠️ 此时千万不能写 *p，会立刻崩溃（段错误）\n");
    }

    /* ---------- ② 野指针：比空指针更可怕 ---------- */
    printf("\n=== ② 野指针 ===\n");
    int *wild;              /* ⚠️ 未初始化！里面是垃圾地址 */

    printf("  int *wild;  未初始化，wild 里的值是随机的\n");
    printf("  wild = %p（这是垃圾值，每次运行可能不同）\n", (void *)wild);
    printf("  如果直接 *wild = 5，程序可能：\n");
    printf("    - 立刻崩溃\n");
    printf("    - 悄悄改坏别的变量（更可怕）\n");
    printf("    - 看起来正常，但几小时后出错\n");

    /* 演示但不解引用 —— 只判断是否为 NULL（对野指针没意义，但至少不崩） */
    printf("  本程序不演示 *wild，因为那是不确定行为\n");

    /* ---------- ③ 三种指针的对比 ---------- */
    printf("\n=== ③ 三种状态 ===\n");
    int  value = 10;
    int *good = &value;     /* ✅ 有效指针 */
    int *null = NULL;       /* ⚠️ 空指针，可以判出来 */
    /* int *wild2; */       /* ❌ 野指针，没法判，只能靠规范避免 */

    printf("  int *good = &value;   值 = %p  ✅ 有效\n", (void *)good);
    printf("  int *null = NULL;     值 = %p  ⚠️ 空，可判断\n", (void *)null);
    printf("  野指针                    值 = 随机地址  ❌ 不可判断，必须避免\n");

    printf("\n  三种的安全性排序：有效指针 > 空指针 > 野指针\n");
    printf("  因为空指针至少能用 if (p == NULL) 检查出来\n");

    /* ---------- ④ 怎么避免野指针 ---------- */
    printf("\n=== ④ 避免野指针的三条规矩 ===\n");
    printf("  ① 声明时就初始化：int *p = NULL;\n");
    printf("  ② 用完就置空：把指针指向的内存释放后，立刻 p = NULL;\n");
    printf("  ③ 用之前判空：if (p != NULL) { *p = ...; }\n");

    /* ---------- ⑤ free 之后要置空（概念演示） ---------- */
    printf("\n=== ⑤ 释放后置空 ===\n");
    printf("  虽然本阶段还没学动态内存（malloc/free），但先记住这个习惯：\n");
    printf("    free(p);\n");
    printf("    p = NULL;      ← 这一句很重要\n");
    printf("  不置空的话，p 就成了「悬空指针」（指向已释放的内存），\n");
    printf("  和野指针一样危险\n");

    /* ---------- ⑥ 判空的正确写法 ---------- */
    printf("\n=== ⑥ 判空的两种写法 ===\n");
    printf("  if (p == NULL)     ← 推荐，意图明确\n");
    printf("  if (!p)            ← 也行，但可读性差一点\n");
    printf("  if (p)             ← 表示 p 非空，可以安全解引用\n");

    return 0;
}
