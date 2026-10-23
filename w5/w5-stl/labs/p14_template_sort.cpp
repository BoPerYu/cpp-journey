// ============================================================================
// 探针 14 · 泛型排序：T + Compare
// ============================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

template <typename T, typename Compare>
void sort_values(std::vector<T>& values, Compare comp) {
    // TODO 1：调用 std::sort(values.begin(), values.end(), comp)。
    std::sort(values.begin(), values.end(), comp);
}

template <typename Container>
void print_all(const Container& values) {
    for (const auto& value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> numbers{3, 1, 4, 2};
    sort_values(numbers, [](int a, int b) { return a > b; });
    print_all(numbers);

    std::vector<std::string> words{"pear", "apple", "fig"};
    sort_values(words, [](const std::string& a, const std::string& b) {
        return a.size() < b.size();
    });
    print_all(words);

    // TODO 2：用注释回答：
    //         为什么 Compare 也要做成模板参数？所以template就是类似于模板参数的概念对吗，因为这里一般如果用lambda的话，由于只有匿名类型，无法显示写出，没办法写在形参里边（不过Compare作为类型名，是不是也可以接我后边自己写的函数？T也可以，因为这两个没有本质区别）
    //         lambda 的类型可以直接写出来吗？不可以

    return 0;
}
