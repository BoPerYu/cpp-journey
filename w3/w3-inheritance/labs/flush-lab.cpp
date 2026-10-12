// 探针 12：flush 是干什么的
//
// std::cout 通常先把内容攒进一个缓冲区，到某个时机才真正写出去；
// flush 就是"别攒了，现在就写出去"。std::endl = 换行 + flush。
//
// 那么什么时候**必须**手动 flush？本探针的实测结果跟直觉不一样，照实记录：
//
// 【实测 A：真的会丢】ASan 报错中止程序的场景（探针 4a）
//     不加 flush：命令行只收到 ASan 报告；程序在 delete 之前打印的
//                 "=== 探针 4a ===" / "[构造] BaseBad" 这些行**一行都没有**
//     加了 flush：先收到程序自己的输出，再收到 ASan 报告
//     —— my\shapes.cpp 里 delete 前那句 flush 就是为这个加的
//
// 【实测 B：居然没丢】本探针：打印 501 行之后用 ExitProcess(1) 硬结束进程
//     .\build\Debug\flush_lab.exe         → 命令行收到 501 行
//     .\build\Debug\flush_lab.exe flush   → 命令行收到 501 行
//     两次一样，说明在这台机器上，MSVC 的 stdout 并没有把这些数据攒住
//     （管道、重定向到文件，两种接法都试过，都是 501 行）
//
// 结论：flush 的语义是确定的（"把缓冲区立刻写出去"），但"到底有没有东西攒在
//       缓冲区里、会不会丢"，跟运行库和终止方式有关 —— **不能凭直觉判断，要实测**。
//       本探针的价值就在这里：它记录了一次被实测纠正的直觉。
//
// 说明：用 ExitProcess 而不是 std::abort()，因为 MSVC 下 std::abort() 会弹
//       崩溃对话框把命令行卡住（本机实测时真卡住过，得手动结束进程）。

#include <iostream>
#include <cstdlib>
#include <windows.h>

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);
    const bool doFlush = (argc > 1);

    std::cout << "本次运行：" << (doFlush ? "结束前会 flush" : "结束前不 flush") << "\n";
    for (int i = 0; i < 500; ++i) {
        std::cout << "第 " << i << " 行：这一行是在进程结束之前打印出来的\n";
    }

    if (doFlush) {
        std::cout.flush();      // ← 现在就把缓冲区推出去
    }

    // ExitProcess 是 Win32 的"立刻结束进程"：连 C 运行库的收尾都不走，
    // 所以它还压在缓冲区里的数据会直接消失。（std::_Exit/_exit 在本机实测里
    // 都被运行库顺手刷掉了，看不出差别。）
    ::ExitProcess(1);
}
