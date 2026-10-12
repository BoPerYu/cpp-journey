// 探针 4a：基类析构没有 virtual，而派生类 new 了内存（故意写错的版本）
//
// 这就是《W2复习_类里的指针.md》第 7 题在真实项目里的样子。
// 用 W2 学过的两个工具量它：
//   · 不加 ASan 时，你只看得到"派生类析构一次都没被调用"
//   · 加了 ASan，才会多出一条正式报告

#include <iostream>
#include <windows.h>

class BaseBad {
public:
    BaseBad() { std::cout << "  [构造] BaseBad\n"; }
    ~BaseBad() { std::cout << "  [析构] ~BaseBad\n"; }      // ← 没有 virtual
};

class DerivedBad : public BaseBad {
public:
    int* data_;

    DerivedBad() : data_(new int[100]) {
        std::cout << "  [构造] DerivedBad，申请了 100 个 int\n";
    }

    ~DerivedBad() {
        delete[] data_;
        std::cout << "  [析构] ~DerivedBad，把内存还了\n";
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 4a：基类析构没有 virtual ===\n";

    BaseBad* p = new DerivedBad();   // 用"基类指针"接管派生类对象
    delete p;                        // 你以为它会好好收尾

    std::cout << "=== main 结束 ===\n";
    return 0;
}
