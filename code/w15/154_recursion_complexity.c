/* 154_recursion_complexity.c —— 递归的复杂度：看「每层分几支、每支多大、几层停」
 *
 * 递归复杂度用递推式表达：
 *   T(n) = a·T(n/b) + f(n)
 *   其中 a 是「每层分几支」，n/b 是「每支规模」，f(n) 是「拆分和合并的开销」
 *
 * 本程序用**调用计数器**把每个递归的实际调用次数数出来，和理论公式对照。
 */

#include <stdio.h>

static long long g_calls = 0;

/* ---------- ① 阶乘：每层只分 1 支，规模减 1 ---------- */
long long fact(int n)
{
    g_calls++;
    if (n <= 1) return 1;
    return n * fact(n - 1);
}
/* T(n) = T(n-1) + O(1) → 共 n 层 → O(n) */

/* ---------- ② 朴素斐波那契：每层分 2 支 ---------- */
long long fib(int n)
{
    g_calls++;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
/* T(n) = T(n-1) + T(n-2) + O(1) → 指数级 O(2^n) */

/* ---------- ③ 二分查找（递归版）：每层分 1 支，规模减半 ---------- */
int binarySearchRec(const int a[], int lo, int hi, int key)
{
    g_calls++;
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == key) return mid;
    if (a[mid] < key)  return binarySearchRec(a, mid + 1, hi, key);
    return binarySearchRec(a, lo, mid - 1, key);
}
/* T(n) = T(n/2) + O(1) → O(log n) */

/* ---------- ④ 归并排序：每层分 2 支，每支规模减半，合并要 O(n) ---------- */
static void merge(int a[], int lo, int mid, int hi, int tmp[])
{
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        g_calls++;                                  /* 每次比较算一次操作 */
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= hi)  tmp[k++] = a[j++];
    for (i = lo; i <= hi; i++) a[i] = tmp[i];
}

void mergeSort(int a[], int lo, int hi, int tmp[])
{
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    mergeSort(a, lo, mid, tmp);
    mergeSort(a, mid + 1, hi, tmp);
    merge(a, lo, mid, hi, tmp);
}
/* T(n) = 2T(n/2) + O(n) → O(n log n) */

/* ---------- ⑤ 汉诺塔：每层分 2 支，规模减 1 ---------- */
void hanoi(int n)
{
    g_calls++;
    if (n == 0) return;
    hanoi(n - 1);
    hanoi(n - 1);
}
/* T(n) = 2T(n-1) + O(1) → O(2^n) */

int main(void)
{
    /* ---------- ① 阶乘 O(n) ---------- */
    printf("=== ① 阶乘 fact(n)：O(n) ===\n");
    printf("  %-6s %-12s %s\n", "n", "调用次数", "说明");
    for (int n = 5; n <= 20; n += 5) {
        g_calls = 0;
        (void)fact(n);
        printf("  %-6d %-12lld 次数 = n（每层只分 1 支）\n", n, g_calls);
    }
    printf("  ⭐ n 翻倍，调用次数也翻倍 —— 这就是 O(n)。\n");

    /* ---------- ② 斐波那契 O(2^n) ---------- */
    printf("\n=== ② 朴素 fib(n)：O(2^n) ===\n");
    printf("  %-6s %-14s %s\n", "n", "调用次数", "比上一行");
    long long prev = 0;
    for (int n = 10; n <= 30; n += 5) {
        g_calls = 0;
        (void)fib(n);
        printf("  %-6d %-14lld ", n, g_calls);
        if (prev > 0) printf("%.2f 倍", (double)g_calls / (double)prev);
        printf("\n");
        prev = g_calls;
    }
    printf("\n  ⭐ n 每加 5，次数涨约 11 倍（接近 2^5 = 32 的一半，\n");
    printf("     因为 T(n)=T(n-1)+T(n-2) 的增长因子是黄金比 1.618，1.618^5 ≈ 11.1）\n");
    printf("     软考按 O(2^n) 回答即可，指数级就够了。\n");

    /* ---------- ③ 二分查找 O(log n) ---------- */
    printf("\n=== ③ 二分查找：O(log n) ===\n");
    int arr[1024];
    for (int i = 0; i < 1024; i++) arr[i] = i * 2;      /* 0,2,4,... */

    printf("  %-10s %-12s %s\n", "数组长度", "比较次数", "log2(n)");
    int sizes[] = {16, 64, 256, 1024};
    for (int k = 0; k < 4; k++) {
        int n = sizes[k];
        g_calls = 0;
        (void)binarySearchRec(arr, 0, n - 1, -1);       /* 找不存在的，走最坏情况 */
        printf("  %-10d %-12lld ", n, g_calls);
        /* 手算 log2 */
        int lg = 0, x = n;
        while (x > 1) { x /= 2; lg++; }
        printf("%d\n", lg);
        printf("              （最坏 %lld 次，约等于 log2(%d)+1）\n", g_calls, n);
    }
    printf("  ⭐ 1024 个元素最多比 11 次；顺序查找最坏要 1024 次。\n");
    printf("     这就是 O(log n) 和 O(n) 的差距 —— 数据越大越明显。\n");

    /* ---------- ④ 归并排序 O(n log n) ---------- */
    printf("\n=== ④ 归并排序：O(n log n) ===\n");
    int tmp[512];                                       /* 归并用的临时数组 */

    printf("  %-10s %-14s %s\n", "n", "比较次数", "n log2 n");
    int ms[] = {32, 64, 128, 256, 512};
    for (int k = 0; k < 5; k++) {
        int n = ms[k];
        int work[512];
        for (int i = 0; i < n; i++) work[i] = n - i;

        g_calls = 0;
        mergeSort(work, 0, n - 1, tmp);

        int lg = 0, x = n;
        while (x > 1) { x /= 2; lg++; }
        printf("  %-10d %-14lld %d\n", n, g_calls, n * lg);
    }
    printf("\n  ⭐ 比较次数比 n·log2(n) 小一些，但同阶 —— \n");
    printf("     因为每层合并的总比较次数不超过 n，共 log n 层。\n");
    printf("     归并排序的好处是**稳定在 O(n log n)**，不像快排会退化。\n");

    /* ---------- ⑤ 汉诺塔 O(2^n) ---------- */
    printf("\n=== ⑤ 汉诺塔：O(2^n) ===\n");
    printf("  %-8s %-14s %-14s %s\n", "盘子数", "调用次数", "2^(n+1)-1", "移动步数 2^n-1");
    for (int n = 4; n <= 20; n += 4) {
        g_calls = 0;
        hanoi(n);
        long long steps = 1;
        for (int i = 0; i < n; i++) steps *= 2;
        steps -= 1;
        printf("  %-8d %-14lld %-14lld %lld\n", n, g_calls, 2 * steps + 1, steps);
    }
    printf("\n  ⭐ 这里调用次数是 2^(n+1)-1，不是 2^n-1 —— 差一倍。\n");
    printf("     原因：本函数把「盘数为 0 的空调用」也数进去了，\n");
    printf("     T(n) = 2T(n-1) + 1 且 T(0) = 1，解得 2^(n+1)-1。\n");
    printf("     而真正的移动步数是 2^n - 1。\n");
    printf("     ⭐ 两者差一个常数因子 2 —— 按大 O 规则，都是 O(2^n)。\n");
    printf("        这正是「常数不影响量级」的又一个例子。\n");
    printf("     n=64 的经典问题：2^64-1 步，每秒一步要 5849 亿年。\n");

    /* ---------- ⑥ 递推式速查 ---------- */
    printf("\n=== ⑥ 四种递推式，四种结论 ===\n");
    printf("  %-26s %-14s %s\n", "递推式", "复杂度", "典型算法");
    printf("  ----------------------------------------------------------\n");
    printf("  %-26s %-14s %s\n", "T(n) = T(n-1) + O(1)",   "O(n)",      "阶乘、递归求和");
    printf("  %-26s %-14s %s\n", "T(n) = T(n/2) + O(1)",   "O(log n)",  "二分查找");
    printf("  %-26s %-14s %s\n", "T(n) = 2T(n/2) + O(n)",  "O(n log n)","归并排序");
    printf("  %-26s %-14s %s\n", "T(n) = 2T(n-1) + O(1)",  "O(2^n)",    "汉诺塔");
    printf("  %-26s %-14s %s\n", "T(n) = T(n-1) + T(n-2)", "O(2^n)",    "朴素斐波那契");

    printf("\n  ⭐ 看递推式的口诀：\n");
    printf("     规模减 1 且只分 1 支 → O(n)\n");
    printf("     规模减半且只分 1 支 → O(log n)\n");
    printf("     规模减半分 2 支且合并要 O(n) → O(n log n)\n");
    printf("     分 2 支但规模只减 1 → 指数级\n");

    return 0;
}
