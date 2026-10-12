cmake_minimum_required(VERSION 3.20)

project(w3_inheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # 中文注释 / 字符串按 UTF-8 读，和 W1、W2 的约定一致
    add_compile_options(/utf-8)

    # CMake 4.x 生成的 VS 工程默认是 /W1，比 W1/W2 的 VS 工程（/W3）安静得多：
    # C4244（double 悄悄转 int）这类警告会被吞掉。这里显式改回 /W3。
    add_compile_options(/W3)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

    # 严格标准模式：和 my-shapes.vcxproj（ConformanceMode=true）保持一致。
    # 不开它，MSVC 会放行 char* p = "abc"; 这种不合标准的写法（实测：退出码 0）。
    add_compile_options(/permissive-)
endif ()

# ------------------------------------------------------------
# 公共函数：给一个目标开 ASan，构建完把 ASan 运行库 DLL 拷到 exe 旁边
#   （MSVC 的 ASan 是动态运行库，exe 旁边没有 dll 会报 0xC0000135）
# ------------------------------------------------------------
function(w3_enable_asan target)
    if (MSVC)
        target_compile_options(${target} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
        target_link_options(${target} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
        get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
                "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
                "$<TARGET_FILE_DIR:${target}>"
            COMMENT "拷贝 ASan 运行库 DLL 到输出目录"
            VERBATIM)
    endif ()
endfunction()

# ------------------------------------------------------------
# 探针：助手写、本人跑、看输出（W2 的老规矩）
#   1 why_inherit  不用继承时，代码长什么样（先看见"重复"）
#   2 minimal      最小的 Shape → Circle（继承语法 + 构造/析构顺序）
#   3 no_virtual   不写 virtual 会怎样（对象切片 + 基类指针调基类版本）
#   4 vdtor_bad    非虚析构 + 派生类 new 了内存（开 ASan，看它怎么报）
#   5 vdtor_good   把析构改成 virtual 之后（开 ASan，看它怎么变干净）
#   6 sizeof_vtable virtual 的"代价"：对象里多出来的那个隐藏指针
#   7 ctor_virtual  在构造 / 析构函数里调用虚函数会发生什么
#   8 upcast        指针层面的多态：基类指针和派生类指针指向同一块内存
#   9 hiding        名字隐藏：派生类同名函数会藏掉基类的所有重载
#  10 abstract      纯虚函数与抽象类 + 通过基类引用调用（多态）
#  11 range_for     range-for 里那个变量到底是怎么来的（拷贝 vs 引用）
#  12 flush_lab      flush 是干什么的（abort 之前不 flush 会丢输出）
#  13 vdtor_size     派生类和基类一样大时，非虚析构还错不错（不靠 ASan 报告）
# ------------------------------------------------------------
add_executable(why_inherit labs/why-inherit.cpp)
add_executable(minimal     labs/minimal.cpp)
add_executable(no_virtual  labs/no-virtual.cpp)
add_executable(vdtor_bad   labs/vdtor-bad.cpp)
add_executable(vdtor_good  labs/vdtor-good.cpp)
add_executable(sizeof_vtable labs/sizeof-vtable.cpp)
add_executable(ctor_virtual  labs/ctor-virtual.cpp)
add_executable(upcast         labs/upcast.cpp)
add_executable(hiding         labs/hiding.cpp)
add_executable(abstract       labs/abstract.cpp)
add_executable(range_for      labs/range-for.cpp)
add_executable(flush_lab      labs/flush-lab.cpp)
add_executable(vdtor_size     labs/vdtor-same-size.cpp)

w3_enable_asan(vdtor_bad)
w3_enable_asan(vdtor_good)

# ------------------------------------------------------------
# 本人的主程序：骨架已给，函数体自己写（W3 周检验的雏形）
# ------------------------------------------------------------
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my/shapes.cpp")
    add_executable(my_shapes my/shapes.cpp)
    w3_enable_asan(my_shapes)
endif ()
