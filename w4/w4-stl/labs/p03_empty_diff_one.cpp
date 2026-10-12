// ============================================================================
// 探针 3 · p03_empty_diff_one
// 问题：空容器的 size() - 1 是多少？"最后一个元素的下标"能不能这么算？
// 讲义：打卡训练\W4\W4D1_C++_string与vector.md（第 5 节）
// ----------------------------------------------------------------------------
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p03_empty_diff_one.exe
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "== 1. 空容器的 size() 和 size() - 1 ==\n";
    // TODO 1  建一个空 std::string（就写 std::string s; 别给初值），
    //         打印 s.size() 和 s.size() - 1
    std::string s;
    std::cout << "s.size()=" << s.size() << "  s.size()-1=" << s.size() - 1 << std::endl;
    // TODO 2  建一个空 std::vector<int>，同样打印这两个表达式
    std::vector<int> t {};
    std::cout << "t.size()=" << t.size() << "  t.size()-1=" << t.size() - 1 << std::endl;
    std::cout << "\n== 2. 标准库自己怎么说 ==\n";
    // TODO 3  打印 std::string::npos
    std::cout << "std::string::npos=" << std::string::npos << "\n";
    // TODO 4  找一个不存在的子串：s.find("zzz")，
    //         打印它的返回值，再打印 (返回值 == std::string::npos)
    std::cout << "s.find(\"zzz\") = " << s.find("zzz") << "\n";
    std::cout << "(s.find(\"zzz\") == std::string::npos) = "
        << (s.find("zzz") == std::string::npos) << "\n";
    std::cout << "\n== 3. 我的结论 ==\n";
    // TODO 5  用一两句话回答：
    //         想取 vector 的"最后一个元素"而写成 v[v.size()-1]，在空容器上等于访问下标几？下标是一个很大的数，2的多少次方-1
    //         标准库给的正规写法是什么？（讲义第 2.4 节有提示）不知道

    return 0;
}
