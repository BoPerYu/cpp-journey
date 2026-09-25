#include<iostream>
#include<vector>
#include<windows.h>
void print(int* p) {
	if (p == nullptr) {
		std::cout << "It's empty. So I won't use it." << std::endl;
	}
	else {
		std::cout << static_cast<const void*>(p) << std::endl;
	}
}

int suma(const std::vector<int>& scores) {
	int t = 0;
	for (int i = 0;i <static_cast<int>(scores.size());++i) {
		t += scores[i];
	}
	return t;
}
int sumb(const std::vector<int>& scores) {
	int t = 0;
	for (int x : scores) {
		x += 1;
		t += x;
	}
	return t;
}
void plus(std::vector<int>& scores) {
	for (int& x : scores) {
		x++;
	}
}
int total(const std::vector<int>& v) {
	int t = 0;
	for (int x : v) {
		t += x;
	}
	return t;
}
void addOne(std::vector<int>& v) {
	for (int& x : v) {
		x += 1;
	}
}
void setToZeroByPtr(int* p) { *p = 0; }       // 用指针，把调用方的变量变成 0
void setToZeroByRef(int& r) { r = 0; }        // 用引用，做同一件事
int* findMax(std::vector<int>& v) {
	if (v.empty()) {
		return nullptr;           // 空容器没有"最大值的地址"可给，这句先给你
	}
	int* best = &v[0];   // ① 先假设第 0 个元素最大，把它"的地址"记下来（提示：&v[0]）
	for (std::size_t i = 1; i < v.size(); ++i) {   // 从第 1 个开始比（第 0 个已经记下了）
		if (v[i]>= *best) {     // ② 比"目前为止最大的那个元素"大吗？（提示：比的是 *best）
			best = &v[i];// ③ 是的话，把 best 改记当前这个元素的地址
		}
	}
	return best;
}
void printAll(const std::vector<int>& v) {
	for (int x : v) {
		std::cout << x << " ";      // 每个元素后面跟一个空格当分隔
	}
	std::cout << "\n";              // 整个列表打完再换行
}
int main() {
	std::vector<int> scores{ 99, 92, 82, 71, 84, 56, 78, 66 };
	std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	int a = 10086;
	int* p = &a;
	SetConsoleOutputCP(CP_UTF8);
	int* q = nullptr;
	std::cout << "你好，指针。"<<std::endl;
	std::cout << suma(scores) <<"\n"<< sumb(scores) << std::endl;
	plus(scores);

	std::cout << total(v) << "\n";
	addOne(v);
	std::cout << total(v) << "\n";
	print(p);
	print(q);
	printAll(scores);
	setToZeroByPtr(p);setToZeroByRef(*p);findMax(v);
}