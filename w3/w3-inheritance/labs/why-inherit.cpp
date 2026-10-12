// 探针 1：不用继承，代码长什么样
// 目的：先看见"重复"，再谈继承到底省掉了什么。
//
// 这里只有两种形状。真实项目里可能有二十种，每加一种就要再抄一遍同样的流程。

#include <iostream>
#include <string>
#include <windows.h>

struct CircleBad {
    double r;
};

struct RectBad {
    double w;
    double h;
};

// 每种形状配一套自己的"自我介绍"函数
void describeBad(const CircleBad& c) {
    std::cout << "圆   r=" << c.r << "  面积=" << 3.14159265 * c.r * c.r << "\n";
}

void describeBad(const RectBad& r) {
    std::cout << "矩形 " << r.w << "x" << r.h << "  面积=" << r.w * r.h << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== 探针 1：不用继承 ===\n";

    CircleBad c{ 2.0 };
    RectBad   r{ 3.0, 4.0 };

    describeBad(c);
    describeBad(r);

    std::cout << "\n想写\"把所有形状放进一个循环里统一处理\"——做不到：\n";
    std::cout << "  c 和 r 的类型之间没有任何关系，没有共同的\"形状\"类型可以写。\n";
    std::cout << "  每加一种形状，就要：① 新增一个结构体 ② 新增一个 describeBad 重载\n";
    std::cout << "                      ③ 翻遍所有处理形状的地方，把这个新函数补上\n";

    return 0;
}
