// ============================================================================
// 探针 7 · set vs unordered_set：顺序和查找
// ============================================================================

#include <iostream>
#include <set>
#include<vector>
#include <string>
#include <unordered_set>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::set<std::string> ordered;
    std::unordered_set<std::string> hashed;

    // TODO 1：用同一组词填满两个容器：
    //         "delta", "alpha", "charlie", "bravo", "echo"
    //         打印两者的 size() 和遍历结果。
    std::vector<std::string> a = { "delta","alpha","charlie","bravo","echo"};
    for (std::size_t i = 0;i < a.size();i++) {
        ordered.insert(a[i]);
        hashed.insert(a[i]);
    }
    for (auto it = ordered.begin();it != ordered.end();it++) {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;
    for (auto it =hashed .begin();it != hashed.end();it++) {
        std::cout << *it << "  ";
    }
    std::cout << "ordered.size = " << ordered.size() << "\n";
    std::cout << "hashed.size = " << hashed.size() << "\n";
    // TODO 2：打印 hashed.bucket_count() 和 hashed.load_factor()。
    std::cout << "hashed.bucket_count() = " << hashed.bucket_count()<<"hashed.load_factor() = " << hashed.load_factor() << "\n";
    // TODO 3：用注释回答：
    //         只做“去重 + 判断在不在”，选哪个？unordered_set
    //         要求“按字典序输出全部词”，选哪个？set
    //         两者的查找复杂度分别是什么？unordered_set:平均O(1)，最坏O(n);set:O(log n)

    return 0;
}
