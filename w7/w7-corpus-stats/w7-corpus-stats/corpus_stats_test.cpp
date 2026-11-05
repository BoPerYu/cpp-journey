#include"corpus_stats.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>

namespace {

    int total_checks = 0;
    int failed_checks = 0;

    void check(bool condition, const std::string& name) {
        ++total_checks;
        if (condition) {
            std::cout << "[PASS] " << name << '\n';
        }
        else {
            ++failed_checks;
            std::cerr << "[FAIL] " << name << '\n';
        }
    }
    void test_empty_file() {
        std::istringstream input("");
        const CorpusStats stats = read_corpus(input);
        check(stats.document_count == 0, "empty file: 0 documents");
        check(stats.frequencies.empty(), "empty file: empty vocabulary");
    }
    void test_single_blank_line() {
        std::istringstream input("\n");
        const CorpusStats stats = read_corpus(input);
        check(stats.document_count == 1, "blank line: 1 document");
        check(stats.frequencies.empty(), "blank line: empty vocabulary");
    }

    void test_corpus_statistics() {
        std::istringstream input("a b \n\na c");
        const CorpusStats stats = read_corpus(input);

        check(stats.document_count == 3, "sample: 3 documents");
        check(stats.frequencies.size() == 3, "sample: 3 unique tokens");
        check(stats.frequencies.at("a") == 2, "sample: a count is 2");
        check(stats.frequencies.at("b") == 1, "sample: b count is 1");
        check(stats.frequencies.at("c") == 1, "sample: c count is 1");
    }

    void test_frequency_ranking() {
        const std::unordered_map<std::string, std::size_t> frequencies{
            {"a", 2},
            {"b", 1},
            {"c", 1},
        };

        const std::vector<Entry> ranking =
            transform_and_order(frequencies);

        check(ranking.size() == 3, "ranking size is 3");

        if (ranking.size() == 3) {
            check(
                ranking[0].token == "a" && ranking[0].count == 2,
                "ranking first item is a 2");
            check(
                ranking[1].token == "b" && ranking[1].count == 1,
                "ranking tie puts b before c");
            check(
                ranking[2].token == "c" && ranking[2].count == 1,
                "ranking last item is c 1");
        }
    }

    void test_tie_lexical_order() {
        const std::unordered_map<std::string, std::size_t> frequencies{
            {"z", 1},
            {"a", 1},
            {"m", 1},
        };

        const std::vector<Entry> ranking =
            transform_and_order(frequencies);

        check(ranking.size() == 3, "tie test: ranking size is 3");

        if (ranking.size() == 3) {
            check(ranking[0].token == "a", "tie test: a first");
            check(ranking[1].token == "m", "tie test: m second");
            check(ranking[2].token == "z", "tie test: z third");
        }
    }

}  // namespace

int main() {
    test_empty_file();
    test_single_blank_line();
    test_corpus_statistics();
    test_frequency_ranking();
    test_tie_lexical_order();

    std::cout << '\n'
        << total_checks - failed_checks
        << '/' << total_checks
        << " checks passed\n";

    return failed_checks == 0 ? 0 : 1;
}
