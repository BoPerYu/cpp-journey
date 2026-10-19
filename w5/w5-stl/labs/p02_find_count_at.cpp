// ============================================================================
// 探针 2 · find / count / at：谁不会插入？
// ============================================================================

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::map<std::string, int> m{{"apple", 1}};
    std::cout << "起始 size = " << m.size() << "\n";

    // TODO 1：用 find("banana") 查找，打印 it == end() 以及 size()。
    auto it = m.find("banana");
    auto a = it == m.end();
    std::cout << a << "  size = " << m.size() << "\n";

    // TODO 2：用 at("banana") 放在 try/catch 里，捕获 std::out_of_range，
    //         打印 e.what() 和 size()。
    // try和catch我目前还没掌握，还有你这里的e.what()是什么，哪里来的
    try {
        m.at("banana");// 这里放可能抛异常的语句
        // 例如对不存在的 key 调用 at
    }
    catch (const std::out_of_range& e) {
        // e 是捕获到的异常对象
        // e.what() 返回一个描述错误的 C 风格字符串
        std::cout << e.what() << "\n";
    }
    // TODO 3：打印 count("apple") 和 count("banana")。
    std::cout << m.count("apple") << "  " << m.count("banana") << "\n";
    // TODO 4：用注释总结：
    //         只读查一个 key，什么时候用 find、什么时候用 at、什么时候用 count ？ count和find都适合只查询不改动的方式，at适合必须存在否则报错的时候用。

    return 0;
}
