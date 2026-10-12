#include <iostream>
#include <vector>

#include "stats.h"

int main() {
    std::vector<int> scores{ 85, 92, 78, 96 };
    std::cout<<"sum(scores)="<<sum(scores)<<std::endl;
    std::cout<<"average(scores)="<<average(scores)<<std::endl;
    // 你写：用 std::cout 把 sum(scores) 和 average(scores) 打印出来

    return 0;
}