#include "option.hpp"

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

int passed = 0;
int failed = 0;

void check(bool condition, const char* name) {
    if (condition) {
        ++passed;
        std::cout << "[PASS] " << name << '\n';
    } else {
        ++failed;
        std::cout << "[FAIL] " << name << '\n';
    }
}

cli::Options parse_arguments(std::initializer_list<const char*> arguments) {
    std::vector<std::string> storage;
    for (const char* argument : arguments) {
        storage.emplace_back(argument);
    }

    std::vector<char*> argv;
    argv.reserve(storage.size());
    for (std::string& argument : storage) {
        argv.push_back(argument.data());
    }

    return cli::parse_options(static_cast<int>(argv.size()), argv.data());
}

void check_invalid_arguments(
    std::initializer_list<const char*> arguments,
    const char* name) {
    try {
        (void)parse_arguments(arguments);
    } catch (const std::invalid_argument&) {
        check(true, name);
        return;
    } catch (...) {
        check(false, name);
        return;
    }
    check(false, name);
}

void run_tests() {
    {
        const auto options = parse_arguments({"word_count"});
        check(
            options.top_k == 10 && options.input_path.empty() &&
                !options.show_help,
            "default options");
    }

    {
        const auto options =
            parse_arguments({"word_count", "--top", "5", "data/sample.txt"});
        check(
            options.top_k == 5 && options.input_path == "data/sample.txt" &&
                !options.show_help,
            "top-k and input path");
    }

    {
        const auto options = parse_arguments({"word_count", "--help"});
        check(options.show_help, "help flag");
    }

    check_invalid_arguments({"word_count", "--top"}, "missing top-k value");
    check_invalid_arguments({"word_count", "--top", "0"}, "zero top-k");
    check_invalid_arguments({"word_count", "--top", "-1"}, "negative top-k");
    check_invalid_arguments({"word_count", "--top", "12x"}, "partly numeric top-k");
    check_invalid_arguments({"word_count", "--unknown"}, "unknown option");
    check_invalid_arguments(
        {"word_count", "first.txt", "second.txt"},
        "multiple input paths");
}

}  // namespace

int main() {
    try {
        run_tests();
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] unexpected exception: " << error.what() << '\n';
        return 1;
    }

    std::cout << '\n' << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
