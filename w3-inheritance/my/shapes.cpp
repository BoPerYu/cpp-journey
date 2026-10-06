// W3 主程序骨架 · Shape / Circle / Rectangle
// ------------------------------------------------------------------
// 规则（你自己的学习约定）：骨架给了，**函数体自己写**。
// 写不动的地方先写注释说"我卡在哪"，再问。
// ------------------------------------------------------------------

#include <iostream>
#include <string>
#include <windows.h>

class Shape {
public:
    std::string name_;

    Shape(std::string name) : name_(name) {}

    virtual ~Shape() {                                  
        std::cout << "  [析构] ~Shape(" << name_ << ")\n";
    }

    virtual double area() const = 0;
    virtual const char* name() const = 0;
};

class Circle : public Shape {
public:
    double r_;

    Circle(double r) : Shape("圆"), r_(r) {}

    ~Circle() {
        std::cout << "  [析构] ~Circle(r=" << r_ << ")\n";
    }

    double area() const override{
        // TODO(你): 写圆的面积
        return r_*r_*3.14159265;
    }
    const char* name() const override{
        return "圆";
    }
};

// ⚠️ 注意这个类名为什么不叫 Rectangle：
//    windows.h 里已经声明了一个函数叫 Rectangle()（画矩形的 Win32 API）。
//     写成 class Rectangle : public Shape 会撞名，报：
//         error C2061: 语法错误: 标识符"Rectangle"
//     所以这里用 Rect。想用全名就得绕开 windows.h，不值得在第一天纠缠。
class Rect : public Shape {
public:
    double w_;
    double h_;

    Rect(double w, double h) : Shape("矩形"), w_(w), h_(h) {}

    ~Rect() {
        std::cout << "  [析构] ~Rect(" << w_ << "x" << h_ << ")\n";
    }

    double area() const override{
        // TODO(你): 写矩形的面积
        return w_*h_;
    }
    const char* name() const override {
        return "矩形";
    }
};
void describe(const Shape& s) {
    std::cout << "Name=" << s.name() << "Area=" << s.area() << std::endl;
}
int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 一个基类指针数组，装三种形状——这就是"统一处理"的入口
    Shape* shapes[3];
    shapes[0] = new Circle(2.0);
    shapes[1] =new Rect(3.0, 4.0);
    shapes[2] = new Circle(1.0);


    std::cout << "=== W3 主程序：三种形状统一处理 ===\n";
    for (Shape* p : shapes) {
        std::cout << p->name() << "  面积 = " << p->area() << "\n";
        describe(*p);
    }
    std::cout << "\n-- 统一 delete --\n";
    // 先 flush：ASan 一旦中止程序，缓冲区里还没写出去的输出会一起丢掉，
    // 你就只能看到 ASan 的报告、看不到前面的结果。加这一行是为了方便对照。
    std::cout.flush();

    for (Shape* p : shapes) {
        delete p;
    }

    // 自检：面积应该是 12.566 / 12 / 3.14159（不是全 0）
    //       析构应该每个对象都出现一次，而且是"先派生、后基类"
    return 0;
}
