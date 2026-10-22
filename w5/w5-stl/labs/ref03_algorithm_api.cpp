// ============================================================================
// ref03 · <algorithm> / <numeric> 基础 API 参考程序
// ============================================================================

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <windows.h>

struct WordCount {
    std::string word;
    int count;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== 1. sort：默认升序 ==========\n";
    std::vector<int> v{5, 1, 4, 2, 3};
    std::sort(v.begin(), v.end());
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "\n========== 2. sort：自定义比较器 ==========\n";
    std::sort(v.begin(), v.end(), std::greater<int>{});
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "\n========== 3. 排序 WordCount ==========\n";
    std::vector<WordCount> words{
        {"banana", 2},
        {"apple", 2},
        {"cherry", 1},
        {"date", 3},
    };
    std::sort(words.begin(), words.end(),
        [](const WordCount& a, const WordCount& b) {
            if (a.count != b.count) {
                return a.count > b.count;
            }
            return a.word < b.word;
        });
    for (const auto& item : words) {
        std::cout << item.word << " " << item.count << "\n";
    }

    std::cout << "\n========== 4. lower_bound / upper_bound ==========\n";
    std::vector<int> sorted{1, 2, 2, 4, 5};
    auto lo = std::lower_bound(sorted.begin(), sorted.end(), 2);
    auto hi = std::upper_bound(sorted.begin(), sorted.end(), 2);
    std::cout << "lower_bound(2) index="
              << std::distance(sorted.begin(), lo) << "\n";
    std::cout << "upper_bound(2) index="
              << std::distance(sorted.begin(), hi) << "\n";

    std::cout << "\n========== 5. accumulate ==========\n";
    std::vector<long long> nums{1000000000LL, 1000000000LL, 1000000000LL};
    long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
    std::cout << "sum=" << total << "\n";

    std::cout << "\n========== 6. count_if ==========\n";
    std::vector<int> values{1, 2, 3, 4, 5, 6};
    auto even_count = std::count_if(values.begin(), values.end(),
        [](int x) { return x % 2 == 0; });
    std::cout << "even count=" << even_count << "\n";

    return 0;
}
