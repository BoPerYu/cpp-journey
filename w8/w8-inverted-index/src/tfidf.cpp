#include "tfidf.h"

#include <algorithm>
#include <cmath>

double inverse_document_frequency(
    const InvertedIndex& index,
    const std::string& term) {
    auto term_id = find_postings(index, term);
    if (term_id == nullptr) {
        return 0;
    }
    double N = static_cast<double>(index.document_count);
    double df = static_cast<double>(term_id->size());
    double term_idf =log((N + 1) / (df + 1)) + 1;
    return term_idf;
}

TfidfIndex build_tfidf_index(std::istream& input) {
    TfidfIndex index;
    index.inverted = build_inverted_index(input);
    index.document_norms.resize(index.inverted.document_count,0.0);
    for (const auto& entry : index.inverted.postings) {
        double term_idf=inverse_document_frequency(index.inverted,entry.first);
        for (const Posting& posting : entry.second) {
            const double weight =
                static_cast<double>(posting.term_frequency) * term_idf;
            index.document_norms[posting.document_id] += weight * weight;
        }   
    }
    for (double& squared_norm : index.document_norms) {
        squared_norm = std::sqrt(squared_norm);
    }
    return index;
}

std::vector<SearchResult> search_tfidf(
    const TfidfIndex& index,
    const std::string& query,
    std::size_t top_k) {
    auto query_stack = split_tokens(query);
    auto query_tf = count_terms(query_stack);
    double query_num_squared = 0;
    std::vector<double>score(index.document_norms.size(),0.0);
    
    for (const auto& entry : query_tf) {
        const std::string& term = entry.first;
        const double qtf = static_cast<double>(entry.second);
        double idf = inverse_document_frequency(index.inverted, term);
        double query_weight = qtf * idf;
        query_num_squared += query_weight * query_weight;
        auto it = index.inverted.postings.find(term);
        if (it != index.inverted.postings.end()) {
            for (const Posting& posting : it->second) {
                double doc_weight = posting.term_frequency * idf;
                score[posting.document_id] += query_weight * doc_weight;
            }
        }
    }
    double query_norm = std::sqrt(query_num_squared);
    if (query_norm == 0) { return {}; }
    std::vector<SearchResult> result;
    for (std::size_t doc_id = 0;doc_id < score.size();++doc_id) {
        double doc_norm = index.document_norms[doc_id];
        if (score[doc_id] == 0 || doc_norm == 0.0) {
            continue;
        }
        score[doc_id] = static_cast<double>(score[doc_id] / (query_norm * doc_norm));
        result.push_back({ doc_id, score[doc_id]});
    }
    std::sort(result.begin(), result.end(), [](const SearchResult& a, const SearchResult& b) {
        if (std::abs(a.score - b.score) <= 1e-12) {
            return a.document_id < b.document_id;
        }
        return a.score > b.score;
        });
    if (result.size() > top_k) {
        result.resize(top_k);
    }
    return result;
}
