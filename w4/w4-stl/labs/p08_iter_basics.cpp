// ============================================================================
// 探针 8 · p08_iter_basics：迭代器的四个基本用法
// ============================================================================
// 讲义：打卡训练\W4\W4D3_C++_迭代器.md
// 骨架是助手写好的（自检器、打印都写好了），你写 4 个 TODO。
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p08_iter_basics.exe
//
// ⚠️ 函数体还空着时会有几条 C4100「未引用的参数」—— 那是 /W4 提醒你参数没用上，
//    写完之后自动消失（和 p06/p07 一样）。
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <windows.h>

// ---------------------------------------------------------------------------
// TODO 1：用【迭代器】把 v 走一遍，拼成 "1,2,3" 这样的字符串返回
//
// 骨架形状（讲义 2.2 的写法 2）：
//     std::string out;
//     for (auto it = v.begin(); it != v.end(); ++it) {
//         out += std::to_string(*it);        // std::to_string 把数字变字符串
//         if (<不是最后一个>) { out += ","; }  // ← 这一句你自己想怎么写
//     }
//     return out;
//
// 提示：怎么判断"不是最后一个"？想想 it 和 v.end() 差几个位置。
// ---------------------------------------------------------------------------
std::string walk_with_iterator(const std::vector<int>& v) {
    // TODO：函数体你写
    std::string out;
    for (auto it = v.begin();it != v.end();it++) {
        out += std::to_string(*it);
        if (it != v.end()-1) {
            out += ',' ;
        }
    }
    return out;
}


// ---------------------------------------------------------------------------
// TODO 2（改版）：用【迭代器】找 target 第一次出现的下标；找不到就返回 v.size()
//
// 为什么改版：原来那题问的是"第三个元素的下标"，答案永远是 2 ——
//   你写 return 2; 也能过，那样的题测不出你会不会用迭代器。所以换成"找某个值"。
//
// 骨架形状：
//     for (auto it = v.begin(); it != v.end(); ++it) {
//         if (<这个位置的值 等于 target>) {
//             return <这个位置的下标>;        // 提示：it - v.begin() 就是下标
//         }
//     }
//     return <没找到时返回什么>;              // ⚠️ 这个 return 千万别漏
//
// ⚠️ 函数末尾那个 return 不能少：少了它，循环走完都没找到时，函数会"掉出末尾"，
//    返回值是未定义的垃圾值 —— 而且【编译器不一定会拦你】。
// ---------------------------------------------------------------------------
std::size_t index_of(const std::vector<int>& v, int target) {
    for (auto it = v.begin();it != v.end();it++) {
        if (*it == target) {
            return it - v.begin();
        }
    }
    return v.size();
}


// ---------------------------------------------------------------------------
// TODO 3：用【迭代器】把每个元素翻倍（原地改 v）
//
// 提示：*it 既可以读也可以写，和指针一样。
// ---------------------------------------------------------------------------
void double_via_iterator(std::vector<int>& v) {
    // TODO：函数体你写
    for (auto it = v.begin();it != v.end();it++) {
        *it *= 2;
    }
}


// ---------------------------------------------------------------------------
// TODO 4：观察题 —— 返回 "迭代器现在指的那块内存地址" 和 "容器缓冲区首地址"
//          是不是同一个
//
// 提示：&*v.begin() 就是"迭代器指着的那格内存的地址"；
//       v.data() 是"缓冲区首地址"。把两个都转成 const void* 再比。
//       实现里写一行 return 比较结果（不要只打印，自检器要拿这个值）。
// ---------------------------------------------------------------------------
bool iterator_points_into_buffer(const std::vector<int>& v) {
    // TODO：函数体你写
    if (&*v.begin() == v.data()) {
        return true;
    }
    return false;
}


// ================== 自检（这一段不要改） ==================
int g_pass = 0;
int g_total = 0;

void check(const std::string& name, bool ok, const std::string& detail) {
    ++g_total;
    if (ok) { ++g_pass; }
    std::cout << (ok ? "[OK  ] " : "[FAIL] ") << name << "   " << detail << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const std::vector<int> base{1, 2, 3};

    // 1
    std::string got = walk_with_iterator(base);
    check("1. 迭代器遍历拼串", got == "1,2,3", "得到 \"" + got + "\"，期望 \"1,2,3\"");

    // 2（四个用例：光问"第三个元素的下标"的话，硬编码 2 也能过，所以换成"找某个值"）
    const std::size_t i1 = index_of(base, 3);
    check("2a. index_of({1,2,3}, 3)", i1 == 2, "得到 " + std::to_string(i1) + "，期望 2");
    const std::size_t i2 = index_of(base, 99);
    check("2b. index_of({1,2,3}, 99) 找不到", i2 == 3,
          "得到 " + std::to_string(i2) + "，期望 3（= v.size()）");
    const std::vector<int> four{5, 5, 7, 9};
    const std::size_t i3 = index_of(four, 7);
    check("2c. index_of({5,5,7,9}, 7)", i3 == 2, "得到 " + std::to_string(i3) + "，期望 2");
    const std::size_t i4 = index_of(four, 9);
    check("2d. index_of({5,5,7,9}, 9)", i4 == 3, "得到 " + std::to_string(i4) + "，期望 3");

    // 3
    std::vector<int> doubled{1, 2, 3};
    double_via_iterator(doubled);
    const bool ok3 = (doubled == std::vector<int>{2, 4, 6});
    std::cout << (ok3 ? "[OK  ] " : "[FAIL] ") << "3. 迭代器改元素   得到 {";
    for (std::size_t i = 0; i < doubled.size(); ++i) {
        std::cout << doubled[i] << (i + 1 < doubled.size() ? ", " : "");
    }
    std::cout << "}，期望 {2, 4, 6}\n";
    if (ok3) { ++g_pass; }
    ++g_total;

    // 4
    const bool ok4 = iterator_points_into_buffer(base);
    check("4. 迭代器指向缓冲区内部", ok4,
          ok4 ? "（&*v.begin() 和 v.data() 是同一个地址）"
              : "（返回 false —— 你还没写，或者算错了）");

    std::cout << "\n" << g_pass << "/" << g_total << " 通过"
              << (g_pass == g_total ? "  ← 全对\n" : "  ← 还没写完/写错了\n");
    return 0;
}
