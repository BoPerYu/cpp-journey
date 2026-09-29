// ============================================================
// W2 内存实验台 · 第四类：内存泄漏（2026-09-29）
// 为什么单独一个文件：**MSVC 的 ASan 不查内存泄漏**。
// 实测报错原文：detect_leaks is not supported on this platform
// 所以查泄漏要走 CRT 调试堆 _CrtDumpMemoryLeaks()，而 CRT 调试堆和 ASan
// 抢同一个分配器，两者不能同时开 —— 这个目标在 CMakeLists 里故意不加 ASan。
// 而且它**只在 Debug 下有效**（Release 里 _CrtDumpMemoryLeaks 是空实现）。
//
// 用法（在 build 目录下）：
//   leak_lab      -> 正确版：申请了就还，报告应该只有 0 个块
//   leak_lab 1    -> 故意泄漏一个 int，报告应该点名 1 个块
// ============================================================
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <windows.h>

// 让泄漏报告点名"哪个文件、哪一行漏的"。
// 光有 _CRTDBG_MAP_ALLOC 还不够：它管的是 malloc/free，
// new 要自己在 Debug 下换成带文件名和行号的版本，报告里才会带 (file, line)。
#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

static void leakSomething() {
    int* p = DBG_NEW int(42);       // 申请了
    std::cout << "故意泄漏一个 int，值是 " << *p << "\n";
    // 到这里就结束了：没有 delete p —— 这就是泄漏
}

static void correct() {
    int* p = DBG_NEW int(42);
    std::cout << "正确：申请了 " << *p << "，也还回去了\n";
    delete p;
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    // 把 CRT 的警告报告改到标准错误，这样控制台里就能直接看到泄漏块
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    if (argc > 1 && argv[1][0] == '1') {
        leakSomething();
    } else {
        correct();
    }

    _CrtDumpMemoryLeaks();          // 程序结束前自查：还有哪块内存没还
    std::cout << "程序结束\n";
    return 0;
}
