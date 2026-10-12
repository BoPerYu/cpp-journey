// 探针 6：在构造函数 / 析构函数里调用虚函数，会发生什么？
//
// 这是一条反直觉的规则：**构造和析构期间不发生多态**。
// 原因：基类构造时，派生类那一半还没构造好；基类析构时，派生类那一半已经拆了。
// 这两种时候，对象的"动态类型"都只能算作基类。

#include <iostream>
#include <windows.h>

class Base {
public:
    Base() {
        std::cout << "  [Base 构造中]   调用 who() → ";
        who();
    }
    virtual ~Base() {
        std::cout << "  [Base 析构中]   调用 who() → ";
        who();
    }
    virtual void who() const { std::cout << "Base::who\n"; }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "  [Derived 构造中] 调用 who() → ";
        who();
    }
    ~Derived() override {
        std::cout << "  [Derived 析构中] 调用 who() → ";
        who();
    }
    void who() const override { std::cout << "Derived::who\n"; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 6：构造 / 析构里调用虚函数 ===\n";
    {
        Derived d;
    }
    std::cout << "=== 结束 ===\n";

    return 0;
}
