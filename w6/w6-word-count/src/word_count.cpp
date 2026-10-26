#include "word_count.hpp"

#include <algorithm>
#include <istream>
#include <ostream>
#include <string>

namespace word_count {

Frequencies count_words(std::istream& input) {
    Frequencies frequencies;
    std::string word;
    while (input >> word) {
        ++frequencies[word];
    }
    return frequencies;
}

Ranking rank_words(const Frequencies& frequencies) {
    Ranking ranking;
    ranking.reserve(frequencies.size());
    for (const auto& [word, count] : frequencies) {
        ranking.push_back(Entry{word, count});
    }

    std::sort(
        ranking.begin(),
        ranking.end(),
        [](const Entry& lhs, const Entry& rhs) {
            if (lhs.count != rhs.count) {
                return lhs.count > rhs.count;
            }
            return lhs.word < rhs.word;
        });
    return ranking;
}

void print_top(std::ostream& output, const Ranking& ranking, std::size_t k) {
    const std::size_t limit = std::min(k, ranking.size());
    for (std::size_t index = 0; index < limit; ++index) {
        output << ranking[index].word << ' ' << ranking[index].count << '\n';
    }
}

}  // namespace word_count
