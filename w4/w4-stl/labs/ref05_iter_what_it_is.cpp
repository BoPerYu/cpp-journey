// ============================================================================
// ref05 · 迭代器到底是什么？（助手写的参考程序，回答"它是值还是地址"）
// ============================================================================
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\ref05_iter_what_it_is.exe
// ============================================================================

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstddef>
#include <typeinfo>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> v{10, 20, 30};

    std::cout << "===== 1. v.begin() 返回的到底是什么 =====\n";
    auto it = v.begin();
    std::cout << "  typeid(it).name() = " << typeid(it).name() << "\n";
    // ⚠️ 这个数随构建配置变（约定第 11 条）：Debug 24 字节、Release 8 字节。
    //    Debug 下迭代器是个类，里面带着调试用的额外成员；Release 下瘦到只包一个指针。
    std::cout << "  sizeof(it)        = " << sizeof(it) << " 字节（Debug 24 / Release 8）\n";
    std::cout << "  *it               = " << *it << "   ← 解引用，拿到第一个元素\n";
    std::cout << "  &*it              = " << static_cast<const void*>(&*it) << "   ← 那一格的内存地址\n";
    std::cout << "  v.data()          = " << static_cast<const void*>(v.data()) << "   ← 缓冲区首地址\n";
    std::cout << "  两者相同吗         = " << ((static_cast<const void*>(&*it) == static_cast<const void*>(v.data())) ? "相同" : "不同") << "\n";

    std::cout << "\n===== 2. ++it 到底做了什么（看地址怎么变） =====\n";
    auto it2 = v.begin();
    std::cout << "  it2 的地址 = " << static_cast<const void*>(&*it2) << "\n";
    ++it2;
    std::cout << "  ++it2 之后 = " << static_cast<const void*>(&*it2)
              << "   （差 " << (reinterpret_cast<const char*>(&*it2) - reinterpret_cast<const char*>(&*v.begin()))
              << " 字节 = sizeof(int)）\n";

    std::cout << "\n===== 3. *it 可以读也可以写（和指针一样） =====\n";
    *v.begin() = 99;
    std::cout << "  执行 *v.begin() = 99 之后 v = {";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    std::cout << "}\n";

    std::cout << "\n===== 4. it - v.begin() 就是下标 =====\n";
    std::cout << "  (v.begin() + 2) - v.begin() = " << ((v.begin() + 2) - v.begin()) << "\n";

    std::cout << "\n===== 5. 为什么需要迭代器：看一个【没有下标】的容器 =====\n";
    std::set<int> st{30, 10, 20};
    std::cout << "  std::set 有下标吗？没写 v[0]（会编译不过）\n";
    std::cout << "  但可以用迭代器遍历： ";
    for (auto s = st.begin(); s != st.end(); ++s) {
        std::cout << *s << "  ";
    }
    std::cout << "\n  同一个 for 形状，套在 vector 上也成立： ";
    for (auto s = v.begin(); s != v.end(); ++s) {
        std::cout << *s << "  ";
    }
    std::cout << "\n  → 这就是迭代器的全部意义：给所有容器一个统一的遍历接口。\n";
    return 0;
}
