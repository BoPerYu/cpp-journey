#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

struct Posting {
    std::size_t document_id = 0;
    std::size_t term_frequency = 0;
};

using PostingList = std::vector<Posting>;

struct InvertedIndex {
    std::size_t document_count = 0;
    std::unordered_map<std::string, PostingList> postings;
};

std::vector<std::string> split_tokens(const std::string& line);

std::unordered_map<std::string, std::size_t>
count_terms(const std::vector<std::string>& tokens);

InvertedIndex build_inverted_index(std::istream& input);

const PostingList* find_postings(
    const InvertedIndex& index,
    const std::string& term);
