#include "inverted_index.h"

#include <sstream>

std::vector<std::string> split_tokens(const std::string& line) {
    std::vector<std::string> stack;
    std::istringstream stream(line);
    std::string token;
    while (stream >> token) {
        stack.push_back(token);
    }
    return stack;
}

std::unordered_map<std::string, std::size_t>
count_terms(const std::vector<std::string>& tokens) {
    std::unordered_map<std::string, std::size_t> um;
    for (std::string token : tokens) {
        ++um[token];
    }
    return um;
}

InvertedIndex build_inverted_index(std::istream& input) {
    InvertedIndex index;
    std::string line;
    while (std::getline(input,line)) {
        std::size_t document_id = index.document_count;
        const auto tokens = split_tokens(line);
        const auto tokens_frequency = count_terms(tokens);
        for (const auto& entry : tokens_frequency) {
            const std::string& term = entry.first;
            const std::size_t frequency = entry.second;
            index.postings[term].push_back(Posting{ document_id,frequency });
        }
        ++index.document_count;
    }
    return index;
}

const PostingList* find_postings(
    const InvertedIndex& index,
    const std::string& term) {
    auto it = index.postings.find(term);
    if (it != index.postings.end()) {
        return &it->second;
    }
    return nullptr;
}
