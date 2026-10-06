// 这个文件**故意写错**，不参与 CMake 构建（不然整个工程都编不过）。
// 它是"覆盖 vs 重载"那一节的证据：派生类签名和基类差一点，会发生什么。
//
// 手动编译它，看编译器怎么说：
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc /c override-miss.cpp"

#include <iostream>

class Shape {
public:
    virtual double area() const { return 0.0; }      // 注意结尾的 const
};

class Circle : public Shape {
public:
    // 这里漏写了 const —— 签名和基类不一样，所以它**不是**覆盖
    double area() override { return 1.0; }
};

int main() { return 0; }
