// ============================================================================
// 探针 4 · 遍历中删除：为什么不能直接 m.erase(it) 后继续 ++it？
// ============================================================================

#include <iostream>
#include <map>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::map<std::string, int> m{{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};

    // TODO 1：用 m.erase("b") 删除 key 为 b 的元素，打印剩余内容。
    m.erase("b");
    for (const auto&[key,value] : m) {
        std::cout << key << "->" << value << "\n";
    }
    // TODO 2：用 find("c") 拿到迭代器，调用 m.erase(it)，打印返回值指向的 key。
    auto it = m.find("c");
    auto a=m.erase(it);
    std::cout << a->first << "->" << a->second << "\n";
    // TODO 3：写一个循环，删除所有 value 为偶数的元素；
    //         必须使用 it = m.erase(it) 的写法。
    for (auto i = m.begin();i != m.end();) {
        if (i->second % 2 == 0) {
            i = m.erase(i);
        }
        else {
            i++;
        }
    }
    // TODO 4：用注释回答：
    //         map 插入时，已有迭代器会不会失效？这个我确实不知道，记得以前学vector的话，如果扩容就会失效，但是我不知道map它的运行原理是什么
    //         unordered_map rehash 时，迭代器/引用/指针分别怎样？ 不知道，unordered_map rehash是指什么

    return 0;
}
