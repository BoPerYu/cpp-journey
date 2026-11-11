# w8-inverted-index

W8 C++ 工程线：从已分词语料建立“词项 -> posting list”的倒排索引，
并支持查询一个词。

## 定位

本工程是独立 C++ 工程训练，不属于 Qwen embedding 研究主线。

## 输入契约

- UTF-8；
- 一行一篇文档；
- 行内 token 使用空白分隔；
- 空行仍是一篇空文档；
- C++ 不负责中文分词、归一化或停用词处理；
- `document_id` 从 0 开始，按行递增。

## 计划中的输出

```text
document_count = 3
term = apple
doc=0 tf=2
doc=2 tf=1
```

## 构建

```powershell
cd D:\Code\cpp-journey\w8\w8-inverted-index
cmake -S . -B build
cmake --build build --config Debug --parallel
cmake --build build --config Release --parallel
```

## 运行

```powershell
.\build\Debug\inverted_index.exe .\data\sample.tokens.txt apple
```

## 测试

```powershell
ctest --test-dir build -C Debug --output-on-failure
ctest --test-dir build -C Release --output-on-failure
```

## 当前范围

仅完成单词语义上的倒排查询。TF-IDF、BM25、Top-K、Python 对拍和性能优化
属于后续阶段。

## 已知限制

- 不检查输入文件是否真的为 UTF-8；
- 不支持多词查询；
- 暂不优化 posting list 的连续内存布局。
