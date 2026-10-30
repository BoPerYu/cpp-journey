# w6-word-count

W6 的 C++17 多文件词频统计器。程序读取以空白分隔的 token，按
“频次降序、同频单词字典序升序”排序，并输出前 K 项。

本项目只处理空白分词，不处理标点、大小写或中文分词。它用于练习多文件
组织、CMake、异常边界、lambda、`auto` 和自动化测试，不是完整的文本检索系统。

## 环境要求

- CMake 3.20 或更新版本
- 支持 C++17 的编译器
- 已验证环境：Windows x64、MSVC、CMake 4.4.3、Debug

## 从 clone 到运行

```powershell
git clone https://github.com/BoPerYu/cpp-journey.git
cd cpp-journey\w6\w6-word-count

cmake -S . -B build
cmake --build build --config Debug --parallel
ctest --test-dir build -C Debug --output-on-failure
```

使用 Visual Studio 多配置生成器时，可执行文件位于 `build\Debug\`：

```powershell
.\build\Debug\word_count.exe --top 5 .\data\sample.txt
```

预期输出：

```text
the 4
quick 3
dog 2
fox 2
and 1
```

也可以从标准输入读取：

```powershell
"one two two three three three" | .\build\Debug\word_count.exe --top 2
```

预期输出：

```text
three 3
two 2
```

使用单配置生成器时，可执行文件通常直接在 `build\`：

```powershell
.\build\word_count --top 5 .\data\sample.txt
```

## 目录结构

```text
w6-word-count\
├── CMakeLists.txt
├── README.md
├── include\
│   └── word_count.hpp
├── src\
│   └── word_count.cpp
├── app\
│   ├── main.cpp
│   ├── option.hpp
│   └── option.cpp
├── tests\
│   ├── word_count_test.cpp
│   └── option_test.cpp
├── drills\
│   ├── w6d1_transfer.cpp
│   └── w6d3_core_features.cpp
└── data\
    └── sample.txt
```

职责边界：

- `include/word_count.hpp`：词频算法的公开类型和函数声明；
- `src/word_count.cpp`：计数、排序和输出实现；
- `app/option.hpp`：命令行参数结构及接口声明；
- `app/option.cpp`：参数解析和帮助文本；
- `app/main.cpp`：文件/标准输入、算法调用和退出码；
- `tests/word_count_test.cpp`：词频算法回归测试；
- `tests/option_test.cpp`：命令行参数契约测试；
- `drills/`：W6 语法与 STL 迁移练习。

## CMake 目标

| 目标 | 用途 |
| --- | --- |
| `word_count` | 正式命令行程序 |
| `word_count_lib` | 词频算法静态库 |
| `word_count_tests` | 词频算法测试 |
| `option_parser_tests` | 参数解析测试 |
| `w6d1_transfer_drill` | STL 综合练习 |
| `w6d3_core_features` | 异常、lambda、`auto` 练习 |

`word_count` 同时编译 `app/main.cpp` 和 `app/option.cpp`；测试目标也显式列出
所需的实现文件。头文件只放声明，不会代替实现参与链接。

## 命令行行为

```text
word_count [--top N] [FILE]
word_count --help
```

- 未给 `FILE`：从标准输入读取；
- `--top N`：输出前 N 项，N 必须为正整数；
- `--help` / `-h`：打印帮助；
- 无法打开输入文件：退出码 `1`；
- 参数错误：退出码 `2`；
- 正常或显示帮助：退出码 `0`。

## 测试

当前 CTest 共注册 4 个测试：

```text
word_count_selftest
w6d1_transfer_drill
w6d3_core_features
option_parser_tests
```

全部运行：

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

单独运行参数测试：

```powershell
.\build\Debug\option_parser_tests.exe
```

验证参数错误退出码：

```powershell
.\build\Debug\word_count.exe --top 0 .\data\sample.txt
$LASTEXITCODE
```

预期命令输出：

```text
error: --top requires a positive integer
```

预期退出码：

```text
2
```

## AddressSanitizer

Debug 构建默认尝试启用 AddressSanitizer。CMake 会把 MSVC 的 ASan 运行库复制到
可执行文件旁。

如果本机编译器不支持该运行库，可以关闭：

```powershell
cmake -S . -B build -DW6_ENABLE_ASAN=OFF
cmake --build build --config Debug --parallel
```

关闭 ASan 只表示这次运行没有自动内存检查器，不代表代码不存在内存错误。

## 已知限制

- 只按空白切分，标点会附着在 token 上；
- 区分大小写；
- 不处理中文分词；
- Top-K 使用完整排序，复杂度为 `O(m log m)`，其中 `m` 是不同 token 数；
- 不同编译器和构建配置下的警告、路径和可执行文件后缀可能不同。
