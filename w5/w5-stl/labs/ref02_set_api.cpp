// ============================================================================
// ref02 · set / unordered_set 基础 API 参考程序（助手写，不是练习答案）
// 注意：重复插入、遍历删除、range 查找的细节留给 p06~p09 探针。
// ============================================================================

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== 1. set：唯一 + 按 key 有序 ==========\n";
    std::set<std::string> ordered{"banana", "apple", "cherry"};
    ordered.insert("apple");
    std::cout << "size=" << ordered.size() << "\n";
    for (const std::string& word : ordered) {
        std::cout << word << "\n";
    }

    std::cout << "\n========== 2. insert 的返回值 ==========\n";
    auto result = ordered.insert("apple");
    std::cout << "insert existing: inserted=" << result.second
              << " value=" << *result.first << "\n";

    std::cout << "\n========== 3. 查找：find / count ==========\n";
    auto it = ordered.find("banana");
    if (it != ordered.end()) {
        std::cout << "found " << *it << "\n";
    }
    std::cout << "count(apple)=" << ordered.count("apple")
              << " count(zoo)=" << ordered.count("zoo") << "\n";

    std::cout << "\n========== 4. lower_bound / upper_bound ==========\n";
    auto lower = ordered.lower_bound("b");
    auto upper = ordered.upper_bound("b");
    std::cout << "lower_bound(\"b\") = "
              << (lower == ordered.end() ? "<end>" : *lower) << "\n";
    std::cout << "upper_bound(\"b\") = "
              << (upper == ordered.end() ? "<end>" : *upper) << "\n";

    std::cout << "\n========== 5. unordered_set：唯一 + 顺序不保证 ==========\n";
    std::unordered_set<std::string> hashed{"banana", "apple", "cherry"};
    hashed.insert("apple");
    std::cout << "size=" << hashed.size()
              << " bucket_count=" << hashed.bucket_count() << "\n";
    for (const std::string& word : hashed) {
        std::cout << word << "\n";
    }
    std::cout << "（顺序是实现相关的，不要依赖）\n";

    return 0;
}
