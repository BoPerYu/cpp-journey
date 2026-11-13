#include "bm25.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
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

bool close_to(double actual, double expected, double tolerance = 1e-12) {
    return std::abs(actual - expected) <= tolerance;
}

Bm25Index build_sample() {
    std::istringstream input(
        "apple apple banana\n"
        "banana\n"
        "apple carrot\n");
    return build_bm25_index(input);
}

void test_idf() {
    const double apple = bm25_inverse_document_frequency(3, 2);
    const double carrot = bm25_inverse_document_frequency(3, 1);

    check(close_to(apple, std::log(1.0 + 1.5 / 2.5)),
          "bm25 idf: apple formula");
    check(close_to(carrot, std::log(1.0 + 2.5 / 1.5)),
          "bm25 idf: carrot formula");
    check(carrot > apple, "bm25 idf: rarer term has larger idf");
    check(apple >= 0.0, "bm25 idf: value is non-negative");
}

void test_document_lengths() {
    const Bm25Index index = build_sample();

    check(index.document_lengths.size() == 3,
          "bm25 lengths: one entry per document");
    if (index.document_lengths.size() == 3) {
        check(index.document_lengths[0] == 3,
              "bm25 lengths: doc zero length");
        check(index.document_lengths[1] == 1,
              "bm25 lengths: doc one length");
        check(index.document_lengths[2] == 2,
              "bm25 lengths: doc two length");
        check(close_to(index.average_document_length, 2.0),
              "bm25 lengths: average length");
    }

    std::istringstream with_blank("apple\n\nbanana\n");
    const Bm25Index blank = build_bm25_index(with_blank);
    check(blank.document_lengths.size() == 3,
          "bm25 lengths: blank document is retained");
    if (blank.document_lengths.size() == 3) {
        check(blank.document_lengths[1] == 0,
              "bm25 lengths: blank document length is zero");
    }
}

void test_ranking() {
    const Bm25Index index = build_sample();

    const std::vector<SearchResult> apple =
        search_bm25(index, "apple", 10);
    check(apple.size() == 2, "bm25 ranking: apple hits two documents");
    if (apple.size() == 2) {
        check(apple[0].document_id == 0 && apple[1].document_id == 2,
              "bm25 ranking: higher apple tf ranks first");
    }

    const std::vector<SearchResult> both =
        search_bm25(index, "apple carrot", 10);
    check(!both.empty(), "bm25 ranking: multi-term query has results");
    if (!both.empty()) {
        check(both[0].document_id == 2,
              "bm25 ranking: document containing both terms ranks first");
    }
}

void test_boundaries_and_validation() {
    const Bm25Index index = build_sample();

    check(search_bm25(index, "", 10).empty(),
          "bm25 query: empty query");
    check(search_bm25(index, "missing", 10).empty(),
          "bm25 query: unknown query");
    check(search_bm25(index, "apple", 0).empty(),
          "bm25 query: top-k zero");
    check(search_bm25(index, "apple", 1).size() == 1,
          "bm25 query: top-k truncation");

    std::istringstream empty_input("");
    const Bm25Index empty = build_bm25_index(empty_input);
    check(search_bm25(empty, "apple", 10).empty(),
          "bm25 query: empty corpus");

    bool rejected_negative_k1 = false;
    try {
        std::istringstream input("apple");
        (void)build_bm25_index(input, -0.1, 0.75);
    } catch (const std::invalid_argument&) {
        rejected_negative_k1 = true;
    }
    check(rejected_negative_k1, "bm25 validation: rejects negative k1");

    bool rejected_bad_b = false;
    try {
        std::istringstream input("apple");
        (void)build_bm25_index(input, 1.2, 1.1);
    } catch (const std::invalid_argument&) {
        rejected_bad_b = true;
    }
    check(rejected_bad_b, "bm25 validation: rejects b outside [0,1]");
}

}  // namespace

int main() {
    test_idf();
    test_document_lengths();
    test_ranking();
    test_boundaries_and_validation();

    const int passed = total_checks - failed_checks;
    std::cout << '\n' << passed << '/' << total_checks
              << " checks passed\n";
    return failed_checks == 0 ? 0 : 1;
}
