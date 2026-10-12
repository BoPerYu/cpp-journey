// 探针 8：名字隐藏（name hiding）
//
// 规则：派生类里只要写了一个和基类同名的函数，基类里**所有**同名重载都会被藏起来
//       ——和你写的那个函数的参数列表毫无关系。
//
// ⚠️ 编译这个探针时你会看到一条**警告**（C4244），那条警告本身就是今天要看的现象之一。

#include <iostream>
#include <windows.h>

class Base {
public:
    void f(int)         { std::cout << "      Base::f(int)\n"; }
    void f(double)      { std::cout << "      Base::f(double)\n"; }
    void f(const char*) { std::cout << "      Base::f(const char*)\n"; }
};

class DerivedHidden : public Base {
public:
    // 只写了这一个：按理说它只"覆盖" Base::f(int)，但实际是藏掉了基类全部三个 f
    void f(int) { std::cout << "      DerivedHidden::f(int)\n"; }
};

class DerivedUsing : public Base {
public:
    using Base::f;                          // ← 想把基类那几个"放回来"，写这一句
    void f(int) { std::cout << "      DerivedUsing::f(int)\n"; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 8：名字隐藏 ===\n\n";

    Base b;
    std::cout << "-- 基类对象：三个重载都能用 --\n";
    b.f(1);
    b.f(3.14);
    b.f("hello");

    std::cout << "\n-- 派生类对象（只写了一个 f(int)）--\n";
    DerivedHidden d;
    d.f(1);
    d.f(3.14);          // 这行能过，但 3.14 被悄悄转成了 int（就是那条 C4244 警告）
    // d.f("hello");    // 这行编译不过：C2664。见 labs\broken\hiding-call.cpp

    std::cout << "\n-- 写一句 using Base::f; 之后 --\n";
    DerivedUsing u;
    u.f(1);
    u.f(3.14);
    u.f("hello");

    return 0;
}
