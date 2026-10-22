// ============================================================================
// 探针 11 · lower_bound / upper_bound / equal_range
// ============================================================================

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> v{1, 2, 2, 4, 5};

    // TODO 1：打印 lower_bound(2) 和 upper_bound(2) 的下标。
    //         用 std::distance(v.begin(), it) 得到下标。
    auto lower = std::lower_bound(v.begin(), v.end(), 2);
    int a = std::distance(v.begin(), lower);
    auto upper = std::upper_bound(v.begin(), v.end(), 2);
    int b = std::distance(v.begin(), upper);
    std::cout << "下标v.lower_bound(2) = " << a << "下标v.upper_bound(2) = " << b << "\n";
    // TODO 2：打印 equal_range(2) 两个边界对应的下标。
    auto [first, second] = std::equal_range(v.begin(), v.end(), 2);
    int m = std::distance(v.begin(), first);
    int n = std::distance(v.begin(), second);
    std::cout << "first = " << m << "  second = " << n << "\n";
    // TODO 3：对 target = 3 和 target = 6 分别查 lower_bound，
    //         先判断是否等于 end()，再打印。
    auto x = std::lower_bound(v.begin(), v.end(), 3);
    if (x != v.end()) {
        int ans = std::distance(v.begin(), x);
        std::cout << ans << "\n";
    }
    else {
        std::cout << "None\n";
    }
    auto y = std::lower_bound(v.begin(), v.end(), 6);
    if (y != v.end()) {
        int ans = std::distance(v.begin(), y);
        std::cout << ans << "\n";
    }
    else {
        std::cout << "None\n";
    }
    // TODO 4：用注释回答：
    //         lower_bound 的前提是什么？不知道，这个取大于等于的函数要什么前提
    //         为什么 vector 的 lower_bound 平均比手写循环快？不知道，是因为不一定要历遍完的关系吗

    return 0;
}
