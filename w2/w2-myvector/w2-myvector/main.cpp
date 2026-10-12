#include<iostream>
#include<vector>
#include<windows.h>
#include <cstddef>
//size是指内存里的元素数量，capacity是指内存的被分配的空间；记录capacity的意义在于判断内存是否已满，满了要扩容就是push_back的核心。
//满了的条件就是新加进去的元素超出了内存的空间的上限；例如扩容时，new int[4]，后面出现a[4]=…就知道超出。
//先申请新的更大的内存，然后用赋值搬运把原来的元素放进去，新的元素在扩容完后就被自动放入，把原来的那个内存归还回去，最后更新元素数目和内存容量。
//我不清楚而且好像没印象，请具体展开讲讲。
class MyVector {
public:
    MyVector()
        : data_(nullptr), size_(0), capacity_(0) {
    }
    explicit MyVector(std::size_t n)
        : data_(nullptr), size_(0), capacity_(0) {
        data_=new int[n]();
        size_=n;
        capacity_=n;
        // TODO: 申请 n 个 int，把 n 个元素初始化为 0，设置 size_ 和 capacity_
    }
    ~MyVector() {
        delete[] data_;
        // TODO: 把堆内存还回去
    }
    void push_back(int value) {
        if (size_==capacity_) {      // 哪两个成员相等？
            grow();                    // 调用扩容
        }
        data_[size_] = value;                // 放到第 size_ 个格子
        size_ += 1;                        // 多用一格
    }
        // TODO: 1) 如果 size_ == capacity_，先扩容
        //       2) 把 value 放到 data_[size_]
        //       3) ++size
    int& operator[](std::size_t i) {
        return data_[i];
        // TODO: 返回第 i 个元素的引用（不检查越界，和 std::vector 一样）
    }
    const int& operator[](std::size_t i) const {
        return data_[i];
        // TODO: 同上，但只读
    }
    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    MyVector(const MyVector& other)
        : data_(nullptr), size_(0), capacity_(0) {   // 初始化列表已给好
        // 第 1 步：给自己申请【一排】int —— 申请几个？（提示：看 other 有几个)
        data_ = new int[other.size_];
        // 第 2 步：把 other 的数据逐个搬过来（循环上界用 other 的哪个成员？）
        for (std::size_t i = 0;i < other.size_;i++) {
            data_[i] = other.data_[i];
        }
        // 第 3 步：把两个计数器也对齐
        size_ = other.size_;
        capacity_ = other.size_;
    }
    MyVector& operator=(const MyVector& other) {
        // 第 0 步：自赋值判断（为什么必须在最前面，见下）
        if (this == &other) return *this;
        // 第 1 步：把自己原来的内存还掉
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        // 第 2 步：申请新内存 + 搬运（和拷贝构造同一套动作）
        if (other.size_ > 0) {
            data_ = new int[other.size_];
            for (std::size_t i = 0;i < other.size_;i++) {
                data_[i] = other.data_[i];
            }
        }
        size_ = other.size_;
        capacity_ = other.size_;
        // 第 3 步：返回自己
        return *this;
    }
private:
    void grow() {
        std::size_t newCap = (capacity_ == 0) ? 1 : 2*capacity_;
        int* newData = new int [newCap];
        for (int i = 0;i < size_;i++) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
        // TODO: 两倍扩容。capacity_ 为 0 时怎么处理？
        //       顺序：算新容量 → 申请新块 → 搬运 → delete 旧块 → 更新成员
    }
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};
int main() {
	SetConsoleOutputCP(CP_UTF8);
    MyVector v;
    for (int i = 0; i < 100000; ++i) {
        v.push_back(i);
    }
    std::cout << "size     = " << v.size() << "\n";
    std::cout << "capacity = " << v.capacity() << "\n";
    std::cout << "v[0]     = " << v[0] << "\n";
    std::cout << "v[99999] = " << v[99999] << "\n";
    MyVector a;
    for (int i = 0; i < 3; ++i) a.push_back(i * 10);
    MyVector b = a;      // 拷贝构造
    b[0] = 999;          // 期望 a[0] 仍是 0
    MyVector c;
    c.push_back(5);
    c = a;               // 拷贝赋值
    c = c;               // 自赋s
    return 0;
}
