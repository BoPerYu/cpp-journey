# w7-corpus-stats

一个用于读取已分词中文语料的 C++17 小项目。程序逐行读取 token 文件，统计文档数和
词表大小，并输出频次最高的 100 个 token。

本项目只处理已经用空格分隔好的 token。中文分词由 Python 侧提前完成，C++ 不负责
分词、Unicode 归一化或标点过滤。

## 数据格式

输入文件必须是 UTF-8，并遵守以下约定：

```text
一行 = 一篇文档
行内 token 使用空白分隔
空行 = 一篇空文档
不删除停用词
英文和全半角归一化由上游脚本完成
```

示例：

```text
南京市 长江大桥
abc python3.14

自然语言 处理 真 有意思
hello world 2026
```

对应结果：

```text
document_count = 5
vocabulary = 11
```

仓库中的 `data/sample.tokens.txt` 可用于最小验证。大型生成语料不提交到 Git。

## 环境要求

- CMake 3.20 或更新版本；
- 支持 C++17 的编译器；
- 已验证环境：Windows、Visual Studio 2026、MSVC、CMake 4.4.3。

## 构建

在项目目录执行：

```powershell
cd D:\Code\cpp-journey\w7\w7-corpus-stats

cmake -S . -B build
cmake --build build --config Debug --parallel
cmake --build build --config Release --parallel
```

Visual Studio 多配置生成器的可执行文件位于：

```text
build\Debug\corpus_stats.exe
build\Release\corpus_stats.exe
```

## 运行

```text
corpus_stats <token-file>
```

示例：

```powershell
.\build\Debug\corpus_stats.exe .\data\sample.tokens.txt
```

输出格式：

```text
document_count = 5
vocabulary = 11
<token> <count>
...
```

程序最多输出 100 个 token，排序规则为：

```text
频次降序
同频时按 token 字典序升序
```

命令行退出码：

| 退出码 | 含义 |
| ---: | --- |
| 0 | 正常处理，包括空文件 |
| 1 | 输入文件无法打开 |
| 2 | 参数数量错误 |

## 自动测试

构建后运行：

```powershell
ctest --test-dir build -C Debug --output-on-failure
ctest --test-dir build -C Release --output-on-failure
```

测试覆盖：

- 空文件：0 篇文档、0 个 token；
- 一行空文档：1 篇文档、0 个 token；
- 跨文档词频累计；
- 文档数与不同 token 数；
- 频次降序；
- 同频 token 字典序升序；
- 排序结果长度。

2026-11-05 已验证 Debug 和 Release 的 CTest 均为 `1/1` 通过。

## Debug 与 AddressSanitizer

Debug 构建默认开启 AddressSanitizer：

```powershell
cmake -S . -B build
cmake --build build --config Debug --parallel
ctest --test-dir build -C Debug --output-on-failure
```

ASan 使用按配置生成的编译与链接选项，因此在 Visual Studio 多配置生成器中也会
对 Debug 目标生效。CMake 会把 MSVC 的 ASan 运行库复制到可执行文件旁。

Release 不开启 ASan，用于正常运行和性能观察：

```powershell
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

如果当前工具链无法使用 ASan，可以显式关闭：

```powershell
cmake -S . -B build -DCORPUS_STATS_ENABLE_ASAN=OFF
```

关闭 ASan 只表示本次运行没有内存检查器，不代表代码不存在内存错误。

## 100,000 篇规模验证

测试数据由 LCQMC `train.txt` 前 100,000 行的第一个句子字段生成，先经过 Python
侧归一化和 jieba 分词，再交给本项目读取。

Release 实测结果：

```text
document_count = 100000
vocabulary = 25282
输出行数 = 102（2 行统计信息 + Top-100）
运行耗时约 0.35 秒
```

Top-5：

```text
的 35816
什么 30707
是 17026
怎么 13207
有 8206
```

运行耗时会随机器、磁盘缓存、构建配置和系统负载变化，以上数字不是通用性能基准。

## 目录结构

```text
w7-corpus-stats/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── data/
│   └── sample.tokens.txt
└── w7-corpus-stats/
    ├── corpus_stats.h
    ├── corpus_stats.cpp
    ├── corpus_stats_test.cpp
    └── main.cpp
```

职责划分：

- `corpus_stats.h/.cpp`：文档读取、词频统计与排序；
- `main.cpp`：命令行参数、文件打开和结果输出；
- `corpus_stats_test.cpp`：不依赖真实文件的自动测试；
- `CMakeLists.txt`：库、主程序和测试三个构建目标；
- `data/sample.tokens.txt`：可提交的小型格式样例。

## 已知限制

- 不负责中文分词或 Unicode 归一化；
- 不删除停用词，因此高频结果会包含“的、什么、是”等功能词；
- 当前会对完整词表排序，复杂度约为 `O(T + V log V)`，其中 `T` 是 token
  总出现次数，`V` 是不同 token 数；
- 暂未优化为堆或 `partial_sort` 的 Top-K 实现；
- 没有验证输入文件是否真的为 UTF-8；
- 当前性能数字只代表这台机器的 Release 运行结果。

## 生成数据

以下大型生成文件不进入 Git：

```text
data/lcqmc_100k.tokens.txt
data/lcqmc_100k.top100.txt
```

重新生成后可运行：

```powershell
Measure-Command {
    & '.\build\Release\corpus_stats.exe' `
      '.\data\lcqmc_100k.tokens.txt' `
      > '.\data\lcqmc_100k.top100.txt'
}
```
