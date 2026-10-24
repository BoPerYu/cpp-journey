# w5-stl · W5 C++ STL 下半

W5（2026-10-19 ~ 10-25）的 C++ 工作目录：`map` / `unordered_map` / `set` / `<algorithm>`，最后收口词频统计器。

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
| `ref02_set_api` | 参考程序 | `set` / `unordered_set` 的基础 API |
| `p06_set_basics` | 探针 | 唯一性、顺序、`find` / `count` / `erase` |
| `p07_set_vs_unordered` | 探针 | `set` 与 `unordered_set` 的顺序和选型 |
| `p08_set_range` | 探针 | `lower_bound` / `upper_bound` / `equal_range` |
| `p09_set_erase_iterate` | 探针 | 遍历删除和 set 元素的只读性 |
| `ref03_algorithm_api` | 参考程序 | `sort`、`lower_bound`、`accumulate`、`count_if` 的基础 API |
| `p10_sort_wordcount` | 探针 | Top-K 的 sort 比较器与严格弱序 |
| `p11_lower_bound` | 探针 | `lower_bound` / `upper_bound` / `equal_range` |
| `p12_accumulate_countif` | 探针 | `accumulate` 初始值类型与 `count_if` |
| `ref04_template_api` | 参考程序 | 函数模板、泛型排序、`const auto&` |
| `p13_template_max` | 探针 | 写一个 `max_value<T>` |
| `p14_template_sort` | 探针 | 写一个 `sort_values<T, Compare>` |
| `ref05_class_template` | 参考程序 | `Box<T>`、`Stack<T>` 和类模板成员 |
| `word_count` | 今日可复用练习 | 输入 token，输出按频次排序的 Top-K |
| `unique_words` | 今日可复用练习 | 输入 token，输出去重后的字典序词表 |
| `generic_stack` | 今日可复用练习 | 用类模板实现类型安全的 `Stack<T>` |

## 约定

- Debug 下开 `/fsanitize=address`，ASan 运行库会自动拷到 exe 旁边。
- `/W4` + `/permissive-` + `/utf-8`。
- `main` 第一句 `SetConsoleOutputCP(CP_UTF8);`。
