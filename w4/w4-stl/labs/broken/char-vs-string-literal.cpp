// ============================================================================
// 反例 · 故意编译不过：单引号 char 和双引号字符串不是一回事
// ============================================================================
// 不参与构建（GLOB 只扫 labs\*.cpp，不扫 labs\broken\）。
// 在 D:\Code\cpp-journey\w4\w4-stl 目录下跑这一行自己编：
//
//   cmd /c 'call "E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat" >nul && cl /nologo /std:c++17 /EHsc /W4 /permissive- /utf-8 /c labs\broken\char-vs-string-literal.cpp'
//
// 期望：第 18 行报错（把一个字符串字面量传给 char 参数）
// ============================================================================

#include <string>

std::size_t find_one(const std::string& s, char delim) {   // 参数是 char
    return s.find(delim);
}

void f() {
    std::string s = "a,b";
    (void)find_one(s, ',');        // 对：单引号 = 一个字符
    (void)find_one(s, ",");        // 错：双引号 = 字符串字面量
}
