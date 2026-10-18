// ============================================================================
// 探针 6 · p06_split：把一句话切成词（今天的主程序）
// ============================================================================
// 讲义：打卡训练\W4\W4D2_C++_string切词与vector传参返回.md（第一、二节）
// 骨架是助手写好的（自检器、打印函数都写好了），你只写 split 的函数体。
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\p06_split.exe
//
// ⚠️ 你还没写函数体的时候，编译会报两条 C4100「未引用的参数」（s 和 delim）。
//    那不是错，是 /W4 在提醒"这两个参数你还没用上"。函数体写完之后它们会自己消失。
//    —— 顺便认识一条：编译器警告也可以是"待办清单"。
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>

// ---------------------------------------------------------------------------
// 要你写的函数：按 delim 把 s 切开，返回所有【非空】片段
//   例：split("the quick brown fox", ' ') -> {"the","quick","brown","fox"}
//       split("a,,b", ',')                -> {"a","b"}     （空片段跳过）
//       split("  hi  ", ' ')              -> {"hi"}        （空片段跳过）
//       split("", ' ')                    -> {}            （空串）
//
// 骨架提示（讲义 1.3 那张表就是它的展开，正文里还有两个"差一格"的坑）：
//   1) 准备一个结果 vector，一个 std::size_t start = 0;
//   2) 循环里先找下一个分隔符：std::size_t pos = s.find(delim, start);
//   3) pos != npos  -> 这一段的长度是 pos - start，取出来；如果是空的就别收；
//                      start 跳到 pos + 1（跳过分隔符本身），继续循环
//   4) pos == npos  -> 把【最后一段】收进去（也是空的就别收），然后收工
// ---------------------------------------------------------------------------
std::vector<std::string> split(const std::string& s, char delim) {
    // TODO：函数体你写
    std::vector<std::string> answer;
    std::size_t start = 0;
    std::size_t pos = s.find(delim, start);
    while (pos != std::string::npos) {
        if (pos - start != 0) {  //我没理清为什么会发生写入空片段，因为没有考虑到pos-start=0也会写入内容这一点
            answer.push_back(s.substr(start, pos - start));
        }
        start = pos + 1;
        pos= s.find(delim, start);
    }
    if (start<s.size()) {
        answer.push_back(s.substr(start));
    }
    return answer;
}


// ================== 自检（这一段不要改） ==================
int g_pass = 0;
int g_total = 0;

void show(const std::vector<std::string>& v) {
    std::cout << "{";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << "\"" << v[i] << "\"" << (i + 1 < v.size() ? ", " : "");
    }
    std::cout << "}\n";
}

void check(const std::string& name, const std::vector<std::string>& want,
           std::function<std::vector<std::string>()> fn) {
    ++g_total;
    std::cout << "[" << name << "]\n";
    try {
        const std::vector<std::string> got = fn();
        const bool ok = (got == want);
        if (ok) { ++g_pass; }
        std::cout << (ok ? "  [OK  ] 得到 " : "  [FAIL] 得到 ");
        show(got);
        if (!ok) {
            std::cout << "         期望   ";
            show(want);
        }
    } catch (const std::exception& e) {
        std::cout << "  [FAIL] 抛异常 " << typeid(e).name() << ": " << e.what() << "\n";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    check("1. 一句话按空格切（应该 4 个词）",
          {"the", "quick", "brown", "fox"},
          [] { return split("the quick brown fox", ' '); });

    check("2. 连续分隔符（空片段要跳过）",
          {"a", "b"},
          [] { return split("a,,b", ','); });

    check("3. 两头都有空格（空片段要跳过）",
          {"hi"},
          [] { return split("  hi  ", ' '); });

    check("4. 空串（应该 0 个词）",
          {},
          [] { return split("", ' '); });

    std::cout << "\n" << g_pass << "/" << g_total << " 通过"
              << (g_pass == g_total ? "  ← 全对\n" : "  ← 还没写完/写错了\n");
    return 0;
}
