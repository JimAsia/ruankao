/* 85_pointer_errors.c —— 指针的七个常见错误
 *
 * ⚠️ 本文件故意保留 1 处 -Wreturn-local-addr 警告。
 *    wrongReturnLocal 返回了局部变量的地址，编译器直接指出「函数返回了局部变量地址」。
 *    这正是第 ⑤ 段要讲的错误 —— 编译器能抓出来的错误，千万别忽略。
 *
 * 本文件只"描述"错误，不真的触发崩溃（那会中断程序）。
 * 每个错误都给出正确写法对照。
 */

#include <stdio.h>

/* 演示用：一个错误的函数（返回局部变量的地址） */
int *wrongReturnLocal(void)
{
    int local = 42;
    return &local;
    /* ⚠️ local 在函数返回时就销毁了，返回它的地址 = 悬空指针 */
}

int main(void)
{
    printf("=== ① 未初始化就解引用（野指针）===\n");
    printf("  错误：int *p;  *p = 5;\n");
    printf("  后果：写到随机地址，可能崩溃或改坏别的变量\n");
    printf("  正确：int *p = NULL;  或者先让它指向有效内存\n");

    printf("\n=== ② 空指针解引用 ===\n");
    printf("  错误：int *p = NULL;  *p = 5;\n");
    printf("  后果：立刻崩溃（段错误），因为地址 0 不可访问\n");
    printf("  正确：用之前先 if (p != NULL)\n");

    printf("\n=== ③ 指针类型不匹配 ===\n");
    printf("  错误：int a; double *p = &a;\n");
    printf("  后果：解引用时按 8 字节读，越界且结果错误\n");
    printf("  正确：类型必须和指向的对象一致（需要的转换用强制转换并说明原因）\n");

    printf("\n=== ④ 数组名当成指针变量来赋值 ===\n");
    printf("  错误：int a[5], b[5];  a = b;\n");
    printf("  后果：编译错误，数组名是常量地址，不能被赋值\n");
    printf("  正确：逐元素复制，或者用 memcpy\n");

    printf("\n=== ⑤ 返回局部变量的地址 ===\n");
    int *dangling = wrongReturnLocal();
    printf("  wrongReturnLocal() 返回了 %p\n", (void *)dangling);
    printf("  但这个地址指向的局部变量已经销毁了\n");
    printf("  后果：读到的可能是别的函数留下的垃圾（本程序不解引用它）\n");
    printf("  正确：用 static 局部变量、全局变量，或者由调用者传入缓冲区\n");

    printf("\n=== ⑥ scanf 忘记取地址 ===\n");
    printf("  错误：int n;  scanf(\"%%d\", n);\n");
    printf("  后果：scanf 把输入写到「地址 = n 当前值」的地方，内存被写坏\n");
    printf("  正确：scanf(\"%%d\", &n);\n");
    printf("  ⚠️ 例外：读字符串数组时不用 &，因为数组名本身就是地址\n");

    printf("\n=== ⑦ 混淆 *p++ 与 (*p)++ ===\n");
    printf("  *p++    取当前值，然后指针后移\n");
    printf("  (*p)++  把指向的值加 1，指针不动\n");
    printf("  ⚠️ 后者要加括号，因为 ++ 优先级高于 *\n");

    printf("\n=== 一张自查表 ===\n");
    printf("  %-28s %s\n", "写指针时的疑问", "该检查什么");
    printf("  %-28s %s\n", "它是 NULL 吗？", "解引用前先判空");
    printf("  %-28s %s\n", "它指向的对象还活着吗？", "别返回局部变量的地址");
    printf("  %-28s %s\n", "类型对吗？", "指向 int 的必须是 int*");
    printf("  %-28s %s\n", "越界了吗？", "下标 0 ~ n-1");
    printf("  %-28s %s\n", "改的是指针还是值？", "*p = 改值，p = 改指向");

    printf("\n=== 为什么指针错误这么难查 ===\n");
    printf("  因为它不报错。编译器大多时候不拦，运行时可能只是「数据悄悄变了」。\n");
    printf("  排查方法：\n");
    printf("    ① 开 -Wall -Wextra，把警告当错误看\n");
    printf("    ② 用 -fsanitize=address 编译，运行时能抓越界和悬空指针\n");
    printf("    ③ 所有指针声明时初始化成 NULL\n");

    return 0;
}
