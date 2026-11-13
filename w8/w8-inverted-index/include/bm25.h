#pragma once

#include "tfidf.h"

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

struct Bm25Index {
    InvertedIndex inverted;
    std::vector<std::size_t> document_lengths;
    double average_document_length = 0.0;
    double k1 = 1.2;
    double b = 0.75;
};

double bm25_inverse_document_frequency(
    std::size_t document_count,
    std::size_t document_frequency);

Bm25Index build_bm25_index(
    std::istream& input,
    double k1 = 1.2,
    double b = 0.75);

std::vector<SearchResult> search_bm25(
    const Bm25Index& index,
    const std::string& query,
    std::size_t top_k);
