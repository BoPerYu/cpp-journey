// ============================================================================
// 探针 7 · p07_pass_by：不加 & 就白改了
// ============================================================================
// 讲义：打卡训练\W4\W4D2_C++_string切词与vector传参返回.md（第二节）
//
// 三个函数的【循环体】你写；"打印地址"那两行是观察脚手架，已经给你了。
// 要观察的就是：**函数里那份 v 的缓冲区地址，和 main 里 v 的是不是同一个**。
//   地址不同 = 函数收到的是【拷贝】，你改了也动不到外面
//   地址相同 = 那就是【原件】，一改就动到了
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p07_pass_by.exe
//
// ⚠️ 函数体还空着时，编译会报 C4100「未引用的参数」—— 那是 /W4 在提醒
//    "参数还没用上"，写完之后会自己消失。
// ============================================================================

#include <iostream>
#include <vector>
#include <windows.h>

// 观察用的打印函数（助手写的，不要改）
void show(const char* label, const std::vector<int>& v) {
    std::cout << "  " << label << "：内容 = {";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    std::cout << "}   缓冲区地址 = " << static_cast<const void*>(v.data()) << "\n";
}

// ---------------------------------------------------------------------------
// TODO 1：按【值】传 —— 把每个元素 +1
//   函数体里第一行（打印地址）已经给你了，下面的 for 循环你写。
void addOne_byvalue(std::vector<int> v) {
    show("[函数内 byvalue] v", v);
    // TODO：一个 for 循环，把每个元素 += 1
    for (std::size_t i = 0; i < v.size(); i++) {
        v[i] += 1;
    }
}

// ---------------------------------------------------------------------------
// TODO 2：按【引用】传 —— 同样把每个元素 +1
//   这次签名里多了个 &，看看地址会不会变成一样的。
void addOne_byref(std::vector<int>& v) {
    show("[函数内 byref  ] v", v);
    // TODO：一个 for 循环，把每个元素 += 1
    for (std::size_t i = 0; i < v.size(); i++) {
        v[i] += 1;
    }
}

// ---------------------------------------------------------------------------
// TODO 3：const 引用 —— 只读求和
int sum_cref(const std::vector<int>& v) {
    show("[函数内 sum_cref] v", v);
    // TODO：把元素累加起来，然后 return 那个和
    int total = 0;
    for (std::size_t i = 0;i < v.size();i++) {
        total += v[i];
    }
    return total;
}


// ================== 观察代码（这一段不要改） ==================
int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> v{1, 2, 3};
    std::cout << "起始：\n";
    show("main 里的 v", v);

    std::cout << "\n=== 1. 调【按值】版 addOne_byvalue(v) ===\n";
    addOne_byvalue(v);
    std::cout << "  调用结束，回到 main：\n";
    show("main 里的 v", v);
    std::cout << "  ↑ 两处地址一样吗？main 里的内容变了吗？\n";

    std::cout << "\n=== 2. 调【引用】版 addOne_byref(v) ===\n";
    addOne_byref(v);
    std::cout << "  调用结束，回到 main：\n";
    show("main 里的 v", v);
    std::cout << "  ↑ 这一次：地址一样吗？内容变成 {2, 3, 4} 了吗？\n";

    std::cout << "\n=== 3. const 引用 sum_cref(v) ===\n";
    const int total = sum_cref(v);        // 先算完，再打印（不然函数里的打印会插在中间）
    std::cout << "  和 = " << total << "   （期望 2+3+4 = 9）\n";

    std::cout << "\n=== 4. 亲手试一次（做完记得改回去）===\n";
    std::cout << "  在 sum_cref 里加一行：  v[0] = 0;\n";
    std::cout << "  再编译 —— 会报错。把真实报错原文抄进证据表。\n";
    std::cout << "  那一行错就是在告诉你：const 引用是\"只读契约\"，编译期就拦。\n";
    return 0;
}
