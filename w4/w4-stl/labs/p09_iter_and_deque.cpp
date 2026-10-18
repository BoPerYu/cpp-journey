// ============================================================================
// 探针 9 · p09_iter_and_deque：deque 两头操作 + 迭代器收尾
// ============================================================================
// 讲义：打卡训练\W4\W4D4_C++_deque与容器对比.md
// 你写 4 个 TODO；自检器已经写好。
// 跑法：.\run.ps1 p09_iter_and_deque
// ⚠️ 函数体空着时会有 C4100「未引用的参数」——写完之后消失（老规矩）。
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstddef>
#include <windows.h>

// ---------------------------------------------------------------------------
// TODO 1：用 deque 做双端操作，返回"最终内容拼成的字符串"（用空格分隔）
//
// 要求（按这个顺序做）：
//     push_back(3); push_front(1); push_back(5); pop_front(); push_front(9);
// 做完 deque 里应该是 {9, 3, 5}  → 返回 "9 3 5"
//
// 提示：std::to_string(数字) 把它变成字符串；拼接用 +=。
// ---------------------------------------------------------------------------
std::string deque_two_ends() {
    // TODO：函数体你写
    return "";
}


// ---------------------------------------------------------------------------
// TODO 2：用【迭代器循环】遍历一个 deque，返回 "元素 元素 ..."（同样用空格分隔）
//
// 骨架形状（和遍历 vector 一模一样）：
//     for (auto it = d.begin(); it != d.end(); ++it) { ... *it ... }
// 注意空格的处理：和 p08 一样，别在最后一个元素后面多留一个空格。
// ---------------------------------------------------------------------------
std::string walk_deque(const std::deque<int>& d) {
    // TODO：函数体你写
    return "";
}


// ---------------------------------------------------------------------------
// TODO 3：用 std::sort 把 vector 从小到大排好（原地改）
//
// 提示：一行。std::sort 收的是"一对迭代器"，表示一个半开区间。
//       需要 #include <algorithm>（已经 include 了）。
// ---------------------------------------------------------------------------
void sort_it(std::vector<int>& v) {
    // TODO：一行
}


// ---------------------------------------------------------------------------
// TODO 4：观察题 —— 返回"扩容前 &*v.begin() 的地址"和"扩容后 &*v.begin() 的地址"
//          是不是同一个
//
// 做法：
//     1) std::vector<int> v;  （空的，容量 0）
//     2) v.push_back(1);      拿到 it = v.begin()，记下 const void* before = &*it;
//     3) 一直 push_back 到【撑破容量】（多推几个，比如再推 100 个）
//     4) 重新拿 auto it2 = v.begin(); 记下 const void* after = &*it2;
//     5) return (before == after);
//
// ⚠️ 注意：第 3 步之后【不要】再用第 2 步那个 it —— 那正是讲义 2.2 说的"悬空"。
//    这个 TODO 只比较地址，不解引用旧迭代器，所以是安全的。
// ---------------------------------------------------------------------------
bool buffer_moved_after_growth() {
    // TODO：函数体你写
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

    const std::string got1 = deque_two_ends();
    check("1. deque 两头操作", got1 == "9 3 5", "得到 \"" + got1 + "\"，期望 \"9 3 5\"");

    const std::deque<int> d{9, 3, 5};
    const std::string got2 = walk_deque(d);
    check("2. 迭代器遍历 deque", got2 == "9 3 5", "得到 \"" + got2 + "\"，期望 \"9 3 5\"");

    std::vector<int> v{3, 1, 4, 1, 5};
    sort_it(v);
    const bool ok3 = (v == std::vector<int>{1, 1, 3, 4, 5});
    std::cout << (ok3 ? "[OK  ] " : "[FAIL] ") << "3. std::sort   得到 {";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    std::cout << "}，期望 {1, 1, 3, 4, 5}\n";
    if (ok3) { ++g_pass; }
    ++g_total;

    const bool moved = buffer_moved_after_growth();
    check("4. 扩容之后缓冲区搬走了吗", moved,
          moved ? "（地址变了 → 旧迭代器确实悬空）"
                : "（返回 false —— 还没写，或者结论反了）");

    std::cout << "\n" << g_pass << "/" << g_total << " 通过"
              << (g_pass == g_total ? "  ← 全对\n" : "  ← 还没写完/写错了\n");
    return 0;
}
