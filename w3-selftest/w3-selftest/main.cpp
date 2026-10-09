// W3 · 阶段测评预演（第 1 轮 · 开卷）
// ------------------------------------------------------------------
// 10/11 的阶段测评是：60 分钟、不看参考，写出含"类 + 指针 + 动态内存"的
// 完整小程序（手写栈或队列），ASan 无内存错误。
//
// 今天先来第 1 轮，规则放宽一点：**允许翻你自己 W2 的 MyVector**，
// 但类要你自己从头写（这次不许继承 MyVector —— 测评要的是你自己管内存）。
//
// 【你要实现的类】IntStack
//   数据成员：自己定（提示：一块 int*、用了几个、一共申请了几格）
//
//   必须有这些接口：
//     IntStack()                                默认构造
//     ~IntStack()                               析构：把内存还回去
//     IntStack(const IntStack& other)           拷贝构造：深拷贝
//     IntStack& operator=(const IntStack& other) 拷贝赋值：先判自赋值
//     void push(int value)                      压栈；满了按两倍扩容
//     int  pop()                                弹栈并返回值（调用者保证非空）
//     int& top()                                返回栈顶的引用
//     std::size_t size() const
//     std::size_t capacity() const
//     bool empty() const
//
//   不许用：std::vector、std::stack（这是测评的规矩：自己管内存）
//
// 【验收】下面 main 里的输出数字全对 + 退出码 0 + ASan 零报告
//
// 【今天和测评的差别】今天 main 是我写好的；测评那天 main 也得你自己写。
// ------------------------------------------------------------------

#include <iostream>
#include <cstddef>
#include <windows.h>

// ============================================================
// 你要写的类写在这里（main 的上面）
// ============================================================
class IntStack {
public:
    IntStack()
        :data_(nullptr),size_(0),capacity_() {}
    ~IntStack() {delete[] data_ ;std::cout << "[析构]" << std::endl; }
    IntStack(const IntStack& other) {
        data_ = nullptr;
        size_ = other.size_;
        if (size_ == 0) {
            return;
        }
        capacity_ = other.capacity_;
        data_ = new int[other.capacity_];
        for (std::size_t i = 0;i < other.size_;i++) {
            data_[i] = other.data_[i];
        }
    }
    IntStack& operator=(const IntStack& other){
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = nullptr;
        if (other.size_ == 0) {
            return *this;
        }
        data_ = new int[other.capacity_];
        for (std::size_t i = 0;i < other.size_;i++) {
            this->data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }
    void push(int value) {
        if(size_==capacity_){
            std::size_t newCap = (capacity_ == 0) ? 1 : 2 * capacity_;
            int* newdata_ = new int[newCap];
            for (std::size_t i = 0;i < size_;i++) {
                newdata_[i] = data_[i];
            }
            delete[] data_;
            capacity_ = newCap;
            data_ = newdata_;
        }
        data_[size_] = value;
        size_++;
    }
    int pop() {
        if (size_ == 0) {
            return 0;
        }
        size_ -= 1;
        return data_[size_];
    }
    int& top() {
        return data_[size_ - 1];
    }
    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_;}
    bool empty() const {
        if (size_ == 0) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};
// ============================================================
// 下面是我的测试驱动，不用改
// ============================================================
int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 1. push 5 个，看 size / capacity / top ===\n";
    IntStack s;
    for (int i = 1; i <= 5; ++i) {
        s.push(i * 10);
    }
    std::cout << "size = " << s.size() << "  capacity = " << s.capacity()
              << "  top = " << s.top() << "\n";
    // 期望：size = 5   top = 50（capacity 只要 >= 5 就行，两倍扩容应该是 8）

    std::cout << "\n=== 2. 弹空，看顺序 ===\n";
    while (!s.empty()) {
        std::cout << s.pop() << " ";
    }
    std::cout << "\n";
    // 期望：50 40 30 20 10

    std::cout << "\n=== 3. push 10 万次 ===\n";
    IntStack big;
    for (int i = 0; i < 100000; ++i) {
        big.push(i);
    }
    std::cout << "size = " << big.size() << "  capacity = " << big.capacity() << "\n";
    // 期望：size = 100000   capacity = 131072

    std::cout << "\n=== 4. 拷贝构造：动副本，原件不能变 ===\n";
    IntStack a;
    a.push(1);
    a.push(2);
    a.push(3);
    IntStack b = a;              // 拷贝构造
    b.pop();                     // 只动 b
    std::cout << "a.size = " << a.size() << "  a.top = " << a.top() << "\n";
    std::cout << "b.size = " << b.size() << "  b.top = " << b.top() << "\n";
    // 期望：a.size = 3  a.top = 3     b.size = 2  b.top = 2

    std::cout << "\n=== 5. 拷贝赋值 + 自赋值 ===\n";
    IntStack c;
    c.push(99);
    c = a;                       // 拷贝赋值
    std::cout << "c.size = " << c.size() << "  c.top = " << c.top() << "\n";
    // 期望：c.size = 3  c.top = 3
    c = c;                       // 自赋值：不能把数据弄没
    std::cout << "自赋值之后 c.size = " << c.size() << "  c.top = " << c.top() << "\n";
    // 期望：还是 3 和 3

    std::cout << "\n=== 6. 空对象之间拷贝 ===\n";
    IntStack e1;
    IntStack e2 = e1;
    e2 = e1;
    std::cout << "空对象拷贝没崩，size = " << e2.size() << "\n";
    // 期望：0

    std::cout << "\n=== 全部跑完 ===\n";
    std::cout.flush();
    return 0;
}
