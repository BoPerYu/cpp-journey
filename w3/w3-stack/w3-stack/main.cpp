// W3 第 3 天 · 继承综合：MyVector → MyStack
// ------------------------------------------------------------------
// 下面这个 MyVector 是从 w2-myvector\main.cpp 搬过来的（原件不动），
// 只清掉了过时的 TODO 注释。
//
// 今天要做三件事：
//   ① 给 MyVector 加一个 pop_back()（为什么必须先做，见文件末尾的说明）
//   ② 用【继承】写 MyStack 的 push / pop / top，跑通弹栈顺序
//   ③ 用【组合】写同一个栈 MyStack2，体会两种写法的差别
//   ④ main 里那个"虚析构实验"原样先跑一遍，看 ASan 说什么
// ------------------------------------------------------------------

#include <iostream>
#include <windows.h>
#include <cstddef>

// ============================================================
// W2 写好的动态数组（原样搬来）
// ============================================================
class MyVector {
public:
    MyVector()
        : data_(nullptr), size_(0), capacity_(0) {
    }

    explicit MyVector(std::size_t n)
        : data_(nullptr), size_(0), capacity_(0) {
        data_ = new int[n]();
        size_ = n;
        capacity_ = n;
    }

    virtual ~MyVector() {                       // TODO(你): 这一行要不要 virtual？第 ④ 步的答案就在这
        delete[] data_;
    }

    void push_back(int value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_] = value;
        size_ += 1;
    }

    // 任务 ①：把最后那个元素"去掉"。写在你自己的空间里（这个注释下面）。
    // 提示：去掉 ≠ 还内存。std::vector 的 pop_back 也不缩容，只把"用了几个"减一。
    void pop_back() {
        size_ -= 1;
    }

    int& operator[](std::size_t i) {
        return data_[i];
    }
    const int& operator[](std::size_t i) const {
        return data_[i];
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    MyVector(const MyVector& other)
        : data_(nullptr), size_(0), capacity_(0) {
        data_ = new int[other.size_];
        for (std::size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.size_;
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        if (other.size_ > 0) {
            data_ = new int[other.size_];
            for (std::size_t i = 0; i < other.size_; i++) {
                data_[i] = other.data_[i];
            }
        }
        size_ = other.size_;
        capacity_ = other.size_;
        return *this;
    }

private:
    void grow() {
        std::size_t newCap = (capacity_ == 0) ? 1 : 2 * capacity_;
        int* newData = new int[newCap];
        for (int i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
    }

    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

// ============================================================
// 任务 ②：用【继承】写栈（三个函数体你自己写）
// ============================================================
class MyStack : public MyVector {
public:
    // 压栈：把 value 放到栈顶。
    // 提示：栈顶就是"最后一个元素"。基类里哪个函数就是干这个的？
    void push(int value) {
        push_back(value);
    }

    // 弹栈：把栈顶【拿走】（元素数减一），并返回它的值。
    // 提示：栈顶在 data_ 的哪一格？拿走之后"用了几个"要变成几？
    //       注意：基类的 size_ 是 private，你动不到它 —— 所以第一步才要先加 pop_back()。
    int pop() {
        int v = operator[](size()-1);
        pop_back();
        return v;
    }

    // 只看栈顶，不拿走。
    // 提示：你 W2 学的 operator[] 这会儿正好用得上。
    int& top() {
        return operator[](size()-1);
    }
    ~MyStack() { std::cout << "{析构} ~MyStack\n"; }
};

// ============================================================
// 任务 ③：用【组合】写同一个栈
//   区别就一句话：继承是"我是一个 MyVector"，组合是"我有一个 MyVector"。
// ============================================================
class MyStack2 {
public:
    void push(int value) { data_.push_back(value);}
    int pop() {
        int v = data_.operator[](size()-1);
        data_.pop_back();
        return v;
    }
    int& top() {
        return data_.operator[](size() - 1);
    }
    std::size_t size() const {return data_.size(); }
    bool empty() const { return data_.empty(); }

private:
    MyVector data_;          // ← 这就是"组合"：它是我的一部分，不是我本身
};

// ============================================================
int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 继承版 MyStack ===\n";
    MyStack s;
    for (int i = 1; i <= 5; ++i) {
        s.push(i * 10);
    }
    std::cout << "size = " << s.size() << "   top = " << s.top() << "\n";
    std::cout << "弹栈顺序（期望 50 40 30 20 10）：";
    while (!s.empty()) {
        std::cout << s.pop() << " ";
    }
    std::cout << "\n\n";
    // 露馅 1：两个对象会互相串（static 每个函数只有一份）
    MyStack2 a; a.push(10);
    MyStack2 b; b.push(20);
    std::cout << "a.top() = " << a.top() << "   b.top() = " << b.top() << "\n";
    // 期望 10 和 20；如果是 10 和 10 —— 就是它

    // 露馅 2：改完再 pop，拿到的是旧值
    MyStack2 c; c.push(10); c.push(20);
    c.top() = 999;
    std::cout << "c.top() = " << c.top() << "   c.pop() = " << c.pop() << "\n";
    // 期望 999 和 999；如果 pop 打出 20 —— 999 改到别处去了
    // ---- 任务 ④：虚析构实验 ----
    // 原样先跑一遍，把 ASan 的输出抄下来；再给 MyVector 的析构加 virtual，对比。
    std::cout << "=== 实验：基类指针 delete 派生对象 ===\n";
    std::cout.flush();
    MyVector* p = new MyStack();
    p->push_back(99);
    delete p;
    std::cout << "delete 完成\n";

    return 0;
}
