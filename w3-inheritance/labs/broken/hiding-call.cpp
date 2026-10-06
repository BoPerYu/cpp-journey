// 故意编译不过：派生类藏掉了基类的 f(const char*)，这一调用没有匹配的重载。
//
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc /c hiding-call.cpp"

class Base {
public:
    void f(int) {}
    void f(double) {}
    void f(const char*) {}
};

class Derived : public Base {
public:
    void f(int) {}          // 只写这一个，基类三个全被藏起来
};

int main() {
    Derived d;
    d.f("hello");           // ← C2664：参数是 const char*，可候选只剩 Derived::f(int)
    return 0;
}
