#include<iostream>
#include<vector>
#include<windows.h>
std::vector<int> data{ 4,7,2,9,1,5,3 };
void maxof(const std::vector<int>& data, int* result) {
    *result = data[0];
    for (std::size_t i = 1; i < data.size(); ++i) {
        if (data[i] > *result) {
            *result = data[i];
        }
    }
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::vector<int> v{ 3, 9, 5 };
    int best = 0;
    maxof(v, &best);                            // 把 best 的地址传进去
    std::cout << "最大值 = " << best << "\n";    // 实测输出：最大值 = 9
    int k = 5;
    int* w = &k;
    int* z = w;
    return 0;
}