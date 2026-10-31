/* ============================================================================
 * 301_verify_cs.c  —— S3-01 计算机组成：数值题验证
 *
 * S3 的题大多靠背，但有几类必须算对，而且考试给分是死的：
 *   ① 原码/反码/补码/移码的表示范围与具体值
 *   ② IEEE 754 单精度的位布局
 *   ③ Cache 平均访问时间
 *   ④ 总线带宽
 *   ⑤ 串联 / 并联可靠性
 *   ⑥ MIPS 与 CPI
 *
 * 本文件把讲义里出现的每个数字都算一遍。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 301.exe 301_verify_cs.c
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>
#include <math.h>

/* ---------- ① 8 位机器数的四种编码 ---------- */
static void bin8(unsigned v, char *out)
{
    for (int i = 0; i < 8; i++) {
        out[i] = ((v >> (7 - i)) & 1) ? '1' : '0';
        if (i == 3) out[i + 1] = ' ';        /* 高 4 位 / 低 4 位之间加空格 */
    }
    out[9] = '\0';
}

static void printCode(int v)
{
    char s[10];

    unsigned sign = v < 0 ? 1u : 0u;
    int mag = v < 0 ? -v : v;

    printf("  %-6d", v);

    /* 原码：-128 超出范围（尾数 7 位放不下 128），没有原码 */
    if (mag > 127) {
        printf(" %-11s", "—");
    } else {
        bin8((sign << 7) | (unsigned)mag, s);
        printf(" %-11s", s);
    }

    /* 反码：范围同原码 */
    if (mag > 127) {
        printf(" %-11s", "—");
    } else {
        unsigned fm = (v >= 0) ? ((sign << 7) | (unsigned)mag)
                               : ((sign << 7) | (unsigned)(~mag & 0x7F));
        bin8(fm, s);
        printf(" %-11s", s);
    }

    /* 补码：范围 -128..127，-128 的补码是 1000 0000 */
    unsigned bm;
    if (v >= 0)      bm = (unsigned)v;
    else if (v == -128) bm = 0x80;
    else             bm = (((sign << 7) | (unsigned)(~mag & 0x7F)) + 1) & 0xFF;
    bin8(bm, s);
    printf(" %-11s", s);

    /* 移码 = 补码符号位取反 */
    bin8(bm ^ 0x80, s);
    printf(" %s\n", s);
}

/* ---------- ② IEEE 754 单精度 ---------- */
static unsigned floatBits(float f)
{
    unsigned u;
    memcpy(&u, &f, 4);
    return u;
}

static void showFloat(float f)
{
    unsigned u = floatBits(f);
    unsigned sign = (u >> 31) & 1;
    unsigned exp  = (u >> 23) & 0xFF;
    unsigned frac = u & 0x7FFFFF;
    printf("  %-8g → 0x%08X\n", f, u);
    printf("           符号 %u，阶码 %u（真值 %d），尾数 0x%06X\n",
           sign, exp, (int)exp - 127, frac);

    /* 手工拼位串，方便对照 */
    printf("           位串：");
    for (int i = 31; i >= 0; i--) {
        printf("%u", (u >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
}

/* ---------- 共用 ---------- */
int main(void)
{
    printf("=== ① 8 位机器数的四种编码 ===\n");
    printf("  %-6s %-11s %-11s %-11s %s\n", "真值", "原码", "反码", "补码", "移码");
    int vals[] = {127, 1, 0, -1, -127, -128};
    for (int i = 0; i < 6; i++) printCode(vals[i]);

    printf("\n  表示范围（n = 8）：\n");
    printf("    原码 / 反码：-(2^7-1) ~ +(2^7-1) = %d ~ %d\n", -(127), 127);
    printf("    补码 / 移码：-2^7 ~ +(2^7-1)     = %d ~ %d\n", -128, 127);
    printf("  ⭐ 补码比原码多表示一个数 %d，且 0 只有一种编码。\n", -128);
    printf("     原码的 +0 = 0000 0000，-0 = 1000 0000 —— 有两个零。\n");

    /* 验证：-128 的补码是 1000 0000，没有对应的原码 */
    printf("\n  -128 的补码 = 1000 0000 = 0x80（原码无法表示 -128，这就是补码的优势）\n");
    printf("  -1 的补码 = 1111 1111 = 0xFF（全 1）\n");

    /* 补码减法的验证：7 - 5 = 7 + (-5) */
    printf("\n  补码把减法变加法：7 - 5 = 7 + (-5)\n");
    printf("    7  的补码 = 0000 0111\n");
    printf("    -5 的补码 = 1111 1011\n");
    printf("    相加      = 1 0000 0010 → 丢弃进位 = 0000 0010 = 2 ✓\n");

    /* ---------- ② IEEE 754 ---------- */
    printf("\n=== ② IEEE 754 单精度（1 位符号 + 8 位阶码 + 23 位尾数）===\n");
    showFloat(12.5f);
    showFloat(0.5f);
    showFloat(-6.0f);
    printf("\n  手工推导 12.5：\n");
    printf("    12.5 = 1100.1(B) = 1.1001 × 2^3\n");
    printf("    符号 0；阶码 = 3 + 127 = 130 = 1000 0010；尾数 = 1001 000...\n");
    printf("    拼起来 0 10000010 10010000000000000000000 = 0x41480000\n");

    printf("\n  单精度能表示的范围与精度：\n");
    printf("    阶码 8 位（移码，偏移 127）→ 指数范围 -126 ~ +127\n");
    printf("    尾数 23 位（隐含最高位 1）→ 有效数字 24 位\n");
    printf("    双精度：1 + 11 + 52，偏移 1023\n");

    /* ---------- ③ Cache ---------- */
    printf("\n=== ③ Cache 平均访问时间 ===\n");
    printf("  公式：t = h × t_cache + (1-h) × t_main\n");
    printf("  %-8s %-12s %-12s %s\n", "命中率h", "t_cache=1ns", "t_cache=2ns", "说明");
    double hs[] = {0.90, 0.95, 0.98, 0.99};
    for (int i = 0; i < 4; i++) {
        double h = hs[i];
        double t1 = h * 1 + (1 - h) * 10;
        double t2 = h * 2 + (1 - h) * 10;
        printf("  %-8.2f %-12.3f %-12.3f %s\n", h, t1, t2,
               i == 3 ? "← 命中率 99% 时几乎等于 Cache 速度" : "");
    }
    printf("  ⭐ 主存 10ns，命中率从 90%% 提到 99%%，平均访问时间从 1.9ns 降到 1.09ns。\n");
    printf("     所以 Cache 的命中率比容量更重要。\n");

    /* ---------- ④ 总线带宽 ---------- */
    printf("\n=== ④ 总线带宽 ===\n");
    printf("  带宽 = 每次传输字节数 × 传输频率\n");
    struct { int width; double freq; const char *name; } bus[] = {
        {32, 66,  "32 位 / 66 MHz"},
        {64, 100, "64 位 / 100 MHz"},
        {32, 133, "32 位 / 133 MHz"}
    };
    for (int i = 0; i < 3; i++) {
        double bytes = bus[i].width / 8.0;
        double bw = bytes * bus[i].freq;      /* MB/s */
        printf("  %-18s → %.0f B × %.0f MHz = %.0f MB/s\n",
               bus[i].name, bytes, bus[i].freq, bw);
    }
    printf("  ⭐ 注意单位：位(bit) 要除以 8 换成字节(B)。这是最常见的失分点。\n");

    /* ---------- ⑤ 可靠性 ---------- */
    printf("\n=== ⑤ 串联 / 并联可靠性 ===\n");
    printf("  串联：R = R1 × R2 × ...（任一个坏就整体坏）\n");
    printf("  并联：R = 1 - (1-R1)(1-R2)...（全坏才坏）\n");
    double r1 = 0.9, r2 = 0.9, r3 = 0.9;
    printf("  三个 0.9 的部件：\n");
    printf("    串联 R = %.4f\n", r1 * r2 * r3);
    printf("    并联 R = %.4f\n", 1 - (1 - r1) * (1 - r2) * (1 - r3));
    printf("  ⭐ 并联能大幅提高可靠性，代价是成本翻倍。\n");

    /* ---------- ⑥ MIPS ---------- */
    printf("\n=== ⑥ 性能指标 ===\n");
    printf("  MIPS = 主频 / (CPI × 10^6)\n");
    struct { double freq; double cpi; } p[] = {
        {1000, 2.0}, {2000, 2.0}, {2000, 4.0}
    };
    for (int i = 0; i < 3; i++) {
        double mips = p[i].freq / (p[i].cpi * 1.0);
        printf("  主频 %4.0f MHz，CPI = %.1f → MIPS = %.0f\n",
               p[i].freq, p[i].cpi, mips);
    }
    printf("  ⭐ 主频高不一定快：CPI 翻倍会把主频的优势全吃掉。\n");

    printf("\n  其他常用公式：\n");
    printf("    响应时间 = 1 / 吞吐率\n");
    printf("    加速比 = 旧时间 / 新时间\n");
    printf("    流水线加速比 ≈ 流水级数（理想情况）\n");
    return 0;
}
