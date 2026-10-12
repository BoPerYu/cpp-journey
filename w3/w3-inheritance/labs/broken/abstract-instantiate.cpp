// 故意编译不过：抽象类不能实例化。
//
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc /c abstract-instantiate.cpp"

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

// 派生类不实现纯虚函数，它自己也是抽象类
class Incomplete : public Shape {
};

int main() {
    Shape s;            // ← C2259：无法实例化抽象类
    Incomplete i;       // ← 同样是 C2259
    return 0;
}
