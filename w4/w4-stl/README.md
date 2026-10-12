# w4-stl · W4 STL 上半（std::string / std::vector / 迭代器）

W4（2026-10-12 ~ 10-18）的 C++ 工作目录。

## 怎么构建

```powershell
cd D:\Code\cpp-journey\w4\w4-stl
cmake -S . -B build -G "Visual Studio 18 2026" -A x64   # 只需第一次（已跑过一次，可跳过）
cmake --build build --config Debug --parallel           # 之后每次都跑这句
```

跑某个探针：

```powershell
.\build\Debug\p02_growth.exe
```

用图形界面的话，打开 `build\w4_stl.slnx`，把目标设为启动项。

## 和 W3 工程的两处不同

- `/W3` → **`/W4`**（约定第 4 条；C4706 在 /W3 下是沉默的）
- `labs\` 里**新加 .cpp 不用改 CMakeLists**：按文件名自动建目标。
  新加文件后重新 configure 一次（或者直接 `cmake --build`，`CONFIGURE_DEPENDS` 会自己重配）。
  文件名用 **ASCII**，中文写进注释——避免 MSBuild 处理非 ASCII 目标名。

## 目标

| 目标 | 文件 | 看什么 |
| --- | --- | --- |
| `p01_sizeof` | `labs\p01_sizeof.cpp` | 容器对象本身多大 vs 里面装几个元素（含 `v(3)` / `v{3}` 陷阱）|
| `p02_growth` | `labs\p02_growth.cpp` | 标准库的扩容因子（对照 W2 手写 MyVector 的 2 倍）|
| `p03_empty_diff_one` | `labs\p03_empty_diff_one.cpp` | 空容器的 `size()-1` = 18446744073709551615 |
| `p04_copy` | `labs\p04_copy.cpp` | `b = a` 是深拷贝（对照 Python 的 `b = a`）|
| `p05_oob` | `labs\p05_oob.cpp` | 越界读：容量 == size 时 ASan 报；容量 > size 时**不报** |
| `my_scores` | `my\scores.cpp` | 本周检验：用 string / vector 重写 W1 成绩管理程序（还没建）|

## 约好的两件事（照 W3）

- `/utf-8` + `main` 第一句 `SetConsoleOutputCP(CP_UTF8);`
- 所有 labs 在 Debug 下开 `/fsanitize=address`，构建后自动把 `clang_rt.asan_*_dynamic-x86_64.dll` 拷到 exe 旁边
- 链接阶段的 `LNK4044` / `LNK4300` 两条噪声照旧可忽略
