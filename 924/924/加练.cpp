#include<iostream>
#include<vector>
#include<windows.h>
void show(std::vector<int>& v) { std::cout << "可改版" << "\n"; }         // 函数体里打印一句"【可改版】"
void show(const std::vector<int>& v) { std::cout << "只读版" << "\n"; }   // 函数体里打印一句"【只读版】"
void f1(int* p) {        // 顶层 const
	p = nullptr;               // 试着改"指针自己"
}
void f2(int* p) {        // 底层 const
	*p = 5;                    // 试着改"指向的那个值"
}
const int* findFirstAbove(const std::vector<int>& data, int threshold) {
	for (int i=0;i < static_cast<int>(data.size());i++) {
		const int* x = &data[i];
		if (x==nullptr) {
			std::cout << "列表为空" << std::endl;
		}
		else {
			if (*x > threshold) {
				return x;
				break;
			}
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
	std::cout << findFirstAbove(data, threshold);
}