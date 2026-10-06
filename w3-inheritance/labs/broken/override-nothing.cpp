// 和 override-miss.cpp 是同一个错误，唯一的区别：**没写** override。
// 结果：编译器一声不吭，编译通过。
//
// 手动编译：
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc /c override-nothing.cpp"

#include <iostream>

class Shape {
public:
    virtual double area() const { return 0.0; }
};

class Circle : public Shape {
public:
    double area() { return 1.0; }        // 漏了 const，但没写 override → 编译器不管
};

class Square : public Shape {
public:
    // 顺便看另一件事：基类 area() 是 const，这里想改数据就又不一样了
    double area() const { return 2.0; }
};

int main() { return 0; }
