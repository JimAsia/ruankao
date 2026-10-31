/* ============================================================================
 * 303_verify_db.c  —— S3-03 数据库：范式判定与关系代数结果验证
 *
 * 数据库题里有两类必须算准：
 *   ① 候选键求解 + 范式判定（1NF/2NF/3NF/BCNF）—— 最容易"感觉对"
 *   ② 关系代数表达式的运算结果（σ π ⋈ ÷）
 *
 * 本文件用属性闭包算法把候选键和范式算出来，再把关系代数的结果
 * 真的算一遍，用来核对讲义里的答案。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 303.exe 303_verify_db.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

/* ==========================================================================
 * 一、函数依赖、属性闭包、候选键、范式
 * ========================================================================*/

#define MAXA 8

typedef struct {
    const char *name;             /* 关系名 */
    int n;                        /* 属性个数 */
    const char *attr[MAXA];       /* 属性名 */
    struct { unsigned lhs, rhs; const char *text; } fd[8];
    int nfd;
} Schema;

/* 属性集用位掩码表示：第 i 位 = 第 i 个属性 */

static unsigned closure(unsigned x, const Schema *s)
{
    unsigned prev;
    do {
        prev = x;
        for (int i = 0; i < s->nfd; i++)
            if ((s->fd[i].lhs & x) == s->fd[i].lhs)     /* lhs ⊆ x */
                x |= s->fd[i].rhs;
    } while (x != prev);
    return x;
}

static void printSet(unsigned mask, const Schema *s, const char *tag)
{
    printf("  %-16s { ", tag);
    int first = 1;
    for (int i = 0; i < s->n; i++)
        if (mask & (1u << i)) {
            printf("%s%s", first ? "" : ",", s->attr[i]);
            first = 0;
        }
    if (first) printf("空");
    printf(" }\n");
}

static void analyze(const Schema *s, const char *title)
{
    unsigned all = (1u << s->n) - 1;
    unsigned cand[64];
    int nc = 0;

    printf("\n=== %s ===\n", title);
    printf("  关系 %s(", s->name);
    for (int i = 0; i < s->n; i++) printf("%s%s", s->attr[i], i == s->n - 1 ? "" : ", ");
    printf(")\n  函数依赖：");
    for (int i = 0; i < s->nfd; i++) printf("%s%s", i ? "，" : "", s->fd[i].text);
    printf("\n\n");

    /* 求所有候选键：闭包等于全集的极小属性集 */
    for (unsigned m = 1; m <= all; m++) {
        if (closure(m, s) != all) continue;
        /* 极小性：去掉任一属性后闭包不再等于全集 */
        int minimal = 1;
        for (int i = 0; i < s->n; i++)
            if ((m & (1u << i)) && closure(m & ~(1u << i), s) == all) {
                minimal = 0; break;
            }
        if (minimal) cand[nc++] = m;
    }

    printf("  候选键：");
    for (int i = 0; i < nc; i++) {
        printf("{ ");
        for (int k = 0; k < s->n; k++)
            if (cand[i] & (1u << k)) printf("%s ", s->attr[k]);
        printf("}%s", i == nc - 1 ? "\n" : "  ");
    }

    /* 主属性 = 所有候选键的并 */
    unsigned prime = 0;
    for (int i = 0; i < nc; i++) prime |= cand[i];
    printSet(prime, s, "主属性");

    /* 逐条 FD 检查 */
    printf("\n  FD 检查：\n");
    int is2 = 1, is3 = 1, isbcnf = 1;
    for (int i = 0; i < s->nfd; i++) {
        unsigned lhs = s->fd[i].lhs, rhs = s->fd[i].rhs;
        int lhsSuper = (closure(lhs, s) == all);        /* lhs 是超键 */
        unsigned nonprimeRhs = rhs & ~prime;            /* RHS 里的非主属性 */

        /* 2NF：非主属性不能只依赖候选键的一部分 */
        int partial = 0;
        if (nonprimeRhs) {
            for (int c = 0; c < nc; c++)
                if ((lhs & cand[c]) == lhs && lhs != cand[c]) { partial = 1; break; }
        }
        if (partial) is2 = 0;

        /* 3NF：要么 lhs 是超键，要么 RHS 全是主属性 */
        int v3 = !(lhsSuper || (rhs & ~prime) == 0);
        if (v3) is3 = 0;

        /* BCNF：任何非平凡 FD 的 lhs 都必须是超键 */
        int vb = !lhsSuper;
        if (vb) isbcnf = 0;

        printf("    %-16s lhs%s超键，RHS%s非主属性 %s%s%s\n",
               s->fd[i].text,
               lhsSuper ? "是" : "不是",
               nonprimeRhs ? "含" : "不含",
               partial ? "→ 违反 2NF " : "",
               v3 ? "→ 违反 3NF " : "",
               vb ? "→ 违反 BCNF" : "");
    }

    printf("\n  结论：");
    if (!is2)          printf("最高满足 1NF（存在非主属性对候选键的部分依赖）\n");
    else if (!is3)     printf("最高满足 2NF（存在非主属性对候选键的传递依赖）\n");
    else if (!isbcnf)  printf("最高满足 3NF（存在主属性对候选键的部分/传递依赖）\n");
    else               printf("满足 BCNF（所有决定因素都是超键）\n");
}

/* ==========================================================================
 * 二、关系代数：真的算一遍
 * ========================================================================*/

typedef struct { const char *sno, *sname, *dept; } Student;
typedef struct { const char *sno, *cno; int grade; } SC;

static Student S[] = {
    {"S1", "张三", "计算机"},
    {"S2", "李四", "数学"},
    {"S3", "王五", "计算机"}
};
static SC SCtab[] = {
    {"S1", "C1", 90}, {"S1", "C2", 85}, {"S1", "C3", 88},
    {"S2", "C1", 70},
    {"S3", "C3", 95}
};
static const char *C[] = {"C1", "C2", "C3"};

#define NS 3
#define NSC (int)(sizeof(SCtab) / sizeof(SCtab[0]))
#define NC 3

int main(void)
{
    /* ---------------- 范式判定 ---------------- */
    printf("################ 一、候选键与范式判定 ################\n");

    /* 例 1：经典学生选课表，最高 1NF */
    Schema s1 = {
        "学生选课", 6, {"学号", "姓名", "系名", "系主任", "课程号", "成绩"},
        {
            {0x01, 0x02, "学号→姓名"},
            {0x01, 0x04, "学号→系名"},
            {0x04, 0x08, "系名→系主任"},
            {0x21, 0x20, "(学号,课程号)→成绩"}
        }, 4
    };
    /* 属性：A=学号 B=姓名 C=? 这里简化：0=学号 1=姓名 2=系名 3=系主任 4=课程号 5=成绩
     * 为避免混淆，重写 FD 位：
     *   学号(bit0) → 姓名(bit1)、系名(bit2)
     *   系名(bit2) → 系主任(bit3)
     *   (学号,课程号)(bit0|bit4) → 成绩(bit5)
     */
    s1.fd[0].lhs = 0x01; s1.fd[0].rhs = 0x02;
    s1.fd[1].lhs = 0x01; s1.fd[1].rhs = 0x04;
    s1.fd[2].lhs = 0x04; s1.fd[2].rhs = 0x08;
    s1.fd[3].lhs = 0x11; s1.fd[3].rhs = 0x20;
    analyze(&s1, "例 1：学生选课（1NF）");

    /* 例 2：只有主键决定全部，BCNF */
    Schema s2 = {
        "选课成绩", 3, {"学号", "课程号", "成绩"},
        { {0x03, 0x04, "(学号,课程号)→成绩"} }, 1
    };
    analyze(&s2, "例 2：选课成绩（BCNF）");

    /* 例 3：A→B, B→C，A 是候选键 → 2NF 但非 3NF */
    Schema s3 = {
        "R3", 3, {"A", "B", "C"},
        { {0x01, 0x02, "A→B"}, {0x02, 0x04, "B→C"} }, 2
    };
    analyze(&s3, "例 3：A→B, B→C（2NF，非 3NF）");

    /* 例 4：AB→C, C→B，候选键 AB、AC → 3NF 但非 BCNF */
    Schema s4 = {
        "R4", 3, {"A", "B", "C"},
        { {0x03, 0x04, "AB→C"}, {0x04, 0x02, "C→B"} }, 2
    };
    analyze(&s4, "例 4：AB→C, C→B（3NF，非 BCNF）");

    /* ---------------- 关系代数 ---------------- */
    printf("\n################ 二、关系代数运算 ################\n");
    printf("\n  S（学生）：\n");
    for (int i = 0; i < NS; i++)
        printf("    %-4s %-6s %s\n", S[i].sno, S[i].sname, S[i].dept);
    printf("  SC（选课）：\n");
    for (int i = 0; i < NSC; i++)
        printf("    %-4s %-4s %d\n", SCtab[i].sno, SCtab[i].cno, SCtab[i].grade);
    printf("  C（课程）：C1 C2 C3\n");

    /* ① 选择 + 投影 */
    printf("\n  ① π姓名(σ系名='计算机'(S))\n     结果：");
    for (int i = 0; i < NS; i++)
        if (strcmp(S[i].dept, "计算机") == 0) printf("%s ", S[i].sname);
    printf("\n");

    /* ② 自然连接 + 选择 + 投影 */
    printf("\n  ② π姓名(σ课程号='C1'(S ⋈ SC))\n     结果：");
    for (int i = 0; i < NS; i++)
        for (int j = 0; j < NSC; j++)
            if (strcmp(S[i].sno, SCtab[j].sno) == 0 && strcmp(SCtab[j].cno, "C1") == 0)
                printf("%s ", S[i].sname);
    printf("\n");

    /* ③ 除法：选修了全部课程的学生 */
    printf("\n  ③ π学号,课程号(SC) ÷ π课程号(C)\n     结果：");
    for (int i = 0; i < NS; i++) {
        int have = 1;
        for (int c = 0; c < NC; c++) {
            int found = 0;
            for (int j = 0; j < NSC; j++)
                if (strcmp(SCtab[j].sno, S[i].sno) == 0 &&
                    strcmp(SCtab[j].cno, C[c]) == 0) { found = 1; break; }
            if (!found) { have = 0; break; }
        }
        if (have) printf("%s(%s) ", S[i].sno, S[i].sname);
    }
    printf("\n     ⭐ 除法的含义：找一个学生，他选的课程【覆盖】了 C 里的全部课程。\n");

    /* ④ 差集：没选任何课的学生 */
    printf("\n  ④ π学号(S) − π学号(SC)\n     结果：");
    for (int i = 0; i < NS; i++) {
        int taken = 0;
        for (int j = 0; j < NSC; j++)
            if (strcmp(S[i].sno, SCtab[j].sno) == 0) { taken = 1; break; }
        if (!taken) printf("%s(%s) ", S[i].sno, S[i].sname);
    }
    printf("（空说明每个学生都选了课）\n");

    return 0;
}
