#include "tfidf.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "usage: tfidf_batch <token-file> <queries-file> <top-k>\n";
        return 2;
    }

    std::ifstream corpus(argv[1]);
    if (!corpus) {
        std::cerr << "cannot open corpus: " << argv[1] << '\n';
        return 1;
    }

    std::ifstream queries(argv[2]);
    if (!queries) {
        std::cerr << "cannot open query file: " << argv[2] << '\n';
        return 1;
    }

    std::size_t top_k = 0;
    try {
        top_k = static_cast<std::size_t>(std::stoul(argv[3]));
    } catch (const std::exception&) {
        std::cerr << "top-k must be a positive integer\n";
        return 2;
    }
    if (top_k == 0) {
        std::cerr << "top-k must be a positive integer\n";
        return 2;
    }

    const TfidfIndex index = build_tfidf_index(corpus);

    std::cout << "query\trank\tdoc_id\tscore\n";
    std::cout << std::setprecision(17);

    std::string query;
    while (std::getline(queries, query)) {
        if (!query.empty() && query.back() == '\r') {
            query.pop_back();
        }
        if (query.empty()) {
            continue;
        }

        const std::vector<SearchResult> results =
            search_tfidf(index, query, top_k);
        for (std::size_t i = 0; i < results.size(); ++i) {
            std::cout << query << '\t'
                      << i + 1 << '\t'
                      << results[i].document_id << '\t'
                      << results[i].score << '\n';
        }
    }

    return 0;
}
