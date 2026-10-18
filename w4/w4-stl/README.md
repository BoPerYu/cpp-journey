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

## 目标（2026-10-19 更新：W4 全部完成）

### 参考程序（助手写，直接跑）

| 目标 | 看什么 |
| --- | --- |
| `ref01_string_vector_api` | `string` / `vector` 的 API 全集（讲义 W4D1 的实测出处）|
| `ref02_string_vs_vector` | `string` 就是 `basic_string<char>`；`vector<char>` 顶不掉它 |
| `ref03_asan_container_overflow` | 越界读的两种结局（`heap-buffer-overflow` / `container-overflow`）|
| `ref04_pass_return_cost` | 传参/返回到底拷几次（两把尺子：元素计数 + 缓冲区地址）|
| `ref05_iter_what_it_is` | 迭代器是对象不是指针：`typeid` / `sizeof` / `&*it == data()` / `++it` 地址 +4 |
| `ref06_char_vs_string_legal` | 单引号/双引号哪些写法合法、哪些报 C2664 |
| `ref07_iter_walk` | vector 迭代器全程 +4；deque 每 4 个元素跳 20 字节 |

### 探针（本人写）

| 目标 | 回答的问题 |
| --- | --- |
| `p01_sizeof` | 容器对象多大 vs 里面装几个元素（含 `v(3)` / `v{3}`）|
| `p02_growth` | 标准库扩容因子（×1.5）vs W2 手写 MyVector（×2）|
| `p03_empty_diff_one` | 空容器 `size()-1` = 18446744073709551615 |
| `p04_copy` | `b = a` 是深拷贝（对照 Python）|
| `p05_oob` | 越界读：两种容量状态都被抓，但"谁抓的"不同 |
| `p06_split` | 用 `find` + `substr` 切词（4/4）|
| `p07_pass_by` | 按值 / 引用 / `const&` 的地址对照（会改与不会改）|
| `p08_iter_basics` | 迭代器遍历 / 算术 / 改元素 / 指向缓冲区（7/7）|
| `p09_iter_invalid` | 扩容后旧迭代器失效（地址变了 → 再用被掐死）|
| `p10_deque_basics` | deque 两端操作 + 迭代器跨容器复用（3/3）|

### 本周检验

| 目标 | 文件 | 说明 |
| --- | --- | --- |
| `my_scores` | `my\scores.cpp` | **W4 检验**：用 `string`/`vector` 重写 W1 成绩管理程序。传参从"指针+长度"改成"容器"；出参用 `int&`/`string&`；`findFirstabove` 返回迭代器 + `.end()`。验收：退出码 0 + **ASan 零报告** |

> 链接阶段的 `LNK4044` / `LNK4300` 是已知噪声（链接器不认识 `/fsanitize=address`），忽略。

## 约好的两件事（照 W3）

- `/utf-8` + `main` 第一句 `SetConsoleOutputCP(CP_UTF8);`
- 所有 labs 在 Debug 下开 `/fsanitize=address`，构建后自动把 `clang_rt.asan_*_dynamic-x86_64.dll` 拷到 exe 旁边
- 链接阶段的 `LNK4044` / `LNK4300` 两条噪声照旧可忽略
