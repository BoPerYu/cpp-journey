#include <iostream>
#include <vector>
#include <windows.h>
#include <string>

std::vector<int> scores{ 99,92,82,71,84,56,78,66 };
// 1) 返回所有分数的总和
int total(const std::vector<int>& scores) {
	int t = 0;
	for (int x : scores) {
		t += x;
	}
	return t;
}

// 2) 往分数列表末尾加一个分数
void addScore(std::vector<int>& scores, int s) {
	scores.push_back(s);
}

// 3) 交换两个整数的值
void swapValues(int& a, int& b) {
	int t;
	t = a;
	a = b;
	b = t;
}

// 4) 根据分数返回等级字符串（"优秀" "良好"…）
std::string rankOf(const int score) {
	if (score < 60) {
		return "不及格";
	}
	else {
		return "及格";
	}
}

// 5) 把列表里每个分数都加 1 分，直接改原列表
void curve(std::vector<int>& scores) {
	for (int& x : scores) {
		x += 1;
	}
}

// 6) 找出列表里的最大值和最小值，并把它们"带出去"
void minMax(const std::vector<int>& scores, int& lo, int& hi) {
	lo = scores[0];
	hi = scores[0];
	for (int x : scores) {
		if (x < lo){ lo = x; }
		if (x > hi) { hi = x; }
	}
}
int main() {
	SetConsoleOutputCP(CP_UTF8);
	int lo;
	int hi;
	int a = 1;
	int b = 5;
	addScore(scores, 90);
	swapValues(a, b);
	minMax(scores, lo, hi);
	curve(scores);
	std::cout << total(scores)<<"\n" << a <<"\n" << b <<"\n" << rankOf(61) << std::endl;
	std::cout << lo <<"\n"<< hi;
}