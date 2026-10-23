// ============================================================================
// 探针 13 · 函数模板：写一个 max_value
// ============================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdexcept>

template <typename T>
T max_value(const std::vector<T>& values) {
    // TODO 1：空容器怎么处理？可以抛 std::invalid_argument。
    if (values.empty()) {
        throw std::invalid_argument("vector 为空");
    }
    // TODO 2：用 std::max_element 或手写循环返回最大值。
    auto it = std::max_element(values.begin(), values.end());//这个是我蒙的，还请讲讲这个的基本语法,而且我不知道他的返回值是什么，但是我猜测是迭代器吧
    return *it;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> numbers{3, 1, 4, 2};
    std::vector<std::string> words{"pear", "apple", "fig"};

    std::cout << "max int = " << max_value(numbers) << "\n";
    std::cout << "max string = " << max_value(words) << "\n";

    // TODO 3：用注释回答：
    //         为什么同一个 max_value 能同时接收 vector<int> 和 vector<string>？因为T作为一个类似于占位符，其元素类型是什么是由在运行函数时传传入的数据类型决定的，因此其可以作为一个模板对不同的类型调用
    // 
    //         它是在运行时决定 T，还是编译时实例化？template是编译期实例化；auto是编译时

    return 0;
}
