// ============================================================================
// 探针 9 · set 遍历中删除 + 元素为什么不能直接改
// ============================================================================

#include <iostream>
#include <set>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::set<std::string> s{"apple", "avocado", "banana", "apricot", "cherry"};

    // TODO 1：遍历删除所有以 'a' 开头的词；
    //         必须用 it = s.erase(it)，不能删完再 ++it。
    for (auto it = s.begin();it != s.end();) {
        if (*it>="a" and *it<"b") {
            it = s.erase(it);
        }
        else {
            it++;
        }
    }
    // TODO 2：按 key 删除 "banana"，打印剩余元素。
    s.erase("banana");
    for (auto it = s.begin();it != s.end();++it) {
        std::cout << *it << "  ";
    }
    std::cout << "\n";
    // TODO 3：用注释回答：
    //         set 的迭代器解引用后是 const 元素吗？应该还是？本质应该只是指针指向一个const 对象，应该改改不了还是改不了
    //         能不能写 *it = "new value"？如果不能，怎么“改”一个元素？ 不能，先删后加。（小问题，你说set按升序排列，那我后加的也会自动排序吗）

    return 0;
}
