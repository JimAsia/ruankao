// ============================================================================
// 306_verify_cpp.cpp  —— S3-07 C++ 面向对象：语义验证
//
// 软考的程序设计语言题常考「这段代码输出什么」，答案完全取决于 C++ 的语义细节：
//   ① 构造 / 析构的顺序（基类 → 成员 → 派生类；析构相反）
//   ② 虚函数与非虚函数通过基类指针调用的差别
//   ③ 纯虚函数与抽象类
//   ④ 拷贝构造在什么情况下被调用
//   ⑤ 静态成员属于类而不属于对象
//   ⑥ 运算符重载
//
// 本文件把这些全部跑出来，讲义里引用的输出都是真实结果。
//
// 编译：g++ -std=c++17 -Wall -Wextra -o 306.exe 306_verify_cpp.cpp
// ============================================================================

#include <cstdio>

// ---------------------------------------------------------------------------
// ① 构造与析构的顺序
// ---------------------------------------------------------------------------
struct BasePart {
    BasePart()  { printf("  构造① 基类 BasePart\n"); }
    ~BasePart() { printf("  析构① 基类 BasePart\n"); }
};

struct MemberPart {
    MemberPart()  { printf("  构造② 成员 MemberPart\n"); }
    ~MemberPart() { printf("  析构② 成员 MemberPart\n"); }
};

class Derived : public BasePart {
    MemberPart m;                       // 成员对象
public:
    Derived()  { printf("  构造③ 派生类 Derived\n"); }
    ~Derived() { printf("  析构③ 派生类 Derived\n"); }
};

// ---------------------------------------------------------------------------
// ② 虚函数 vs 非虚函数
// ---------------------------------------------------------------------------
class Shape {
public:
    void show()        { printf("  Shape::show（非虚）\n"); }
    virtual void draw() { printf("  Shape::draw（虚）\n"); }
    virtual ~Shape()   { printf("  Shape 析构（虚析构）\n"); }
};

class Circle : public Shape {
public:
    void show()        { printf("  Circle::show（非虚，隐藏）\n"); }
    void draw() override { printf("  Circle::draw（虚，覆盖）\n"); }
    ~Circle() override { printf("  Circle 析构\n"); }
};

// ---------------------------------------------------------------------------
// ③ 纯虚函数与抽象类
// ---------------------------------------------------------------------------
class Abstract {
public:
    virtual int area() const = 0;        // 纯虚函数 → 抽象类，不能实例化
    virtual ~Abstract() {}
};

class Square : public Abstract {
    int side;
public:
    explicit Square(int s) : side(s) {}
    int area() const override { return side * side; }
};

// ---------------------------------------------------------------------------
// ④ 拷贝构造的调用时机
// ---------------------------------------------------------------------------
struct Tracked {
    static int copies;
    int v;
    Tracked(int x = 0) : v(x) {}
    Tracked(const Tracked &o) : v(o.v) { copies++; }
};

int Tracked::copies = 0;

void byValue(Tracked t) { (void)t; }       // 传值 → 拷贝一次
void byRef(Tracked &t)  { (void)t; }       // 传引用 → 不拷贝
void byConstRef(const Tracked &t) { (void)t; }

Tracked makeOne() { return Tracked(7); }   // 返回值优化，通常不拷贝

// ---------------------------------------------------------------------------
// ⑤ 静态成员
// ---------------------------------------------------------------------------
class Counter {
public:
    static int created;                 // 属于类，所有对象共享
    Counter()  { created++; }
    static int get() { return created; }
};

int Counter::created = 0;

// ---------------------------------------------------------------------------
// ⑥ 运算符重载
// ---------------------------------------------------------------------------
struct Complex {
    double re, im;
    Complex(double r = 0, double i = 0) : re(r), im(i) {}
    Complex operator+(const Complex &o) const {
        return Complex(re + o.re, im + o.im);
    }
    void print() const { printf("  %.1f + %.1fi\n", re, im); }
};

// ---------------------------------------------------------------------------
// ⑦ 重载 vs 重写
// ---------------------------------------------------------------------------
class OverloadDemo {
public:
    int f(int x)            { return x; }
    int f(int x, int y)     { return x + y; }   // 重载：同名不同参
    double f(double x)      { return x; }
};

int main() {
    printf("=== ① 构造 / 析构顺序 ===\n");
    {
        printf("  开始构造 Derived：\n");
        Derived d;
        printf("  ——— d 离开作用域 ———\n");
    }

    printf("\n=== ② 虚函数 vs 非虚函数 ===\n");
    {
        Circle c;
        Shape *p = &c;                  // 基类指针指向派生类对象
        printf("  通过基类指针 p 调用：\n");
        p->show();                      // 非虚 → 静态绑定，调 Shape::show
        p->draw();                      // 虚   → 动态绑定，调 Circle::draw
        printf("  直接通过对象 c 调用：\n");
        c.show();
        c.draw();
    }

    printf("\n=== ③ 抽象类 ===\n");
    {
        Square s(5);
        Abstract *pa = &s;
        printf("  通过抽象类指针调 area() = %d\n", pa->area());
        printf("  ⭐ Abstract 有纯虚函数，不能定义 Abstract 对象（编译报错）。\n");
    }

    printf("\n=== ④ 拷贝构造的调用 ===\n");
    {
        Tracked t(1);
        Tracked::copies = 0;

        byValue(t);
        printf("  byValue(t)       → 拷贝 %d 次\n", Tracked::copies);
        Tracked::copies = 0;

        byRef(t);
        printf("  byRef(t)         → 拷贝 %d 次\n", Tracked::copies);
        Tracked::copies = 0;

        byConstRef(t);
        printf("  byConstRef(t)    → 拷贝 %d 次\n", Tracked::copies);
        Tracked::copies = 0;

        Tracked t2 = t;
        printf("  Tracked t2 = t   → 拷贝 %d 次\n", Tracked::copies);
        Tracked::copies = 0;

        Tracked t3 = makeOne();
        printf("  makeOne() 返回   → 拷贝 %d 次（返回值优化 RVO）\n", Tracked::copies);
        (void)t2; (void)t3;
    }

    printf("\n=== ⑤ 静态成员 ===\n");
    {
        printf("  创建前 created = %d\n", Counter::get());
        Counter a, b, c;
        printf("  创建 3 个对象后 created = %d\n", Counter::get());
        printf("  三个对象看到的是【同一个】值，因为它属于类不属于对象。\n");
    }

    printf("\n=== ⑥ 运算符重载 ===\n");
    {
        Complex x(1, 2), y(3, 4), z = x + y;
        z.print();
        printf("  x + y 等价于 x.operator+(y)\n");
    }

    printf("\n=== ⑦ 重载 vs 重写 ===\n");
    {
        OverloadDemo d;
        printf("  d.f(3)      = %d\n", d.f(3));
        printf("  d.f(3, 4)   = %d\n", d.f(3, 4));
        printf("  d.f(2.5)    = %.1f\n", d.f(2.5));
        printf("  ⭐ 同一个类里同名不同参 = 重载（编译期决定）。\n");
        printf("     派生类覆盖基类虚函数 = 重写（运行期决定）。\n");
    }

    printf("\n=== ⑧ 三个概念的判定 ===\n");
    printf("  %-10s %-16s %-14s %s\n", "概念", "发生位置", "决定时机", "条件");
    printf("  %-10s %-16s %-14s %s\n", "重载", "同一个类", "编译期", "同名、参数不同");
    printf("  %-10s %-16s %-14s %s\n", "重写", "基类与派生类", "运行期", "虚函数、签名相同");
    printf("  %-10s %-16s %-14s %s\n", "隐藏", "基类与派生类", "编译期", "同名但非虚/签名不同");

    return 0;
}
