// 探针 4b：和 4a 逐字相同，只改一处——给基类析构加上 virtual
//
// 跑完把 4a、4b 的输出并排看：析构的调用顺序和对象数量都变了。

#include <iostream>
#include <windows.h>

class BaseGood {
public:
    BaseGood() { std::cout << "  [构造] BaseGood\n"; }
    virtual ~BaseGood() { std::cout << "  [析构] ~BaseGood\n"; }   // ← 唯一的区别
};

class DerivedGood : public BaseGood {
public:
    int* data_;

    DerivedGood() : data_(new int[100]) {
        std::cout << "  [构造] DerivedGood，申请了 100 个 int\n";
    }

    ~DerivedGood() {
        delete[] data_;
        std::cout << "  [析构] ~DerivedGood，把内存还了\n";
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 4b：基类析构加了 virtual ===\n";

    BaseGood* p = new DerivedGood();
    delete p;

    std::cout << "=== main 结束 ===\n";
    return 0;
}
