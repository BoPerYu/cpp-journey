// ============================================================================
// 探针 10 · p10_deque_basics：deque 的两端操作 + 迭代器跨容器复用
// ============================================================================
// 讲义：打卡训练\W4\W4D4_C++_deque.md
// 骨架是助手写好的，你写 3 个 TODO。跑法：.\run.ps1 p10_deque_basics
// ⚠️ 函数体还空着时会有几条 C4100「未引用的参数」，写完自动消失。
// ============================================================================

#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <windows.h>

// ---------------------------------------------------------------------------
// TODO 1：往 deque 的【两端】各插一个数
//   要求：头部插 10（用 push_front），尾部插 20（用 push_back）
//   传进来时 d 里已经有 {1, 2, 3}，做完应该是 {10, 1, 2, 3, 20}
// ---------------------------------------------------------------------------
void push_both_ends(std::deque<int>& d) {
    d.push_front(10);
    d.push_back(20);
    // TODO：函数体你写
}

// ---------------------------------------------------------------------------
// TODO 2：用【迭代器】把 deque 里的元素按顺序拷进一个 vector 返回
//   关键体验：昨天那段 for (auto it = d.begin(); it != d.end(); ++it) 这里【原样能用】——
//             只是把 v 换成了 d，其它一个字都不用改。
// ---------------------------------------------------------------------------
std::vector<int> to_vector(const std::deque<int>& d) {
    // TODO：函数体你写
    std::vector<int> answer;
    for (auto it = d.begin();it != d.end();it++) {
        answer.push_back(*it);
    }
    return answer;
}

// ---------------------------------------------------------------------------
// TODO 3：返回 front() + back()
//   （提示：这两个函数 deque 和 vector 都有，用法一样）
// ---------------------------------------------------------------------------
int first_plus_last(const std::deque<int>& d) {
    // TODO：函数体你写
    return d.front()+d.back();
}


// ================== 自检（这一段不要改） ==================
void show(const char* label, const std::deque<int>& d) {
    std::cout << "   " << label << " = {";
    for (std::size_t i = 0; i < d.size(); ++i) {
        std::cout << d[i] << (i + 1 < d.size() ? ", " : "");
    }
    std::cout << "}\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int pass = 0, total = 0;

    std::deque<int> d{1, 2, 3};
    std::cout << "起始：\n";
    show("d", d);
    push_both_ends(d);
    show("两端各插一个之后 d", d);
    ++total;
    const bool ok1 = (d == std::deque<int>{10, 1, 2, 3, 20});
    if (ok1) { ++pass; }
    std::cout << (ok1 ? "[OK  ] " : "[FAIL] ") << "1. 两端插入   期望 {10, 1, 2, 3, 20}\n";

    const std::deque<int> src{5, 6, 7};
    const std::vector<int> v = to_vector(src);
    ++total;
    const bool ok2 = (v == std::vector<int>{5, 6, 7});
    if (ok2) { ++pass; }
    std::cout << (ok2 ? "[OK  ] " : "[FAIL] ") << "2. 迭代器跨容器拷到 vector   ";
    std::cout << "得到 {";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    std::cout << "}，期望 {5, 6, 7}\n";

    const std::deque<int> d3{4, 5, 6};
    const int sum = first_plus_last(d3);
    ++total;
    const bool ok3 = (sum == 10);
    if (ok3) { ++pass; }
    std::cout << (ok3 ? "[OK  ] " : "[FAIL] ") << "3. front()+back()  得到 " << sum << "，期望 10\n";

    std::cout << "\n" << pass << "/" << total << " 通过"
              << (pass == total ? "  ← 全对\n" : "  ← 还没写完/写错了\n");
    std::cout << "顺手看两个事实：\n";
    std::cout << "   sizeof(std::deque<int>)   = " << sizeof(std::deque<int>) << "\n";
    std::cout << "   sizeof(std::vector<int>)  = " << sizeof(std::vector<int>) << "\n";
    return 0;
}
