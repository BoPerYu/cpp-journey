// ============================================================================
// ref03 · p05_oob 的"能留下证词"版（助手写的参考程序）
// ============================================================================
// 为什么需要这个文件：p05_oob 用 "\n" 输出，程序被 ASan 中止时**缓冲区里的东西全丢**，
// 你在管道/重定向里跑就只看到一个退出码（你 W3 的 flush_lab 探针讲的就是这件事）。
// 这里改成 std::endl（= 换行 + flush），所以即使程序当场死，前面的输出也留在屏幕上。
//
// 跑法（在 D:\Code\cpp-journey\w4\w4-stl 目录下，一次跑一段）：
//     .\build\Debug\ref03_asan_container_overflow.exe A
//     .\build\Debug\ref03_asan_container_overflow.exe B
//
// ---- 2026-10-12 实测结论（用 p05 的同一句代码做的对照实验）----
//   设置 1：Debug（_ITERATOR_DEBUG_LEVEL=2，默认）
//            → 进程当场终止，退出码 -1073740791 (0xC0000409)，stderr 0 字节（连报告都没有）
//   设置 2：同样 /MDd，加 /D_ITERATOR_DEBUG_LEVEL=0
//            → AddressSanitizer: container-overflow ... READ of size 4（3949 字节报告）
//   即：越界读【两种情况都抓得到】，但在 Debug 下是标准库自己的检查先开火，
//       而且因为输出没 flush，屏幕上什么都看不到（W3 的 flush_lab 讲的就是这件事）。
// ============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <windows.h>

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);
    const int which = (argc > 1) ? std::atoi(argv[1]) : 0;

    if (which != 2) {
        std::cout << "===== A 段：容量恰好等于 size，读 v[3] =====" << std::endl;
        std::vector<int> v{1, 2, 3};
        std::cout << "v.size()=" << v.size() << "  v.capacity()=" << v.capacity() << std::endl;
        std::cout << "准备读 v[3] ……" << std::endl;
        std::cout << "v[3] = " << v[3] << std::endl;      // 越出"已申请内存"的边界
        std::cout << "A 段活着走出了这一行" << std::endl;
    }

    if (which != 1) {
        std::cout << "\n===== B 段：容量大于 size，读 w[3] =====" << std::endl;
        std::vector<int> w;
        for (int i = 0; i < 5; ++i) { w.push_back(i * 10); }
        w.pop_back();
        w.pop_back();
        std::cout << "w.size()=" << w.size() << "  w.capacity()=" << w.capacity() << std::endl;
        std::cout << "准备读 w[3] ……" << std::endl;
        std::cout << "w[3] = " << w[3] << std::endl;      // 在"已申请内存"里面，但超出 size
        std::cout << "B 段活着走出了这一行" << std::endl;
    }

    return 0;
}
