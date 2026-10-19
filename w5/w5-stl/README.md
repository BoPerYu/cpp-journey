# w5-stl · W5 C++ STL 下半

W5（2026-10-19 ~ 10-25）的 C++ 工作目录。今天只做 `std::map` / `std::unordered_map`。

## 构建

```powershell
cd D:\Code\cpp-journey\w5\w5-stl
cmake -S . -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Debug --parallel
```

跑某个目标：

```powershell
.\build\Debug\ref01_map_api.exe
.\build\Debug\p01_operator_bracket.exe
.\build\Debug\word_count.exe --selftest
```

`labs\` 里新加 `.cpp` 不用改 `CMakeLists.txt`，重新 configure 即可。

## 目标

| 目标 | 类型 | 用途 |
| --- | --- | --- |
| `ref01_map_api` | 参考程序 | 看 `map` / `unordered_map` 的实际行为 |
| `p01_operator_bracket` | 探针 | 证明 `operator[]` 会插入默认值 |
| `p02_find_count_at` | 探针 | 对照 `find` / `count` / `at` |
| `p03_insert_conflict` | 探针 | 对照 `insert` / `insert_or_assign` / `try_emplace` |
| `p04_erase_iterate` | 探针 | 在遍历中正确删除元素 |
| `p05_map_iterator_drill` | 加练 | `it->first` / `it->second`、`find`、`distance`、`lower_bound`、遍历删除 |
| `word_count` | 今日可复用练习 | 输入 token，输出按频次排序的 Top-K |

## 约定

- Debug 下开 `/fsanitize=address`，ASan 运行库会自动拷到 exe 旁边。
- `/W4` + `/permissive-` + `/utf-8`。
- `main` 第一句 `SetConsoleOutputCP(CP_UTF8);`。
