// 探针 2：最小的 Shape → Circle（只用继承语法，先不碰 virtual）
//
// 要观察两件事：
//   ① 派生类怎么"继承"基类的成员和函数
//   ② 构造 / 析构的调用顺序（W2 讲对象生命周期，这里多了一层基类）

#include <iostream>
#include <string>
#include <windows.h>

class Shape {
public:
    std::string name_;                  // 基类的成员：派生类可以直接用

    Shape(std::string name) : name_(name) {
        std::cout << "  [构造] Shape(" << name_ << ")\n";
    }

    ~Shape() {
        std::cout << "  [析构] ~Shape(" << name_ << ")\n";
    }

    // 基类版本：不知道任何一个具体形状，只能返回 0。
    // 注意：这里**没有** virtual。先记住这一行，探针 3 会回来看它。
    double area() const {
        return 0.0;
    }
};

class Circle : public Shape {
public:
    double r_;

    // 派生类的构造函数必须负责把"基类那一半"也构造好：
    // ": Shape("圆")" 这一步叫"调用基类构造函数"
    Circle(double r) : Shape("圆"), r_(r) {
        std::cout << "  [构造] Circle(r=" << r_ << ")\n";
    }

    ~Circle() {
        std::cout << "  [析构] ~Circle(r=" << r_ << ")\n";
    }

    double area() const {
        return 3.14159265 * r_ * r_;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 2：最小继承 + 构造/析构顺序 ===\n\n";

    std::cout << "-- 情况 A：直接建一个 Circle 对象 --\n";
    {
        Circle c(2.0);
        std::cout << "  c.name_ = " << c.name_ << "      ← 用的是基类成员\n";
        std::cout << "  c.area() = " << c.area() << "     ← Circle 那份（对）\n";
    }   // 出作用域，析构

    std::cout << "\n-- 情况 B：通过基类指针看它 --\n";
    {
        Shape* p = new Circle(2.0);
        std::cout << "  p->name_ = " << p->name_ << "\n";
        std::cout << "  p->area() = " << p->area()
                  << "          ← 跑的是 Shape 那份（不对！），指针背后明明是个圆\n";
        delete p;                        // ← 也记住这一行，探针 4 会回来看它
    }

    return 0;
}
