#include<iostream>
#include<vector>
#include<string>
#include<windows.h>
int total(const std::vector<int>& v) {
	int i = 0;
	for (int x : v) {
		i += x;
	}
	return i;
}
void addone(std::vector<int>& v) {
	for (int& x : v) {
		x += 1;
	}
}
void minmax_(const std::vector<int>& v, const std::vector<std::string>& name, int& max_, int& min_, std::string& maxname, std::string& minname) {
	max_ = v[0];
	min_ = v[0];
	for (int i = 0;i < v.size();i++) {
		if (v[i] >= max_) {
			max_ = v[i];
			maxname = name[i];
		}
		if (v[i] <= min_) {
			min_ = v[i];
			minname = name[i];
		}
	}
}
auto findfirstabove(std::vector<int>& v, int threshold) {
	for (auto it = v.begin();it != v.end();it++) {
		if (*it >= threshold) {
			return it;
		}
	}
	return v.end();
}
std::string findname(const std::vector<int>& v, const  std::vector<std::string>& name, int target) {
	for (int i = 0;i < v.size();i++) {
		if (v[i] == target) {
			return name[i];
		}
	}
	return "none";
}
void print_(const std::vector<int>& v) {
	for (int x : v) {
		std::cout << x << ",";
	}
	std::cout << std::endl;
}
int main() {
	SetConsoleOutputCP(CP_UTF8);
	std::vector<int>mark = { 59,85,73,79,92,84 };
	std::vector<std::string>name = { "小红","小张","小李","小明","小雪","小王" };
	std::cout << "total=" << total(mark) << "\n";
	std::cout << "92 name=" << findname(mark, name, 92) << "\n";
	std::cout << "60 name=" << findname(mark, name, 60) << "\n";
	print_(mark);
	addone(mark);
	print_(mark);
	int max_ = 0;
	int min_ = 0;
	std::string maxname;
	std::string minname;
	minmax_(mark, name, max_, min_, maxname, minname);
	std::cout << "max=" << max_ << "  min_" << min_ << "  maxname=" << maxname << "  minname=" << minname << "\n";
	int threshold = 60;
	auto n = findfirstabove(mark, threshold);
	if (n == mark.end()) {
		std::cout << "None" << "\n";
	}
	else {
		std::cout << "firstabove= " << *n << "\n";
	}
	return 0;
}