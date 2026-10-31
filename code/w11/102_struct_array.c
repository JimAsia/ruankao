/* 102_struct_array.c —— 结构体数组：把 W5 的四大范式搬到结构体上
 *
 * 结构体数组是成绩管理、通讯录、库存表这类程序的基本结构。
 * 排序、查找、求最值的写法完全一样，只是比较的东西从 a[i] 变成 a[i].score
 */

#include <stdio.h>
#include <string.h>

#define N 6

struct Student {
    int    id;
    char   name[20];
    double score;
};

/* ---------- 打印整个数组（结构体数组必须传长度） ---------- */
void printAll(const struct Student a[], int n)
{
    printf("  %-8s %-10s %s\n", "学号", "姓名", "成绩");
    for (int i = 0; i < n; i++) {
        printf("  %-8d %-10s %.1f\n", a[i].id, a[i].name, a[i].score);
    }
}

int main(void)
{
    /* ---------- ① 定义与初始化 ---------- */
    struct Student stu[N] = {
        {2026001, "张三", 92.5},
        {2026002, "李四", 78.0},
        {2026003, "王五", 96.5},
        {2026004, "赵六", 65.0},
        {2026005, "钱七", 88.0},
        {2026006, "孙八", 78.0}
    };

    printf("=== ① 原始数据 ===\n");
    printAll(stu, N);
    printf("\n  整个数组占 %zu 字节 = %d × %zu\n", sizeof(stu), N, sizeof(stu[0]));
    printf("  单个元素 %zu 字节 = 4 + 20 + 8，正好没有填充\n", sizeof(stu[0]));
    printf("  因为 4 + 20 = 24，已经是 double 的对齐倍数，接上去不用补\n");
    printf("  把 name 改成 char[10]，4+10=14 就要补 2 字节，元素变 24 字节\n");

    /* ---------- ② 求最高分（打擂台，模式与 W4 完全一样） ---------- */
    printf("\n=== ② 求最高分 ===\n");
    int maxIdx = 0;                          /* 存下标，不存值 */
    for (int i = 1; i < N; i++) {
        if (stu[i].score > stu[maxIdx].score) maxIdx = i;
    }
    printf("  最高分：%s %.1f\n", stu[maxIdx].name, stu[maxIdx].score);
    printf("  ⭐ 为什么存下标而不是存值？因为后面还要用到姓名、学号\n");
    printf("     存值只能拿到分数，存下标能拿到这个人的全部信息\n");

    /* ---------- ③ 平均分（累加 + 计数） ---------- */
    printf("\n=== ③ 平均分 ===\n");
    double sum = 0;
    for (int i = 0; i < N; i++) sum += stu[i].score;
    printf("  总分 = %.1f，平均 = %.2f\n", sum, sum / N);

    /* 用 int 累加会怎样？真的算一遍 */
    int badSum = 0;
    for (int i = 0; i < N; i++) badSum += (int)stu[i].score;
    printf("  如果 sum 写成 int：%d 分，少了 %.1f 分\n",
           badSum, sum - badSum);
    printf("  ⭐ 每加一次就截断一次小数，6 个 .5 全部丢掉\n");
    printf("     这种错不会报错、不会警告，只是结果不对\n");

    /* ---------- ④ 按成绩排序（冒泡，比较的是 .score） ---------- */
    printf("\n=== ④ 按成绩降序排序 ===\n");
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (stu[j].score < stu[j + 1].score) {
                struct Student t = stu[j];       /* ✅ 整体交换，不需要逐字段 */
                stu[j]     = stu[j + 1];
                stu[j + 1] = t;
            }
        }
    }
    printAll(stu, N);

    printf("\n  ⭐ 交换时用 struct Student t，整体赋值三行搞定\n");
    printf("     不要逐个字段交换（id、name、score 各写一次），极易漏\n");

    /* ---------- ⑤ 按姓名查找（strcmp 比较字符串） ---------- */
    printf("\n=== ⑤ 按姓名查找 ===\n");
    const char *target = "赵六";
    int found = -1;
    for (int i = 0; i < N; i++) {
        if (strcmp(stu[i].name, target) == 0) {   /* ⚠️ 必须 strcmp，不能 == */
            found = i;
            break;
        }
    }
    if (found >= 0) {
        printf("  找到 %s：学号 %d，成绩 %.1f\n",
               stu[found].name, stu[found].id, stu[found].score);
    } else {
        printf("  没找到 %s\n", target);
    }

    /* ---------- ⑥ 统计各分数段人数（计数 + 多分支） ---------- */
    printf("\n=== ⑥ 分数段统计 ===\n");
    int cnt[5] = {0};                        /* 90+, 80-89, 70-79, 60-69, <60 */
    for (int i = 0; i < N; i++) {
        int s = (int)stu[i].score;
        if      (s >= 90) cnt[0]++;
        else if (s >= 80) cnt[1]++;
        else if (s >= 70) cnt[2]++;
        else if (s >= 60) cnt[3]++;
        else              cnt[4]++;
    }
    const char *label[5] = {"90 以上", "80-89", "70-79", "60-69", "60 以下"};
    for (int i = 0; i < 5; i++) {
        printf("  %-8s %d 人  ", label[i], cnt[i]);
        for (int k = 0; k < cnt[i]; k++) printf("★");
        printf("\n");
    }
    printf("\n  ⭐ 用计数数组代替 5 个独立变量，这是标准做法\n");
    printf("     5 个独立变量要写 5 段 if，加一档就要改 5 处\n");

    return 0;
}
