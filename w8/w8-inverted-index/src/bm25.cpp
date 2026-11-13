#include "bm25.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

double bm25_inverse_document_frequency(
    std::size_t document_count,
    std::size_t document_frequency) {
    const double N = static_cast<double>(document_count);
    const double df = static_cast<double>(document_frequency);
    double idf = log(1 + (N - df + 0.5) / (df + 0.5));
    return idf;
}

Bm25Index build_bm25_index(
    std::istream& input,
    double k1,
    double b) {
    if (k1 < 0.0 || b < 0.0 || b > 1.0) {
        throw std::invalid_argument("BM25 requires k1 >= 0 and 0 <= b <= 1");
    }

    Bm25Index index;
    index.k1 = k1;
    index.b = b;
    index.inverted = build_inverted_index(input);
    index.document_lengths.resize(index.inverted.document_count, 0);

    std::size_t token_total = 0;
    for (const auto& entry : index.inverted.postings) {
        std::string token = entry.first;
        PostingList postlist = entry.second;
        for (const Posting& posting : postlist) {
            index.document_lengths[posting.document_id] += posting.term_frequency;
        }
    }
    for (const std::size_t& num : index.document_lengths) {
        token_total += num;
    }
    if (index.inverted.document_count > 0) {
        index.average_document_length = static_cast<double>(token_total) / static_cast<double>(index.inverted.document_count);
    }
    return index;
}

std::vector<SearchResult> search_bm25(
    const Bm25Index& index,
    const std::string& query,
    std::size_t top_k) {

    auto query_stack = split_tokens(query);
    auto query_tf = count_terms(query_stack);
    if (query_tf.empty() or top_k == 0 or index.average_document_length == 0) {
        return {};
    }
    std::size_t doc_count = index.inverted.document_count;
    std::vector<double>scores(index.inverted.document_count);
    std::vector<SearchResult> result;
    for (const auto& entry : query_tf) {
        std::string term=entry.first;
        double qtf = static_cast<double>(entry.second);
        auto it = index.inverted.postings.find(term);
        if (it != index.inverted.postings.end()) {
            std::size_t df = it->second.size();
            double t_idf = bm25_inverse_document_frequency(doc_count, df);
            for (const Posting& posting : it->second) {
                std::size_t tf = posting.term_frequency;
                double score = static_cast<double>(qtf*t_idf * tf * (index.k1 + 1.0) /
                    (tf + index.k1 * (1.0 - index.b + index.b * (index.document_lengths[posting.document_id] / index.average_document_length))));
                scores[posting.document_id] += score;
            }
        }
    }
    for (std::size_t doc_id = 0;doc_id < index.inverted.document_count;doc_id++) {
        if(scores[doc_id]>0.0){
            result.push_back({ doc_id,scores[doc_id] });
        }
    }
    std::sort(result.begin(),result.end(), [](const auto& x, const auto& y) {
        if (std::abs(x.score - y.score) <= 1e-12) {
            return x.document_id < y.document_id;
        }
        return x.score > y.score;
        });
    if(result.size()>top_k){
        result.resize(top_k);
    }
    return result;
}
