// 故意编译不过：派生类构造函数没写初始化列表里的"基类那一项"。
//
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc /c no-base-init.cpp"

#include <string>

class Shape {
public:
    std::string name_;
    Shape(std::string name) : name_(name) {}     // 注意：Shape 没有"默认构造函数"
};

class Circle : public Shape {
public:
    double r_;
    Circle(double r) : r_(r) {}                  // ← 没有写 Shape("圆")
};

int main() { Circle c(2.0); return 0; }
