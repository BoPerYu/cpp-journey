# w6-word-count

W6 的 C++ 多文件词频统计器。输入以空白分隔的 token，按
“频次降序、同频单词字典序升序”排序，输出前 K 项。

本版本只处理空白分词，不处理标点、大小写或中文分词。它是工程组织练习，
不是文本检索系统。

## 从 clone 到运行

需要 C++17 编译器与 CMake 3.20 或更新版本。

```powershell
git clone https://github.com/BoPerYu/cpp-journey.git
cd cpp-journey\w6\w6-word-count
cmake -S . -B build
cmake --build build --config Debug --parallel
ctest --test-dir build -C Debug --output-on-failure
```

使用 Visual Studio 多配置生成器时，可执行文件在 `build\Debug\`：

```powershell
.\build\Debug\word_count.exe --top 5 .\data\sample.txt
```

使用单配置生成器时，可执行文件通常直接在 `build\`：

```powershell
.\build\word_count --top 5 .\data\sample.txt
```

从标准输入读取：

```powershell
"one two two three three three" | .\build\Debug\word_count.exe --top 2
```

预期输出：

```text
three 3
two 2
```

## 目录结构

```text
w6-word-count\
├── CMakeLists.txt
├── include\
│   └── word_count.hpp
├── src\
│   └── word_count.cpp
├── app\
│   └── main.cpp
├── tests\
│   └── word_count_test.cpp
└── data\
    └── sample.txt
```

职责边界：

- `include/word_count.hpp`：公开类型和三个函数声明；
- `src/word_count.cpp`：计数、排序、打印的实现；
- `app/main.cpp`：参数解析和文件/标准输入；
- `tests/word_count_test.cpp`：不依赖测试框架的最小回归测试。

## 构建选项

Debug 构建默认启用 AddressSanitizer。若本机编译器不支持，可以关闭：

```powershell
cmake -S . -B build -DW6_ENABLE_ASAN=OFF
```

## 已验证环境

- Windows
- CMake 4.4.3
- MSVC，C++17
- Debug 构建；`ctest` 全部通过

不同编译器对 `std::size_t` 和警告的输出可能不同，但样例排名规则与测试结果一致。
