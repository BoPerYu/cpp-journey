// ============================================================================
// 探针 4 · p04_copy
// 问题：std::vector 的 b = a 是"复制一份"还是"指向同一块"？（对照 Python 的 b = a）
// 讲义：打卡训练\W4\W4D1_C++_string与vector.md（第 5 节）
// ----------------------------------------------------------------------------
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p04_copy.exe
// ============================================================================

#include <iostream>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "== 1. 拷贝构造：std::vector<int> b = a ==\n";
    // TODO 1  建 std::vector<int> a{1, 2, 3}; 然后 std::vector<int> b = a;
    std::vector<int> a{ 1, 2, 3 };
    std::vector<int> b = a;
    // TODO 2  把 b[0] 改成 999，然后打印 a[0] 和 b[0]
    //         （问：改的是 b，a 有没有跟着变？）
    b[0] = 999;
    std::cout << "a[0]=" << a[0] << "  b[0]=" << b[0] << "\n";
    // TODO 3  打印 a.data() 和 b.data()。
    //         这两个是"数据首地址"的指针，直接 std::cout << a.data() 会打出一串十六进制；
    //         要看得清楚，就照讲义里那样转成 const void* 再打：
    //         std::cout << static_cast<const void*>(a.data()) << "\n";
    //         问：两个地址一样吗？这说明什么？
    std::cout << "a.data()=" << a.data() << "  b.data=" << b.data() << "\n";
    std::cout << "a.data()=" << static_cast<const void*>(a.data()) << "\n";
    std::cout << "\n== 2. 拷贝赋值：c = a ==\n";
    // TODO 4  先 std::vector<int> c;（空的），再 c = a;
    //         把 c[1] 改掉，打印 c[1] 和 a[1]，看 a 有没有被影响
    std::vector<int> c;
    c = a;
    c[1] = 0;
    std::cout << "c[1]=" << c[1] << "  a[1]=" << a[1] << "\n";
    std::cout << "\n== 3. 我的结论 ==\n";
    // TODO 5  一句话：C++ 的 b = a 和 Python 的 b = a（列表）差在哪？
    //         顺便说一句：这件事你 W2 自己写 MyVector 的拷贝构造时，亲手做过一遍——
    //         那两行代码在 w2-myvector 里，回去看一眼能找到吗？

    return 0;
}
