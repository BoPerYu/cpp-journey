// ============================================================
// W2 成员初始化列表探针（2026-10-01）
// 用途：看清"初始化"和"赋值"的区别，以及初始化顺序到底按什么来。
// 用法：init_lab
// ============================================================
#include <iostream>
#include <windows.h>

// 探针类：每个特殊成员函数都打印一行
class Tracer {
public:
    Tracer()                         { std::cout << "      [Tracer 默认构造]\n"; }
    explicit Tracer(int)             { std::cout << "      [Tracer 带参构造]\n"; }
    Tracer(const Tracer&)            { std::cout << "      [Tracer 拷贝构造]\n"; }
    Tracer& operator=(const Tracer&) { std::cout << "      [Tracer 拷贝赋值]\n"; return *this; }
    ~Tracer()                        { std::cout << "      [Tracer 析构]\n"; }
};

// A：成员都写在初始化列表里
class UseInitList {
public:
    UseInitList() : t_(), n_(5) {
        std::cout << "   【A】进入构造函数体（t_ 和 n_ 早就有值了）\n";
    }
private:
    Tracer t_;
    int n_;
};

// B：成员放到构造函数体里"赋值"
class UseBodyAssign {
public:
    UseBodyAssign() {
        std::cout << "   【B】进入构造函数体（t_ 已经被默认构造过了）\n";
        t_ = Tracer(1);       // 这是赋值，不是初始化
        n_ = 5;
    }
private:
    Tracer t_;
    int n_;
};

// C：初始化顺序看"声明顺序"，不看初始化列表的书写顺序
class Named {
public:
    explicit Named(const char* name) : name_(name) {
        std::cout << "      初始化 " << name_ << "\n";
    }
private:
    const char* name_;
};

class Order {
public:
    // 初始化列表里 b_ 写在前面，但成员声明顺序是 a_ 在前
    Order() : b_("b_（在初始化列表里写在前面）"), a_("a_（在初始化列表里写在后面）") {}
private:
    Named a_;
    Named b_;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== A. 用初始化列表 ===\n";
    { UseInitList a; }

    std::cout << "\n=== B. 在函数体里赋值 ===\n";
    { UseBodyAssign b; }

    std::cout << "\n=== C. 初始化顺序按声明顺序（不是书写顺序）===\n";
    { Order o; }

    std::cout << "\n对照：A 只有 1 次构造 + 1 次析构；B 多出 1 次构造 + 1 次拷贝赋值 + 1 次析构。\n";
    return 0;
}
