// ============================================================================
// 探针 1 · operator[] 到底会不会插入？
// 讲义：打卡训练\W5\W5D1_C++_map与unordered_map.md
// ----------------------------------------------------------------------------
// 只填 TODO，不抄 ref01。跑完把输出抄进讲义的证据表。
// ============================================================================

#include <iostream>
#include <map>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::map<std::string, int> m;
    std::cout << "起始 size = " << m.size() << "\n";
    // TODO 1：用 m["apple"] 读一次，把返回的东西绑定到 int&；
    //         打印这次访问前后的 size()，以及读到的值。
    std::cout << "size0 =" << m.size() << "\n";
    int& a = m["apple"];
    std::cout << "size1 =" << m.size() << "  值为" << a << "\n";
    // TODO 2：把 m["apple"] 改成 10，再打印 size() 和值。
    m.insert_or_assign("apple", 10);
    std::cout << "size2 =" << m.size() << "  值为" << a << "\n";
    // TODO 3：执行 m["banana"] += 2，打印 size() 和 m["banana"]。
    m["banana"] += 2;
    std::cout << "size3 =" << m.size() << "  m[banana] =" << m["banana"] << "\n";
    // TODO 4：用 2~3 句注释回答：
    //         为什么 operator[] 既能读又能写？ 因为和vector类似，这里的键就像vector的下标一样
    //         如果 mapped type 没有默认构造函数，会发生什么？会导致无法直接通过[]来改变或者加入值

    return 0;
}
