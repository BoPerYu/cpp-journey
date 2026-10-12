// ============================================================
// W2 内存地图（2026-09-29）
// 用途：把"栈上的"和"堆上的"地址并排打出来，看一眼它们离多远。
// 这是探针，不是作业。地址每次运行都会变，看的是"量级和远近"，不是具体数字。
// 用法：mem_map          -> 打印地址地图
//       mem_map 1        -> 栈溢出实验（程序会当场死掉，退出码 0xC00000FD）
// ============================================================
#include <iostream>
#include <windows.h>

int g_counter = 0;              // 全局变量：全程序一份

static int g_static = 0;        // 静态变量：和全局放一起，但只有本文件看得见

// 一个普通函数，用来观察"函数里的局部变量"落在哪儿。
// 说明：inner 是"由参数算出来的一个变量"（seed * 2 只是让它真的依赖参数，
// 不是因为地址和 2 有什么关系）。这个函数唯一有用的一句是打印 &inner ——
// 拿它的地址和 main 里那两个局部变量比一比，你会看到它们在同一片区域（栈），
// 但不是同一个格子：每个函数调用都有自己的"栈帧"。
int insideFunction(int seed) {
    int inner = seed * 2;
    std::cout << "  函数内局部变量 inner       " << &inner << "\n";
    return inner;
}

// 【为什么需要堆】栈装不下它。栈默认只有 1 MB（见讲解里的 dumpbin 实测），
// 100 万个 int 要 4 MB，一进函数就撞墙 —— 程序当场结束，退出码 0xC00000FD。
static void stackOverflowDemo() {
    int big[1000000];        // 4 MB，超过栈的容量
    big[0] = 1;              // 只是"用一下"这个数组，证明它真的被分配了
    std::cout << "如果打印出这一行，说明你的栈比 4 MB 还大：" << big[0] << "\n";
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc > 1 && argv[1][0] == '1') {
        stackOverflowDemo();      // 跑完这一句之前程序就结束了
        return 0;
    }

    int local = 42;                          // 栈
    int local2 = 43;                         // 栈
    int* heapOne = new int(7);               // 堆（1 个 int）
    int* heapArr = new int[4]{10, 20, 30, 40}; // 堆（4 个 int）
    const char* lit = "常量字符串";           // 字面量：在只读的常量区

    std::cout << "—— 栈（函数一进来就自动分配，函数一结束就自动回收）\n";
    std::cout << "  main 里的 local           " << &local << "\n";
    std::cout << "  main 里的 local2          " << &local2 << "\n";
    insideFunction(1);

    std::cout << "\n—— 堆（要自己 new，自己 delete）\n";
    std::cout << "  new int                   " << heapOne << "\n";
    std::cout << "  new int[4]                " << heapArr << "\n";
    std::cout << "  数组第 0 个元素            " << &heapArr[0] << "\n";
    std::cout << "  数组第 1 个元素            " << &heapArr[1] << "\n";
    std::cout << "  数组第 2 个元素            " << &heapArr[2] << "\n";
    std::cout << "  数组第 3 个元素            " << &heapArr[3] << "\n";

    std::cout << "\n—— 全局 / 静态 / 常量 / 代码（都不是栈也不是堆）\n";
    std::cout << "  全局 g_counter            " << &g_counter << "\n";
    std::cout << "  静态 g_static             " << &g_static << "\n";
    std::cout << "  字面量 \"常量字符串\"       " << static_cast<const void*>(lit) << "\n";
    std::cout << "  main 函数本身             " << reinterpret_cast<const void*>(&main) << "\n";

    std::cout << "\n—— 几件顺带确认的事\n";
    std::cout << "  sizeof(int)   = " << sizeof(int) << "\n";
    std::cout << "  sizeof(int*)  = " << sizeof(int*) << "（指针大小和它指向什么类型无关）\n";
    std::cout << "  sizeof(heapArr) 那种 4 个 int 的数组，元素之间正好差 "
              << (reinterpret_cast<char*>(&heapArr[1]) - reinterpret_cast<char*>(&heapArr[0]))
              << " 字节\n";

    delete heapOne;
    delete[] heapArr;
    std::cout << "\n（这一轮申请的都还回去了，所以不会出泄漏报告）\n";
    return 0;
}
