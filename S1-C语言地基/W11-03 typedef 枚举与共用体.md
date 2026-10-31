---
tags: [软考程序员, C语言, 结构体, typedef, 枚举, 共用体, S1]
week: W11
stage: S1
status: 已完成
created: 2026-10-24
---

# W11-03 typedef、枚举与共用体

> 结构体有四个搭档：`typedef` 给它起别名，嵌套让它能组合，`enum` 给整数起名字，`union` 让它和内存重叠。
> 这四个都是软考选择题的高频考点，而且**每个都能单独出一道题**。

---

## 一、typedef：给类型起别名

```c
/* 老写法：先定义，再起别名 */
struct Student { int id; char name[20]; };
typedef struct Student Student;

/* 合并写法（工程里最常见） */
typedef struct {
    int year, month, day;
} Date;

typedef unsigned int uint;              /* 基本类型也能别名 */
```

起别名后，`Student s1;` 和 `struct Student s1;` 完全等价。

> ⭐ **`typedef` 只是起别名，不产生新类型。**
> `Student` 和 `struct Student` 是两个名字、同一个类型，编译器完全当成一样的东西。

### 软考怎么考

| 问法 | 答案 |
|---|---|
| `typedef int INT;` 之后 `INT` 是什么 | `int` 的别名，不是新类型 |
| `typedef` 和 `#define` 的区别 | `typedef` 由编译器处理，有类型检查；`#define` 是文本替换 |
| 为什么 `typedef struct` 常见 | 省掉每次写 `struct` 三个字 |

> 📌 一个经典陷阱：`typedef int *PINT;` 之后 `PINT a, b;` 的 `b` 是 `int *` 还是 `int`？
> 答案是 **`int *`**，两个都是指针。而 `#define PINT int *` 时 `PINT a, b;` 展开成 `int *a, b;`，`b` 就变成 `int` 了。
> **这是 `typedef` 优于 `#define` 的核心理由**，软考考过。

---

## 二、嵌套结构体

结构体成员可以是另一个结构体：

```c
typedef struct {
    int   id;
    char  name[20];
    Date  birthday;            /* 结构体作成员 */
    double scores[3];          /* 数组作成员 */
} Person;
```

```c
Person p = {
    .id = 2026002,
    .name = "李四",
    .birthday = {2008, 3, 15},
    .scores = {88.0, 92.5, 79.0}
};

printf("%s 生日 %d-%02d-%02d\n",
       p.name, p.birthday.year, p.birthday.month, p.birthday.day);
```

真实输出：

```text
李四 生日 2008-03-15
三门成绩：88.0 92.5 79.0
嵌套后整个结构体占 64 字节
```

> ❌ 访问嵌套成员要一层一层点：`p.birthday.year`。
> 写成 `p.year` 编译报错 —— 那是另一个不存在的成员。

### 大小怎么算

`Person` 的成员：`int`(4) + `char[20]`(20) + `Date`(12) + `double[3]`(24) = 60，但实际 64，补了 4 字节。

算嵌套结构体大小时，**先把内层结构体当成一个整体**（用它的 `sizeof`），再套外层对齐规则。

---

## 三、枚举：给整数起名字

```c
enum Weekday {
    MON = 1,                   /* 手动从 1 开始 */
    TUE, WED, THU, FRI, SAT, SUN    /* 依次 +1 */
};

enum Color {
    RED,                       /* 不写就从 0 开始 */
    GREEN = 5,                 /* 手动跳到 5 */
    BLUE                       /* 接着就是 6 */
};

enum Status {
    OK = 0,
    ERR_FILE = -1,
    ERR_MEM  = -2
};
```

真实输出：

```text
MON = 1, TUE = 2, SUN = 7
RED = 0, GREEN = 5, BLUE = 6
OK = 0, ERR_FILE = -1, ERR_MEM = -2
sizeof(enum Weekday) = 4 字节
```

### 三条考点

1. **默认从 0 开始，逐个 +1**
2. **可以手动赋值，后面的接着 +1**（`GREEN = 5` → `BLUE = 6`）
3. **本质是 int**，`sizeof` 是 4，能和整数直接比较、能强制转换

```c
enum Weekday w = (enum Weekday)n;      /* 整数转枚举 */
if (w == WED) { /* ... */ }            /* 直接比较 */
```

### 枚举配 switch：比数字可读

```c
enum Status st = ERR_FILE;
switch (st) {
    case OK:       printf("成功\n"); break;
    case ERR_FILE: printf("文件错误（code %d）\n", st); break;
    case ERR_MEM:  printf("内存错误（code %d）\n", st); break;
    default:       printf("未知错误\n"); break;
}
```

真实输出：`文件错误（code -1）`

> ✅ 枚举的价值是**可读性和防错**。写 `if (st == ERR_FILE)` 比 `if (st == -1)` 清楚一百倍，而且拼错了编译器会报「未声明的标识符」。
> 但要注意：C 语言的枚举**不做范围检查**，`enum Weekday w = 99;` 照样编译通过。这个检查要靠你自己写。

### 多个 case 共用分支

W3 讲过「case 穿透」，这里是它的**正确用法**：

```c
switch (w) {
    case MON:
    case TUE:
    case WED:
    case THU:
    case FRI:
        printf("工作日\n");        /* 五个 case 共享这一段 */
        break;
    case SAT:
    case SUN:
        printf("休息日\n");
        break;
}
```

> 📝 故意不写 `break`，让 5 个 case 掉进同一段代码。这是唯一被认可的「穿透」用法。

---

## 四、共用体：所有成员共用一块内存

```c
union Data {
    int   i;          /* 4 字节 */
    float f;          /* 4 字节 */
    char  c[8];       /* 8 字节 */
};
```

真实输出：

```text
union Data 占 8 字节 = 最大成员的大小
（int 4、float 4、char[8] 8 → 取最大 8）
```

### 最直观的演示

```c
union Data d;
d.i = 0x41424344;
```

真实输出：

```text
d.i = 0x41424344
d.c = DCBA  ← 同一块内存，按 char 读出来
```

> ⭐ 这个 `DCBA` 揭示了**小端序**：低位字节存在低地址。
> `0x41424344` 的四个字节是 `44 43 42 41`，从低地址往高读就是 `D C B A`。
> **软考考过大小端**：x86 是小端，网络字节序是大端。这里看到的就是小端的实证。

再写一个成员，前面的值就失效：

```c
d.f = 3.14f;
```

真实输出：

```text
d.f = 3.14
d.i = 1078523331  ← 已经被踩坏，原来的 0x41424344 没了
```

> ❌ **共用体同一时刻只能用一个成员。** 写 `f` 就把 `i` 覆盖了。
> 这不是 bug，是设计 —— 它的用途就是「同一块内存，不同时候装不同东西」。

### 结构体 vs 共用体

```c
struct S { int i; double d; };
union  U { int i; double d; };
```

真实输出（这就是软考的标准问法）：

```text
struct { int; double; } 16         成员各占位置
union  { int; double; } 8          成员共用一块
```

| | 结构体 `struct` | 共用体 `union` |
|---|---|---|
| 内存 | 成员**各占**位置，地址不同 | 成员**共用**一块，地址相同 |
| 大小 | ≈ 成员之和 + 填充 | = **最大**成员大小（再套对齐） |
| 同时使用 | 全部成员可同时有效 | **只能有一个**有效 |
| 用途 | 打包一组相关数据 | 节省内存、类型转换（如判断大小端） |

> 📌 一句话记忆：**结构体是「和」，共用体是「最大」。**

---

## 五、软考怎么考

| 考点 | 典型问法 | 要点 |
|---|---|---|
| `typedef` 本质 | 是不是新类型 | 不是，只是别名 |
| `typedef` vs `#define` | 哪个有类型检查 | `typedef`，编译器处理 |
| 枚举默认值 | `enum {A,B,C}` 各是多少 | 0,1,2 |
| 枚举跳值 | `enum {A, B=5, C}` 的 C | 6（接着 +1） |
| 枚举大小 | `sizeof(enum)` | 4（就是 int） |
| 共用体大小 | `union {int; double;}` | 8（最大成员） |
| 共用体特性 | 能否同时用两个成员 | 不能，会互相覆盖 |
| 嵌套访问 | `p.birthday.year` 写法 | 一层一层点 |

---

## 六、动手验证

```bash
cd /e/learn_notebook/Text/软考程序员/code/w11
gcc -std=c17 -Wall -Wextra -o 104 104_typedef_nested.c && ./104
```

- [ ] 跑通 `104`，看枚举的默认值规律
- [ ] 看 `d.c` 输出 `DCBA`，想清楚为什么不是 `ABCD`（小端）
- [ ] 把 `enum Color` 改成 `{RED=1, GREEN, BLUE}`，看 GREEN 变几
- [ ] 把 `union Data` 的 `char c[8]` 改成 `char c[2]`，看 `sizeof` 变几

---

**上一篇：** [[W11-02 结构体数组与指针]]
**下一篇：** [[W12-01 文件读写基础]]

---

## 附录：英文术语全称与中文对照

> 本表只收录**本页正文出现过**的英文缩写，按字母序排列。
> 全库统一术语表见 [[术语表 英文全称与中文对照]]。

| 缩写 | 英文全称 | 中文 |
|---|---|---|
| enum | enumeration | 枚举关键字 |
| printf | print formatted | 格式化输出函数 |
| sizeof | size of | 取字节数运算符 |
| struct | structure | 结构体关键字 |
| typedef | type definition | 类型定义关键字 |
| union | union | 共用体关键字 |
