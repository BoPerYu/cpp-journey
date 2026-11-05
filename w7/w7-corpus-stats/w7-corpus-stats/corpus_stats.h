#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

struct CorpusStats {
    std::size_t document_count = 0;
    std::unordered_map<std::string, std::size_t> frequencies;
};
struct Entry {
    std::string token;
    std::size_t count;
};
CorpusStats read_corpus(std::istream& input);
std::vector<Entry> transform_and_order(const std::unordered_map<std::string,std::size_t>& t);
