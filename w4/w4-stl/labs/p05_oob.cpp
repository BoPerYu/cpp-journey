// ============================================================================
// 探针 5 · p05_oob
// 问题：越界读 v[3]，谁会发现？是标准库？是编译器？还是 ASan？还是谁都发现不了？
// 讲义：打卡训练\W4\W4D1_C++_string与vector.md（第 5 节）
// ----------------------------------------------------------------------------
// ⚠️ 这个探针要跑**两遍**，因为 ① 会让程序当场终止，② 就再也跑不到了：
//     第 1 遍：只留 ①，把 ② 的代码注释掉 → 跑 → 记结果
//     第 2 遍：把 ① 的代码注释掉，只留 ② → 跑 → 记结果
//   两遍的输出都抄进讲义第 6 节证据表（分两行）。
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p05_oob.exe
// ============================================================================

#include <iostream>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "== ① 容量恰好等于 size 时，读 v[3] ==\n";
    // TODO 1  建 std::vector<int> v{1, 2, 3};
    //         打印 v.size() 和 v.capacity()（先看清楚"容量有没有富余"）
    // TODO 2  读 v[3] 并打印它
    //std::vector<int> v{ 1, 2, 3 };
    //std::cout << "v.size()=" << v.size() << "  v.capacity()=" << v.capacity() << "\n";
    //std::cout << "v[3]=" << v[3] << "\n";

    //std::cout << "（如果程序在上面那一行直接终止了，那你就已经看到答案了）\n";

    std::cout << "\n== ② 容量大于 size 时，读 w[3] ==\n";
    // TODO 3  建 std::vector<int> w;
    //         先 push_back 五个数（把容量撑大），
    //         再 pop_back 两次，让 size 回到 3；
    //         打印 w.size() 和 w.capacity()，确认"容量大于 size"。
    // TODO 4  读 w[3] 并打印它
    std::vector<int> w;
    for (int i = 0;i < 5;i++) {
        w.push_back(i * 10);
    }
    w.pop_back();
    w.pop_back();
    std::cout << "w.size()=" << w.size() << "  w.capacity()=" << w.capacity() << "\n";
    std::cout << "w[3]=" << w[3] << "\n";
    std::cout << "\n== ③ 我的结论 ==\n";
    // TODO 5  两次读的是"同一个位置"吗？为什么一次被发现、一次没有？
    //         这和你的薄弱点第 5 条（"工具不报 ≠ 没错"）是什么关系？

    return 0;
}
