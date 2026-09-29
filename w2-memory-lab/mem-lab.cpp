// ============================================================
// W2 内存实验台（2026-09-29）
// 用途：把三种"堆内存写错"各看一遍，读懂 ASan 报告。
// 这是探针，不是作业 —— 不用抄、不用背，改一行跑一次就行。
//
// 用法（在 build 目录下）：
//   mem_lab       -> 正确版，ASan 零报告，退出码 0
//   mem_lab 1     -> 释放之后再读（悬垂）
//   mem_lab 2     -> 数组越界写
//   mem_lab 3     -> 重复释放同一块内存
//   mem_lab 4     -> 释放方式配错：new[] 出来的内存用 delete（而不是 delete[]）还
// 每次只跑一个：ASan 一报错就终止，同一轮里看不到后面几个。
//
// 关于第五类"野指针"（int* p; 直接 *p = 5;）：这一条**故意没有做成探针**。
// 实测（2026-09-29）：连着跑三次，程序都在运行时挂住、不自行退出，
// 只能手动结束进程；编译期倒是稳定给一条 C4700。
// 这个差别本身就是结论 —— 野指针是四类里唯一连"报错给你看"都不保证的一类。
//
// 第四类"内存泄漏"不在这个文件里 —— MSVC 的 ASan 不查泄漏（实测报
// "detect_leaks is not supported on this platform"），要看 leak-lab.cpp。
// ============================================================
#include <iostream>
#include <windows.h>

// 【第 1 类】悬垂指针 / use-after-free
// 内存已经被还回去了，指针还留着，还去读它。
static void probeUseAfterFree() {
    int* p = new int(7);
    std::cout << "释放之后读到 " << *p << "\n";   
    delete p;                       // 内存还给系统了
    
}

// 【第 2 类】越界写 / heap-buffer-overflow
// 申请了 4 个 int（下标 0-3），却写到下标 4。
static void probeHeapOverflow() {
    int* a = new int[4];
    for (int i = 0; i < 4; ++i) {
        a[i] = i;
    }
    std::cout << "最后一个数 " << a[3] << "\n";
    delete[] a;
}

// 【第 3 类】重复释放 / double free
// q 只是 p 的拷贝，两个指针指着同一块内存，却 delete 了两次。
static void probeDoubleFree() {
    int* p = new int(1);
    int* q = p;                     // 注意：这里拷的是"地址"，不是新内存
    delete q;                       
}

// 【第 5 类】配对错误：new[] 申请的内存，用 delete（少了方括号）还
// 规则是 new ↔ delete、new[] ↔ delete[]。配错了会破坏堆的内部记账。
static void probeMismatchDelete() {
    int* a = new int[4]{1, 2, 3, 4};
    std::cout << "数组里第 4 个是 " << a[3] << "\n";
    delete a;                       // 错在这一行：少了 []
}

// 【对照组】同样四件事的正确写法，用来确认"零报告"长什么样
static void correctAll() {
    int* p = new int(7);
    std::cout << "正确：读到 " << *p << "\n";
    delete p;
    p = nullptr;                    // 还回去之后立刻掐断，防止自己再误用

    int* a = new int[4];
    for (int i = 0; i < 4; ++i) {   // 注意是 < 4
        a[i] = i;
    }
    std::cout << "正确：a[3] = " << a[3] << "，没有越界、没有重复释放\n";
    delete[] a;
    a = nullptr;
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    int mode = (argc > 1) ? (argv[1][0] - '0') : 0;
    switch (mode) {
    case 1: probeUseAfterFree(); break;
    case 2: probeHeapOverflow(); break;
    case 3: probeDoubleFree();   break;
    case 4: probeMismatchDelete(); break;
    default: correctAll();       break;
    }

    std::cout << "程序走到了最后一句 —— 这一轮没有触发 ASan\n";
    return 0;
}
