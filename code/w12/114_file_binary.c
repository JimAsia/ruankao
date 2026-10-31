/* 114_file_binary.c —— 二进制文件：fwrite / fread 直接存取结构体
 *
 * 文本文件要「转成字符」再写，二进制文件直接把内存字节倒进文件。
 * 好处：快、精确（double 不会丢精度）；坏处：不可读、跨平台不通用。
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    int    id;
    char   name[20];
    double score;
} Student;

int main(void)
{
    Student src[3] = {
        {2026001, "张三", 92.5},
        {2026002, "李四", 78.0},
        {2026003, "王五", 96.5}
    };

    /* ---------- ① 写二进制：fwrite ---------- */
    printf("=== ① 写二进制文件 ===\n");
    printf("  sizeof(Student) = %zu 字节\n", sizeof(Student));
    printf("  3 条记录应占 %zu 字节\n", sizeof(Student) * 3);

    FILE *fp = fopen("students.dat", "wb");     /* wb：二进制写 */
    if (fp == NULL) { perror("fopen wb"); return 1; }

    /* 参数：数据地址、单个元素大小、元素个数、文件指针 */
    size_t written = fwrite(src, sizeof(Student), 3, fp);
    fclose(fp);

    printf("  实际写入 %zu 条\n", written);
    printf("  ⭐ 返回值是「成功写入的元素个数」，不检查就可能丢数据\n");

    /* ---------- ② 读二进制：fread ---------- */
    printf("\n=== ② 读回来 ===\n");
    Student dst[3];
    memset(dst, 0, sizeof(dst));                /* 先清零，便于观察 */

    fp = fopen("students.dat", "rb");           /* rb：二进制读 */
    if (fp == NULL) { perror("fopen rb"); return 1; }

    size_t n = fread(dst, sizeof(Student), 3, fp);
    fclose(fp);

    printf("  读到 %zu 条：\n", n);
    for (size_t i = 0; i < n; i++) {
        printf("    %d %s %.1f\n", dst[i].id, dst[i].name, dst[i].score);
    }
    printf("\n  ⭐ 读回来的数据和原来完全一致 —— double 的 92.5 一位不差\n");

    /* ---------- ③ 文本 vs 二进制，体积对比 ---------- */
    printf("\n=== ③ 同一个数据，两种格式的体积 ===\n");

    fp = fopen("students.txt", "w");
    if (fp == NULL) { perror("fopen txt"); return 1; }
    for (int i = 0; i < 3; i++) {
        fprintf(fp, "%d %s %.1f\n", src[i].id, src[i].name, src[i].score);
    }
    fclose(fp);

    /* 用 ftell 量大小：先定位到末尾，再问当前位置 */
    long binSize, txtSize;
    fp = fopen("students.dat", "rb");
    fseek(fp, 0, SEEK_END);
    binSize = ftell(fp);
    fclose(fp);

    fp = fopen("students.txt", "r");
    fseek(fp, 0, SEEK_END);
    txtSize = ftell(fp);
    fclose(fp);

    printf("  二进制 students.dat: %ld 字节\n", binSize);
    printf("  文本   students.txt: %ld 字节\n", txtSize);
    printf("\n  二进制 = 3 × 32 = 96 字节，正好是 sizeof(Student) × 3\n");
    printf("  文本按实际字符数，中文一个字 3 字节\n");

    printf("\n  ⚠️ 注意：这里二进制反而更大（96 > 63）！\n");
    printf("     原因：char name[20] 是定长的，张三只用 6 字节却占 20，\n");
    printf("     而文本只存真正用到的字符。\n");
    printf("     所以「二进制更省空间」并不总成立，取决于字段长度是否浪费。\n");
    printf("     二进制真正的优势是速度和 fseek 随机访问，不是体积。\n");

    /* ---------- ④ 二进制的致命缺陷 ---------- */
    printf("\n=== ④ 二进制文件的三个坑 ===\n");
    printf("  1. 不可读：用记事本打开是乱码\n");
    printf("  2. 不可跨平台：int 大小、字节序、对齐方式都可能不同\n");
    printf("     在 x86 Windows 写的 .dat，拿到 ARM 机器上可能读错\n");
    printf("  3. 结构体一变，旧文件全废\n");
    printf("     给 Student 加一个字段，原来 32 字节变成 40，\n");
    printf("     读旧文件时每条记录都会错位\n");
    printf("\n  ⭐ 所以工程上更常见的是「文本存配置，二进制存大数据」\n");
    printf("     软考考文件大题基本都用文本模式，二进制只考概念\n");

    /* ---------- ⑤ fseek 随机读写 ---------- */
    printf("\n=== ⑤ fseek：直接跳到第 2 条记录 ===\n");
    fp = fopen("students.dat", "rb");
    if (fp == NULL) { perror("fopen rb"); return 1; }

    /* 跳过前 1 条记录：偏移 1 × sizeof(Student) */
    fseek(fp, (long)sizeof(Student), SEEK_SET);

    Student one;
    if (fread(&one, sizeof(Student), 1, fp) == 1) {
        printf("  第 2 条：%d %s %.1f\n", one.id, one.name, one.score);
    }
    fclose(fp);

    printf("\n  ⭐ 这是二进制文件的唯一优势：O(1) 定位任意记录\n");
    printf("     文本文件要找到第 1000 条，只能从头一行一行数\n");
    printf("     fseek 的第三个参数：SEEK_SET 开头、SEEK_CUR 当前、SEEK_END 末尾\n");

    return 0;
}
