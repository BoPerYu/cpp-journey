#include"corpus_stats.h"
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<unordered_map>

CorpusStats read_corpus(std::istream& input) {
	CorpusStats a;
	std::string line;
	while (std::getline(input, line)) {
		++a.document_count;
		std::string token;
		std::istringstream line_stream(line);
		while (line_stream >> token) {
			++a.frequencies[token];
		}
	}
	return a;
}

std::vector<Entry> transform_and_order(const std::unordered_map<std::string, std::size_t>& t) {
	std::vector<Entry> ans;
	ans.reserve(t.size());
	for (const auto& [token, count] : t) {
		ans.push_back({ token, count });
	}
	std::sort(ans.begin(), ans.end(),
		[](const Entry& a,const Entry& b) {
			if (a.count == b.count) {
				return a.token < b.token;
			}
			return a.count > b.count;
		});
	return ans;
}

