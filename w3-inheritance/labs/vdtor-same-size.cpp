// 探针 13：派生类和基类【一样大】的时候，非虚析构还有没有问题？
//
// 背景：探针 4a 里 ASan 报过 new-delete-type-mismatch，但那条检查是【按大小】判的。
//       如果派生类没有新增成员（和基类一样大），ASan 就一声不吭 —— 那是不是说明没问题？
//
// 这个探针不靠 ASan 报告来回答，而是看【派生类的析构函数有没有被调用】。

#include <iostream>
#include <windows.h>

// ---- 第一对：基类析构【没有】virtual，两边的类都没有数据成员 ----
class BaseBad {
public:
    BaseBad() { std::cout << "  [构造] BaseBad\n"; }
    ~BaseBad() { std::cout << "  [析构] ~BaseBad\n"; }
};

class DerivedBad : public BaseBad {
public:
    DerivedBad() { std::cout << "  [构造] DerivedBad\n"; }
    ~DerivedBad() { std::cout << "  [析构] ~DerivedBad\n"; }
};

// ---- 第二对：同样的形状，只把基类析构加上 virtual ----
class BaseGood {
public:
    BaseGood() { std::cout << "  [构造] BaseGood\n"; }
    virtual ~BaseGood() { std::cout << "  [析构] ~BaseGood\n"; }
};

class DerivedGood : public BaseGood {
public:
    DerivedGood() { std::cout << "  [构造] DerivedGood\n"; }
    ~DerivedGood() { std::cout << "  [析构] ~DerivedGood\n"; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 13：一样大的派生类，非虚析构还错不错？ ===\n\n";
    std::cout << "sizeof(BaseBad)  = " << sizeof(BaseBad)
              << "   sizeof(DerivedBad)  = " << sizeof(DerivedBad) << "\n";
    std::cout << "sizeof(BaseGood) = " << sizeof(BaseGood)
              << "   sizeof(DerivedGood) = " << sizeof(DerivedGood) << "\n\n";

    std::cout << "-- 非虚析构版：delete 一个基类指针 --\n";
    {
        BaseBad* p = new DerivedBad();
        delete p;
    }
    std::cout << "   ^ 数一数 ~DerivedBad 出现了几次\n\n";

    std::cout << "-- 虚析构版：同样的写法 --\n";
    {
        BaseGood* p = new DerivedGood();
        delete p;
    }
    std::cout << "   ^ 再数一次\n";

    std::cout << "\n两边的 ASan 报告都是零 —— 但行为完全不一样。\n";
    return 0;
}
