#include "word_count.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace drill {

// 1. 读取空白分隔的 token，用 map 的 operator[] 完成逐词计数。
word_count::Frequencies count_words(std::istream& input) {
    (void)input;
    std::unordered_map<std::string, std::size_t> a;
    std::string word;
    while (input>>word) {
        ++a[word];
    }
    return a;
}

// 2. 把 map 复制到 vector，再按“频次降序、同频单词升序”排序。
word_count::Ranking rank_words(const word_count::Frequencies& frequencies) {
    (void)frequencies;
    word_count::Ranking b;
    for (auto [key, count] : frequencies) {
        b.push_back({key,count});
    }
    std::sort(b.begin(), b.end(),
        [](auto x, auto y) {
            if (x.count == y.count) {
                return x.word < y.word;
            }
            return x.count > y.count;});
    return b;
}

// 3. 使用 std::set 去重并保持字典序。
std::set<std::string> unique_words(const std::vector<std::string>& words) {
    (void)words;
    std::set<std::string> a;
    for (std::string x : words) {
        a.insert(x);
    }
    return a;
}

// 4. 使用 std::count_if 统计偶数个数。
std::size_t count_even(const std::vector<int>& values) {
    (void)values;
    std::size_t nums;
    nums=std::count_if(values.begin(), values.end(), [](int x) {return x % 2 == 0;});
    return nums;
}

// 5. 使用 std::accumulate，并让累加器从一开始就是 long long。
long long sum_values(const std::vector<int>& values) {
    (void)values;
    long long a = 0;
    a = std::accumulate(values.begin(), values.end(), 0LL);
    return a;
}

// 6. 使用 std::set 的成员函数 equal_range，返回 [lower, upper) 的字符串对。
std::pair<std::string, std::string> equal_range_text(
    const std::set<std::string>& words,
    const std::string& target) {
    (void)words;
    (void)target;
    auto [left, right] = words.equal_range(target);
    if (left == words.end()) {
        return {};
    }
    if (right == words.end()) {
        return std::pair < std::string, std::string>(*left, " ");
    }
    return std::pair<std::string,std::string>(*left,*right);
}

}  // namespace drill

namespace {

int passed = 0;
int failed = 0;

void check(bool condition, const char* name) {
    if (condition) {
        ++passed;
        std::cout << "[PASS] " << name << '\n';
    } else {
        ++failed;
        std::cout << "[FAIL] " << name << '\n';
    }
}

void run_tests() {
    {
        std::istringstream input("b a b a c");
        const auto frequencies = drill::count_words(input);
        check(
            frequencies.size() == 3 && frequencies.at("a") == 2 &&
                frequencies.at("b") == 2 && frequencies.at("c") == 1,
            "count_words counts each token independently");

        const auto ranking = drill::rank_words(frequencies);
        check(
            ranking.size() == 3 &&
                ranking[0] == word_count::Entry{"a", 2} &&
                ranking[1] == word_count::Entry{"b", 2} &&
                ranking[2] == word_count::Entry{"c", 1},
            "rank_words uses frequency descending and word ascending");
    }

    {
        const std::vector<std::string> words{
            "pear", "apple", "pear", "banana"};
        const auto unique = drill::unique_words(words);
        check(
            unique == std::set<std::string>{"apple", "banana", "pear"},
            "unique_words deduplicates in lexical order");
    }

    {
        const std::vector<int> values{1, 2, 4, 7, 8};
        check(drill::count_even(values) == 3, "count_even counts 2, 4, 8");
        check(drill::sum_values(values) == 22, "sum_values accumulates all values");
    }

    {
        const std::set<std::string> words{"apple", "banana", "cherry"};
        check(
            drill::equal_range_text(words, "banana") ==
                std::pair<std::string, std::string>{"banana", "cherry"},
            "equal_range returns lower and upper boundaries");
    }
}

}  // namespace

int main() {
    run_tests();
    std::cout << '\n' << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
