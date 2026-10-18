// ============================================================================
// ref07 · vector 的迭代器和 deque 的迭代器，"走"起来有什么不一样
// ============================================================================
// 起因：问"迭代器是不是一个类，会自己跳过中间空着的地方去找下一个元素？"
// 这个程序把两种迭代器每走一步的【地址】打出来，一眼就能看出区别。
// 跑法：.\build\Debug\ref07_iter_walk.exe
// ============================================================================

#include <iostream>
#include <vector>
#include <deque>
#include <cstddef>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "sizeof(vector<int>::iterator) = " << sizeof(std::vector<int>::iterator) << " 字节\n";
    std::cout << "sizeof(deque<int>::iterator)  = " << sizeof(std::deque<int>::iterator) << " 字节\n";

    // ---- vector：一路连续 ----
    std::vector<int> v(8, 7);
    std::cout << "\n--- vector：每次 ++it，地址应该稳定地 +" << sizeof(int) << " ---\n";
    const void* prev = nullptr;
    int vector_jumps = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        const void* p = static_cast<const void*>(&*it);
        if (prev != nullptr) {
            const long long diff = static_cast<const char*>(p) - static_cast<const char*>(prev);
            if (diff != static_cast<long long>(sizeof(int))) { ++vector_jumps; }
        }
        std::cout << "   第 " << (it - v.begin()) << " 个元素: &*it = " << p << "\n";
        prev = p;
    }
    std::cout << "   → 不是 +4 的次数：" << vector_jumps << "（0 就是全程连续）\n";

    // ---- deque：多数也 +4，但跨块时会跳 ----
    std::deque<int> d(300, 7);
    std::cout << "\n--- deque：多数步也是 +" << sizeof(int) << "，但跨块时会【跳一大步】 ---\n";
    prev = nullptr;
    int deque_jumps = 0;
    for (auto it = d.begin(); it != d.end(); ++it) {
        const void* p = static_cast<const void*>(&*it);
        if (prev != nullptr) {
            const long long diff = static_cast<const char*>(p) - static_cast<const char*>(prev);
            if (diff != static_cast<long long>(sizeof(int))) {
                ++deque_jumps;
                std::cout << "   ↑ 在【第 " << (it - d.begin()) << " 个元素】处跳了 "
                          << diff << " 字节（跨块了）\n";
            }
        }
        prev = p;
    }
    std::cout << "   → 不是 +4 的次数：" << deque_jumps << "（>0 就说明中间有跳跃）\n";
    std::cout << "   注意：这 " << deque_jumps << " 次跳跃，迭代器自己处理掉了，你写 ++it 时看不见。\n";
    return 0;
}
