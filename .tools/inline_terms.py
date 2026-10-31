# -*- coding: utf-8 -*-
"""把英文全称内联到 S3 模块手册正文的首次出现处。

只处理「正文段落与列表项」：
  · 跳过 frontmatter、围栏代码块、标题行、表格行
  · 跳过行内代码（`XXX`）里的出现
  · 跳过已经带括号注释的出现（后面紧跟（或(）
  · 每个术语每份文档只展开一次
这样能保证代码和表格排版一点不变。
"""
import io, os, re, sys

# 缩写: (英文全称, 中文)
INLINE = {
    # 计算机组成
    "CPU": ("Central Processing Unit", "中央处理器"),
    "ALU": ("Arithmetic Logic Unit", "算术逻辑单元"),
    "IR": ("Instruction Register", "指令寄存器"),
    "PSW": ("Program Status Word", "程序状态字"),
    "CISC": ("Complex Instruction Set Computer", "复杂指令集计算机"),
    "RISC": ("Reduced Instruction Set Computer", "精简指令集计算机"),
    "Cache": ("Cache Memory", "高速缓冲存储器"),
    "RAM": ("Random Access Memory", "随机存取存储器"),
    "ROM": ("Read-Only Memory", "只读存储器"),
    "DMA": ("Direct Memory Access", "直接存储器存取"),
    "I/O": ("Input/Output", "输入/输出"),
    "IEEE": ("Institute of Electrical and Electronics Engineers", "电气与电子工程师协会"),
    "MIPS": ("Million Instructions Per Second", "每秒百万条指令"),
    "CPI": ("Cycles Per Instruction", "每条指令平均时钟周期数"),
    "MTBF": ("Mean Time Between Failures", "平均无故障时间"),
    "MTTR": ("Mean Time To Repair", "平均修复时间"),
    "ASCII": ("American Standard Code for Information Interchange", "美国信息交换标准代码"),
    # 操作系统
    "PCB": ("Process Control Block", "进程控制块"),
    "FCFS": ("First Come First Served", "先来先服务"),
    "SJF": ("Shortest Job First", "短作业优先"),
    "RR": ("Round Robin", "时间片轮转"),
    "FIFO": ("First In First Out", "先进先出"),
    "LRU": ("Least Recently Used", "最近最少使用"),
    "OPT": ("Optimal Page Replacement", "最佳页面置换"),
    "SPOOLing": ("Simultaneous Peripheral Operations On-Line", "假脱机技术"),
    "TLB": ("Translation Lookaside Buffer", "快表"),
    # 数据库
    "DBMS": ("Database Management System", "数据库管理系统"),
    "DBA": ("Database Administrator", "数据库管理员"),
    "ER": ("Entity-Relationship", "实体-联系"),
    "SQL": ("Structured Query Language", "结构化查询语言"),
    "DDL": ("Data Definition Language", "数据定义语言"),
    "DML": ("Data Manipulation Language", "数据操纵语言"),
    "DCL": ("Data Control Language", "数据控制语言"),
    "ACID": ("Atomicity, Consistency, Isolation, Durability", "原子性、一致性、隔离性、持久性"),
    "BCNF": ("Boyce-Codd Normal Form", "鲍依斯-科得范式"),
    "FD": ("Functional Dependency", "函数依赖"),
    # 网络
    "OSI": ("Open Systems Interconnection", "开放系统互连"),
    "TCP": ("Transmission Control Protocol", "传输控制协议"),
    "UDP": ("User Datagram Protocol", "用户数据报协议"),
    "IP": ("Internet Protocol", "网际协议"),
    "DNS": ("Domain Name System", "域名系统"),
    "HTTP": ("HyperText Transfer Protocol", "超文本传输协议"),
    "HTTPS": ("HyperText Transfer Protocol Secure", "安全超文本传输协议"),
    "FTP": ("File Transfer Protocol", "文件传输协议"),
    "SMTP": ("Simple Mail Transfer Protocol", "简单邮件传输协议"),
    "POP3": ("Post Office Protocol Version 3", "邮局协议第 3 版"),
    "SNMP": ("Simple Network Management Protocol", "简单网络管理协议"),
    "ARP": ("Address Resolution Protocol", "地址解析协议"),
    "ICMP": ("Internet Control Message Protocol", "互联网控制报文协议"),
    "CIDR": ("Classless Inter-Domain Routing", "无类域间路由"),
    "ACK": ("Acknowledgment", "确认"),
    "SYN": ("Synchronize", "同步"),
    "FIN": ("Finish", "结束"),
    # 软件工程
    "UML": ("Unified Modeling Language", "统一建模语言"),
    "DFD": ("Data Flow Diagram", "数据流图"),
    "CMMI": ("Capability Maturity Model Integration", "能力成熟度模型集成"),
    "PERT": ("Program Evaluation and Review Technique", "计划评审技术"),
    # C++
    "OOP": ("Object-Oriented Programming", "面向对象程序设计"),
    "STL": ("Standard Template Library", "标准模板库"),
    "RVO": ("Return Value Optimization", "返回值优化"),
    "API": ("Application Programming Interface", "应用程序编程接口"),
    # 知识产权
    "ISO": ("International Organization for Standardization", "国际标准化组织"),
    "IEC": ("International Electrotechnical Commission", "国际电工委员会"),
    "ITU": ("International Telecommunication Union", "国际电信联盟"),
    "WIPO": ("World Intellectual Property Organization", "世界知识产权组织"),
    "TRIPS": ("Agreement on Trade-Related Aspects of Intellectual Property Rights", "与贸易有关的知识产权协定"),
}


def token_pattern(abbr):
    """左右都不能是字母数字、下划线或斜杠，避免 TCP 命中 TCP/IP 里的片段。"""
    return re.compile(r'(?<![A-Za-z0-9_/])' + re.escape(abbr) + r'(?![A-Za-z0-9_/])')


def paren_depth(line, pos):
    """pos 之前未闭合的中文/英文括号层数。"""
    return (line.count('（', 0, pos) - line.count('）', 0, pos)
            + line.count('(', 0, pos) - line.count(')', 0, pos))


def in_code_span(line, pos):
    """判断 pos 是否落在行内代码 `...` 里。"""
    return line.count('`', 0, pos) % 2 == 1


def annotate_file(path):
    """两阶段：先正文（自测之前），再标题。表格不动，留给文末附录。"""
    with io.open(path, encoding='utf-8') as f:
        lines = f.read().split('\n')

    done = set()
    changed = 0

    def expand(line, allow_heading):
        """在一行里展开一个尚未覆盖的术语，返回 (新行, 是否改动)。"""
        nonlocal changed
        stripped = line.lstrip()
        is_heading = stripped.startswith('#')
        if is_heading != allow_heading:
            return line, False

        for abbr, (full, cn) in INLINE.items():
            if abbr in done:
                continue
            pat = token_pattern(abbr)
            for m in pat.finditer(line):
                pos = m.start()
                if in_code_span(line, pos):
                    continue
                if paren_depth(line, pos) > 0:      # 已在某个括号里，再套一层会难看
                    continue
                after = line[m.end():m.end() + 1]
                if after in ('（', '('):
                    done.add(abbr)          # 已带注释，视为已出现
                    return line, False
                tail = line[m.end():]
                # 中文前多余的空格去掉，避免出现「） 和」
                if (tail[:1] == ' ' and len(tail) > 1
                        and ('\u4e00' <= tail[1] <= '\u9fff' or tail[1].isdigit())):
                    tail = tail[1:]
                line = (line[:pos] + '%s（%s，%s）' % (abbr, full, cn) + tail)
                done.add(abbr)
                changed += 1
                return line, True
        return line, False

    # ---- 阶段一：正文（跳过 frontmatter / 代码块 / 标题 / 表格 / 自测之后）----
    in_fence = False
    in_front = False
    stop = False
    for idx, line in enumerate(lines):
        stripped = line.strip()
        if idx == 0 and stripped == '---':
            in_front = True
            continue
        if in_front:
            if stripped == '---':
                in_front = False
            continue
        if stripped.startswith('```'):
            in_fence = not in_fence
            continue
        if in_fence:
            continue
        if stripped.startswith('## ') and ('自测' in stripped or '附录' in stripped):
            stop = True
        if stop or not stripped:
            continue
        if stripped.startswith('#') or stripped.startswith('|') or stripped == '---':
            continue
        # 一行里可能含多个术语，循环到没有可展开的为止
        for _ in range(4):
            lines[idx], ch = expand(lines[idx], allow_heading=False)
            if not ch:
                break

    # ---- 阶段二：标题（正文没覆盖到的，退到标题）----
    in_fence = False
    for idx, line in enumerate(lines):
        stripped = line.strip()
        if stripped.startswith('```'):
            in_fence = not in_fence
            continue
        if in_fence or not stripped.startswith('#'):
            continue
        for _ in range(4):
            lines[idx], ch = expand(lines[idx], allow_heading=True)
            if not ch:
                break

    # ---- 阶段三：只出现在表格里的术语，集中成一段，放在「三、」之前 ----
    text_now = '\n'.join(lines)
    rest = []
    for abbr, (full, cn) in INLINE.items():
        if abbr in done:
            continue
        if token_pattern(abbr).search(text_now):
            rest.append((abbr, '%s（%s，%s）' % (abbr, full, cn)))

    if rest and '其余术语全称' not in text_now:
        anchor = None
        for i, l in enumerate(lines):
            if l.strip().startswith('## ') and ('三、' in l or '四、' in l):
                anchor = i
                break
        if anchor is not None:
            # 往前退过分隔线和空行，让这段话留在「必背考点」小节内
            while anchor > 0 and lines[anchor - 1].strip() in ('', '---'):
                anchor -= 1
            block = ['', '**其余术语全称**（主要出现在上方表格中，为避免撑坏列宽未在原处展开）：', '']
            block += ['- ' + r for _, r in sorted(rest)]
            block += ['']
            lines[anchor:anchor] = block
            changed += 1

    if changed:
        with io.open(path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
    return changed, len(done)


if __name__ == "__main__":
    root = r"E:/learn_notebook/Text/软考程序员/S3-基础知识"
    files = sorted(n for n in os.listdir(root)
                   if n.startswith("S3-0") and n.endswith(".md") and "考点手册" in n)
    total = 0
    for name in files:
        c, d = annotate_file(os.path.join(root, name))
        total += c
        print("  %-46s 内联 %2d 处，覆盖 %2d 个术语" % (name, c, d))
    print("\n合计内联 %d 处" % total)
