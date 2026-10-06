// 探针 9：纯虚函数与抽象类
//
//   virtual double area() const = 0;   ← "= 0" 就是纯虚函数：我只声明，不实现
//   有纯虚函数的类叫抽象类 → 不能创建它的对象（Shape s; 编译不过，见 broken 文件夹）
//   它只做一件事：规定"凡是形状，都必须能算面积、都必须有名字"

#include <iostream>
#include <windows.h>

class Shape {
public:
    virtual double area() const = 0;                 // 纯虚函数
    virtual const char* name() const = 0;            // 纯虚函数
    virtual ~Shape() { std::cout << "  [析构] ~Shape\n"; }
};

class Circle : public Shape {
public:
    double r_;
    Circle(double r) : r_(r) {}

    ~Circle() { std::cout << "  [析构] ~Circle\n"; }
    double area() const override { return 3.14159265 * r_ * r_; }
    const char* name() const override { return "圆  "; }
};

class Rect : public Shape {
public:
    double w_;
    double h_;

    Rect(double w, double h) : w_(w), h_(h) {}

    ~Rect() { std::cout << "  [析构] ~Rect\n"; }
    double area() const override { return w_ * h_; }
    const char* name() const override { return "矩形"; }
};

// 通过基类【引用】调用，一样是多态（昨天只演示过指针）
void describe(const Shape& s) {
    std::cout << "  引用调用：" << s.name() << " 面积 = " << s.area() << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 9：纯虚函数与抽象类 ===\n\n";
    // Shape s;      ← 这一行编译不过：C2259 无法实例化抽象类

    Shape* shapes[3];
    shapes[0] = new Circle(2.0);
    shapes[1] = new Rect(3.0, 4.0);
    shapes[2] = new Circle(1.0);

    std::cout << "-- 用基类指针数组统一处理 --\n";
    double total = 0.0;
    for (Shape* p : shapes) {
        std::cout << "  " << p->name() << " 面积 = " << p->area() << "\n";
        total += p->area();
    }
    std::cout << "  总面积 = " << total << "\n";

    std::cout << "\n-- 用基类引用单独看一个 --\n";
    describe(*shapes[0]);

    std::cout << "\n-- 统一 delete --\n";
    std::cout.flush();
    for (Shape* p : shapes) delete p;

    std::cout << "\n抽象类本身一个对象都没建过，但所有操作都写在它身上。\n";
    return 0;
}
