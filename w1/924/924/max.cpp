#include<iostream>
#include<vector>
#include<windows.h>
bool maxof(const std::vector<int>& data, int* result) {
	if (data.empty()) {
		return false;               // 第一步就挡掉，后面可以放心用 data[0]
	}
	*result = data[0];
	for (std::size_t i = 1; i < data.size(); ++i) {
		if (data[i] > *result) {
			*result = data[i];
		}
	}
	return true;
}
void show(std::vector<int>& v) { std::cout << "可改版" << "\n"; }         // 函数体里打印一句"【可改版】"
void show(const std::vector<int>& v) { std::cout << "只读版" << "\n"; }   // 函数体里打印一句"【只读版】"
void f1(int* p) {        // 顶层 const
	p = nullptr;               // 试着改"指针自己"
}
void f2(int* p) {        // 底层 const
	*p = 5;                    // 试着改"指向的那个值"
}
const int* findFirstAbove(const std::vector<int>& data, int threshold) {
	if (data.empty()) {
		std::cout << "data为空。" << "\n";
		return nullptr;
	}
	else {
		const int* x = 0;
		for (int i = 0;i < static_cast<int>(data.size());i++) {
			const int* x = &data[i];
			if (*x > threshold) {
				break;
			}
		}
		return x;
	}
}
bool minMax(const std::vector<int>& data, int* lo, int* hi) {
	* lo = data[0];
	* hi = data[0];
	for (int i = 0;i < static_cast<int>(data.size());i++) {
		if (lo == nullptr || hi == nullptr) {
			return false;
			break;
		}
		else {
			if (*lo < data[i]) {
				*lo = data[i];
			}
			if (*hi > data[i]) {
				*hi = data[i];
			}
			return true;
		}
	}
}
int main() {
	SetConsoleOutputCP(CP_UTF8);
	std::vector<int> a{ 1, 2, 3 };            // 非 const 的 vector
	std::vector<int> data{ 80,82,67,77,94,79 };
	int threshold = 90;
	const std::vector<int> b{ 1, 2, 3 };      // const 的 vector
	show(a);
	show(b);
	show({ 1, 2, 3 });                        // 临时对象
	const int* p = findFirstAbove(data, threshold);
	if (p != nullptr) {
		std::cout << "第一个大于 " << threshold << " 的是 " << *p << "\n";
	}
	else {
		std::cout << "没找到\n";
	}
	int lo = 0;
	int hi = 0;
	bool maxof(std::vector<int>data, int* p);
	if (minMax (data,&lo,&hi)){
		std::cout << lo << "\n" << hi << "\n";
	}
}
