#include "word_count.hpp"

#include <exception>
#include <iostream>
#include <sstream>

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
        std::istringstream input("apple banana apple\ncherry banana apple\n");
        const auto frequencies = word_count::count_words(input);
        check(
            frequencies.size() == 3 && frequencies.at("apple") == 3 &&
                frequencies.at("banana") == 2 &&
                frequencies.at("cherry") == 1,
            "count_words counts repeated tokens");

        const auto ranking = word_count::rank_words(frequencies);
        check(
            ranking.size() == 3 &&
                ranking[0] == word_count::Entry{"apple", 3} &&
                ranking[1] == word_count::Entry{"banana", 2} &&
                ranking[2] == word_count::Entry{"cherry", 1},
            "rank_words sorts by count descending");
    }

    {
        std::istringstream input("b a b a c");
        const auto ranking =
            word_count::rank_words(word_count::count_words(input));
        check(
            ranking.size() == 3 &&
                ranking[0] == word_count::Entry{"a", 2} &&
                ranking[1] == word_count::Entry{"b", 2} &&
                ranking[2] == word_count::Entry{"c", 1},
            "rank_words breaks ties by word ascending");
    }

    {
        std::istringstream input("");
        const auto frequencies = word_count::count_words(input);
        check(frequencies.empty(), "count_words accepts empty input");
        check(
            word_count::rank_words(frequencies).empty(),
            "rank_words accepts empty input");
    }

    {
        const word_count::Ranking ranking{
            {"x", 3},
            {"y", 2},
            {"z", 1},
        };
        std::ostringstream output;
        word_count::print_top(output, ranking, 2);
        check(output.str() == "x 3\ny 2\n", "print_top respects k");

        std::ostringstream oversized_output;
        word_count::print_top(oversized_output, ranking, 100);
        check(
            oversized_output.str() == "x 3\ny 2\nz 1\n",
            "print_top clamps k to ranking size");
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
