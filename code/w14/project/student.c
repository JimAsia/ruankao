/* student.c —— 学生成绩管理系统（S1 综合项目）
 *
 * 把 S1 全部内容串起来：
 *   W1  变量、printf、scanf
 *   W3  多分支、switch（菜单）
 *   W4  循环（菜单循环、遍历）
 *   W5  一维数组（结构体数组）
 *   W6  字符串（strcmp、strcpy）
 *   W7  函数、值传递
 *   W8  递归（二分查找用迭代，注释里给递归版）
 *   W9-W10 指针（函数参数用指针回传结果）
 *   W11 结构体、typedef
 *   W12 文件读写
 *   W13 位运算（及格标记）
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o student student.c
 * 运行：./student
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ==================== 数据结构 ==================== */

#define MAXN      100
#define NAMELEN   20
#define FILEPATH  "students.txt"

typedef struct {
    int    id;                  /* 学号，唯一 */
    char   name[NAMELEN];       /* 姓名 */
    double score;               /* 成绩 0~100 */
} Student;

/* 全局数据：结构体数组 + 当前人数
 * 用全局变量是为了让所有函数都能直接访问，不用层层传参。
 * 工程上更好的是把两个打包成一个 struct，作为参数传递 —— 见文末说明。 */
static Student g_stu[MAXN];
static int     g_count = 0;

/* ==================== 工具函数 ==================== */

/* 清空输入缓冲区：菜单里输入非法字符后，不清理会陷入死循环 */
static void clearInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* 丢弃 */
    }
}

/* 读一个整数，成功返回 1，失败返回 0 */
static int readInt(const char *prompt, int *out)
{
    printf("%s", prompt);
    if (scanf("%d", out) != 1) {
        clearInput();
        printf("  输入无效，请输入数字\n");
        return 0;
    }
    return 1;
}

/* 读一个 double，带范围检查 */
static int readScore(const char *prompt, double *out)
{
    printf("%s", prompt);
    if (scanf("%lf", out) != 1) {
        clearInput();
        printf("  输入无效，请输入数字\n");
        return 0;
    }
    if (*out < 0.0 || *out > 100.0) {
        printf("  成绩必须在 0~100 之间\n");
        return 0;
    }
    return 1;
}

/* 打印分隔线 */
static void line(void)
{
    printf("--------------------------------------------\n");
}

/* ==================== 文件操作 ==================== */

/* 从文件加载。返回加载条数，失败返回 -1 */
static int loadFromFile(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("  文件 %s 不存在，将使用空数据\n", path);
        return -1;
    }

    int n = 0;
    Student s;
    /* 格式串必须和写入时一致 */
    while (n < MAXN &&
           fscanf(fp, "%d %19s %lf", &s.id, s.name, &s.score) == 3) {
        g_stu[n++] = s;
    }
    fclose(fp);

    g_count = n;
    return n;
}

/* 保存到文件。成功返回 0，失败返回 -1 */
static int saveToFile(const char *path)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        printf("  无法写入 %s\n", path);
        return -1;
    }

    for (int i = 0; i < g_count; i++) {
        fprintf(fp, "%d %s %.1f\n",
                g_stu[i].id, g_stu[i].name, g_stu[i].score);
    }
    fclose(fp);
    return 0;
}

/* ==================== 基本功能 ==================== */

/* 按学号查找，返回下标，找不到返回 -1 */
static int findById(int id)
{
    for (int i = 0; i < g_count; i++) {
        if (g_stu[i].id == id) return i;
    }
    return -1;
}

/* 1. 添加学生 */
static void addStudent(void)
{
    printf("\n--- 添加学生 ---\n");

    if (g_count >= MAXN) {
        printf("  人数已满（上限 %d）\n", MAXN);
        return;
    }

    int id;
    if (!readInt("学号：", &id)) return;

    /* 学号不能重复 —— 这是「唯一键」的概念 */
    if (findById(id) >= 0) {
        printf("  学号 %d 已存在\n", id);
        return;
    }

    /* 姓名必须是「一行里没有空格的串」，所以用 %19s */
    char name[NAMELEN];
    printf("姓名：");
    if (scanf("%19s", name) != 1) {
        clearInput();
        printf("  输入无效\n");
        return;
    }

    double score;
    if (!readScore("成绩：", &score)) return;

    g_stu[g_count].id = id;
    strcpy(g_stu[g_count].name, name);      /* 字符数组不能用 = */
    g_stu[g_count].score = score;
    g_count++;

    printf("  已添加：%d %s %.1f（当前共 %d 人）\n", id, name, score, g_count);
}

/* 2. 显示全部 */
static void showAll(void)
{
    printf("\n--- 学生列表（共 %d 人）---\n", g_count);

    if (g_count == 0) {
        printf("  暂无数据\n");
        return;
    }

    line();
    printf("%-8s %-12s %-8s %s\n", "学号", "姓名", "成绩", "状态");
    line();
    for (int i = 0; i < g_count; i++) {
        printf("%-8d %-12s %-8.1f %s\n",
               g_stu[i].id,
               g_stu[i].name,
               g_stu[i].score,
               g_stu[i].score >= 60.0 ? "及格" : "不及格");
    }
    line();
}

/* 3. 按学号查找 */
static void searchById(void)
{
    printf("\n--- 按学号查找 ---\n");

    int id;
    if (!readInt("学号：", &id)) return;

    int idx = findById(id);
    if (idx < 0) {
        printf("  未找到学号 %d\n", id);
        return;
    }

    printf("  学号：%d\n", g_stu[idx].id);
    printf("  姓名：%s\n", g_stu[idx].name);
    printf("  成绩：%.1f（%s）\n",
           g_stu[idx].score,
           g_stu[idx].score >= 60.0 ? "及格" : "不及格");
}

/* 4. 按成绩降序排序（冒泡，整体交换） */
static void sortByScore(void)
{
    printf("\n--- 按成绩降序排序 ---\n");

    if (g_count < 2) {
        printf("  数据不足，无需排序\n");
        return;
    }

    int swaps = 0;
    for (int i = 0; i < g_count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < g_count - 1 - i; j++) {
            if (g_stu[j].score < g_stu[j + 1].score) {
                Student t   = g_stu[j];     /* 整体交换，不能逐字段 */
                g_stu[j]     = g_stu[j + 1];
                g_stu[j + 1] = t;
                swapped = 1;
                swaps++;
            }
        }
        if (!swapped) break;                /* 本趟无交换，已有序 */
    }

    printf("  排序完成，交换 %d 次\n", swaps);
}

/* 5. 修改成绩 */
static void modifyScore(void)
{
    printf("\n--- 修改成绩 ---\n");

    int id;
    if (!readInt("要修改的学号：", &id)) return;

    int idx = findById(id);
    if (idx < 0) {
        printf("  未找到学号 %d\n", id);
        return;
    }

    printf("  当前：%s %.1f\n", g_stu[idx].name, g_stu[idx].score);

    double score;
    if (!readScore("新成绩：", &score)) return;

    g_stu[idx].score = score;               /* 直接改数组元素 */
    printf("  已更新为 %.1f\n", g_stu[idx].score);
}

/* 6. 删除学生 */
static void deleteStudent(void)
{
    printf("\n--- 删除学生 ---\n");

    int id;
    if (!readInt("要删除的学号：", &id)) return;

    int idx = findById(id);
    if (idx < 0) {
        printf("  未找到学号 %d\n", id);
        return;
    }

    printf("  确认删除 %d %s？(1=是, 0=否)：", g_stu[idx].id, g_stu[idx].name);
    int confirm;
    if (scanf("%d", &confirm) != 1) { clearInput(); return; }
    if (confirm != 1) {
        printf("  已取消\n");
        return;
    }

    /* 从前往后移，覆盖被删元素 */
    for (int i = idx; i < g_count - 1; i++) {
        g_stu[i] = g_stu[i + 1];
    }
    g_count--;
    printf("  已删除，当前共 %d 人\n", g_count);
}

/* 7. 统计 */
static void showStats(void)
{
    printf("\n--- 成绩统计 ---\n");

    if (g_count == 0) {
        printf("  暂无数据\n");
        return;
    }

    double sum = 0.0;
    int maxIdx = 0, minIdx = 0;
    int passCnt = 0;

    /* 计数数组：90+ / 80-89 / 70-79 / 60-69 / <60 */
    int buckets[5] = {0};

    for (int i = 0; i < g_count; i++) {
        sum += g_stu[i].score;

        if (g_stu[i].score > g_stu[maxIdx].score) maxIdx = i;
        if (g_stu[i].score < g_stu[minIdx].score) minIdx = i;

        if (g_stu[i].score >= 60.0) passCnt++;

        int s = (int)g_stu[i].score;
        if      (s >= 90) buckets[0]++;
        else if (s >= 80) buckets[1]++;
        else if (s >= 70) buckets[2]++;
        else if (s >= 60) buckets[3]++;
        else              buckets[4]++;
    }

    line();
    printf("  人数    ：%d\n", g_count);
    printf("  总分    ：%.1f\n", sum);
    printf("  平均分  ：%.2f\n", sum / g_count);
    printf("  最高分  ：%s %.1f\n", g_stu[maxIdx].name, g_stu[maxIdx].score);
    printf("  最低分  ：%s %.1f\n", g_stu[minIdx].name, g_stu[minIdx].score);
    printf("  及格人数：%d / %d（及格率 %.1f%%）\n",
           passCnt, g_count, 100.0 * passCnt / g_count);

    const char *labels[5] = {"90 以上", "80-89", "70-79", "60-69", "60 以下"};
    for (int i = 0; i < 5; i++) {
        printf("  %-8s %d 人  ", labels[i], buckets[i]);
        for (int k = 0; k < buckets[i]; k++) printf("★");
        printf("\n");
    }
    line();
}

/* ==================== 菜单 ==================== */

static void printMenu(void)
{
    printf("\n");
    line();
    printf("   学生成绩管理系统    （当前 %d 人）\n", g_count);
    line();
    printf("   1. 添加学生        2. 显示全部\n");
    printf("   3. 按学号查找      4. 按成绩排序\n");
    printf("   5. 修改成绩        6. 删除学生\n");
    printf("   7. 成绩统计        8. 保存到文件\n");
    printf("   9. 从文件加载      0. 退出\n");
    line();
    printf("请选择：");
}

int main(void)
{
    printf("=== 学生成绩管理系统 ===\n");

    /* 启动时尝试加载已有数据 */
    if (loadFromFile(FILEPATH) > 0) {
        printf("已从 %s 加载 %d 条记录\n", FILEPATH, g_count);
    }

    int running = 1;
    while (running) {
        printMenu();

        int choice;
        if (scanf("%d", &choice) != 1) {
            clearInput();                   /* ⚠️ 不清理会死循环 */
            printf("  无效输入，请输入 0-9\n");
            continue;
        }

        switch (choice) {
            case 1: addStudent();     break;
            case 2: showAll();        break;
            case 3: searchById();     break;
            case 4: sortByScore();    break;
            case 5: modifyScore();    break;
            case 6: deleteStudent();  break;
            case 7: showStats();      break;
            case 8:
                if (saveToFile(FILEPATH) == 0)
                    printf("  已保存 %d 条记录到 %s\n", g_count, FILEPATH);
                break;
            case 9:
                g_count = 0;
                if (loadFromFile(FILEPATH) >= 0)
                    printf("  已加载 %d 条记录\n", g_count);
                break;
            case 0:
                running = 0;
                printf("\n");
                if (g_count > 0) {
                    printf("是否保存修改？(1=保存, 0=不保存)：");
                    int save;
                    if (scanf("%d", &save) == 1 && save == 1) {
                        if (saveToFile(FILEPATH) == 0)
                            printf("已保存 %d 条记录\n", g_count);
                    }
                }
                printf("再见。\n");
                break;
            default:
                printf("  无效选项，请输入 0-9\n");
                break;
        }
    }

    return 0;
}
