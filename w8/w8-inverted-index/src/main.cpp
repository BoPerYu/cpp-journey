#include "inverted_index.h"

#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: inverted_index <token-file> <query-term>\n";
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "cannot open input file: " << argv[1] << '\n';
        return 1;
    }

    const InvertedIndex index = build_inverted_index(input);
    const std::string term = argv[2];

    std::cout << "document_count = " << index.document_count << '\n';
    std::cout << "term = " << term << '\n';

    const PostingList* postings = find_postings(index, term);
    if (postings == nullptr) {
        std::cout << "term not found\n";
        return 0;
    }

    for (const Posting& posting : *postings) {
        std::cout << "doc=" << posting.document_id
                  << " tf=" << posting.term_frequency << '\n';
    }

    return 0;
}
