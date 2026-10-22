// ============================================================================
// W5D2 可复用练习 · 唯一词表（set 版）
// ----------------------------------------------------------------------------
// 输入：空白分隔的 token。
// 输出：按字典序排列的唯一 token，每行一个；最后打印 unique count。
// 目标：把 set 用作“词汇表去重”，这是检索项目建词表的最小一步。
// ============================================================================

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <windows.h>

using WordSet = std::set<std::string>;

WordSet unique_words(std::istream& in) {
    WordSet words;
    std::string word;
    // TODO 1：while (in >> word) { words.insert(word); }
    while (in >> word) {
        words.insert(word);
    }
    (void)in;
    return words;
}

void print_words(std::ostream& out, const WordSet& words) {
    // TODO 2：按 set 的顺序逐行输出。
    for (auto it = words.begin();it != words.end();it++) {
        out << *it << "\n";
    }
    (void)out;
    (void)words;
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

    {
        std::istringstream in("banana apple banana cherry apple");
        WordSet words = unique_words(in);
        check(words.size() == 3 &&
              words.count("apple") == 1 &&
              words.count("banana") == 1 &&
              words.count("cherry") == 1,
              "unique_words: deduplicate");

        std::ostringstream out;
        print_words(out, words);
        check(out.str() == "apple\nbanana\ncherry\n",
              "print_words: sorted order");
    }

    {
        std::istringstream in("");
        WordSet words = unique_words(in);
        check(words.empty(), "unique_words: empty input");
    }

    {
        std::istringstream in("Apple apple APPLE");
        WordSet words = unique_words(in);
        check(words.size() == 3, "unique_words: case is preserved");
    }

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc > 1 && std::string(argv[1]) == "--selftest") {
        return run_selftests();
    }

    WordSet words = unique_words(std::cin);
    print_words(std::cout, words);
    std::cout << "unique count = " << words.size() << "\n";
    return 0;
}
