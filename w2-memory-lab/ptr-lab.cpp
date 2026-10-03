// ============================================================
// W2 指针与动态内存语法实验台（2026-10-03）
// 用途：把 data_[i] / new[] / delete[] / 指针算术这些"没接触过"的写法跑给你看。
// 这是探针，不是作业。用法：ptr_lab
// ============================================================
#include <iostream>
#include <cstddef>
#include <windows.h>

// 一个最小的"容器"，专门用来看成员指针怎么用（不是 MyVector，别混）
class TinyBag {
public:
    explicit TinyBag(std::size_t n)
        : data_(nullptr), size_(0), capacity_(0) {
        data_ = new int[n]();        // 申请 n 个 int，括号让它全部置 0
        size_ = n;
        capacity_ = n;
    }
    ~TinyBag() {
        delete[] data_;              // new[] 配 delete[]；对 nullptr 调用是安全的
    }
    int& at(std::size_t i) { return data_[i]; }
    std::size_t size() const { return size_; }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "===== 1. 栈数组 vs 堆数组 =====\n";
    int stackArr[3] = {1, 2, 3};
    int* heapArr = new int[3]{10, 20, 30};
    std::cout << "栈数组 stackArr:  stackArr[0]=" << stackArr[0]
              << "  sizeof(stackArr)=" << sizeof(stackArr) << "（数组大小）\n";
    std::cout << "堆数组 heapArr :  heapArr[0]=" << heapArr[0]
              << "  sizeof(heapArr)=" << sizeof(heapArr) << "（指针大小！不是数组大小）\n";

    std::cout << "\n===== 2. p[i] 和 *(p+i) 完全等价 =====\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "heapArr[" << i << "] = " << heapArr[i]
                  << "   *(heapArr+" << i << ") = " << *(heapArr + i)
                  << "   &heapArr[" << i << "] = " << static_cast<const void*>(&heapArr[i]) << "\n";
    }

    std::cout << "\n===== 3. 指针算术：+1 走几个字节 =====\n";
    std::cout << "heapArr    的地址 = " << static_cast<const void*>(heapArr) << "\n";
    std::cout << "heapArr + 1 的地址 = " << static_cast<const void*>(heapArr + 1)
              << "   相差 " << (reinterpret_cast<char*>(heapArr + 1) - reinterpret_cast<char*>(heapArr))
              << " 字节 = sizeof(int)\n";

    std::cout << "\n===== 4. new 的几种形式 =====\n";
    int* one = new int(7);           // 一个 int，值是 7
    int* zeroed = new int[4]();      // 4 个 int，全部 0
    int* listed = new int[4]{1, 2, 3, 4};   // 4 个 int，逐个给值
    std::cout << "new int(7)          -> " << *one << "\n";
    std::cout << "new int[4]()        -> " << zeroed[0] << " " << zeroed[1] << " " << zeroed[2] << " " << zeroed[3] << "\n";
    std::cout << "new int[4]{1,2,3,4} -> " << listed[0] << " " << listed[1] << " " << listed[2] << " " << listed[3] << "\n";
    delete one;                      // 一个 → delete
    delete[] zeroed;                 // 一排 → delete[]
    delete[] listed;
    delete[] heapArr;
    heapArr = nullptr;               // 还完立刻掐断

    std::cout << "\n===== 5. 空指针判断 =====\n";
    int* p = nullptr;
    std::cout << "p == nullptr ? " << (p == nullptr ? "是" : "否") << "\n";
    std::cout << "（如果这里写 *p，就是空指针解引用 → 崩。所以用之前先判空）\n";

    std::cout << "\n===== 6. 成员指针怎么用（MyVector 的 data_ 就是这种）=====\n";
    TinyBag bag(3);
    bag.at(0) = 100;
    bag.at(1) = 200;
    std::cout << "bag.size() = " << bag.size()
              << "  bag.at(0) = " << bag.at(0)
              << "  bag.at(1) = " << bag.at(1) << "\n";
    std::cout << "（bag 离开作用域时，析构函数里的 delete[] data_ 自动执行）\n";
    return 0;
}
