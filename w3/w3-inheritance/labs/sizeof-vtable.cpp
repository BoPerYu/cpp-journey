// 探针 5：virtual 的"代价"——对象里多了一个隐藏指针
//
// 目的：把"虚函数表"从传说变成可以量出来的字节数。
// 同一个类，只加一个 virtual，对象就变大；再加几个虚函数，却不再变大。

#include <iostream>
#include <windows.h>

class NoVirtual {                       // 一个 int 成员，没有虚函数
    int x_;
public:
    void f() {}
};

class OneVirtual {                      // 一个 int 成员，一个虚函数
    int x_;
public:
    virtual void f() {}
};

class ThreeVirtual {                    // 一个 int 成员，三个虚函数
    int x_;
public:
    virtual void f() {}
    virtual void g() {}
    virtual void h() {}
};

class VirtualNoData {                   // 没有数据成员，只有一个虚函数
public:
    virtual void f() {}
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 5：虚函数让对象变大多少 ===\n\n";
    std::cout << "sizeof(int)   = " << sizeof(int) << "\n";
    std::cout << "sizeof(void*) = " << sizeof(void*) << "      ← x64 下指针是 8 字节\n\n";

    std::cout << "一个 int 成员，没有虚函数：   " << sizeof(NoVirtual) << "\n";
    std::cout << "一个 int 成员，一个虚函数：   " << sizeof(OneVirtual) << "\n";
    std::cout << "一个 int 成员，三个虚函数：   " << sizeof(ThreeVirtual) << "\n";
    std::cout << "没有数据成员，一个虚函数：    " << sizeof(VirtualNoData) << "\n";

    std::cout << "\n一个类只要【有】虚函数，它的每个对象就多一个隐藏指针（vptr），\n";
    std::cout << "指向这个类共享的虚函数表（vtable）。多几个虚函数不再变胖——\n";
    std::cout << "变胖的只是那张表，表是每个类一张，不是每个对象一张。\n";

    return 0;
}
