// ============================================================
// W2 对象生命周期探针（2026-09-30）
// 用途：把"什么时候构造、什么时候析构、什么时候拷贝"打印出来看。
// 这是探针，不是作业。每个特殊成员函数都只打印一行，方便你数调用次数。
//
// 用法：
//   life_lab      -> 作用域、析构顺序、传值 / 传引用 / 返回
//   life_lab 1    -> 拷贝构造 vs 拷贝赋值 vs 自赋值
//   life_lab 2    -> 堆对象（new / delete）与放进 vector 时的搬运
// ============================================================
#include <iostream>
#include <vector>
#include <windows.h>

class Tracer {
public:
    Tracer() : id_(0) {
        std::cout << "   [构造]     默认构造，id = 0\n";
    }
    explicit Tracer(int id) : id_(id) {
        std::cout << "   [构造]     带参构造，id = " << id_ << "\n";
    }
    Tracer(const Tracer& other) : id_(other.id_) {
        std::cout << "   [拷贝构造] 由 id = " << other.id_ << " 造出新的 id = " << id_ << "\n";
    }
    Tracer& operator=(const Tracer& other) {
        if (this == &other) {
            std::cout << "   [拷贝赋值] 自赋值！识别出来了，什么也不用做\n";
            return *this;
        }
        std::cout << "   [拷贝赋值] 本对象 id = " << id_ << "  改成  " << other.id_ << "\n";
        id_ = other.id_;
        return *this;
    }
    ~Tracer() {
        std::cout << "   [析构]     id = " << id_ << " 没了\n";
    }
    int id() const { return id_; }

private:
    int id_;
};

static void byValue(Tracer t) {
    std::cout << "      函数内部（参数是副本，id = " << t.id() << "）\n";
}

static void byRef(Tracer& t) {
    std::cout << "      函数内部（参数是本人，id = " << t.id() << "）\n";
}

static Tracer makeTracer(int id) {
    Tracer local(id);
    return local;
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);
    int mode = (argc > 1) ? (argv[1][0] - '0') : 0;

    if (mode == 0) {
        std::cout << "=== A. 块作用域：出块就析构，顺序与构造相反 ===\n";
        {
            Tracer a(1);
            Tracer b(2);
            std::cout << "   （块结束，下面开始析构）\n";
        }

        std::cout << "\n=== B. 传值：函数拿到的是副本（会多一次拷贝构造 + 一次析构）===\n";
        Tracer c(3);
        byValue(c);

        std::cout << "\n=== C. 传引用：函数拿到的是本人（不拷贝）===\n";
        byRef(c);

        std::cout << "\n=== D. 返回对象：局部变量 local 先析构，再把值交给外面 ===\n";
        Tracer d = makeTracer(4);
        std::cout << "   （main 里拿到 d，id = " << d.id() << "）\n";

        std::cout << "\n=== main 要结束了，c 和 d 在这里析构 ===\n";
    } else if (mode == 1) {
        Tracer a(10);
        std::cout << "\n--- Tracer b = a;  ← 这是【拷贝构造】，不是赋值 ---\n";
        Tracer b = a;

        std::cout << "\n--- Tracer c(99); c = a;  ← 这才是【拷贝赋值】 ---\n";
        Tracer c(99);
        c = a;

        std::cout << "\n--- c = c;  ← 自赋值 ---\n";
        c = c;

        std::cout << "\n--- main 结束，析构顺序：c、b、a（与构造相反）---\n";
    } else if (mode == 2) {
        std::cout << "=== A. 堆对象：new 的时候构造，delete 的时候才析构 ===\n";
        Tracer* p = new Tracer(7);
        std::cout << "   （只要不 delete，它就一直活着）\n";
        delete p;

        std::cout << "\n=== B. 放进 std::vector，看扩容那一刻发生了什么 ===\n";
        std::vector<Tracer> v;
        for (int i = 0; i < 4; ++i) {
            std::cout << "-- push_back(" << i << ") 之前 capacity = " << v.capacity() << "\n";
            v.push_back(Tracer(i));
        }
        std::cout << "\n=== vector 离开作用域：里面每个元素都被析构 ===\n";
    }
    return 0;
}
