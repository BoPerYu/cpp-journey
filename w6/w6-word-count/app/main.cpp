#include "word_count.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include"option.hpp"

int main(int argc, char** argv) {
    try {
        const cli::Options options = cli::parse_options(argc, argv);
        if (options.show_help) {
            cli::print_usage(argv[0]);
            return 0;
        }

        if (!options.input_path.empty()) {
            std::ifstream input(options.input_path);
            if (!input) {
                std::cerr << "cannot open input file: " << options.input_path << '\n';
                return 1;
            }
            const auto ranking =
                word_count::rank_words(word_count::count_words(input));
            word_count::print_top(std::cout, ranking, options.top_k);
            return 0;
        }

        const auto ranking = word_count::rank_words(word_count::count_words(std::cin));
        word_count::print_top(std::cout, ranking, options.top_k);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 2;
    }
}
