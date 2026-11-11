#include "inverted_index.h"

#include <iostream>
#include <sstream>
#include <string>

namespace {

int total_checks = 0;
int failed_checks = 0;

void check(bool condition, const std::string& name) {
    ++total_checks;
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
    } else {
        ++failed_checks;
        std::cerr << "[FAIL] " << name << '\n';
    }
}

void test_split_tokens() {
    const std::vector<std::string> empty = split_tokens("");
    const std::vector<std::string> normal = split_tokens("a b c");
    const std::vector<std::string> spaces = split_tokens("  a   b  ");

    check(empty.empty(), "split: empty line has no tokens");
    check(normal == std::vector<std::string>{"a", "b", "c"},
          "split: normal tokens");
    check(spaces == std::vector<std::string>{"a", "b"},
          "split: repeated whitespace");
}

void test_count_terms() {
    const auto counts = count_terms({"apple", "apple", "banana"});
    const auto apple = counts.find("apple");
    const auto banana = counts.find("banana");

    check(counts.size() == 2, "count: two unique terms");
    check(apple != counts.end() && apple->second == 2,
          "count: repeated term frequency");
    check(banana != counts.end() && banana->second == 1,
          "count: single term frequency");
}

void test_empty_and_blank_documents() {
    std::istringstream empty_input("");
    const InvertedIndex empty_index = build_inverted_index(empty_input);
    check(empty_index.document_count == 0,
          "index: empty file has zero documents");
    check(empty_index.postings.empty(),
          "index: empty file has no postings");

    std::istringstream blank_input("\n");
    const InvertedIndex blank_index = build_inverted_index(blank_input);
    check(blank_index.document_count == 1,
          "index: blank line is one document");
    check(blank_index.postings.empty(),
          "index: blank line adds no postings");
}

void test_postings() {
    std::istringstream input(
        "apple apple banana\n"
        "\n"
        "apple carrot\n");

    const InvertedIndex index = build_inverted_index(input);
    check(index.document_count == 3, "index: three documents");

    const PostingList* apple = find_postings(index, "apple");
    check(apple != nullptr, "query: apple exists");
    if (apple != nullptr) {
        check(apple->size() == 2, "query: apple appears in two documents");
        if (apple->size() == 2) {
            check((*apple)[0].document_id == 0
                      && (*apple)[0].term_frequency == 2,
                  "query: first apple posting");
            check((*apple)[1].document_id == 2
                      && (*apple)[1].term_frequency == 1,
                  "query: second apple posting");
            check((*apple)[0].document_id < (*apple)[1].document_id,
                  "query: postings are ordered by document id");
        }
    }

    const PostingList* banana = find_postings(index, "banana");
    check(banana != nullptr && banana->size() == 1,
          "query: banana appears once");

    const PostingList* missing = find_postings(index, "missing");
    check(missing == nullptr, "query: missing term returns nullptr");
}

}  // namespace

int main() {
    test_split_tokens();
    test_count_terms();
    test_empty_and_blank_documents();
    test_postings();

    const int passed = total_checks - failed_checks;
    std::cout << '\n' << passed << '/' << total_checks
              << " checks passed\n";
    return failed_checks == 0 ? 0 : 1;
}
