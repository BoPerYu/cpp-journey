#include "tfidf.h"

#include <cmath>
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

bool close_to(double actual, double expected, double tolerance = 1e-9) {
    return std::abs(actual - expected) <= tolerance;
}

TfidfIndex build_sample() {
    std::istringstream input(
        "apple apple banana\n"
        "banana\n"
        "apple carrot\n");
    return build_tfidf_index(input);
}

void test_idf() {
    const TfidfIndex index = build_sample();
    const double apple_idf =
        inverse_document_frequency(index.inverted, "apple");
    const double carrot_idf =
        inverse_document_frequency(index.inverted, "carrot");
    const double missing_idf =
        inverse_document_frequency(index.inverted, "missing");

    check(close_to(apple_idf, std::log(4.0 / 3.0) + 1.0),
          "idf: apple uses fixed smooth formula");
    check(close_to(carrot_idf, std::log(4.0 / 2.0) + 1.0),
          "idf: carrot uses fixed smooth formula");
    check(carrot_idf > apple_idf, "idf: rarer carrot has larger idf");
    check(close_to(missing_idf, 0.0), "idf: missing term returns zero");
}

void test_document_norms() {
    const TfidfIndex index = build_sample();
    check(index.document_norms.size() == 3,
          "norms: one entry per document");
    if (index.document_norms.size() == 3) {
        check(index.document_norms[0] > 0.0,
              "norms: non-empty document has positive norm");
    }
    for (double norm : index.document_norms) {
        check(std::isfinite(norm), "norms: value is finite");
    }

    std::istringstream input("apple\n\nbanana\n");
    const TfidfIndex with_blank = build_tfidf_index(input);
    check(with_blank.document_norms.size() == 3,
          "norms: blank document still has an entry");
    if (with_blank.document_norms.size() == 3) {
        check(close_to(with_blank.document_norms[1], 0.0),
              "norms: blank document norm is zero");
    }
}

void test_single_term_ranking() {
    const TfidfIndex index = build_sample();
    const std::vector<SearchResult> apple = search_tfidf(index, "apple", 10);

    check(apple.size() == 2, "ranking: apple hits two documents");
    if (apple.size() == 2) {
        check(apple[0].document_id == 0,
              "ranking: higher apple tf ranks document zero first");
        check(apple[1].document_id == 2,
              "ranking: lower apple tf ranks document two second");
    }

    const std::vector<SearchResult> banana =
        search_tfidf(index, "banana", 10);
    check(banana.size() == 2, "ranking: banana hits two documents");
    if (banana.size() == 2) {
        check(banana[0].document_id == 1
                  && banana[1].document_id == 0,
              "ranking: shorter vector has higher cosine for same term");
    }

    std::istringstream tie_input(
        "banana\n"
        "banana\n");
    const TfidfIndex tie_index = build_tfidf_index(tie_input);
    const std::vector<SearchResult> tied =
        search_tfidf(tie_index, "banana", 10);
    check(tied.size() == 2, "ranking: tie corpus returns two documents");
    if (tied.size() == 2) {
        check(tied[0].document_id == 0
                  && tied[1].document_id == 1,
              "ranking: equal scores use document id ascending");
    }
}

void test_multi_term_and_limits() {
    const TfidfIndex index = build_sample();
    const std::vector<SearchResult> both =
        search_tfidf(index, "apple carrot", 10);
    check(!both.empty(), "multi: query has results");
    if (!both.empty()) {
        check(both[0].document_id == 2,
              "multi: document containing both terms ranks first");
    }

    check(search_tfidf(index, "", 10).empty(),
          "query: empty query returns no result");
    check(search_tfidf(index, "missing", 10).empty(),
          "query: unknown query term returns no result");
    check(search_tfidf(index, "apple", 0).empty(),
          "query: top-k zero returns no result");
    check(search_tfidf(index, "apple", 1).size() == 1,
          "query: top-k truncates results");
}

}  // namespace

int main() {
    test_idf();
    test_document_norms();
    test_single_term_ranking();
    test_multi_term_and_limits();

    const int passed = total_checks - failed_checks;
    std::cout << '\n' << passed << '/' << total_checks
              << " checks passed\n";
    return failed_checks == 0 ? 0 : 1;
}
