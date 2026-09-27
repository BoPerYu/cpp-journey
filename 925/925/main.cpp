#include<iostream>
#include<vector>
#include<Windows.h>
#include <type_traits>
// 把"成功了吗"和两个结果一起打包
struct MinMaxResult {
    bool ok;      // 成功了吗
    int  lo;      // 最小值
    int  hi;      // 最大值
};

MinMaxResult minMax(const std::vector<int>& data) {
    if (data.empty()) {
        return { false, 0, 0 };        // 失败：两个数随便给，因为 ok 是假
    }
    MinMaxResult r{ true, data[0], data[0] };
    for (std::size_t i = 1; i < data.size(); ++i) {
        if (data[i] < r.lo) { r.lo = data[i]; }
        if (data[i] > r.hi) { r.hi = data[i]; }
    }
    return r;
}

int main() {
    std::vector<int> data{ 80, 82, 67, 77, 94, 79 };
    std::vector<int> empty;

    MinMaxResult r = minMax(data);
    if (r.ok) {
        std::cout << "最小 = " << r.lo << "   最大 = " << r.hi << "\n";
    }
    else {
        std::cout << "列表是空的\n";
    }

    MinMaxResult e = minMax(empty);
    if (e.ok) {
        std::cout << "最小 = " << e.lo << "   最大 = " << e.hi << "\n";
    }
    else {
        std::cout << "列表是空的，没有最小值和最大值\n";
    }
    return 0;
}