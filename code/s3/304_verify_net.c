/* ============================================================================
 * 304_verify_net.c  —— S3-04 网络：子网划分与 CIDR 聚合
 *
 * 网络题里唯一会算的就是 IP 地址，而它恰好最容易错：
 *   ① 给 IP/前缀，求子网掩码、网络地址、广播地址、可用主机数
 *   ② 把一个网段划分成若干子网，写出每段的地址范围
 *   ③ CIDR 聚合（把连续网段合成一个）
 *   ④ 判断两个 IP 是否在同一子网
 *
 * 本文件把这些全部真算一遍，讲义里的答案直接引用它的输出。
 *
 * 编译：gcc -std=c17 -Wall -Wextra -o 304.exe 304_verify_net.c
 * ==========================================================================*/

#include <stdio.h>
#include <stdint.h>

/* ---------------- IP 与字符串互转 ---------------- */

static uint32_t ip2u(const char *s)
{
    unsigned a, b, c, d;
    if (sscanf(s, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) return 0;
    return ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) | d;
}

static void u2ip(uint32_t u, char *out)
{
    sprintf(out, "%u.%u.%u.%u",
            (u >> 24) & 0xFF, (u >> 16) & 0xFF, (u >> 8) & 0xFF, u & 0xFF);
}

static uint32_t maskOf(int prefix)
{
    if (prefix == 0) return 0;
    return 0xFFFFFFFFu << (32 - prefix);
}

/* ---------------- 打印一段网络信息 ---------------- */

static void showNet(const char *ip, int prefix)
{
    uint32_t a = ip2u(ip);
    uint32_t m = maskOf(prefix);
    uint32_t net = a & m;
    uint32_t bcast = net | ~m;
    uint32_t hosts = (prefix >= 31) ? (1u << (32 - prefix))   /* /31 /32 特例 */
                                    : ((1u << (32 - prefix)) - 2);
    char s1[20], s2[20], s3[20], s4[20];

    u2ip(m, s1); u2ip(net, s2); u2ip(bcast, s3);
    u2ip(net + 1, s4);

    printf("  %-18s/%-3d\n", ip, prefix);
    printf("    子网掩码    %-16s\n", s1);
    printf("    网络地址    %-16s\n", s2);
    printf("    广播地址    %-16s\n", s3);
    if (prefix <= 30) {
        char e[20]; u2ip(bcast - 1, e);
        printf("    可用主机    %s ~ %s\n", s4, e);
    } else {
        printf("    可用主机    （/31 /32 无广播地址概念）\n");
    }
    printf("    主机数      %u\n\n", hosts);
}

int main(void)
{
    /* ---------------- ① 单个地址分析 ---------------- */
    printf("=== ① 给定 IP 与前缀，求网络信息 ===\n\n");
    showNet("192.168.1.130", 26);
    showNet("10.10.10.10", 12);
    showNet("172.16.5.200", 20);

    /* ---------------- ② 前缀容量表 ---------------- */
    printf("=== ② 常用前缀的容量 ===\n");
    printf("  %-8s %-18s %-12s %s\n", "前缀", "掩码", "地址总数", "可用主机数");
    for (int p = 24; p <= 30; p++) {
        char m[20];
        u2ip(maskOf(p), m);
        unsigned total = 1u << (32 - p);
        printf("  /%-7d %-18s %-12u %u\n", p, m, total, total - 2);
    }
    printf("  ⭐ 规律：前缀每 +1，地址数减半，可用主机数约减半再减 2。\n\n");

    /* ---------------- ③ 子网划分 ---------------- */
    printf("=== ③ 把 192.168.1.0/24 划分成 4 个子网 ===\n");
    printf("  需要借 2 位（2^2 = 4），新前缀 = 24 + 2 = 26\n\n");
    for (int i = 0; i < 4; i++) {
        uint32_t net = ip2u("192.168.1.0") + (uint32_t)i * 64;   /* 每段 64 个地址 */
        char n[20], f[20], l[20], b[20];
        u2ip(net, n); u2ip(net + 1, f); u2ip(net + 62, l); u2ip(net + 63, b);
        printf("  子网 %d：%-16s/26\n", i + 1, n);
        printf("          可用 %s ~ %s，广播 %s\n", f, l, b);
    }
    printf("\n  ⭐ 每段 64 个地址 = 2^6，其中 62 个可用（去掉网络号和广播号）。\n\n");

    /* ---------------- ④ CIDR 聚合 ---------------- */
    printf("=== ④ CIDR 聚合 ===\n");
    {
        /* 4 个连续的 /24 合成一个 /22 */
        const char *blocks[] = {"192.168.0.0", "192.168.1.0", "192.168.2.0", "192.168.3.0"};
        uint32_t base = ip2u(blocks[0]);
        int ok = 1;
        for (int i = 0; i < 4; i++)
            if (ip2u(blocks[i]) != base + (uint32_t)i * 256) ok = 0;
        printf("  待聚合：");
        for (int i = 0; i < 4; i++) printf("%s/24 ", blocks[i]);
        printf("\n");

        /* 共同的最高位有多少：从 /24 往前找，看能不能合并 */
        uint32_t m22 = maskOf(22);
        int can = 1;
        for (int i = 0; i < 4; i++)
            if ((ip2u(blocks[i]) & m22) != (base & m22)) can = 0;

        if (ok && can) {
            char n[20];
            u2ip(base & m22, n);
            printf("  聚合结果：%s/22  %s\n", n,
                   (base & m22) == base ? "（起始地址正好对齐）" : "（起始地址未对齐，需先对齐）");
            printf("  ⭐ 4 个连续 /24 正好填满一个 /22（2^(24-22) = 4）。\n");
        } else {
            printf("  无法聚合\n");
        }
    }

    /* ---------------- ⑤ 判断是否同子网 ---------------- */
    printf("\n=== ⑤ 判断两个 IP 是否在同一子网 ===\n");
    struct { const char *a, *b; int prefix; } cases[] = {
        {"192.168.1.10", "192.168.1.200", 24},
        {"192.168.1.10", "192.168.2.10",  24},
        {"192.168.1.10", "192.168.1.70",  26},
        {"192.168.1.10", "192.168.1.70",  25}
    };
    for (int i = 0; i < 4; i++) {
        uint32_t m = maskOf(cases[i].prefix);
        int same = (ip2u(cases[i].a) & m) == (ip2u(cases[i].b) & m);
        char na[20], nb[20];
        u2ip(ip2u(cases[i].a) & m, na);
        u2ip(ip2u(cases[i].b) & m, nb);
        printf("  %-15s vs %-15s /%-2d → 网络号 %s / %s  %s\n",
               cases[i].a, cases[i].b, cases[i].prefix, na, nb,
               same ? "同一子网" : "不同子网");
    }
    printf("  ⭐ 关键：看【网络号】是否相同，而不是看 IP 像不像。\n");

    /* ---------------- ⑥ 主机数反推 ---------------- */
    printf("\n=== ⑥ 反推：需要 50 台主机，前缀该取多少？ ===\n");
    for (int p = 24; p <= 30; p++) {
        unsigned hosts = (1u << (32 - p)) - 2;
        printf("  /%-2d → %-4u 台 %s\n", p, hosts, hosts >= 50 ? "✓ 够用" : "");
    }
    printf("  ⭐ 从 /26 开始够（62 台）。注意不能只看 ≥50 就选 /27（30 台不够），\n");
    printf("     也不能只看地址数（64）而不减 2。\n");
    return 0;
}
