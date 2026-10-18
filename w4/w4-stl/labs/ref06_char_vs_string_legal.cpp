// ============================================================================
// ref06 · 单引号 vs 双引号：哪些写法是【合法】的（助手写的参考程序）
// ============================================================================
// 起因：助手在 Q3 里举了"把字符串字面量传给 char 参数会报错"，但表述容易让人以为
//       "双引号不能用"。这个程序把【合法】的那几种全跑一遍。
//       违规的那种在 labs\broken\char-vs-string-literal.cpp（故意编译不过）。
// 跑法：.\build\Debug\ref06_char_vs_string_legal.exe
// ============================================================================

#include <iostream>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const std::string s = "a,b";

    std::cout << "===== 1. std::string::find 有两个重载，两种引号都收 =====\n";
    std::cout << "s.find(\",\") = " << s.find(",") << "   ← 双引号 = 字符串字面量\n";
    std::cout << "s.find(',') = " << s.find(',') << "   ← 单引号 = 一个字符，也合法\n";

    std::cout << "\n===== 2. std::string 能被【赋值】一个 char（有 operator=）=====\n";
    std::string t;
    t = ',';
    std::cout << "t = ',' 之后 t = [" << t << "]，t.size() = " << t.size() << "（只装了一个逗号）\n";

    std::cout << "\n===== 3. 但把字符串字面量传给 char 参数 → 编译不过 =====\n";
    std::cout << "  证据：labs\\broken\\char-vs-string-literal.cpp，报 C2664\n";
    std::cout << "  原因：\",\" 的类型是 const char[2]（逗号 + 结尾的 0），不是一个 char\n";
    return 0;
}
