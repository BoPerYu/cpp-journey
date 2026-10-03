cmake_minimum_required(VERSION 3.20)

project(w2_memory_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # 中文注释 / 字符串按 UTF-8 读，和 W1 的约定一致
    add_compile_options(/utf-8)
endif ()

# ------------------------------------------------------------
# 目标 1：mem_lab —— 三种堆写入错误的 ASan 实验台
#   只跑 Debug。Release 下不开 ASan（ASan 本来也不是给 Release 用的）
# ------------------------------------------------------------
add_executable(mem_lab mem-lab.cpp)

if (MSVC)
    target_compile_options(mem_lab PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
    target_link_options(mem_lab PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)

    # 链接时可能看到 LNK4044「无法识别的选项 /fsanitize=address」——那是
    # link.exe 不认识编译器的开关，可忽略；ASan 元数据在目标文件里，
    # 链接器会自动带上运行库。
    #
    # MSVC 的 ASan 是「动态」运行库：exe 旁边必须有 clang_rt.asan_*_dynamic
    # 那个 dll，否则从普通终端直接跑会报 0xC0000135（找不到 DLL）——
    # 程序还没跑就退出，极易误判成代码写坏。这里构建完自动拷一份。
    get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    add_custom_command(TARGET mem_lab POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
            "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
            "$<TARGET_FILE_DIR:mem_lab>"
        COMMENT "拷贝 ASan 运行库 DLL 到输出目录"
        VERBATIM)
endif ()

# ------------------------------------------------------------
# 目标 2：leak_lab —— 泄漏探针，**故意不加 ASan**
#   原因见 leak-lab.cpp 顶部注释（CRT 调试堆和 ASan 二选一）
# ------------------------------------------------------------
add_executable(leak_lab leak-lab.cpp)

# ------------------------------------------------------------
# 目标 3：mem_map —— 内存地图，把栈/堆/全局/常量的地址并排打出来
#   只观察地址，不制造错误，所以也不开 ASan
# ------------------------------------------------------------
add_executable(mem_map mem-map.cpp)

# ------------------------------------------------------------
# 目标 4：basics_lab —— 命令行参数 + new 的几种写法对照
#   故意**不开 ASan**：要看的是普通 Debug 堆里"没初始化的内存"长什么样
# ------------------------------------------------------------
add_executable(basics_lab basics-lab.cpp)

# ------------------------------------------------------------
# 目标 5：life_lab —— 对象生命周期探针（构造 / 析构 / 拷贝的调用时机）
#   看的是"什么时候调用"，不需要 ASan
# ------------------------------------------------------------
add_executable(life_lab life-lab.cpp)

# ------------------------------------------------------------
# 目标 6：init_lab —— 成员初始化列表探针（初始化 vs 赋值、初始化顺序）
# ------------------------------------------------------------
add_executable(init_lab init-lab.cpp)

# ------------------------------------------------------------
# 目标 7：ptr_lab —— 指针与动态内存语法实验台（p[i] / new[] / delete[] / 指针算术）
# ------------------------------------------------------------
add_executable(ptr_lab ptr-lab.cpp)
