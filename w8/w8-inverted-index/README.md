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

测试覆盖：

- IDF 固定平滑公式；
- 文档 TF-IDF 范数；
- 空文档范数为 0；
- 单词查询排序；
- 多查询词排序；
- 空查询和未知词；
- 并列分数的 `document_id` 排序；
- Top-K 截断。

## 批量对拍

生成 C++ 结果：

```powershell
.\build\Release\tfidf_batch.exe `
  D:\Code\cpp-journey\w7\w7-corpus-stats\data\lcqmc_100k.tokens.txt `
  .\data\queries.txt `
  10 `
  > .\artifacts\cpp_tfidf_100k.tsv
```

生成 Python 参考结果：

```powershell
python D:\Code\python-journey\w8-d2\batch_reference.py `
  --corpus D:\Code\cpp-journey\w7\w7-corpus-stats\data\lcqmc_100k.tokens.txt `
  --queries .\data\queries.txt `
  --top-k 10 `
  --output D:\Code\python-journey\w8-d2\artifacts\python_tfidf_100k.tsv
```

比较：

```powershell
python .\tools\compare_topk.py `
  --cpp .\artifacts\cpp_tfidf_100k.tsv `
  --python D:\Code\python-journey\w8-d2\artifacts\python_tfidf_100k.tsv `
  --tolerance 1e-9
```

2026-11-13 已用 100,000 篇语料、10 个查询完成对拍：

```text
PASS: 10 queries, 100 result rows matched
```

## BM25

BM25 已完成，固定参数为 `k1 = 1.2`、`b = 0.75`，IDF 使用：

```text
ln(1 + (N - df + 0.5) / (df + 0.5))
```

```powershell
cmake --build build --config Debug --parallel
.\build\Debug\bm25_tests.exe
```

2026-11-13 已验证：

```text
Debug CTest:   3/3 passed
Release CTest: 3/3 passed
```

## 当前范围

已完成单词倒排查询、TF-IDF + 余弦检索和 BM25 检索。Python BM25 对拍与
Release 性能记录属于后续阶段。

## TF-IDF 契约

- `df(term)` = posting list 长度；
- `N` = 文档总数；
- `idf(term) = ln((N + 1) / (df(term) + 1)) + 1`；
- 文档权重 = `tf * idf`；
- 查询词在语料中不存在时忽略；
- 分数为查询与文档 TF-IDF 向量的余弦；
- 分数降序，分数相同时 `document_id` 升序；
- 空查询和无命中查询返回空结果；
- 空文档范数为 0，不参与结果。

## 已知限制

- 不检查输入文件是否真的为 UTF-8；
- 尚未与 Python BM25 实现按同一契约对拍；
- 暂不优化 posting list 的连续内存布局。
