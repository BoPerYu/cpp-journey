// ============================================================================
// 探针 8 · lower_bound / upper_bound / equal_range
// ============================================================================

#include <iostream>
#include <set>
#include <string>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::set<std::string> s{"ant", "bear", "cat", "dog", "elephant"};

    // TODO 1：打印 lower_bound("c") 和 upper_bound("c") 指向的词。
    //         注意先判断是否等于 end()，不要直接解引用 end()。
    if (s.lower_bound("c") != s.end()) {
        std::cout << "lower_bound(c) = " << *s.lower_bound("c") << "\n";
    }
    if (s.upper_bound("c") != s.end()) {
        std::cout << "upper_bound(c) = " << *s.upper_bound("c") << "\n";
    }
    // TODO 2：用 equal_range("cat") 打印两个边界；
    //         因为 set 的 key 唯一，这个区间最多包含一个元素。
    auto range = s.equal_range("cat");
    auto low = range.first;
    auto high = range.second;
    if (range.second != s.end()) {
        std::cout << "border = " << *low << " to " << *high << "\n";
    }
    // TODO 3：写一个手写循环找第一个 >= "bb" 的词；
    //         再用 lower_bound 做同一件事，比较两者复杂度。
    for (auto i = s.begin();i != s.end();i++) {
        if (*i >= "bb") {
            std::cout << *i << "\n";
            break;
        }
    }
    auto it = s.lower_bound("bb");
    if (it != s.end()) {
        std::cout << *s.lower_bound("bb") << "\n";
    }

    // TODO 4：用注释回答：
    //         lower_bound 和 upper_bound 的区别是什么？>= / >
    //         unordered_set 为什么没有这两个成员函数？因为set默认是按照key的大小升序排列，但是unorder是哈希表，无顺序

    return 0;
}
