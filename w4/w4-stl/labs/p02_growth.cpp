// ============================================================================
// 探针 2 · p02_growth
// 问题：标准库的扩容因子是几倍？（对照你 W2 手写的 MyVector：它是 2 倍）
// 讲义：打卡训练\W4\W4D1_C++_string与vector.md（第 5 节）
// ----------------------------------------------------------------------------
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p02_growth.exe
// 提示：这个探针会 push_back 一百万次，跑起来要一两秒，属正常。
// ============================================================================

#include <iostream>
#include <vector>
#include <cstddef>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "== 1. 容量变化序列（容量一变就打印）==\n";
    // TODO 1  建一个空的 std::vector<int> v，再建一个 std::size_t last = 0;
    //         （last 用来记住"上次打印过的容量"）
    std::vector<int> v{};
    std::size_t last = 0;
    // TODO 2  写一个 for 循环，i 从 0 数到 999999：
    //             v.push_back(i);
    //             然后判断 v.capacity() 和 last 相不相等；
    //             不相等就打印 v.capacity()、跟一个空格，并把 last 更新成现在的容量。
    //         （想不出来就先写注释，试着用中文把步骤写清楚，再翻成代码）
    for (int i = 0;i < 1000000;i++) {
        v.push_back(i);
        if (v.capacity() != last) {
            std::cout << "v.capacity()=" << v.capacity() << "  \n";
            last = v.capacity();
        }
    }
    // TODO 3  循环结束之后，打印 v.size() 和 v.capacity()
    std::cout << "v.size()=" << v.size() << "  v.capacity()=" << v.capacity()<<"\n";
    std::cout << "\n== 2. 我的结论 ==\n";
    // TODO 4  把相邻两个容量相除（后面的除以前面的），结果是 1.5 还是 2? 1.5
    //         然后回答：你 MyVector（2 倍扩容）跑 10 万次，容量会停在哪个数？2^n，n取整数的同时大于10万且最小的数

    return 0;
}
