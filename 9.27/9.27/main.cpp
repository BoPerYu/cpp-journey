#include<iostream>
#include<vector>
#include<Windows.h>
int  totalByPtr(const int* data, int n) {
	int total = 0;
	for (int i = 0;i < n;i++) {
		total += data[i];
	}
	return total;
}                      // 求和
void addOne(int* data, int n) {
	for (int i = 0;i < n;i++) {
		data[i] += 1;
	}
}                                // 就地把每个元素 +1
void minMaxByPtr(const int* data, int n, int* lo, int* hi) {
	if (n == 0) {
		std::cout << "出错，为空容器。" << "\n";
	}
	else {
		*lo = data[0];
		*hi = data[0];
		for (int i = 0;i < n;i++) {
			if(*lo > data[i]) {
				*lo = data[i];
			}
			if (*hi< data[i]) {
				*hi= data[i];
			}
		}
	}
}   // 用指针把最小/最大带出去
void print(const int* data, int n) {
	for (int i = 0;i < n;i++) {
		std::cout << data[i] << "  ";
	}
	std::cout << std::endl;
}
int* findFirstAbove(int* data, int n, int threshold) {
	for (int i = 0;i < n;i++) {
		if (data[i] > threshold) {
			int* t = &data[i];
			return t;
		}
	}
	return nullptr;
}         // 找不到返回 nullptr
int main() {
	SetConsoleOutputCP(CP_UTF8);
	std::vector<int>scores{ 88,90,69,77,73,93,58,80 };
	int*m = scores.data();
	int n = static_cast<int>(scores.size());
	std::cout << "总和为" << totalByPtr(m, n) << "\n";
	addOne(m, n);
	print(m, n);
	int lo = 0;
	int hi = 0;
	minMaxByPtr(m, n, &lo, &hi);
	std::cout << "Max=" << hi << "  Min=" << lo << "\n";	
	int* result =findFirstAbove(m, n, 90);
	if (result == nullptr) {
		std::cout << "报错，为空容器" << "\n";
	}
	else {
		int answer = *result;
		std::cout << answer;
	}
}