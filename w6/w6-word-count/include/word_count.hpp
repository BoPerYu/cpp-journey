#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

namespace word_count {

struct Entry {
    std::string word;
    std::size_t count;
};

inline bool operator==(const Entry& lhs, const Entry& rhs) {
    return lhs.word == rhs.word && lhs.count == rhs.count;
}

using Frequencies = std::unordered_map<std::string, std::size_t>;
using Ranking = std::vector<Entry>;

Frequencies count_words(std::istream& input);
Ranking rank_words(const Frequencies& frequencies);
void print_top(std::ostream& output, const Ranking& ranking, std::size_t k);

}  // namespace word_count
