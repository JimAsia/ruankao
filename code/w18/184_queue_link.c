/* 184_queue_link.c —— 链队列 + 两个经典应用
 *
 * 链队列用带头结点的单链表：front 指向头结点，rear 指向尾节点。
 * 没有「假溢出」，长度想多长就多长。
 *
 * 应用：
 *   ① 杨辉三角（队列法，每行只用一个队列）
 *   ② 约瑟夫环（循环队列模拟）
 */

#include <stdio.h>
#include <stdlib.h>

/* ==================== 链队列 ==================== */
typedef struct QNode {
    int           data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;           /* 指向头结点（dummy） */
    QNode *rear;            /* 指向最后一个真节点 */
    int    length;
} LinkQueue;

LinkQueue *lqCreate(void)
{
    LinkQueue *Q = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (!Q) return NULL;

    Q->front = (QNode *)malloc(sizeof(QNode));
    if (!Q->front) { free(Q); return NULL; }

    Q->front->next = NULL;
    Q->front->data = 0;
    Q->rear = Q->front;             /* 空队列：rear 也指向头结点 */
    Q->length = 0;
    return Q;
}

int lqEmpty(const LinkQueue *Q) { return Q->front == Q->rear; }

/* 入队：只在 rear 后面加，O(1) */
int lqEnqueue(LinkQueue *Q, int v)
{
    QNode *n = (QNode *)malloc(sizeof(QNode));
    if (!n) return 0;

    n->data = v;
    n->next = NULL;

    Q->rear->next = n;              /* ① 旧尾节点指向新节点 */
    Q->rear = n;                    /* ② rear 前移到新节点 */
    Q->length++;
    return 1;
}

/* 出队：从 front 后面取，O(1) */
int lqDequeue(LinkQueue *Q, int *out)
{
    if (lqEmpty(Q)) return 0;

    QNode *victim = Q->front->next; /* 要出队的是头结点后面那个 */
    if (out) *out = victim->data;

    Q->front->next = victim->next;  /* 头结点跳过它 */

    /* ⚠️ 关键：如果出队的是最后一个节点，rear 会变成悬空指针 */
    if (Q->rear == victim) {
        Q->rear = Q->front;         /* rear 收回头结点 */
    }

    free(victim);
    Q->length--;
    return 1;
}

void lqPrint(const LinkQueue *Q)
{
    printf("  ");
    for (QNode *p = Q->front->next; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf(" -> NULL   (length=%d)\n", Q->length);
}

void lqDestroy(LinkQueue *Q)
{
    if (!Q) return;
    QNode *p = Q->front;
    while (p) { QNode *nx = p->next; free(p); p = nx; }
    free(Q);
}

/* ==================== 应用① 杨辉三角（队列法） ==================== */
/* 思路：队列里放「当前行」。生成下一行时，逐个出队，边出边把「相邻两数之和」
 * 入队到队尾 —— 出队和入队互不干扰，一趟就完成整行的更新。
 * 首尾各补一个 1。 */
void pascalTriangle(int rows)
{
    int q[1024];
    int front = 0, rear = 0;
    const int N = 1024;

    q[rear] = 1;  rear = (rear + 1) % N;      /* 第 1 行只有 1 */
    int rowLen = 1;

    for (int row = 1; row <= rows; row++) {
        /* ① 先打印当前行（只是窥视，不出队） */
        printf("  第 %d 行：", row);
        for (int i = 0; i < rowLen; i++) {
            printf("%4d", q[(front + i) % N]);
        }
        printf("\n");

        /* ② 边出队边生成下一行 */
        int prev = 0;                          /* 左边界当作 0 */
        for (int i = 0; i < rowLen; i++) {
            int a = q[front];
            front = (front + 1) % N;           /* 出队 */
            q[rear] = prev + a;                /* 相邻两数之和入队 */
            rear = (rear + 1) % N;
            prev = a;
        }
        q[rear] = prev;                        /* 末尾补 1 */
        rear = (rear + 1) % N;

        rowLen++;                              /* 下一行多一个元素 */
    }
}

/* ==================== 应用② 约瑟夫环 ==================== */
/* n 个人围成一圈，从 1 开始报数，报到 m 的人出圈，求最后剩下的编号 */
int josephus(int n, int m)
{
    int q[256];
    int front = 0, rear = 0;
    const int N = 256;

    for (int i = 1; i <= n; i++) {
        q[rear] = i;
        rear = (rear + 1) % N;
    }

    int count = n;
    int outOrder[256], outCnt = 0;

    while (count > 1) {
        /* 前 m-1 个人：出队再入队，相当于「跳过」 */
        for (int i = 1; i < m; i++) {
            q[rear] = q[front];
            front = (front + 1) % N;
            rear = (rear + 1) % N;
        }
        /* 第 m 个人出圈 */
        outOrder[outCnt++] = q[front];
        front = (front + 1) % N;
        count--;
    }

    printf("  出圈顺序：");
    for (int i = 0; i < outCnt; i++) printf("%d ", outOrder[i]);
    printf("\n");

    return q[front];
}

int main(void)
{
    /* ---------- 链队列基本操作 ---------- */
    printf("=== ① 链队列 ===\n");
    LinkQueue *Q = lqCreate();

    printf("  入队 10 20 30：\n");
    for (int v = 10; v <= 30; v += 10) {
        lqEnqueue(Q, v);
        lqPrint(Q);
    }

    printf("\n  出队两个：\n");
    int v;
    for (int i = 0; i < 2; i++) {
        lqDequeue(Q, &v);
        printf("    出队 %d → ", v);
        lqPrint(Q);
    }

    printf("\n  ⭐ 链队列不需要「取模」，也不会有假溢出。\n");
    printf("     front 恒指向头结点，rear 指向最后一个真节点。\n");
    printf("     判空条件：front == rear（空队列时两者都指向头结点）。\n");

    printf("\n  ⚠️ 一个致命的坑：出队最后一个节点时必须把 rear 收回头结点。\n");
    printf("     否则 rear 指向已 free 的节点，下次入队就写野指针。\n");

    /* 出队到空，验证 rear 是否正确回收 */
    printf("\n  继续出队到空：\n");
    while (lqDequeue(Q, &v)) printf("    出队 %d\n", v);
    printf("  队列空了吗？%s\n", lqEmpty(Q) ? "是" : "否");
    printf("  再入队 99：\n");
    lqEnqueue(Q, 99);
    lqPrint(Q);
    printf("  → 没崩，说明 rear 处理正确 ✓\n");
    lqDestroy(Q);

    /* ---------- 杨辉三角 ---------- */
    printf("\n=== ② 杨辉三角（队列法）===\n");
    pascalTriangle(6);

    printf("\n  ⭐ 队列法的思路：队列里存的是「上一行」，\n");
    printf("     每次出队一个 a、窥视队头 b，算 a+b 得到下一行的值，再入队。\n");
    printf("     每行末尾补一个 0 当哨兵，解决边界问题。\n");
    printf("     📌 这是「用队列生成序列」的经典题型。\n");

    /* ---------- 约瑟夫环 ---------- */
    printf("\n=== ③ 约瑟夫环 ===\n");
    printf("  n=7, m=3（7 个人报数到 3 出圈）：\n");
    int last = josephus(7, 3);
    printf("  最后剩下：%d\n", last);

    printf("\n  n=5, m=2：\n");
    last = josephus(5, 2);
    printf("  最后剩下：%d\n", last);

    printf("\n  ⭐ 队列法的思路：\n");
    printf("     前 m-1 个人：出队后立刻入队（相当于「跳过」，绕到队尾）\n");
    printf("     第 m 个人：真的出队（出圈）\n");
    printf("     重复直到只剩 1 个。\n");
    printf("     📌 循环队列天生适合「围成一圈」的问题。\n");

    /* ---------- 链队列 vs 循环队列 ---------- */
    printf("\n=== ④ 链队列 vs 循环队列 ===\n");
    printf("  %-18s %-18s %s\n", "对比项", "链队列", "循环队列");
    printf("  ------------------------------------------------------------------\n");
    printf("  %-18s %-18s %s\n", "存储", "链式，节点分散", "数组，连续");
    printf("  %-18s %-18s %s\n", "长度", "动态", "固定，最多 MAXSIZE-1");
    printf("  %-18s %-18s %s\n", "假溢出", "不存在", "不存在（靠取模）");
    printf("  %-18s %-18s %s\n", "判空", "front == rear", "front == rear");
    printf("  %-18s %-18s %s\n", "判满", "不存在", "(rear+1)%MAX==front");
    printf("  %-18s %-18s %s\n", "额外空间", "每节点 1 个指针", "无");
    printf("  %-18s %-18s %s\n", "入队出队", "O(1)", "O(1)");
    printf("\n  ⭐ 长度不确定用链队列，长度可预估用循环队列（更快，无 malloc）。\n");

    return 0;
}
