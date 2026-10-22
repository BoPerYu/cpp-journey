// ============================================================================
// 探针 12 · accumulate 和 count_if
// ============================================================================

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> values{1, 2, 3, 4, 5, 6};

    // TODO 1：用 std::accumulate 求和，初始值分别试 0 和 0LL；
    //         打印两个结果，解释为什么大数求和要用 0LL。
    int a = std::accumulate(values.begin(), values.end(), 0);
    long long b = std::accumulate(values.begin(), values.end(), 0LL);
    std::cout << "a = " << a << "b = " << b << "\n";
    // TODO 2：用 std::count_if + lambda 统计偶数个数。
    auto ans = std::count_if(values.begin(), values.end(),
        [](int x) {return x % 2 == 0;});
    // TODO 3：用 std::count_if + lambda 统计大于 3 的个数。
    auto ans_ = std::count_if(values.begin(), values.end(),
        [](int x) {return x > 3;});
    std::cout << "even=" << ans << " greater_than_3=" << ans_ << "\n";
    // TODO 4：用注释回答：
    //         accumulate 在哪个头文件？ numeric。
    //         初始值类型为什么会改变结果？因为不同的计数法，会存在隐式转化，可能导致数值出问题。

    return 0;
}
