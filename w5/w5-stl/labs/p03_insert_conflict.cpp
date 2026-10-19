// ============================================================================
// 探针 3 · 插入时 key 已存在，谁覆盖、谁不覆盖？
// ============================================================================

#include <iostream>
#include <map>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::map<std::string, int> m{{"apple", 1}};

    // TODO 1：调用 m.insert({"apple", 99})，保存返回的 pair；
    //         打印 .second 和 m["apple"]。
    auto a = m.insert({ "apple",99 });
    std::cout << ".second = " << a.second << "  m[apple] = " << m["apple"] << "\n";
    // TODO 2：调用 m.insert_or_assign("apple", 99)，打印 .second 和值。
    auto b = m.insert_or_assign("apple",99);
    std::cout << ".second = " << b.second << "  m[apple] = " << m["apple"] << "\n";
    // TODO 3：调用两次 m.try_emplace("banana", ...)，第二次换一个值；
    //         分别打印 .second 和 m["banana"]。
    auto c = m.try_emplace("banana", 5);
    std::cout << ".second = " << c.second << "  m[banana] = " << m["banana"] << "\n";
    auto d = m.try_emplace("banana", 10);
    std::cout << ".second = " << d.second << "  m[banana] = " << m["banana"] << "\n";
    // TODO 4：用注释回答：
    //         insert / insert_or_assign / try_emplace 各自适合什么场景？ 前者适合只插入，有则放弃，中间的是强制更新，try和insert类似，但是能提升运算速度

    return 0;
}
