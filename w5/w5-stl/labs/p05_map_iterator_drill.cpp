// ============================================================================
// 加练 · map 迭代器专项
// ----------------------------------------------------------------------------
// 目标：把 it->first / it->second、find、distance、lower_bound、
//       遍历中 erase 这几件事练到不用想。
// 只填 TODO 的函数体；run_selftests 已经写好，直接跑 --selftest。
// ============================================================================

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

using Map = std::map<std::string, int>;

// 1. 用迭代器按 key 顺序收集所有 key。
std::vector<std::string> keys_in_order(const Map& m) {
    std::vector<std::string> keys;
    // TODO 1：for (auto it = m.begin(); it != m.end(); ++it)
    //         把 it->first push_back 进 keys。
    (void)m;
    return keys;
}

// 2. 找到 key，把它的 value 加 1；找不到返回 false。
bool increment_value(Map& m, const std::string& key) {
    // TODO 2：用 find；找到后改 it->second。
    (void)m;
    (void)key;
    return false;
}

// 3. 返回 key 在有序 map 中的位置（0-based）；找不到返回 m.size()。
std::size_t index_of(const Map& m, const std::string& key) {
    // TODO 3：用 find + std::distance(m.begin(), it)。
    //         注意：map 的迭代器不是随机访问迭代器，不能写 it - m.begin()。
    (void)m;
    (void)key;
    return 0;
}

// 4. 删除所有 value 为偶数的元素，返回删掉的个数。
std::size_t erase_even(Map& m) {
    std::size_t erased = 0;
    // TODO 4：遍历中删除，必须写 it = m.erase(it)；
    //         每删一个 ++erased。
    (void)m;
    return erased;
}

// 5. 返回第一个 key >= target 的 key；没有就返回空串。
std::string first_key_ge(const Map& m, const std::string& target) {
    // TODO 5：用 m.lower_bound(target)，并判断是否等于 m.end()。
    (void)m;
    (void)target;
    return "";
}

// 6. 用迭代器把 value 求和。
int sum_values(const Map& m) {
    int total = 0;
    // TODO 6：用迭代器或 range-for 累加 it->second / pair.second。
    (void)m;
    return total;
}

int run_selftests() {
    int passed = 0;
    int failed = 0;

    auto check = [&](bool ok, const char* name) {
        if (ok) {
            ++passed;
            std::cout << "[PASS] " << name << "\n";
        } else {
            ++failed;
            std::cout << "[FAIL] " << name << "\n";
        }
    };

    Map m{{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};

    check(keys_in_order(m) == std::vector<std::string>{"a", "b", "c", "d"},
          "keys_in_order");

    check(increment_value(m, "b") && m["b"] == 3,
          "increment_value: found");
    check(!increment_value(m, "z") && m.size() == 4,
          "increment_value: missing");

    check(index_of(m, "c") == 2, "index_of: found");
    check(index_of(m, "z") == m.size(), "index_of: missing");

    check(first_key_ge(m, "bb") == "c", "lower_bound: middle");
    check(first_key_ge(m, "z").empty(), "lower_bound: none");

    check(sum_values(m) == 10, "sum_values");

    check(erase_even(m) == 2 && m.size() == 2 &&
          m.count("a") == 1 && m.count("c") == 1,
          "erase_even");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    return run_selftests();
}
