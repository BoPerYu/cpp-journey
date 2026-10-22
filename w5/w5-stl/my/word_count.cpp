// ============================================================================
// 今日可复用练习 · 词频统计器 v0
// ----------------------------------------------------------------------------
// 目标：把“读 token → 计数 → 排序 → 输出 Top-K”拆成四个函数。
// 你只写 TODO 的函数体；测试代码已经写好，直接跑 --selftest。
//
// 输入格式：空白分隔的 token；本版本不处理标点、大小写、中文分词。
// 排序规则：频次从高到低；频次相同按单词字典序升序。
// ============================================================================

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <windows.h>

using FreqMap = std::unordered_map<std::string, int>;
using Ranked = std::vector<std::pair<std::string, int>>;

FreqMap count_words(std::istream& in) {
    FreqMap freq;
    // TODO 1：从 in 逐个读入 std::string token，统计次数。
    //         提示：可以用 while (in >> word) { ... }。
    //         想一想：这里用 ++freq[word] 和用 find 再插入，差别是什么？
    std::string word;
    while (in >> word) {
        ++freq[word];
    }
    (void)in;
    return freq;
}

Ranked rank_words(const FreqMap& freq) {
    Ranked ranked;
    // TODO 2：把 freq 的 {word, count} 拷进 ranked，
    //         然后按“频次降序、同频单词升序”排序。
    //         提示：std::sort + lambda；比较器必须满足严格弱序。
    for (const std::pair<std::string,int>& x : freq) {
        ranked.push_back(x);
    }
    std::sort(ranked.begin(), ranked.end(),
        [](const auto& a, const auto& b) {
            if (a.second == b.second) {
                return a.first < b.first;
            }
            return a.second > b.second;
        });
    (void)freq;
    return ranked;
}

void print_top(std::ostream& out, const Ranked& ranked, std::size_t k) {
    // TODO 3：打印前 min(k, ranked.size()) 行，每行 "word count"。
    std::size_t t = std::min<std::size_t>(k, ranked.size());
    for (int i = 0;i < t; i++) {
        out << ranked[i].first << " " << ranked[i].second << "\n";
    }
    (void)out;
    (void)ranked;
    (void)k;
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
        std::istringstream in("apple banana apple\ncherry banana apple\n");
        FreqMap f = count_words(in);
        check(f.size() == 3 && f["apple"] == 3 && f["banana"] == 2 && f["cherry"] == 1,
              "count_words: basic counts");

        Ranked r = rank_words(f);
        check(r.size() == 3 &&
              r[0] == std::make_pair(std::string("apple"), 3) &&
              r[1] == std::make_pair(std::string("banana"), 2) &&
              r[2] == std::make_pair(std::string("cherry"), 1),
              "rank_words: count descending");
    }

    {
        std::istringstream in("b a b a c");
        FreqMap f = count_words(in);
        Ranked r = rank_words(f);
        check(r.size() == 3 &&
              r[0] == std::make_pair(std::string("a"), 2) &&
              r[1] == std::make_pair(std::string("b"), 2) &&
              r[2] == std::make_pair(std::string("c"), 1),
              "rank_words: tie by word ascending");
    }

    {
        std::istringstream in("");
        FreqMap f = count_words(in);
        check(f.empty(), "count_words: empty input");
        check(rank_words(f).empty(), "rank_words: empty input");
    }

    {
        std::istringstream in("x x y");
        FreqMap f = count_words(in);
        Ranked r = rank_words(f);
        std::ostringstream out;
        print_top(out, r, 1);
        check(out.str() == "x 2\n", "print_top: k limits output");
    }

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc > 1 && std::string(argv[1]) == "--selftest") {
        return run_selftests();
    }

    FreqMap freq = count_words(std::cin);
    Ranked ranked = rank_words(freq);
    print_top(std::cout, ranked, 10);
    return 0;
}
