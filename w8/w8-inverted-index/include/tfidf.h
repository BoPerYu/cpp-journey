#pragma once

#include "inverted_index.h"

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

struct SearchResult {
    std::size_t document_id = 0;
    double score = 0.0;
};

struct TfidfIndex {
    InvertedIndex inverted;
    std::vector<double> document_norms;
};

double inverse_document_frequency(
    const InvertedIndex& index,
    const std::string& term);

TfidfIndex build_tfidf_index(std::istream& input);

std::vector<SearchResult> search_tfidf(
    const TfidfIndex& index,
    const std::string& query,
    std::size_t top_k);
