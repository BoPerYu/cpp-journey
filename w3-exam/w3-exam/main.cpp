// W3 阶段测评 1（2026-10-11）· 60 分钟 · 不看任何参考
// ==================================================================
// 【题目】写一个完整的小程序，包含"类 + 指针 + 动态内存"。
//   手写一个栈（或队列）—— 内存自己管，不许用 std::vector / std::stack。
//
// 【必须包含】
//   · 一块自己 new 出来的内存（int*）
//   · "用了几个" 和 "一共申请了几格" 两个计数器
//   · 构造 / 析构 / 拷贝构造 / 拷贝赋值（四项一个都不能少）
//   · 至少三个对外操作（压入 / 弹出 / 看顶 之类）
//   · 一个 main：造对象 → 压数据 → 取数据 → 拷贝一个对象 → 看副本改动有没有影响原件 → 全部析构
//
// 【验收】
//   · 退出码 0
//   · ASan 零报告
//   · 你自己打出来的数字自己说得通
//
// 【规则】
//   · 不看 w3-selftest / w3-selftest2 / w2-myvector / 讲义 / 之前的代码
//   · 60 分钟一到就停手，没写完也停
//   · 只有"编译不过"时才现场修；"能编译但结果不对"的，记下来，等测评结束再一起看
//
// 【卡点记录】（哪一行 / 什么现象 / 你猜的原因）
//
// ==================================================================

#include <iostream>
#include <cstddef>
#include <windows.h>
class testvector {
private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
public:
    testvector():data_(nullptr),size_(0),capacity_(0){}
    ~testvector() { delete[] data_;std::cout << "[delete]\n"; }
    testvector (testvector& other) {
        data_ = nullptr;
        if (other.size_ == 0) {
            //注意拷贝构造的早退分支，size_ / capacity_ 没初始化（第 40–42 行）
            size_ = 0;
            capacity_ = 0;
            return;
        }
        data_ = new int[other.capacity_];
        for (std::size_t i = 0;i < other.size_;i++) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    testvector& operator= (const testvector& other) {
        int* newdata_;
        newdata_ = nullptr;
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        newdata_ = new int[other.capacity_];
        for (std::size_t i = 0;i < other.size_;i++) {
            newdata_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = newdata_;
        return *this;
    }
    void yaru(int value) {
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : 2 * capacity_;
            int* newdata_;
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
            data_[size_-1] = value;
        }
    }
    int pop() {
        if (size_ == 0) {
            return 0;
    }
        size_ -= 1;
        return data_[size_];
    }
    void read() {
        if (size_ == 0) {
            std::cout<<"None";
        }
        for (std::size_t i = 0;i < size_;i++) {
            std::cout << data_[i] << "  ";
        }
        std::cout << std::endl;
    }
    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
};
int main() {
    SetConsoleOutputCP(CP_UTF8);
    testvector a;
    a.read();
    for (int i = 0;i < 5;i++) {
        a.yaru(i * 10);
    }
    a.read();
    testvector b = a;
    testvector c;
    c = a;
    b.read();
    c.read();
    std::cout << a.pop() << std::endl;
    a.read();

    // 从这里开始

    return 0;
}
