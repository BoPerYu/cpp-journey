#include "stats.h"
int sum(const std::vector<int>& v) {
	int total = 0;
	for (int num : v) {
		total += num;
	}
	return total;
	// 你写：先定义一个整数变量存总和，初始为 0
	//       再用一个循环，把 v 里每个数加到它上面
	//       最后把它 return 出去
}
double average(const std::vector<int>& v) {
	int num = sum(v);
	return  static_cast<double>(num) / v.size();
	// 你写：总和 ÷ 个数
	//       这里有个坑，见下面
}