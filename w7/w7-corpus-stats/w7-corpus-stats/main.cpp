#include"corpus_stats.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>

int main(int argc,char** argv) {
    if (argc != 2) {
        std::cerr << "usage: corpus_stats <token-file>\n";
        return 2;
    }
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "cannot open input file: " << argv[1] << '\n';
        return 1;
    }
    const CorpusStats t = read_corpus(file);
	std::cout << "document_count = " << t.document_count << "\n";
	std::cout << "vocabulary = "
		<< t.frequencies.size() << '\n';
	std::vector<Entry> token_list = transform_and_order(t.frequencies);
    if (token_list.empty()) {
        std::cout << "no tokens\n";
    }
    const std::size_t limit = std::min<std::size_t>(100, token_list.size());
    for (std::size_t i = 0; i < limit; ++i) {
        std::cout << token_list[i].token
            << ' ' << token_list[i].count << '\n';
    }
    return 0;
}