#include"option.hpp"
#include<iostream>
#include<stdexcept>
#include<string>

namespace cli{
    Options parse_options(int argc, char** argv) {
        Options options;
        for (int index = 1; index < argc; ++index) {
            const std::string argument = argv[index];
            if (argument == "--help" || argument == "-h") {
                options.show_help = true;
            }
            else if (argument == "--top") {
                if (index + 1 >= argc) {
                    throw std::invalid_argument("--top requires a positive integer");
                }
                const std::string value = argv[++index];
                std::size_t consumed = 0;
                const unsigned long parsed = std::stoul(value, &consumed);
                if (parsed == 0 || consumed != value.size() ||
                    value.front() == '-' || value.front() == '+') {
                    throw std::invalid_argument("--top requires a positive integer");
                }
                options.top_k = static_cast<std::size_t>(parsed);
            }
            else if (!argument.empty() && argument.front() == '-') {
                throw std::invalid_argument("unknown option: " + argument);
            }
            else if (options.input_path.empty()) {
                options.input_path = argument;
            }
            else {
                throw std::invalid_argument("only one input file may be provided");
            }
        }
        return options;
    }
    void print_usage(const char* program) {
        std::cout
            << "Usage: " << program << " [--top N] [FILE]\n"
            << "Read whitespace-separated tokens and print the top N frequencies.\n"
            << "When FILE is omitted, input is read from stdin.\n";
    }
}

