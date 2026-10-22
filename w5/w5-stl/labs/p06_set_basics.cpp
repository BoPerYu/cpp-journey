// ============================================================================
// 探针 6 · set 的唯一性、顺序、find/count/erase
// ============================================================================

#include <iostream>
#include <set>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::set<std::string> s;
    s.insert("banana");
    s.insert("apple");
    s.insert("cherry");
    s.insert("banana");
    // TODO 1：依次插入 banana、apple、cherry、banana；
    //         打印 size()，再用 range-for 打印全部元素。
    std::cout << "size = " << s.size() << "\n";
    for (const std::string& x : s) {
        std::cout << x << "  ";
    }
    // TODO 2：再插入一次 apple，保存 insert 返回的 pair；
    //         打印 .second 和 size()，说明第二次为什么没有增加元素。因为已有apple键，因此不会添加了
    auto [it,inserted] = s.insert("apple");
    std::cout << ".second" << inserted << "  size = " << s.size()<<"\n";
    // TODO 3：用 find("banana") 打印是否找到；
    //         打印 count("banana") 和 count("zoo")。
    if (s.find("banana") != s.end()) {
        std::cout << "find banana" << "\n";
    }
    std::cout << s.count("banana") << "  " << s.count("zoo") << "\n";
    // TODO 4：erase("apple")，打印 size() 和剩余元素；
    //         用注释回答：为什么 set 没有 operator[]？因为其只有键，无需用[]对取出的数字进行解包或赋值，取出来的就是要元素。
    s.erase("apple");
    for (const std::string& x : s) {
        std::cout << x << "  ";
    }
    std::cout << "size =" << s.size() << "\n";
    return 0;
}
