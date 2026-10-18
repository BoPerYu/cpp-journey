// ============================================================================
// ref04 · "传参 / 返回到底拷了几次"测量台（助手写的参考程序，不是练习）
// ============================================================================
// 今天要回答：为什么"传 vector 不加 & 就慢"，而"返回 vector 却不慢"？
//
// 用两把尺子量（这是关键——只用一把会得出错误结论）：
//   尺子 1（Track 计数器）：【元素】层面的拷贝 / 移动各几次
//   尺子 2（缓冲区地址）：vector 内部那块内存在哪 —— 用来判断"有没有重新分配"
//
// ⚠️ 为什么要两把：std::vector 的"移动"是**搬 3 个指针**（O(1)），
//    元素一个都不碰 —— 所以尺子 1 在"移动"那里永远读到 0。只拿尺子 1 看，
//    会得出"根本没发生移动"的错误结论（助手第一版就是这么错到沟里的）。
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下）：
//     cmake --build build --config Debug --parallel
//     .\build\Debug\ref04_pass_return_cost.exe
// ============================================================================

#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>
#include <windows.h>

// ---------- 尺子 1：会数数的元素类型 ----------
struct Track {
    static long long copies;
    static long long moves;
    int id = 0;

    explicit Track(int i = 0) : id(i) {}                            // 普通构造：不计数
    Track(const Track& o) : id(o.id) { ++copies; }                  // 拷贝构造
    Track(Track&& o) noexcept : id(o.id) { ++moves; }               // 移动构造
    Track& operator=(const Track& o) { id = o.id; ++copies; return *this; }
    Track& operator=(Track&& o) noexcept { id = o.id; ++moves; return *this; }
};
long long Track::copies = 0;
long long Track::moves = 0;

void reset() { Track::copies = 0; Track::moves = 0; }
void report(const char* label) {
    std::cout << "    元素：拷贝 " << Track::copies << " 次，移动 " << Track::moves
              << " 次      ← " << label << "\n";
    reset();
}

// 建一个 n 个元素的 vector（reserve + emplace_back，保证"建"的过程本身不拷贝元素）
std::vector<Track> build(int n) {
    std::vector<Track> v;
    v.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        v.emplace_back(i);
    }
    return v;
}

// ---------- 尺子 2：记录"函数内部那块缓冲区"的地址 ----------
const void* g_inner_buffer = nullptr;
const void* g_inner_n = nullptr;

std::vector<Track> build_and_return(int n) {
    std::vector<Track> v = build(n);
    g_inner_buffer = v.data();          // 记下函数内部这块内存的地址
    return v;
}

// ---------- 被测量的三种传参 ----------
void take_by_value(std::vector<Track> v) {
    std::cout << "    （函数里收到 " << v.size() << " 个元素）\n";
}
void take_by_cref(const std::vector<Track>& v) {
    std::cout << "    （函数里收到 " << v.size() << " 个元素）\n";
}
void take_by_ref(std::vector<Track>& v) {
    v.emplace_back(-1);                 // 引用：能改到原件
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== A. 尺子 1：元素层面谁在被逐个复制 ==========\n";

    reset();
    std::vector<Track> src = build(5);
    report("build(5)");

    reset(); take_by_value(src);   report("按值传参   take_by_value(src)");
    reset(); take_by_cref(src);    report("const&    take_by_cref(src)");
    reset(); take_by_ref(src);     report("引用&     take_by_ref(src)（函数里 push 了一个）");
    std::cout << "    src.size() 现在是 " << src.size() << " —— 引用传参确实改到了原件\n";

    reset();
    std::vector<Track> a = build_and_return(5);
    report("建一个 vector 再 return（a 拿到结果那一步）");

    reset();
    std::vector<Track> c;
    c = src;
    report("c = src              （拷贝赋值）");

    reset();
    std::vector<Track> d;
    d = std::move(src);
    report("d = std::move(src)    （移动赋值）");
    std::cout << "    src.size() 现在是 " << src.size() << " —— 被搬空了\n";

    std::cout << "\n========== B. 尺子 2：那块内存在哪 ==========\n";
    reset();
    std::vector<Track> e = build_and_return(5);
    reset();
    std::cout << "    函数内部的缓冲区地址   = " << g_inner_buffer << "\n";
    std::cout << "    返回之后拿到的缓冲区地址 = " << static_cast<const void*>(e.data()) << "\n";
    std::cout << "    " << (g_inner_buffer == static_cast<const void*>(e.data())
                               ? "→ 同一个地址：元素没有被搬去新地方"
                               : "→ 地址不同：元素被搬到了新缓冲区") << "\n";

    std::cout << "\n========== C. 那元素什么时候真的会被移动？==========\n";
    reset();
    std::vector<Track> v;
    v.reserve(10);
    for (int i = 0; i < 5; ++i) { v.emplace_back(i); }
    reset();
    v.insert(v.begin(), Track(-1));       // 在【开头】插一个：后面 5 个都得往后挪
    report("v.insert(v.begin(), ...)   中间插入");

    reset();
    std::vector<Track> w;
    w.reserve(2);
    w.emplace_back(0);
    w.emplace_back(1);
    reset();
    w.push_back(Track(2));                // 容量只有 2，撑破 → 重新分配，老元素被搬走
    report("w.push_back(...) 撑破容量  扩容");

    return 0;
}
