// 这个文件**编译能过，但链接不过** —— 用它来回答一个具体问题：
//   想在基类析构函数里打印"派生类的名字"，靠虚函数行不行？
//
// 试一下（本机实测）：
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc purecall-in-dtor.cpp"
//
// 实测报错原文：
//   purecall-in-dtor.obj : error LNK2019: 无法解析的外部符号
//     "public: virtual char const * __cdecl Shape::name(void)const"
//     ，函数 "public: virtual __cdecl Shape::~Shape(void)" 中引用了该符号
//   purecall-in-dtor.exe : fatal error LNK1120: 1 个无法解析的外部命令
//
// 结论：析构期间的调用是**静态绑定**到基类那一份的，所以编译器要求
//       "Shape::name 必须有函数体"；纯虚函数没有函数体 → 直接链接失败。
//       换句话说：**想在析构里拿到派生类的名字，虚函数这条路走不通**，
//       只能像 my\shapes.cpp 那样，用一个普通成员（name_）把名字存下来。

#include <iostream>
#include <windows.h>

class Shape {
public:
    virtual const char* name() const = 0;      // 纯虚：没有函数体
    virtual ~Shape() {
        std::cout << "  [~Shape] 想在析构里打印名字：";
        std::cout << name() << "\n";           // ← 析构里调用它
    }
};

class Circle : public Shape {
public:
    const char* name() const override { return "圆"; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Circle c;
    return 0;
}
