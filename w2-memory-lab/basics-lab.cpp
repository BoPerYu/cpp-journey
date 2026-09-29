// ============================================================
// W2 基础形状实验台（2026-09-29）
// 用途：回答三个"为什么这么写"的问题 —— 命令行参数怎么看、new 有几种写法、数组版 new 和普通 new 的区别。
// 这个目标故意**不开 ASan**：要看的就是普通 Debug 堆里"没初始化的内存"长什么样。
//
// 用法：
//   basics_lab            -> 打印 argc / argv（这次没有额外参数）
//   basics_lab 1 7        -> 再跑一次，看两个参数是怎么进来的
//   basics_lab new        -> 对照 new 的各种写法
// ============================================================
#include <iostream>
#include <windows.h>

// 打印命令行参数：谁是"第几个参数"，谁是"参数里的第几个字符"
static void showArgs(int argc, char** argv) {
    std::cout << "argc = " << argc << "   （参数个数，**包含程序名自己**）\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << "  argv[" << i << "] = \"" << argv[i] << "\"\n";
    }

    if (argc > 1) {
        std::cout << "  argv[1][0] = '" << argv[1][0] << "'   （这是字符 '1'，不是整数 1）\n";
        std::cout << "  argv[1][0] 的 ASCII 码 = " << static_cast<int>(argv[1][0]) << "\n";
        std::cout << "  argv 这个数组的首地址        " << static_cast<const void*>(argv) << "\n";
        std::cout << "  argv[1] 指向的字符串的首地址  " << static_cast<const void*>(argv[1]) << "\n";
        std::cout << "  argv[1] 这个格子的地址(=argv+1)" << static_cast<const void*>(&argv[1]) << "\n";
    } else {
        std::cout << "  （这次没传参数，所以根本没有 argv[1] 这个格子）\n";
    }
}

// 对照 new 的各种写法
static void showNewForms() {
    int* none = new int;                    // 不初始化
    int* one = new int(7);                  // 圆括号：初始化成 7
    int* two = new int{8};                  // 花括号：也初始化成 8
    int* zero = new int();                  // 空圆括号：值初始化 → 0
    int* arrNone = new int[4];              // 数组，不初始化
    int* arrZero = new int[4]();            // 数组 + 值初始化 → 全 0
    int* arrList = new int[4]{10, 20, 30, 40};  // 数组 + 花括号逐个给值

    std::cout << "new int            -> " << *none << "        （没初始化，是内存里的残留）\n";
    std::cout << "new int(7)         -> " << *one << "\n";
    std::cout << "new int{8}         -> " << *two << "\n";
    std::cout << "new int()          -> " << *zero << "\n";
    std::cout << "new int[4]         -> " << arrNone[0] << " " << arrNone[1] << " " << arrNone[2] << " " << arrNone[3] << "\n";
    std::cout << "new int[4]()       -> " << arrZero[0] << " " << arrZero[1] << " " << arrZero[2] << " " << arrZero[3] << "\n";
    std::cout << "new int[4]{10,20,30,40} -> " << arrList[0] << " " << arrList[1] << " " << arrList[2] << " " << arrList[3] << "\n";
    std::cout << "sizeof(指针) = " << sizeof(arrList)
              << "   （不是 16！指针记不住【这块数组有几个】）\n";

    delete none;
    delete one;
    delete two;
    delete zero;
    delete[] arrNone;
    delete[] arrZero;
    delete[] arrList;
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc > 1 && argv[1][0] == 'n') {    // 第一个字符是 n，就当我们敲的是 "new"
        showNewForms();
    } else {
        showArgs(argc, argv);
    }
    return 0;
}
