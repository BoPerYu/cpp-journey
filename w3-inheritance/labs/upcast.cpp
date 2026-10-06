// 探针 7：指针层面的多态
//
// 要回答三个问题：
//   ① Circle* 为什么能直接塞进 Shape* 的格子里？（隐式向上转型）
//   ② 转型之后，两个指针指向的地址是不是变了？
//   ③ 对象里的 vptr 到底占在哪儿？

#include <iostream>
#include <windows.h>

class Shape {
public:
    virtual double area() const { return 0.0; }
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    double r_;

    Circle(double r) : r_(r) {}

    double area() const override { return 3.14159265 * r_ * r_; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Circle c(2.0);
    Circle* pc = &c;
    Shape*  ps = &c;                 // 隐式向上转型：不写任何转换，编译器自动做

    std::cout << "=== 探针 7：指针层面的多态 ===\n\n";

    std::cout << "sizeof(Shape)  = " << sizeof(Shape) << "      ← 只有 vptr，没有数据成员\n";
    std::cout << "sizeof(Circle) = " << sizeof(Circle) << "     ← vptr(8) + double(8)\n";
    std::cout << "sizeof(Shape*) = " << sizeof(Shape*) << "      ← 指针自己永远是 8 字节\n\n";

    std::cout << "Circle* pc = " << pc << "\n";
    std::cout << "Shape*  ps = " << ps << "\n";
    std::cout << "两个指针的值相同吗？ "
              << (static_cast<void*>(pc) == static_cast<void*>(ps)) << "\n\n";

    std::cout << "对象起始地址 : " << static_cast<void*>(&c) << "\n";
    std::cout << "成员 r_ 的偏移 : "
              << (reinterpret_cast<char*>(&c.r_) - reinterpret_cast<char*>(&c))
              << " 字节   ← 开头那 8 字节被 vptr 占了\n\n";

    std::cout << "ps->area() = " << ps->area()
              << "   ← ps 只是 Shape*，却算出了圆的面积\n";

    return 0;
}
