// ============================================================================
// ref01 · 讲义配套参考程序（助手写，不是你的练习）
// ============================================================================
// 这个文件把 W4D1 讲义里出现的**每一个用法**跑一遍。你不必自己敲它——
// 直接跑、看输出、愿意的话在调试器里单步走，比读文档快。
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\ref01_string_vector_api.exe
//
// 注意：这里**不涉及**"sizeof / 扩容因子 / 越界 / 深浅拷贝"这些误区——
//       那些是你 5 个探针（p01~p05）的活，别在这儿提前看答案。
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

// —— 讲义 1.8 / 2.8：传参为什么用 const 引用 ——
// 加 &  = 不拷贝（直接看原来那个对象）
// 加 const = 只读，函数里改不了它
void print_string(const std::string& s) {
    std::cout << "  [print_string] 收到 \"" << s << "\"，size=" << s.size() << "\n";
}

void print_vector(const std::vector<int>& v) {
    std::cout << "  [print_vector] size=" << v.size() << "，内容:";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << " " << v[i];
    }
    std::cout << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== 1. std::string 的六种初始化 ==========\n";
    std::string s1;                  // 空串
    std::string s2 = "abc";          // 拷贝初始化
    std::string s3{"abc"};           // 列表初始化
    std::string s4(5, 'x');          // 5 个 'x'      ← () 问的是"几个"
    std::string s5("abcde", 2);      // 取前 2 个字符
    std::string s6{s2};              // 从另一个 string 拷贝
    std::cout << "s1 (空)             = [" << s1 << "]   size=" << s1.size() << "\n";
    std::cout << "s2 = \"abc\"          = [" << s2 << "]\n";
    std::cout << "s3 {\"abc\"}           = [" << s3 << "]\n";
    std::cout << "s4 (5, 'x')         = [" << s4 << "]\n";
    std::cout << "s5 (\"abcde\", 2)     = [" << s5 << "]\n";
    std::cout << "s6 {s2}             = [" << s6 << "]\n";

    std::cout << "\n========== 2. 长度 / 判空 / 取字符 ==========\n";
    std::cout << "s2.size()   = " << s2.size()   << "   s2.length() = " << s2.length() << "\n";
    std::cout << "s1.empty()  = " << s1.empty()  << "   s2.empty()  = " << s2.empty() << "\n";
    std::cout << "s2[0]=" << s2[0] << "   s2.at(1)=" << s2.at(1)
              << "   s2.front()=" << s2.front() << "   s2.back()=" << s2.back() << "\n";

    std::cout << "\n========== 3. 改内容 ==========\n";
    std::string t = "hello";
    t += " world";                   // 追加（原地改）
    std::cout << "t += \" world\"   -> " << t << "\n";
    t = t + "!";                     // 拼接（产生一个新串再赋值回去）
    std::cout << "t = t + \"!\"     -> " << t << "\n";
    t[0] = 'H';                      // 改一个字符
    std::cout << "t[0] = 'H'       -> " << t << "\n";

    std::cout << "\n========== 4. 子串 / 查找 / 比较 ==========\n";
    std::cout << "t.substr(0, 5)    = [" << t.substr(0, 5) << "]\n";
    std::cout << "t.substr(6)       = [" << t.substr(6) << "]\n";
    std::cout << "t.find(\"world\")   = " << t.find("world") << "\n";
    std::cout << "t.find(\"zzz\")     = " << t.find("zzz")
              << "   （== npos? " << (t.find("zzz") == std::string::npos) << "）\n";
    std::cout << "std::string::npos = " << std::string::npos << "\n";
    std::string a = "apple", b = "banana";
    std::cout << "(a < b) = " << (a < b) << "   (a == a) = " << (a == a)
              << "   (a == \"apple\") = " << (a == "apple") << "\n";

    std::cout << "\n========== 5. 遍历一个 string（两种写法）==========\n";
    std::cout << "下标循环   : ";
    for (std::size_t i = 0; i < t.size(); ++i) {
        std::cout << t[i];
    }
    std::cout << "\nrange-for  : ";
    for (char c : t) {                       // c 是每个字符的**拷贝**
        std::cout << c;
    }
    std::cout << "\nrange-for 用引用改元素 : ";
    for (char& c : t) {                      // & 才是"改得动原件"
        if (c == 'l') { c = 'L'; }
    }
    std::cout << t << "\n";

    std::cout << "\n========== 6. 和 C 风格字符串互转 ==========\n";
    const char* p = t.c_str();               // 只读的 char*
    std::cout << "t.c_str() 的前 5 个字符 = ";
    for (int i = 0; i < 5; ++i) { std::cout << p[i]; }
    std::cout << "\n（注意：c_str() 给的是 const char*，只能读不能改）\n";

    std::cout << "\n========== 7. string 传参：const 引用 ==========\n";
    print_string(t);

    std::cout << "\n========== 8. std::vector 的五种初始化 ==========\n";
    std::vector<int> v1;              // 空
    std::vector<int> v2(3);           // 3 个 0        ← () 问"几个"
    std::vector<int> v3(3, 7);        // 3 个 7
    std::vector<int> v4{1, 2, 3};     // 这几个值      ← {} 给"这些值"
    std::vector<int> v5(v4);          // 从另一个 vector 拷贝
    std::cout << "v1 (空)     size=" << v1.size() << "\n";
    std::cout << "v2 (3)      "; print_vector(v2);
    std::cout << "v3 (3, 7)   "; print_vector(v3);
    std::cout << "v4 {1,2,3}  "; print_vector(v4);
    std::cout << "v5 (v4)     "; print_vector(v5);

    std::cout << "\n========== 9. 加 / 删 / 看首尾 ==========\n";
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    std::cout << "push_back 三次   "; print_vector(v);
    std::cout << "front()=" << v.front() << "  back()=" << v.back()
              << "  size()=" << v.size() << "  capacity()=" << v.capacity() << "\n";
    v.pop_back();
    std::cout << "pop_back 一次    "; print_vector(v);
    v.insert(v.begin() + 1, 99);             // 在下标 1 的位置【前】插入 99
    std::cout << "insert(begin+1, 99) "; print_vector(v);
    v.erase(v.begin() + 1);                  // 删掉下标 1
    std::cout << "erase(begin+1)   "; print_vector(v);
    std::cout << "v.empty() = " << v.empty() << "\n";
    v.clear();
    std::cout << "clear() 之后 size=" << v.size() << "  capacity=" << v.capacity() << "\n";

    std::cout << "\n========== 10. reserve 和 data() ==========\n";
    std::vector<int> r;
    r.reserve(100);                          // 先把内存要够，size 还是 0
    std::cout << "reserve(100) 后 size=" << r.size() << "  capacity=" << r.capacity() << "\n";
    r.push_back(1);
    std::cout << "push_back(1) 后 size=" << r.size() << "  capacity=" << r.capacity() << "\n";
    std::cout << "r.data() = " << static_cast<const void*>(r.data())
              << "   *r.data() = " << *r.data() << "\n";

    std::cout << "\n========== 11. 嵌套：vector<string> —— 检索项目的形状 ==========\n";
    std::vector<std::string> words{"文本", "检索", "项目"};
    std::cout << "words.size() = " << words.size() << "\n";
    for (const std::string& w : words) {
        std::cout << "  [" << w << "]  size()=" << w.size() << "\n";
    }
    std::cout << "（注意上面 size() 打出来的数：中文一个字在这台机器上占几个字节？）\n";

    std::cout << "\n========== 12. vector 传参：const 引用 ==========\n";
    print_vector(v4);

    return 0;
}
