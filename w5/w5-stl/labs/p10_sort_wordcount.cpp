// ============================================================================
// 探针 10 · sort 自定义比较器：词频降序，同频单词升序
// ============================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

struct WordCount {
    std::string word;
    int count;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<WordCount> data{
        {"banana", 2},
        {"apple", 2},
        {"cherry", 1},
        {"date", 3},
    };

    // TODO 1：用 std::sort + lambda 排序：
    //         count 从大到小；count 相同，word 从小到大。
    //         打印排序结果。
    std::sort(data.begin(), data.end(),
        [](const WordCount& a, const WordCount& b) {
            if (a.count != b.count) {
                return a.count > b.count;
            }
            return a.word < b.word;
        });
    for (const auto& [key, count]:data) {
        std::cout << key << "->" << count << "  ";
    }
    // TODO 2：把数据恢复成原顺序，再用 std::stable_sort，
    //         比较器只比较 count；打印结果，观察同频词的相对顺序。
    std::vector<WordCount> data_{
    {"banana", 2},
    {"apple", 2},
    {"cherry", 1},
    {"date", 3},
    };
    std::stable_sort(data_.begin(), data_.end(),
        [](const WordCount& a, const WordCount& b) {
        return a.count > b.count;
        });
    for (const auto& [key, count] : data_) {
        std::cout << key << "->" << count << "  ";
    }
    // TODO 3：用注释回答：
    //         为什么比较器不能写 a.count >= b.count？因为会被判定成两个数互相小于而报错
    //         什么叫“严格弱序”？就是只能小于，不能小于等于或者大于等于

    return 0;
}
