// ============================================================================
// ref02 · `std::string` 和 `std::vector<char>` 到底差在哪（助手写的参考程序）
// ============================================================================
// 这个文件回答一个问题：既然 std::vector 能跟类型参数，那能不能用它顶替 std::string？
// 每一段输出都可以自己跑一遍核对：
//     cd D:\Code\cpp-journey\w4\w4-stl
//     cmake --build build --config Debug --parallel
//     .\build\Debug\ref02_string_vs_vector.exe
//
// 配套反例（故意编译不过，不参与构建）：labs\broken\vector-char-is-not-a-string.cpp
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <type_traits>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== 1. std::string 本身就是一个【模板实例】==========\n";
    std::cout << "is_same<std::string,  std::basic_string<char>>    = "
              << std::is_same<std::string, std::basic_string<char>>::value << "\n";
    std::cout << "is_same<std::wstring, std::basic_string<wchar_t>> = "
              << std::is_same<std::wstring, std::basic_string<wchar_t>>::value << "\n";
    std::cout << "1 代表【是同一个类型】。所以 string 不是\"没有类型参数\"，\n";
    std::cout << "它是 basic_string 这个模板被固定成 char 之后起的别名。\n";

    std::cout << "\n========== 2. 容器对象本身的大小，和里面装什么无关 ==========\n";
    // ⚠️ 下面这几个数会随【构建配置】变！Debug 和 Release 不一样，
    //    因为 MSVC 的调试版会在容器里多塞一个"代理指针"（由 _ITERATOR_DEBUG_LEVEL 控制）。
    //    想看两组数：cmake --build build --config Debug   → 再 --config Release
    std::cout << "_ITERATOR_DEBUG_LEVEL = " << _ITERATOR_DEBUG_LEVEL << "\n";
    std::cout << "sizeof(std::string)              = " << sizeof(std::string) << "\n";
    std::cout << "sizeof(std::vector<int>)         = " << sizeof(std::vector<int>) << "\n";
    std::cout << "sizeof(std::vector<char>)        = " << sizeof(std::vector<char>) << "\n";
    std::cout << "sizeof(std::vector<double>)      = " << sizeof(std::vector<double>) << "\n";
    std::cout << "sizeof(std::vector<std::string>) = " << sizeof(std::vector<std::string>) << "\n";

    std::cout << "\n========== 3. 装同一段文字：string 和 vector<char> 都能装 ==========\n";
    std::string s = "hello";
    std::vector<char> vc{'h', 'e', 'l', 'l', 'o'};
    std::cout << "s.size()=" << s.size() << "   vc.size()=" << vc.size() << "\n";
    std::cout << "s[0]=" << s[0] << "   vc[0]=" << vc[0] << "\n";
    s.push_back('!');
    vc.push_back('!');
    std::cout << "两边都能 push_back： s = " << s << "   vc = [";
    for (char c : vc) { std::cout << c; }
    std::cout << "]\n";

    std::cout << "\n========== 4. string 独有、vector<char> 完全【没有】的东西 ==========\n";
    std::cout << "s.substr(1, 3)   = " << s.substr(1, 3) << "\n";
    std::cout << "s.find(\"ll\")     = " << s.find("ll") << "\n";
    std::cout << "s + \" world\"     = " << (s + " world") << "\n";
    std::cout << "s == \"hello!\"    = " << (s == "hello!") << "\n";
    std::cout << "s < \"world\"      = " << (s < "world") << "\n";
    std::cout << "这几行在 std::vector<char> 上全都写不出来（编译器直接报错，见 broken 反例）\n";

    std::cout << "\n========== 5. C++11 起 string 保证结尾藏着一个 0 ==========\n";
    std::cout << "(int)s.data()[s.size()] = " << static_cast<int>(s.data()[s.size()]) << "\n";
    std::cout << "(int)s[s.size()]        = " << static_cast<int>(s[s.size()]) << "\n";
    std::cout << "std::strlen(s.c_str())  = " << std::strlen(s.c_str()) << "\n";
    std::cout << "那个 0 就是 c_str() 能直接喂给 C 函数的原因；\n";
    std::cout << "vector<char> 没有这个保证，vc.data()[vc.size()] 是越界读。\n";

    std::cout << "\n========== 6. vector<string> 是【装字符串的数组】，不是【字符串】==========\n";
    std::vector<std::string> words{"文本", "检索"};
    std::cout << "words.size() = " << words.size() << "（两个元素，不是一个字符串）\n";
    for (const std::string& w : words) {
        std::cout << "  [" << w << "]  w.size()=" << w.size() << " 字节\n";
    }

    return 0;
}
