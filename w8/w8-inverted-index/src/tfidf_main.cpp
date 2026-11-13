#include "tfidf.h"

#include <fstream>
#include <iostream>
#include <string>
#include<iomanip>

int main(int argc, char** argv) {
    if (argc != 3 && argc != 4) {
        std::cerr << "usage: tfidf_search <token-file> <query> [top-k]\n";
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "cannot open input file: " << argv[1] << '\n';
        return 1;
    }

    std::size_t top_k = 10;
    if (argc == 4) {
        try {
            const unsigned long parsed = std::stoul(argv[3]);
            top_k = static_cast<std::size_t>(parsed);
        } catch (const std::exception&) {
            std::cerr << "top-k must be a non-negative integer\n";
            return 2;
        }
    }

    std::cout << std::setprecision(17);
    const TfidfIndex index = build_tfidf_index(input);
    const std::vector<SearchResult> results =
        search_tfidf(index, argv[2], top_k);
    std::cout << "document_count = " << index.inverted.document_count << '\n';
    std::cout << "query = " << argv[2] << '\n';
    for (const SearchResult& result : results) {
        std::cout << "doc=" << result.document_id
                  << " score=" <<result.score << '\n';
    }

    return 0;
}
