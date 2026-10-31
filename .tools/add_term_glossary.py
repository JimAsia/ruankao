# -*- coding: utf-8 -*-
"""给已有讲义补「英文全称 + 中文」对照表。

策略：
  1. 维护一份术语词典（缩写 → 英文全称 / 中文 / 所属模块）
  2. 扫描每份文档，只挑出该文档里【真正出现过】的术语
  3. 在文档末尾追加「附录：英文术语全称与中文对照」表格
  4. 不改动正文、代码块与表格，避免破坏原有排版

同时生成一份总表。
"""
import io, os, re, sys

# ---------------------------------------------------------------- 术语词典
# 缩写: (英文全称, 中文, 模块)
TERMS = {
    # ---- 计算机组成 ----
    "CPU": ("Central Processing Unit", "中央处理器", "计算机组成"),
    "ALU": ("Arithmetic Logic Unit", "算术逻辑单元", "计算机组成"),
    "PC": ("Program Counter", "程序计数器", "计算机组成"),
    "IR": ("Instruction Register", "指令寄存器", "计算机组成"),
    "ACC": ("Accumulator", "累加器", "计算机组成"),
    "PSW": ("Program Status Word", "程序状态字", "计算机组成"),
    "CISC": ("Complex Instruction Set Computer", "复杂指令集计算机", "计算机组成"),
    "RISC": ("Reduced Instruction Set Computer", "精简指令集计算机", "计算机组成"),
    "Cache": ("Cache Memory", "高速缓冲存储器", "计算机组成"),
    "RAM": ("Random Access Memory", "随机存取存储器", "计算机组成"),
    "ROM": ("Read-Only Memory", "只读存储器", "计算机组成"),
    "SRAM": ("Static Random Access Memory", "静态随机存取存储器", "计算机组成"),
    "DRAM": ("Dynamic Random Access Memory", "动态随机存取存储器", "计算机组成"),
    "DMA": ("Direct Memory Access", "直接存储器存取", "计算机组成"),
    "I/O": ("Input/Output", "输入/输出", "计算机组成"),
    "IEEE": ("Institute of Electrical and Electronics Engineers", "电气与电子工程师协会", "计算机组成"),
    "MIPS": ("Million Instructions Per Second", "每秒百万条指令", "计算机组成"),
    "CPI": ("Cycles Per Instruction", "每条指令的平均时钟周期数", "计算机组成"),
    "MTBF": ("Mean Time Between Failures", "平均无故障时间", "计算机组成"),
    "MTTR": ("Mean Time To Repair", "平均修复时间", "计算机组成"),
    "MHz": ("Megahertz", "兆赫兹", "计算机组成"),
    "GHz": ("Gigahertz", "吉赫兹", "计算机组成"),
    "MB/s": ("Megabytes per second", "兆字节每秒", "计算机组成"),
    "KB": ("Kilobyte", "千字节", "计算机组成"),
    "MB": ("Megabyte", "兆字节", "计算机组成"),
    "TB": ("Terabyte", "太字节", "计算机组成"),
    "ASCII": ("American Standard Code for Information Interchange", "美国信息交换标准代码", "计算机组成"),
    "ANSI": ("American National Standards Institute", "美国国家标准学会", "计算机组成"),
    "BIOS": ("Basic Input/Output System", "基本输入输出系统", "计算机组成"),

    # ---- 操作系统 ----
    "PCB": ("Process Control Block", "进程控制块", "操作系统"),
    "FCFS": ("First Come First Served", "先来先服务", "操作系统"),
    "SJF": ("Shortest Job First", "短作业优先", "操作系统"),
    "RR": ("Round Robin", "时间片轮转", "操作系统"),
    "FIFO": ("First In First Out", "先进先出", "操作系统"),
    "LIFO": ("Last In First Out", "后进先出", "操作系统"),
    "LRU": ("Least Recently Used", "最近最少使用", "操作系统"),
    "LFU": ("Least Frequently Used", "最不经常使用", "操作系统"),
    "OPT": ("Optimal Page Replacement", "最佳页面置换", "操作系统"),
    "SPOOLing": ("Simultaneous Peripheral Operations On-Line", "假脱机技术", "操作系统"),
    "TLB": ("Translation Lookaside Buffer", "快表（转换检测缓冲）", "操作系统"),
    "PV": ("Passeren / Vrijgeven（荷兰语）", "P 操作（申请）/ V 操作（释放）", "操作系统"),
    "Belady": ("Belady's Anomaly", "贝拉迪异常（页框增多反而缺页更多）", "操作系统"),
    "Allocation": ("Allocation", "已分配资源矩阵（银行家算法）", "操作系统"),
    "Need": ("Need", "尚需资源矩阵（银行家算法）", "操作系统"),
    "Work": ("Work", "工作向量（银行家算法）", "操作系统"),

    # ---- 数据库 ----
    "DBMS": ("Database Management System", "数据库管理系统", "数据库"),
    "DBA": ("Database Administrator", "数据库管理员", "数据库"),
    "ER": ("Entity-Relationship", "实体-联系（模型/图）", "数据库"),
    "SQL": ("Structured Query Language", "结构化查询语言", "数据库"),
    "DDL": ("Data Definition Language", "数据定义语言", "数据库"),
    "DML": ("Data Manipulation Language", "数据操纵语言", "数据库"),
    "DCL": ("Data Control Language", "数据控制语言", "数据库"),
    "ACID": ("Atomicity, Consistency, Isolation, Durability", "原子性、一致性、隔离性、持久性", "数据库"),
    "BCNF": ("Boyce-Codd Normal Form", "鲍依斯-科得范式（BC 范式）", "数据库"),
    "1NF": ("First Normal Form", "第一范式", "数据库"),
    "2NF": ("Second Normal Form", "第二范式", "数据库"),
    "3NF": ("Third Normal Form", "第三范式", "数据库"),
    "FD": ("Functional Dependency", "函数依赖", "数据库"),
    "SELECT": ("SELECT（SQL 关键字）", "查询（选列）", "数据库"),
    "INSERT": ("INSERT（SQL 关键字）", "插入", "数据库"),
    "UPDATE": ("UPDATE（SQL 关键字）", "更新", "数据库"),
    "DELETE": ("DELETE（SQL 关键字）", "删除数据", "数据库"),
    "DROP": ("DROP（SQL 关键字）", "删除（表结构等对象）", "数据库"),
    "CREATE": ("CREATE（SQL 关键字）", "创建", "数据库"),
    "ALTER": ("ALTER（SQL 关键字）", "修改表结构", "数据库"),
    "GRANT": ("GRANT（SQL 关键字）", "授权", "数据库"),
    "REVOKE": ("REVOKE（SQL 关键字）", "收回权限", "数据库"),
    "WHERE": ("WHERE（SQL 关键字）", "条件子句", "数据库"),
    "OLTP": ("On-Line Transaction Processing", "联机事务处理", "数据库"),
    "OLAP": ("On-Line Analytical Processing", "联机分析处理", "数据库"),

    # ---- 计算机网络 ----
    "OSI": ("Open Systems Interconnection", "开放系统互连（参考模型）", "计算机网络"),
    "TCP": ("Transmission Control Protocol", "传输控制协议", "计算机网络"),
    "UDP": ("User Datagram Protocol", "用户数据报协议", "计算机网络"),
    "IP": ("Internet Protocol", "网际协议", "计算机网络"),
    "TCP/IP": ("Transmission Control Protocol / Internet Protocol", "传输控制协议/网际协议（协议族）", "计算机网络"),
    "DNS": ("Domain Name System", "域名系统", "计算机网络"),
    "HTTP": ("HyperText Transfer Protocol", "超文本传输协议", "计算机网络"),
    "HTTPS": ("HyperText Transfer Protocol Secure", "安全超文本传输协议", "计算机网络"),
    "FTP": ("File Transfer Protocol", "文件传输协议", "计算机网络"),
    "SMTP": ("Simple Mail Transfer Protocol", "简单邮件传输协议", "计算机网络"),
    "POP3": ("Post Office Protocol Version 3", "邮局协议第 3 版", "计算机网络"),
    "IMAP": ("Internet Message Access Protocol", "互联网邮件访问协议", "计算机网络"),
    "SSH": ("Secure Shell", "安全外壳协议", "计算机网络"),
    "Telnet": ("Telecommunication Network Protocol", "远程登录协议", "计算机网络"),
    "SNMP": ("Simple Network Management Protocol", "简单网络管理协议", "计算机网络"),
    "ARP": ("Address Resolution Protocol", "地址解析协议", "计算机网络"),
    "ICMP": ("Internet Control Message Protocol", "互联网控制报文协议", "计算机网络"),
    "RIP": ("Routing Information Protocol", "路由信息协议", "计算机网络"),
    "OSPF": ("Open Shortest Path First", "开放最短路径优先", "计算机网络"),
    "BGP": ("Border Gateway Protocol", "边界网关协议", "计算机网络"),
    "CIDR": ("Classless Inter-Domain Routing", "无类域间路由", "计算机网络"),
    "NAT": ("Network Address Translation", "网络地址转换", "计算机网络"),
    "ACK": ("Acknowledgment", "确认（报文）", "计算机网络"),
    "SYN": ("Synchronize", "同步（连接请求报文）", "计算机网络"),
    "FIN": ("Finish", "结束（断开请求报文）", "计算机网络"),
    "URL": ("Uniform Resource Locator", "统一资源定位符", "计算机网络"),
    "LAN": ("Local Area Network", "局域网", "计算机网络"),
    "WAN": ("Wide Area Network", "广域网", "计算机网络"),
    "MAN": ("Metropolitan Area Network", "城域网", "计算机网络"),
    "DES": ("Data Encryption Standard", "数据加密标准（对称）", "网络安全"),
    "AES": ("Advanced Encryption Standard", "高级加密标准（对称）", "网络安全"),
    "RSA": ("Rivest-Shamir-Adleman", "RSA 公钥算法（非对称）", "网络安全"),
    "MD5": ("Message Digest Algorithm 5", "消息摘要算法第 5 版", "网络安全"),
    "SHA": ("Secure Hash Algorithm", "安全散列算法", "网络安全"),
    "DMZ": ("Demilitarized Zone", "隔离区（非军事区）", "网络安全"),
    "MAC": ("Media Access Control", "介质访问控制（地址）", "计算机网络"),

    # ---- 软件工程 ----
    "UML": ("Unified Modeling Language", "统一建模语言", "软件工程"),
    "DFD": ("Data Flow Diagram", "数据流图", "软件工程"),
    "DD": ("Data Dictionary", "数据字典", "软件工程"),
    "CMMI": ("Capability Maturity Model Integration", "能力成熟度模型集成", "软件工程"),
    "PERT": ("Program Evaluation and Review Technique", "计划评审技术（网络图）", "软件工程"),
    "McCabe": ("McCabe Cyclomatic Complexity", "McCabe 环形复杂度", "软件工程"),
    "LOC": ("Lines of Code", "代码行数", "软件工程"),
    "OO": ("Object-Oriented", "面向对象", "软件工程"),
    "XP": ("Extreme Programming", "极限编程", "软件工程"),
    "SA": ("Structured Analysis", "结构化分析", "软件工程"),
    "SD": ("Structured Design", "结构化设计", "软件工程"),
    "SQA": ("Software Quality Assurance", "软件质量保证", "软件工程"),
    "API": ("Application Programming Interface", "应用程序编程接口", "软件工程"),
    "IDE": ("Integrated Development Environment", "集成开发环境", "软件工程"),

    # ---- C++ / 语言 ----
    "OOP": ("Object-Oriented Programming", "面向对象程序设计", "C++"),
    "STL": ("Standard Template Library", "标准模板库", "C++"),
    "RVO": ("Return Value Optimization", "返回值优化", "C++"),
    "RAII": ("Resource Acquisition Is Initialization", "资源获取即初始化", "C++"),
    "const": ("constant", "常量（只读）", "C++"),
    "nullptr": ("null pointer", "空指针字面量", "C++"),
    "vector": ("vector（动态数组容器）", "向量容器", "C++"),
    "map": ("map（关联容器）", "映射容器（红黑树）", "C++"),
    "unordered_map": ("unordered_map（哈希容器）", "无序映射容器", "C++"),
    "sizeof": ("size of", "取字节数运算符", "C++"),

    # ---- 知识产权与标准化 ----
    "ISO": ("International Organization for Standardization", "国际标准化组织", "知识产权与标准化"),
    "IEC": ("International Electrotechnical Commission", "国际电工委员会", "知识产权与标准化"),
    "ITU": ("International Telecommunication Union", "国际电信联盟", "知识产权与标准化"),
    "GB": ("Guobiao（国家标准代号）", "中国强制性国家标准；存储容量语境下 GB = Gigabyte 吉字节", "知识产权与标准化"),
    "GB/T": ("Guobiao/Tuijian（推荐性国家标准代号）", "中国推荐性国家标准", "知识产权与标准化"),
    "SJ": ("SJ（行业标准代号，无英文全称）", "中国电子行业标准", "知识产权与标准化"),
    "DB": ("DB（Difang Biaozhun，地方标准代号）", "中国地方标准；计算机语境下 DB = Database 数据库", "知识产权与标准化"),
    "WIPO": ("World Intellectual Property Organization", "世界知识产权组织", "知识产权与标准化"),
    "TRIPS": ("Agreement on Trade-Related Aspects of Intellectual Property Rights", "与贸易有关的知识产权协定", "知识产权与标准化"),

    # ---- 数据结构与算法 ----
    "ASL": ("Average Search Length", "平均查找长度", "数据结构"),
    "BST": ("Binary Search Tree", "二叉排序树（二叉搜索树）", "数据结构"),
    "AVL": ("Adelson-Velsky and Landis Tree", "平衡二叉树（AVL 树）", "数据结构"),
    "DFS": ("Depth-First Search", "深度优先搜索", "数据结构"),
    "BFS": ("Breadth-First Search", "广度优先搜索", "数据结构"),
    "MST": ("Minimum Spanning Tree", "最小生成树", "数据结构"),
    "DP": ("Dynamic Programming", "动态规划", "数据结构"),
    "LCS": ("Longest Common Subsequence", "最长公共子序列", "数据结构"),
    "WPL": ("Weighted Path Length", "带权路径长度", "数据结构"),
    "KMP": ("Knuth-Morris-Pratt", "KMP 字符串匹配算法", "数据结构"),
    "Prim": ("Prim's Algorithm", "普里姆算法（最小生成树）", "数据结构"),
    "Kruskal": ("Kruskal's Algorithm", "克鲁斯卡尔算法（最小生成树）", "数据结构"),
    "Dijkstra": ("Dijkstra's Algorithm", "迪杰斯特拉算法（单源最短路）", "数据结构"),
    "Floyd": ("Floyd-Warshall Algorithm", "弗洛伊德算法（多源最短路）", "数据结构"),
    "Huffman": ("Huffman Coding", "哈夫曼编码", "数据结构"),

    # ---- C 语言 ----
    "EOF": ("End Of File", "文件结束标志", "C 语言"),
    "NULL": ("null pointer constant", "空指针常量", "C 语言"),
    "stdio": ("standard input/output", "标准输入输出（头文件）", "C 语言"),
    "printf": ("print formatted", "格式化输出函数", "C 语言"),
    "scanf": ("scan formatted", "格式化输入函数", "C 语言"),
    "malloc": ("memory allocation", "动态内存分配函数", "C 语言"),
    "argc": ("argument count", "命令行参数个数", "C 语言"),
    "argv": ("argument vector", "命令行参数数组", "C 语言"),
    "fopen": ("file open", "打开文件函数", "C 语言"),
    "fclose": ("file close", "关闭文件函数", "C 语言"),
    "fread": ("file read", "块读取函数", "C 语言"),
    "fwrite": ("file write", "块写入函数", "C 语言"),
    "fseek": ("file seek", "文件定位函数", "C 语言"),
    "typedef": ("type definition", "类型定义关键字", "C 语言"),
    "struct": ("structure", "结构体关键字", "C 语言"),
    "union": ("union", "共用体关键字", "C 语言"),
    "enum": ("enumeration", "枚举关键字", "C 语言"),
}

MODULE_ORDER = ["计算机组成", "操作系统", "数据库", "计算机网络", "网络安全",
                "软件工程", "C++", "知识产权与标准化", "数据结构", "C 语言"]


def find_terms(text):
    """返回该文本中实际出现过的术语（按词典顺序）。"""
    hits = []
    for abbr in TERMS:
        # 自定义边界：左右不能是字母数字，避免 CPU 命中 CPUX
        pat = r'(?<![A-Za-z0-9_])' + re.escape(abbr) + r'(?![A-Za-z0-9_])'
        if re.search(pat, text):
            hits.append(abbr)
    return hits


def table_for(abbrs):
    lines = ["| 缩写 | 英文全称 | 中文 |", "|---|---|---|"]
    for a in abbrs:
        full, cn, _ = TERMS[a]
        lines.append("| %s | %s | %s |" % (a, full, cn))
    return "\n".join(lines)


MIN_TERMS = 3      # 少于这个数就不加附录


def append_section(path, title):
    with io.open(path, encoding="utf-8") as f:
        text = f.read()
    if "英文术语全称与中文对照" in text:
        print("  跳过（已有）：%s" % os.path.basename(path))
        return 0
    abbrs = find_terms(text)
    if len(abbrs) < MIN_TERMS:
        print("  跳过（仅 %d 条，低于阈值）：%s" % (len(abbrs), os.path.basename(path)))
        return 0

    section = "\n\n---\n\n## 附录：英文术语全称与中文对照\n\n"
    section += "> 本表只收录**本页正文出现过**的英文缩写，按字母序排列。\n"
    section += "> 全库统一术语表见 [[术语表 英文全称与中文对照]]。\n\n"
    section += table_for(sorted(abbrs))
    section += "\n"

    with io.open(path, "w", encoding="utf-8") as f:
        f.write(text.rstrip() + section)
    print("  已补 %2d 条：%s" % (len(abbrs), os.path.basename(path)))
    return len(abbrs)


def build_master(out_path):
    total = 0
    lines = [
        "---",
        "tags: [软考程序员, 术语表, 英文全称]",
        "stage: 全阶段",
        "status: 已完成",
        "created: 2026-10-25",
        "---",
        "",
        "# 术语表 英文全称与中文对照",
        "",
        "> 全库英文缩写总表，按模块分组。每份讲义末尾还有「只含本页术语」的子表。",
        "> 记忆建议：先记中文含义，再回头看英文全称 —— 英文全称往往能解释缩写为什么这么写。",
        "",
    ]
    for mod in MODULE_ORDER:
        items = [(a, v) for a, v in TERMS.items() if v[2] == mod]
        if not items:
            continue
        lines.append("## %s（%d 条）" % (mod, len(items)))
        lines.append("")
        lines.append("| 缩写 | 英文全称 | 中文 |")
        lines.append("|---|---|---|")
        for a, (full, cn, _) in sorted(items):
            lines.append("| %s | %s | %s |" % (a, full, cn))
        lines.append("")
        total += len(items)

    lines.append("---")
    lines.append("")
    lines.append("**统计**：共 %d 条术语，覆盖 %d 个模块。" % (total, len(
        [m for m in MODULE_ORDER if any(v[2] == m for v in TERMS.values())])))
    with io.open(out_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    print("总表已生成：%s（%d 条）" % (out_path, total))


if __name__ == "__main__":
    root = r"E:/learn_notebook/Text/软考程序员"
    targets = []

    s3 = os.path.join(root, "S3-基础知识")
    for name in sorted(os.listdir(s3)):
        if name.endswith(".md"):
            targets.append(os.path.join(s3, name))

    # S1 / S2：术语 ≥ 3 条的周讲义也补（少于 3 条不值得单独加一张表）
    for folder in ["S1-C语言地基", "S2-数据结构与算法"]:
        d = os.path.join(root, folder)
        for name in sorted(os.listdir(d)):
            if name.endswith(".md"):
                targets.append(os.path.join(d, name))

    print("=== 逐份补术语表 ===")
    n = 0
    for t in targets:
        if os.path.exists(t):
            n += append_section(t, "")
        else:
            print("  缺失：%s" % t)

    print("\n=== 生成总表 ===")
    build_master(os.path.join(root, "术语表 英文全称与中文对照.md"))
    print("\n合计补入 %d 条（含重复计数）" % n)
