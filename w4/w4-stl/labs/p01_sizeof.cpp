// ============================================================================
// 探针 1 · p01_sizeof
// 问题：容器对象本身占多少字节？和它里面装了几个元素有关系吗？
// 讲义：打卡训练\W4\W4D1_C++_string与vector.md（第 5 节）
// ----------------------------------------------------------------------------
// 说明：骨架是助手写好的，TODO 你自己填。填完跑一遍，把输出抄进讲义第 6 节证据表。
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p01_sizeof.exe
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "== 1. 容器对象本身占多少字节 ==\n";
    // TODO 1  打印 sizeof(std::string)
    //   句式给你一条，剩下两条照着自己写：
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << "\n";

    // TODO 2  打印 sizeof(std::vector<int>)
    std::cout << "sizeof(std::vector<int>)=" << sizeof(std::vector<int>) << "\n";
    // TODO 3  打印 sizeof(std::vector<std::string>)
    //   先猜，把猜测写在这行注释里，再写代码：
    //   我猜 sizeof(std::vector<std::string>) =std::string自己的大小（具体多少看它），因为std::vector<std::string>相当于是把一个string类作为类似于一个int类型了，存的是它一整个类，比如类里有六个字，vector里就是只存了他一个，这一个是这个类，类比int就是只存了数字2。
    std::cout << "sizeof(std::vector<std::string>)=" << sizeof(std::vector<std::string>) << "\n";
    std::cout << "\n== 2. 对象大小 vs 里面有几个元素 ==\n";
    // TODO 4  建 std::string s = "abc"；打印 sizeof(s) 和 s.size()
    //         然后把 s 换成一句长得多的话（比如 s = "一二三四五六七八九十"），
    //         再把这两个数打一遍。
    //         问自己：哪一个是变的，哪一个没变？为什么？
    std::string s = "abc";
    std::cout << "sizeof(s)=" << sizeof(s) << "  s.size()=" << s.size() << "\n";
    s = "一二三四五六七八九十";
    std::cout << "sizeof(s)=" << sizeof(s) << "  s.size()=" << s.size() << "\n";
    std::cout << "\n== 3. v(3) 和 v{3} 差在哪 ==\n";
    // TODO 5  建三个 vector：std::vector<int> v1(3)、v2{3}、v3{1,2,3}
    //         分别打印它们的 size()，并且把内容也打出来
    //         （内容用下标循环打，或者用 range-for，两种都行）
    std::vector<int> v1(3);
    std::vector<int> v2{ 3 };
    std::vector<int> v3{ 1,2,3 };
    for (const auto& a : {v1,v2,v3}) {
        std::cout << "size()=" << a.size() << "\n";
    }
    std::cout << "\n== 4. 我的结论 ==\n";
    // TODO 6  用两、三句话打出来：sizeof 量的是什么？它和 size() 有什么区别？sizeof测量内存，size（）量元素数目。
    //         v1(3) 和 v2{3} 的区别是什么？前者构建含三个元素的vector类，默认值为0.后者构建仅含一个“3”元素的vector类。

    return 0;
}
