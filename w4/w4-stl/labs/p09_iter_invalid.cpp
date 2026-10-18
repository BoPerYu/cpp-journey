// ============================================================================
// 探针 9 · p09_iter_invalid：迭代器失效（观察题，结果 OPEN）
// ============================================================================
// 讲义：打卡训练\W4\W4D3_C++_迭代器.md 第四节
//
// 要看的就一件事：**拿到迭代器 → 让容器扩容 → 旧迭代器还指着原来那块内存吗？**
// ⚠️ 程序可能当场终止（Debug 版标准库会检查迭代器有效性）—— 那是【预期结果】，不是你的错。
// ⚠️ 全程用 std::endl（带 flush）：这样即使程序被中止，前面打印的证据也留在屏幕上。
//    （这是 p05 那次的教训：用 "\n" 的话，进程一被掐，缓冲区里的东西全丢。）
//
// 跑法：.\run.ps1 p09_iter_invalid
// ============================================================================

#include <iostream>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> v;
    v.reserve(2);                     // 故意只留 2 格，方便下一步撑破
    v.push_back(1);
    v.push_back(2);
    std::cout << "初始：size=" << v.size() << "  capacity=" << v.capacity() << std::endl;

    auto it = v.begin();              // 拿一个迭代器
    std::cout << "旧迭代器指着的地址   = " << static_cast<const void*>(&*it) << std::endl;
    std::cout << "此时 v.data()        = " << static_cast<const void*>(v.data()) << std::endl;
    std::cout << "*it                  = " << *it << std::endl;

    std::cout << "\n现在 push_back 第 3 个（容量只有 2，必然扩容）……" << std::endl;
    v.push_back(3);
    std::cout << "扩容后：size=" << v.size() << "  capacity=" << v.capacity() << std::endl;
    std::cout << "扩容后 v.data()      = " << static_cast<const void*>(v.data()) << std::endl;
    std::cout << "→ 和上面【旧迭代器指着的地址】比一比，一样吗？" << std::endl;

    std::cout << "\n最后一步：再用那个旧迭代器（这一步可能让程序当场终止）……" << std::endl;
    std::cout << "*it = " << *it << std::endl;
    std::cout << "（如果这行打出来了，说明这次没被抓住 —— 那也是有用的信息：" << std::endl;
    std::cout << "  '工具不报' 不等于 '没出错'，旧迭代器指的已经是别的地方了。）" << std::endl;
    return 0;
}
