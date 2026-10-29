#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace drill {

// 1. 空 vector 时抛出 std::out_of_range；否则返回最后一个元素。
int checked_back(const std::vector<int>& values) {
    (void)values;
    if (values.empty()) {
        throw std::out_of_range("empty vector");
    }
    else {
        return values.back();
    }
}

// 2. 使用捕获 min_length 的 lambda，选出长度 >= min_length 的字符串。
std::vector<std::string> select_long_words(
    const std::vector<std::string>& words,
    std::size_t min_length) {
    (void)words;
    (void)min_length;
    std::vector<std::string> ans;
    std::copy_if(words.begin(),words.end(), std::back_inserter(ans),
        [min_length](const std::string& word) {return word.length() >= min_length;});
    return ans;
}

// 3. 使用 auto& 遍历，并让每个元素增加 1。
void increment_all(std::vector<int>& values) {
    (void)values;
    for (auto& i : values) {
        ++i;
    }
}

// 4. 使用捕获 threshold 的 lambda，统计 >= threshold 的元素个数。
std::size_t count_at_least(const std::vector<int>& values, int threshold) {
    (void)values;
    (void)threshold;
    return std::count_if(values.begin(), values.end(), [threshold](int x) {return x >= threshold;});
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
        check(drill::checked_back({3, 7, 2}) == 2, "checked_back returns the last value");

        bool threw_expected = false;
        try {
            (void)drill::checked_back({});
        } catch (const std::out_of_range&) {
            threw_expected = true;
        } catch (...) {
            threw_expected = false;
        }
        check(threw_expected, "checked_back throws std::out_of_range on empty input");
    }

    {
        const std::vector<std::string> words{
            "a", "pear", "fig", "banana", "cat"};
        check(
            drill::select_long_words(words, 4) ==
                std::vector<std::string>{"pear", "banana"},
            "select_long_words captures the minimum length");
        check(
            drill::select_long_words(words, 10).empty(),
            "select_long_words accepts no matching words");
    }

    {
        std::vector<int> values{1, -2, 0};
        drill::increment_all(values);
        check(values == std::vector<int>{2, -1, 1}, "increment_all mutates in place");
    }

    {
        const std::vector<int> values{1, 2, 4, 7, 8};
        check(drill::count_at_least(values, 4) == 3, "count_at_least captures threshold");
        check(drill::count_at_least({}, 4) == 0, "count_at_least accepts empty input");
    }
}

}  // namespace

int main() {
    try {
        run_tests();
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] unexpected exception: " << error.what() << '\n';
        return 1;
    }

    std::cout << '\n' << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
