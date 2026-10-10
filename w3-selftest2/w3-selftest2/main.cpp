// W3 · 阶段测评预演（第 2 轮 · 【闭卷】限时 60 分钟）
// ==================================================================
// 规则（自己对自己诚实，这一轮才有意义）：
//   1. 不许打开 w3-selftest、不许翻 W2 的 MyVector、不许问助手
//   2. 60 分钟一到就停手，哪怕没写完
//   3. 【只有编译不过时才现场动手改】；"能编译但结果不对"的，记到下面的卡点记录
//   4. 参考版在 w3-selftest（已提交），今天不要看它
//
// 【要交的东西】一个完整的小程序：类 + 指针 + 动态内存
//   类名自己定，但必须包含：
//     · 一块自己 new 出来的内存（int*）
//     · "用了几个" 和 "一共申请了几格" 两个计数器
//     · 构造 / 析构 / 拷贝构造 / 拷贝赋值（四项一个都不能少）
//     · 至少三个对外操作（比如 压入 / 弹出 / 看顶）
//     · 一个 main：造对象 → 压数据 → 取数据 → 拷贝一个对象 → 全部析构
//
// 【验收】退出码 0 + ASan 零报告 + 你打出来的数字自己对得上
//
// 【卡点记录】（边写边记：哪一行 / 什么现象 / 你猜的原因）
//
// ==================================================================

#include <iostream>
#include <cstddef>
#include <windows.h>
class Vector {
private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
public:
    Vector():data_(nullptr),size_(0),capacity_(0){}
    ~Vector() { delete[] data_;std::cout << "[析构]" << std::endl; }
    const std::size_t size() { return size_; }
    const std::size_t capacity() { return capacity_; }
    void read() {
        for (std::size_t i = 0;i < size_;i++) {
            std::cout << data_[i] << "\n";
        }
    }
    Vector(const Vector& other) {
        data_ = new int[other.capacity_];
        for (std::size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    Vector& operator= (const Vector& other){
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = new int[other.capacity_];
        for (std::size_t i = 0;i < other.size_;i++) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }
    void push(int value) {
        if (size_ == capacity_ ) {
            int* newdata_ = nullptr;
            capacity_ = (capacity_ == 0) ? 1 : 2 * capacity_;
            newdata_ = new int[capacity_];
            for (std::size_t i = 0;i < size_;i++) {
                newdata_[i] = data_[i];
            }
            delete[] data_;
            size_++;
            newdata_[size_ - 1] = value;
            data_ = newdata_;
        }
        else {
            size_++;
            data_[size_ - 1] = value;
        }
    }
    int pop() {
        size_ -= 1;
        return data_[size_];
    }
    int top() {
        return data_[size_-1];
    }
};
int main() {
    SetConsoleOutputCP(CP_UTF8);

    // TODO(你)：从这里开始，全部自己写（类和 main 的测试都自己安排）
    Vector v;
    for (int i = 0;i <= 5;i++) {
        v.push(i * 10);
    }
    std::cout << "size_=" << v.size() << "   capacity_=" << v.capacity() << std::endl;
    std::cout << "top_=" << v.top() << std::endl;
    Vector a = v;
    Vector b;
    b = v;
    v.read();
    a.read();
    b.read();
    return 0;
}
