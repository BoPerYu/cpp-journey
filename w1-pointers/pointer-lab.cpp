// ============================================================
// W1 指针观察实验室（2026-09-23）
// 用途：把"地址"这种东西亲眼看一遍。这是工具，不是作业，不用抄、不用改。
// 构建：见同目录 CMakeLists.txt
// 注意：第 4、5 段各有一处故意注释掉的 UB 实验。
//       放开之前先想好会发生什么，再跑，再看退出码。
// ============================================================
#include <iostream>
#include <windows.h>

// 把任意指针按"地址"打印出来。
// 为什么要多这一步：int* 直接 << 也能打印地址，但 char* 会被当成字符串打印，
// 很容易看错。统一转成 const void* 就永远是地址。
const void* A(const void* p) { return p; }

// 一个"悬垂指针"的制造现场。默认不调用。
//
// 实测（2026-09-23，本机）：
//   * 下面这种"同一个函数里出了块作用域"的悬垂 —— ASan 会报
//     stack-use-after-scope，退出码 1。
//   * 但另一种「返回局部变量的地址」造成的悬垂，ASan 默认**抓不到**：
//     程序退出码 0，安静地打印一个垃圾值（实测 -507793408）。
//   → 所以千万别把"ASan 没报错"当成"代码没问题"。这是悬垂指针最难的地方。
void danglingDemo() {
    int* p = nullptr;
    {
        int local = 9;      // local 活在这个花括号里
        p = &local;         // p 记下了 local 的地址
    }                       // ← local 在这里被销毁
    std::cout << "p  = " << A(p) << "   <- 地址还在，但那个对象已经没了\n";
    std::cout << "*p = " << *p << "   <- UB：读一块已经不属于你的内存\n";
    std::cout << "它现在很可能“看起来正常”，正因如此比空指针更危险\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "===== 1. 一个对象，两个名字 =====\n";
    int x = 42;
    int* p = &x;

    std::cout << "x   = " << x << "\n";
    std::cout << "&x  = " << A(&x) << "\n";
    std::cout << "p   = " << A(p) << "   <- 和上一行必须一模一样\n";
    std::cout << "*p  = " << *p << "   <- 和 x 必须一模一样\n";
    std::cout << "&p  = " << A(&p) << "   <- 指针自己也有地址，是另一串数字\n";

    *p = 77;
    std::cout << "\n执行 *p = 77; 之后：x = " << x
              << "   而 p 没变：" << A(p) << "\n";
    std::cout << "结论：x 和 *p 是同一个对象的两种写法。\n\n";

    std::cout << "===== 2. 指针的大小与指向什么类型无关 =====\n";
    std::cout << "sizeof(int)     = " << sizeof(int) << "\n";
    std::cout << "sizeof(double)  = " << sizeof(double) << "\n";
    std::cout << "sizeof(char)    = " << sizeof(char) << "\n";
    std::cout << "sizeof(int*)    = " << sizeof(int*) << "\n";
    std::cout << "sizeof(double*) = " << sizeof(double*) << "\n";
    std::cout << "sizeof(char*)   = " << sizeof(char*) << "   <- x64 上三个指针都是 8\n\n";

    std::cout << "===== 3. 把 & 和 * 的几种用法摆在一起 =====\n";
    int& r = x;                // &  粘在类型名后面：引用声明
    int* q2 = &x;              // &  一元运算符：取地址
    int a3 = 6, b3 = 3;
    int andResult = a3 & b3;   // &  二元运算符：按位与
    int mulResult = a3 * b3;   // *  二元运算符：乘法
    std::cout << "引用 r        = " << r << "\n";
    std::cout << "取地址 &x     = " << A(&x) << "\n";
    std::cout << "解引用 *q2    = " << *q2 << "\n";
    std::cout << "按位与 6 & 3  = " << andResult << "   （110 & 011 = 010）\n";
    std::cout << "乘法   6 * 3  = " << mulResult << "\n";
    std::cout << "判别口诀：看左边是不是类型名。是→声明，不是→运算符。\n\n";

    std::cout << "===== 4. 空指针：能检查，不能解引用 =====\n";
    int* q = nullptr;
    if (q == nullptr) {
        std::cout << "q 是空指针。用之前先检查——这是 nullptr 的正确用法。\n";
    }
    // 下面这行是今天的实验之一。想清楚会发生什么，再放开注释。
    // 实测：开 ASan 时 ASan 先接住，报 access-violation on unknown address
    //       0x000000000000，退出码 1；不开 ASan 时退出码 0xC0000005（访问冲突）。
    // std::cout << *q << "\n";   // 解引用空指针 = UB

    std::cout << "\n===== 5. 悬垂指针 =====\n";
    std::cout << "danglingDemo() 默认不调用。想看就把下一行的注释放开。\n";
    // danglingDemo();

    std::cout << "\n实验室到此结束。注意：上面没有一行会编译报错或给警告。\n";
    return 0;
}
