---
type: 讲义
stage: S1
week: 3
exam: 两者
tags: [C语言, 分支, switch, case穿透, else-if]
updated: 2026-10-24
---

# W3-02 多分支与 switch

> 📝 S1 地基期 · 第 3 周 · 第 2 节
> 上一篇：[[W3-01 if 与 else]] ｜ 下一篇：[[W3-03 条件运算符与分支实战]]
> 示例代码：`code/w3/22_switch.c`、`code/w3/23_switch_penetrate.c`

---

## 一、else if 链：处理多区间

```c
if (score >= 90)      printf("优秀\n");
else if (score >= 80) printf("良好\n");
else if (score >= 70) printf("中等\n");
else if (score >= 60) printf("及格\n");
else                  printf("不及格\n");
```

### 1.1 ⭐ 顺序不能乱

**必须从大到小（或从小到大）依次判断。**

```c
/* ❌ 错误顺序 */
if (score >= 60)      printf("及格\n");
else if (score >= 90) printf("优秀\n");     /* 永远轮不到！ */
```

原因：`else if` 只在前面的条件**全部为假**时才会被判断。85 分在第一个条件就命中了，直接输出「及格」走人。

> 📌 这是软考找错题和读程序题的高频陷阱。看到 `else if` 链，先检查条件顺序。

### 1.2 else if 与独立 if 的区别

```c
/* else if 链：最多执行一个分支 */
if (a > 0) ...
else if (a > 10) ...      /* a > 0 成立时，这里不会被判断 */

/* 独立 if：每个都判断 */
if (a > 0) ...
if (a > 10) ...           /* a = 15 时两个都执行 */
```

| 写法 | 执行分支数 | 适用 |
|---|---|---|
| `if / else if` | 最多 1 个 | 互斥的区间判断 |
| 独立 `if` | 可能多个 | 各自独立的判断 |

---

## 二、switch：等值匹配

```c
switch (表达式) {
    case 常量1:
        语句组1;
        break;
    case 常量2:
        语句组2;
        break;
    default:
        语句组;
}
```

### 2.1 六条硬规则

| # | 规则 | 违反后果 |
|---|---|---|
| 1 | 表达式必须是**整型**（int / char / enum） | float、字符串直接编译错误 |
| 2 | `case` 后必须是**常量表达式** | 用变量报错 |
| 3 | `case` 的值不能重复 | 编译错误 |
| 4 | `default` 可省略，位置任意 | 没匹配时直接跳出 |
| 5 | 忘写 `break` 会**穿透** | 逻辑错误，且极难发现 |
| 6 | `break` 只跳出 switch | 不是跳出函数 |

> 💡 `case 2+3:` 是合法的，因为 `2+3` 是常量表达式，编译期就能算出 5。

### 2.2 ⭐ case 穿透：陷阱也是武器

**忘了 break 的样子**（`23_switch_penetrate.c` 真实输出，n = 2）：

```text
=== 忘了 break 会怎样 ===
n = 2，执行：
  case 2
  case 3
  default
↑ 从 case 2 开始一路往下执行到底，因为没遇到 break
```

对照加上 break 之后：

```text
  case 2
↑ 只执行 case 2，然后跳出
```

编译器会逐条提醒：

```text
warning: this statement may fall through [-Wimplicit-fallthrough=]
```

> ⚠️ 真实代码里看到这个警告，八成是你漏了 break。别忽略。

**故意不写 break 的正确用法**——让多个 case 共享同一段代码：

```c
switch (score / 10) {
    case 10:
    case 9:
        printf("优秀\n");      /* 100 和 90~99 都走这里 */
        break;
    case 8:
    case 7:
        printf("良好\n");
        break;
    case 6:
        printf("及格\n");
        break;
    default:
        printf("不及格\n");
}
```

真实输出（score = 85）：

```text
等级：良好
↑ 90~100 都走「优秀」，80~89 都走「良好」—— 这是标准用法
```

---

## 三、switch 还是 if-else

| 判断 | 用哪个 |
|---|---|
| 等值匹配（`x == 1`、`ch == 'A'`） | **switch** |
| 分支很多（5 个以上） | **switch**（编译器可做跳转表，比 if-else 链快） |
| 范围判断（`x >= 60 && x < 70`） | if-else |
| 条件复杂（多个变量混合判断） | if-else |
| 浮点、字符串比较 | if-else（switch 不支持） |

**把范围判断塞进 switch 的常用技巧**：先做一次除法或取余，把范围压成离散值。

```c
switch (score / 10)     /* 85 → 8，93 → 9 */
```

⚠️ 这个技巧有边界问题：`score = 100` 得 10，`score = 105` 也是 10，要靠 `default` 兜底或提前校验。

---

## 四、多层分支怎么组织

分支嵌套超过三层就该重构了。两种常见手法：

**① 提前 return**（函数里用，最有效）

```c
if (x < 0)      return -1;      /* 处理异常情况 */
if (x > 100)    return -1;
/* 到这里 x 一定合法，后面不用再判断 */
process(x);
```

**② 用表格代替分支**（考点少时）

```c
static const char *level[] = {"不及格", "及格", "中等", "良好", "优秀"};
printf("%s\n", level[score / 20]);     /* 0~19→0, 20~39→1 ... */
```

> 📌 第二种是标答级别的写法，但 C 语言里需要数组（W5 才学）。先知道有这么个思路。

---

## 五、软考怎么考这部分

| 考点 | 位置 | 典型问法 |
|---|---|---|
| `case` 穿透的输出 | 应用技术 | 给一段没写 break 的 switch 问输出 |
| `else if` 顺序错误 | 应用技术 | 找出逻辑错误 |
| switch 能接什么类型 | 基础知识 | 「switch 表达式可以是 float 吗」（不能） |
| `case` 必须是常量 | 基础知识 | 「case 后面能写变量吗」 |
| switch vs if 效率 | 基础知识 | 分支多时哪个快 |
| 流程图与 switch 对应 | 应用技术 | 多路分支画成流程图 |

---

## 六、本节动手清单

- [ ] 跑通 `22_switch.c`，注意 `default` 放在最前面时的行为
- [ ] 跑通 `23_switch_penetrate.c`，读懂那 3 个 `-Wimplicit-fallthrough` 警告
- [ ] 把「忘了 break」那段的每个 case 补上 break，确认输出变化
- [ ] 手算：`n = 3` 时，没写 break 的 switch（case 1/2/3/default）会输出哪几行
- [ ] 完成 `practice/ex23_grade.c`、`ex26_calc.c`

---

## 附录：英文术语全称与中文对照

> 本表只收录**本页正文出现过**的英文缩写，按字母序排列。
> 全库统一术语表见 [[术语表 英文全称与中文对照]]。

| 缩写 | 英文全称 | 中文 |
|---|---|---|
| const | constant | 常量（只读） |
| enum | enumeration | 枚举关键字 |
| printf | print formatted | 格式化输出函数 |
