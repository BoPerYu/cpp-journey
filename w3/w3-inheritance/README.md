# w3-inheritance · W3 继承与多态

W3（2026-10-05 ~ 10-11）的工作目录。

## 怎么构建

```powershell
cd D:\Code\cpp-journey\w3-inheritance

cmake -S . -B build -G "Visual Studio 18 2026" -A x64   # 只需第一次
cmake --build build --config Debug                      # 之后每次都跑这句
```

用图形界面的话，打开 `build\w3_inheritance.slnx`。

## 目标

| 目标 | 文件 | 看什么 |
| --- | --- | --- |
| `why_inherit` | `labs\why-inherit.cpp` | 不用继承，代码长什么样 |
| `minimal` | `labs\minimal.cpp` | 最小 Shape→Circle + 构造/析构顺序 |
| `no_virtual` | `labs\no-virtual.cpp` | 不写 virtual 的两种翻车（对象切片 / 静态绑定） |
| `vdtor_bad` | `labs\vdtor-bad.cpp` | 非虚析构 + 派生类 new 了内存（开 ASan） |
| `vdtor_good` | `labs\vdtor-good.cpp` | 基类析构加了 virtual（开 ASan） |
| `sizeof_vtable` | `labs\sizeof-vtable.cpp` | virtual 的代价：对象里多出来的隐藏指针 vptr |
| `ctor_virtual` | `labs\ctor-virtual.cpp` | 构造 / 析构里调用虚函数，不发生多态 |
| `upcast` | `labs\upcast.cpp` | 指针层面的多态：基类指针和派生类指针指向同一块内存 |
| `hiding` | `labs\hiding.cpp` | 名字隐藏：派生类同名函数藏掉基类所有重载 |
| `abstract` | `labs\abstract.cpp` | 纯虚函数与抽象类 + 通过基类引用调用 |
| `range_for` | `labs\range-for.cpp` | range-for 里那个变量是拷贝还是引用 |
| `flush_lab` | `labs\flush-lab.cpp` | flush 是干什么的（abort 前不 flush 会丢输出） |
| `vdtor_size` | `labs\vdtor-same-size.cpp` | 派生类和基类一样大时，非虚析构照样漏调派生类析构 |
| `my_shapes` | `my\shapes.cpp` | 本周主程序（Shape / Circle / Rect），函数体自己写 |

`labs\broken\` 里两个文件**故意编译不过 / 故意不报错**，不参与构建，要用命令行单独编（文件头有命令）。

## 约好的两件事

- `/utf-8` + `main` 第一句 `SetConsoleOutputCP(CP_UTF8);`
- 涉及动态内存的目标在 Debug 下开 `/fsanitize=address`，构建后自动把
  `clang_rt.asan_*_dynamic-x86_64.dll` 拷到 exe 旁边（见 `CMakeLists.txt` 里的 `w3_enable_asan`）

## 已知可忽略的警告

链接阶段会打 `LNK4044: 无法识别的选项"/fsanitize=address"` 和
`LNK4300: 忽略"/INCREMENTAL"，因为输入模块包含 ASAN 元数据`——
两条都可忽略，链接器只是不认识编译器的开关。
