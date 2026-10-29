#pragma once
#include<string>
#include<cstddef>

namespace cli{
    struct Options {
        std::size_t top_k = 10;
        std::string input_path;
        bool show_help = false;
    };
    Options parse_options(int argc, char** argv);
    void print_usage(const char* program);
}