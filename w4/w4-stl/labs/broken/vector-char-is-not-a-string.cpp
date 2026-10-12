// ============================================================================
// 反例 · 故意编译不过：std::vector<char> 不是 std::string
// ============================================================================
// 不参与构建（CMakeLists 的 GLOB 只扫 labs\*.cpp，不扫 labs\broken\）。
// 要自己编，在 D:\Code\cpp-journey\w4\w4-stl 目录下跑这一行：
//
//   cmd /c 'call "E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat" >nul && cl /nologo /std:c++17 /EHsc /W4 /permissive- /utf-8 /c labs\broken\vector-char-is-not-a-string.cpp'
//
// 期望：下面 4 行各报一个错。把真实错误号抄进你的笔记。
// ============================================================================

#include <string>
#include <vector>

void f() {
    std::vector<char> vc{'a', 'b', 'c'};
    std::string s = "abc";
    (void)s;

    vc.find('a');            // 1) vector<char> 没有 find
    vc.substr(1);            // 2) vector<char> 没有 substr
    if (vc == "abc") { }     // 3) vector<char> 不能直接和字符串字面量比
    std::string t = vc;      // 4) 不能把 vector<char> 当字符串初始化
}
