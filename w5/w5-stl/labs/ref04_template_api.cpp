// ============================================================================
// ref04 · 函数模板 + 泛型排序参考程序
// ============================================================================

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>

template <typename T>
T max_value(const std::vector<T>& values) {
    if (values.empty()) {
        throw std::invalid_argument("max_value: empty vector");
    }
    return *std::max_element(values.begin(), values.end());
}

template <typename T, typename Compare>
void sort_values(std::vector<T>& values, Compare comp) {
    std::sort(values.begin(), values.end(), comp);
}

template <typename Container>
void print_all(const Container& values, std::ostream& out) {
    for (const auto& value : values) {
        out << value << " ";
    }
    out << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> numbers{3, 1, 4, 2};
    std::cout << "max int = " << max_value(numbers) << "\n";

    sort_values(numbers, [](int a, int b) { return a > b; });
    std::cout << "int desc: ";
    print_all(numbers, std::cout);

    std::vector<std::string> words{"pear", "apple", "fig"};
    std::cout << "max string = " << max_value(words) << "\n";

    sort_values(words, [](const std::string& a, const std::string& b) {
        return a.size() < b.size();
    });
    std::cout << "string by length: ";
    print_all(words, std::cout);

    return 0;
}
