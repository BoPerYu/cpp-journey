#include<iostream>
#include<vector>
#include<windows.h>
int maxOf(int c, int d) {
	if (c > d) {
		return c;
	}
	else if (c < d) {
		return d;
	}
	else {
		return c;
	}
};
int main() {
	SetConsoleOutputCP(CP_UTF8);   // 需要 #include <windows.h>
	std::cout << "请输入两个数，我会输出他们的和"  ;
	int a;
	int b;
	std::cin >> a >> b;
	std::cout << a + b;
	int t;
	std::cout << "Please input a number in 0 to 100, I'll rank it.";
	std::cin >> t;
	if (t < 0 || t>100) {
		std::cout << "请重新输入";
	}
	else if (t < 60) {
		std::cout << "不及格";
	}
	else if (t >= 60 && t < 80) {
		std::cout << "及格";
	}
	else if (t >= 80 && t < 90) {
		std::cout << "良好";
	}
	else {
		std::cout << "优秀";
	}
	int i;
	int m = 0;
	for (int i = 1;i <=100;i++) {
		m += i;
	}
	std::cout << "The sum of 1~100 =" << m;
	int e = 1;
	while (e <= 9) {
		std::cout << "9 * " << e << "=" << 9 * e;
		e += 1;
	}
	std::cout << "Please input two numbers";
	int x, y,z;
	std::cin >> x >> y;
	z = maxOf(x, y);
	std::cout << "The bigger number is " << z;

	return 0;
}

