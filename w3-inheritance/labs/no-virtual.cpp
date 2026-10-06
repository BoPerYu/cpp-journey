// 探针 3：不写 virtual 会怎样
//
// 两处翻车，都不报错、不崩溃，只是结果不对——W2 那类"静默错误"的继承版：
//   ① 对象切片：用 Shape 变量接住 Circle，派生类那一半被切掉
//   ② 基类指针调用：指针背后是圆，执行的却是 Shape 那份函数

#include <iostream>
#include <string>
#include <windows.h>

class Shape {
public:
    std::string name_;

    Shape(std::string n) : name_(n) {}

    double area() const {                // 没有 virtual；基类不知道具体形状，只能返回 0
        return 0.0;
    }
};

class Circle : public Shape {
public:
    double r_;

    Circle(double r) : Shape("圆"), r_(r) {}

    double area() const {
        return 3.14159265 * r_ * r_;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 3：不写 virtual 会怎样 ===\n\n";

    Circle c(2.0);

    std::cout << "-- ① 直接通过 Circle 对象调用 --\n";
    std::cout << "   c.area() = " << c.area() << "      ← 正确\n\n";

    std::cout << "-- ② 对象切片：Shape s = c; --\n";
    Shape s = c;                         // 只把基类那一半拷进来，r_ 没了
    std::cout << "   s.name_ = " << s.name_ << "      ← 只有 name_ 活了下来\n";
    std::cout << "   s.area() = " << s.area() << "        ← r_ 已经被切掉，算不出面积\n\n";

    std::cout << "-- ③ 基类指针：Shape* p = &c; --\n";
    Shape* p = &c;
    std::cout << "   p->area() = " << p->area() << "        ← p 指向的明明是 Circle\n";
    std::cout << "   编译器只看 p 的静态类型 Shape*，函数地址在编译期就定死了\n";

    std::cout << "\n-- 对照：加上 virtual 之后，同样的写法会怎样？ --\n";
    std::cout << "   先把《W3D1_虚函数从零讲透》读完，再跑 vdtor_good 看答案。\n";

    return 0;
}
