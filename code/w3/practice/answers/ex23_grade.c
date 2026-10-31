/* ex23 参考答案 —— 成绩分级（两种写法） */
#include <stdio.h>

int main(void)
{
    int score = 0;

    printf("请输入成绩(0~100): ");
    if (scanf("%d", &score) != 1) {
        printf("输入格式不对\n");
        return 1;
    }

    /* ---------- 写法一：if - else if 链 ---------- */
    /* 关键：必须从大到小判断。
     * 如果先写 if (score >= 60)，那 85 会直接命中"及格"就走了，后面的分支永远轮不到。 */
    printf("if-else：");
    if (score >= 90)      printf("优秀\n");
    else if (score >= 80) printf("良好\n");
    else if (score >= 70) printf("中等\n");
    else if (score >= 60) printf("及格\n");
    else                  printf("不及格\n");

    /* ---------- 写法二：switch ---------- */
    /* 关键：用 score / 10 把范围压成离散值 10、9、8…，再交给 case 匹配。
     * 故意不写 break，让 100 和 90 共享"优秀"这段代码。 */
    printf("switch ：");
    switch (score / 10) {
        case 10:
        case 9:
            printf("优秀\n");
            break;
        case 8:
            printf("良好\n");
            break;
        case 7:
            printf("中等\n");
            break;
        case 6:
            printf("及格\n");
            break;
        default:
            printf("不及格\n");
            break;
    }

    return 0;
}
