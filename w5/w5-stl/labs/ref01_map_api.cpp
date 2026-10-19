// ============================================================================
// ref01 · map / unordered_map 基础 API 参考程序（助手写，不是练习答案）
// 注意：operator[] 的插入坑、insert 冲突、遍历中删除，
//       故意留给 p01~p04 探针，不在这个参考程序里提前给答案。
// ============================================================================

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== 1. map：按 key 有序 ==========\n";
    std::map<std::string, int> ordered;
    ordered["banana"] = 1;
    ordered["apple"] = 2;
    ordered["cherry"] = 3;
    for (const auto& [word, count] : ordered) {
        std::cout << word << ":" << count << "\n";
    }

    std::cout << "\n========== 2. unordered_map：迭代顺序不保证 ==========\n";
    std::unordered_map<std::string, int> hashed;
    hashed["banana"] = 1;
    hashed["apple"] = 2;
    hashed["cherry"] = 3;
    for (const auto& [word, count] : hashed) {
        std::cout << word << ":" << count << "\n";
    }
    std::cout << "bucket_count=" << hashed.bucket_count()
              << " load_factor=" << hashed.load_factor() << "\n";
    std::cout << "（这里的顺序是实现相关的，不要拿它和 map 的顺序做稳定比较）\n";

    std::cout << "\n========== 3. 三种基础插入方式 ==========\n";
    std::map<std::string, int> t;
    t["apple"] = 2;                 // 用 operator[] 写入
    t.emplace("banana", 1);         // 直接构造一个 pair
    t.insert({"cherry", 3});        // 插入一个 pair
    for (const auto& [word, count] : t) {
        std::cout << word << ":" << count << "\n";
    }

    std::cout << "\n========== 4. 查找已存在的 key ==========\n";
    auto it = t.find("apple");
    if (it != t.end()) {
        std::cout << "found " << it->first << " -> " << it->second << "\n";
    }
    std::cout << "count(\"banana\")=" << t.count("banana") << "\n";
    std::cout << "at(\"cherry\")=" << t.at("cherry") << "\n";

    std::cout << "\n========== 5. 遍历时用结构化绑定 ==========\n";
    for (const auto& [word, count] : t) {
        std::cout << "[" << word << "] = " << count << "\n";
    }

    return 0;
}
